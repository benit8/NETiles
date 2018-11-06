/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Widget.cpp
*/

#include "Widget.hpp"

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
	m_eventDispatcher.onMouseDown(BIND2(Widget::callback_mouseDown), sf::Mouse::Left);
	m_eventDispatcher.onMouseUp(BIND2(Widget::callback_mouseUp), sf::Mouse::Left);
	// m_eventDispatcher.onText(BIND1(Widget::callback_text));
}

////////////////////////////////////////////////////////////////////////////////

void Widget::handleEvent(sf::Event &e)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->handleEvent(e);

	if (this != GUI::getRoot())
		m_eventDispatcher.dispatchEvent(e);
}

void Widget::render(sf::RenderTarget &rt)
{
	if (this != GUI::getRoot())
		draw(rt);

	for (auto it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->render(rt);
}


bool Widget::isMouseHover(sf::Vector2i mouse) {
	return isMouseHover(sf::Vector2f(mouse.x, mouse.y));
}

bool Widget::isMouseHover(sf::Vector2f mouse) {
	return m_zone.contains(mouse);
}

////////////////////////////////////////////////////////////////////////////////

void Widget::callback_mouseMove(sf::Vector2i pos, sf::Vector2i offset)
{
	if (m_mode < Mode::Hoverable)
		return;

	if (m_state == State::Dragged) {
		move(offset.x, offset.y);
		onDrag.emit(pos, offset);
		return;
	}

	bool in = isMouseHover(pos);
	if (in && m_state == State::Clicked && m_mode >= Mode::Draggable) {
		m_state = State::Dragged;
		onDragBegin.emit(pos);
	}
	else if (!in && m_state > State::Normal) {
		m_state = State::Normal;
		onHoverOut.emit(pos);
	}
	else if (in && m_state == State::Normal) {
		m_state = State::Hovered;
		onHoverIn.emit(pos);
	}
}

void Widget::callback_mouseDown(sf::Mouse::Button btn, sf::Vector2i pos)
{
	if (m_mode < Mode::Clickable)
		return;

	if (m_state == State::Hovered) {
		m_state = State::Clicked;
		onClick.emit(btn, pos);
	}
}

void Widget::callback_mouseUp(sf::Mouse::Button btn, sf::Vector2i pos)
{
	if (m_mode < Mode::Clickable)
		return;

	if (m_state >= State::Clicked) {
		if (m_state == State::Dragged)
			onDragEnd.emit(pos);
		onRelease.emit(btn, pos);
		m_state = isMouseHover(pos) ? State::Hovered : State::Normal;
	}
}

void Widget::callback_text(unsigned unicode)
{
	if (this != Env::target)
		return;

	// Handle character
}

////////////////////////////////////////////////////////////////////////////////

const Widget *Widget::getParent() const {
	return m_parent;
}

const std::vector<Widget *> &Widget::getChildren() const {
	return m_children;
}

void Widget::setParent(Widget *parent) {
	m_parent = parent;
}

void Widget::addChild(Widget *child) {
	m_children.push_back(child);
	child->setParent(this);
}


bool Widget::isHovered() const {
	return m_state >= State::Hovered;
}

bool Widget::isClicked() const {
	return m_state >= State::Clicked;
}

bool Widget::isDragged() const {
	return m_state >= State::Dragged;
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


sf::FloatRect Widget::getZone() const {
	return m_zone;
}

void Widget::setZone(const sf::FloatRect &zone) {
	setSize(zone.width, zone.height);
	setPosition(zone.left, zone.top);
}


sf::Vector2f Widget::getPosition() const {
	return sf::Vector2f(m_zone.left, m_zone.top);
}

void Widget::setPosition(float offsetX, float offsetY) {
	setPosition(sf::Vector2f(offsetX, offsetY));
}

void Widget::setPosition(const sf::Vector2f &position) {
	move(position - getPosition());
}

void Widget::move(float offsetX, float offsetY) {
	move(sf::Vector2f(offsetX, offsetY));
}

void Widget::move(const sf::Vector2f &offset) {
	m_zone.left += offset.x;
	m_zone.top += offset.y;
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->move(offset);
}


sf::Vector2f Widget::getSize() const {
	return sf::Vector2f(m_zone.width, m_zone.height);
}

void Widget::setSize(float width, float height) {
	setSize(sf::Vector2f(width, height));
}

void Widget::setSize(const sf::Vector2f &size) {
	m_zone.width = size.x;
	m_zone.height = size.y;
}

void Widget::setWidth(float width) {
	m_zone.width = width;
}

void Widget::setHeight(float height) {
	m_zone.height = height;
}

////////////////////////////////////////////////////////////////////////////////

}