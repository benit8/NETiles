/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Widget.cpp
*/

#include "Widget.hpp"
#include "../Window.hpp"
#include "GUI.hpp"
#include "Env.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Widget::Widget()
: m_parent(nullptr)
, m_state(Normal)
, m_mode(Clickable)
{
	m_eventDispatcher.onMouseMove(BIND2(Widget::callback_mouseMove));
	m_eventDispatcher.onMouseDown(BIND1(Widget::callback_mouseDown), sf::Mouse::Left);
	m_eventDispatcher.onMouseUp(BIND1(Widget::callback_mouseUp), sf::Mouse::Left);
	m_eventDispatcher.onText(BIND1(Widget::callback_text));

	onFocusOut.connect(this, &Widget::unfocus);
}

Widget::~Widget()
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->setParent(nullptr);
	m_children.clear();
}

////////////////////////////////////////////////////////////////////////////////

void Widget::handleEvent(sf::Event &e, bool isRoot)
{
	if (isRoot && Env::modal != nullptr) {
		Env::modal->handleEvent(e);

		if (e.type == sf::Event::Closed || e.type == sf::Event::Resized) {
			for (auto it = m_children.begin(); it != m_children.end(); ++it)
				(*it)->handleEvent(e);
		}

		return;
	}
	else {
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
			(*it)->handleEvent(e);
	}

	if (!isRoot) {
		m_eventDispatcher.dispatchEvent(e);
	}
	else {
		Env::foundTarget = false;
	}
}

void Widget::render(sf::RenderTarget &rt, bool isRoot)
{
	if (!isRoot) {
		sf::Vector2f offset = getParentOffset();
		m_zone.move(offset);
		draw(rt);
		m_zone.move(-offset);
	}

	for (auto it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->render(rt);

	if (isRoot && Env::modal) {
		Env::modal->render(rt);
	}
}

void Widget::focus()
{
	if (isTargeted())
		return;

	if (Env::target)
		Env::target->onFocusOut.emit();
	Env::target = this;
	onFocusIn.emit();
}

void Widget::unfocus()
{
	if (isClicked()) {
		onRelease.emit({0, 0});
		m_state &= ~State::Clicked;
	}
}

////////////////////////////////////////////////////////////////////////////////

bool Widget::isMouseHover(sf::Vector2i mouse)
{
	return isMouseHover(sf::Vector2f(mouse.x, mouse.y));
}

bool Widget::isMouseHover(sf::Vector2f mouse)
{
	sf::FloatRect rect(getPosition(), getSize());
	sf::Vector2f parentOffset = getParentOffset();

	rect.left += parentOffset.x;
	rect.top += parentOffset.y;
	return rect.contains(mouse);
}

sf::Vector2f Widget::getParentOffset()
{
	sf::Vector2f offset;

	if (m_parent) {
		offset += m_parent->getParentOffset() + m_parent->getPosition();
	}

	return offset;
}

bool Widget::isFromModal()
{
	if (Env::modal == this)
		return true;

	if (m_parent)
		return m_parent->isFromModal();

	return false;
}

////////////////////////////////////////////////////////////////////////////////

void Widget::callback_mouseMove(sf::Vector2i pos, sf::Vector2i offset)
{
	if (!isHoverable())
		return;

	if (isDragged()) {
		move(offset.x, offset.y);
		onDrag.emit(pos, offset);
		return;
	}

	bool in = isMouseHover(pos);
	if (in && isClicked() && isDraggable()) {
		onDragBegin.emit(pos);
		m_state |= State::Dragged;
	}
	else if (!in && isHovered()) {
		onHoverOut.emit(pos);
		m_state &= ~State::Hovered;
	}
	else if (in && !isHovered()) {
		onHoverIn.emit(pos);
		m_state |= State::Hovered;
	}
	else if (!in && !isHovered() && isClicked()) {
		onRelease.emit(pos);
		m_state &= ~State::Clicked;
	}
}

void Widget::callback_mouseDown(sf::Vector2i pos)
{
	if (!isClickable())
		return;

	if (isHovered()) {
		onClick.emit(pos);
		m_state |= State::Clicked;

		if (!Env::foundTarget) {
			focus();
			Env::foundTarget = true;
		}
	}
}

void Widget::callback_mouseUp(sf::Vector2i pos)
{
	if (!isClickable())
		return;

	if (isClicked()) {
		if (isDragged()) {
			onDragEnd.emit(pos);
			m_state &= ~State::Dragged;
		}
		onRelease.emit(pos);
		m_state &= ~State::Clicked;
	}
}

void Widget::callback_text(unsigned unicode)
{
	if (Env::target == this)
		onTextInput.emit(unicode);
}

////////////////////////////////////////////////////////////////////////////////

const Widget *Widget::getParent() const {
	return m_parent;
}

const std::list<Widget *> &Widget::getChildren() const {
	return m_children;
}

void Widget::setParent(Widget *parent) {
	m_parent = parent;
}

void Widget::addChild(Widget *child)
{
	m_children.push_back(child);
	child->setParent(this);
}

void Widget::removeChild(Widget *child)
{
	auto it = std::find(m_children.begin(), m_children.end(), child);
	if (it == m_children.end())
		return;

	child->setParent(nullptr);
	m_children.remove(child);
}

////////////////////////////////////////////////////////////////////////////////

bool Widget::isTargeted() const {
	return this == Env::target;
}

bool Widget::isHovered() const {
	return m_state & State::Hovered;
}

bool Widget::isClicked() const {
	return m_state & State::Clicked;
}

bool Widget::isDragged() const {
	return m_state & State::Dragged;
}

bool Widget::isHoverable() const {
	return m_mode >= Mode::Hoverable;
}

bool Widget::isClickable() const {
	return m_mode >= Mode::Clickable;
}

bool Widget::isDraggable() const {
	return m_mode >= Mode::Draggable;
}

void Widget::setMode(Mode mode) {
	m_mode = mode;
}

////////////////////////////////////////////////////////////////////////////////

float Widget::left() const {
	return getPosition().x;
}

float Widget::top() const {
	return getPosition().y;
}

void Widget::left(float left) {
	return setPosition(left, top());
}

void Widget::top(float top) {
	return setPosition(left(), top);
}

void Widget::move(float offsetX, float offsetY) {
	move(sf::Vector2f(offsetX, offsetY));
}

void Widget::move(const sf::Vector2f &offset) {
	setPosition(getPosition() + offset);
}

void Widget::setPosition(float offsetX, float offsetY) {
	setPosition(sf::Vector2f(offsetX, offsetY));
}

void Widget::setPosition(const sf::Vector2f &position) {
	m_zone.setPosition(position);
	update();
}

const sf::Vector2f &Widget::getPosition() const {
	return m_zone.getPosition();
}


float Widget::width() const {
	return getSize().x;
}

float Widget::height() const {
	return getSize().y;
}

void Widget::width(float width) {
	setSize(width, height());
}

void Widget::height(float height) {
	setSize(width(), height);
}

void Widget::setSize(float width, float height) {
	setSize(sf::Vector2f(width, height));
}

void Widget::setSize(const sf::Vector2f &size) {
	m_zone.setSize(size);
	update();
}

const sf::Vector2f &Widget::getSize() const {
	return m_zone.getSize();
}

////////////////////////////////////////////////////////////////////////////////

}