/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Object.cpp
*/

#include "Object.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Object::Object()
: m_parent(nullptr)
, m_state(Normal)
, m_mode(Clickable)
, m_position(0, 0)
, m_size(0, 0)
{
	m_eventDispatcher.onMouseMove(BIND2(Object::callback_mouseMove));
	m_eventDispatcher.onMouseDown(BIND2(Object::callback_mouseDown), sf::Mouse::Left);
	m_eventDispatcher.onMouseUp(BIND2(Object::callback_mouseUp), sf::Mouse::Left);
	m_eventDispatcher.onText(BIND1(Object::callback_text));
}

////////////////////////////////////////////////////////////////////////////////

void Object::handleEvent(sf::Event &e)
{
	for (std::vector<Object *>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->handleEvent(e);
	m_eventDispatcher.dispatchEvent(e);
}

void Object::render(sf::RenderTarget &rt)
{
	draw(rt);
	for (std::vector<Object *>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->render(rt);
}


bool Object::doesMouseHover(sf::Vector2i pos)
{
	sf::IntRect bounds(m_position, sf::Vector2i(m_size));
	return bounds.contains(pos);
}

////////////////////////////////////////////////////////////////////////////////

void Object::callback_mouseMove(sf::Vector2i pos, sf::Vector2i offset)
{
	if (m_mode < Mode::Hoverable)
		return;

	if (m_state == State::Dragged) {
		move(offset);
		onDrag(pos, offset);
		return;
	}

	bool in = doesMouseHover(pos);

	if (in && m_state == State::Clicked && m_mode >= Mode::Draggable) {
		m_state = State::Dragged;
		onDragBegin(pos);
	}
	else if (!in && m_state > State::Normal) {
		m_state = State::Normal;
		onHoverOut(pos);
	}
	else if (in && m_state == State::Normal) {
		m_state = State::Hovered;
		onHoverIn(pos);
	}
}

void Object::callback_mouseDown(sf::Mouse::Button btn, sf::Vector2i pos)
{
	if (m_mode < Mode::Clickable)
		return;

	if (m_state == State::Hovered) {
		m_state = State::Clicked;
		onClick(btn, pos);
	}
}

void Object::callback_mouseUp(sf::Mouse::Button btn, sf::Vector2i pos)
{
	if (m_mode < Mode::Clickable)
		return;

	if (m_state >= State::Clicked) {
		if (m_state == State::Dragged)
			onDragEnd(pos);
		onRelease(btn, pos);
		m_state = doesMouseHover(pos) ? State::Hovered : State::Normal;
	}
}

void Object::callback_text(unsigned unicode)
{
	if (this != Env::target)
		return;

	// Handle character
}

////////////////////////////////////////////////////////////////////////////////

const Object *Object::getParent() const {
	return m_parent;
}

const std::vector<Object *> &Object::getChildren() const {
	return m_children;
}

void Object::setParent(Object *parent) {
	m_parent = parent;
}

void Object::addChild(Object *child) {
	m_children.push_back(child);
}


bool Object::isHovered() const
{
	return m_state >= State::Hovered;
}

bool Object::isClicked() const
{
	return m_state >= State::Clicked;
}

bool Object::isDragged() const
{
	return m_state >= State::Dragged;
}

bool Object::isHoverable() const
{
	return m_mode >= Mode::Hoverable;
}

bool Object::isClickable() const
{
	return m_mode >= Mode::Clickable;
}

bool Object::isDraggable() const
{
	return m_mode >= Mode::Draggable;
}

void Object::setMode(Mode mode)
{
	m_mode = mode;
}



sf::Vector2i Object::getPosition() const {
	return m_position;
}

void Object::setPosition(int offsetX, int offsetY) {
	setPosition(sf::Vector2i(offsetX, offsetY));
}

void Object::setPosition(const sf::Vector2i &position) {
	move(position - m_position);
}

void Object::move(int offsetX, int offsetY) {
	move(sf::Vector2i(offsetX, offsetY));
}

void Object::move(const sf::Vector2i &offset) {
	m_position += offset;
	for (std::vector<Object *>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->move(offset);
}

sf::Vector2u Object::getSize() const {
	return m_size;
}

void Object::setSize(unsigned width, unsigned height) {
	setSize(sf::Vector2u(width, height));
}

void Object::setSize(const sf::Vector2u &size) {
	m_size = size;
}

////////////////////////////////////////////////////////////////////////////////

}