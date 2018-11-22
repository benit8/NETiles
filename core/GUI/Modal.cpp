/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Modal.cpp
*/

#include "Modal.hpp"
#include "Env.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Modal::Modal()
: m_previousModal(nullptr)
, m_opened(false)
{
	m_eventDispatcher.onResize(BIND1(Modal::updatePositions));
	m_eventDispatcher.onKeyDown(BIND(Modal::close), sf::Keyboard::Escape);

	m_back.setBackgroundColor(sf::Color(0, 0, 0, 150));
	m_zone.setFillColor(sf::Color::Black);
	m_zone.setOutlineThickness(1);
}

Modal::~Modal()
{
	close();
}

////////////////////////////////////////////////////////////////////////////////

void Modal::draw(sf::RenderTarget &rt)
{
	m_back.draw(rt);
	rt.draw(m_zone);
}

void Modal::updatePositions(sf::Vector2u size)
{
	m_back.setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
	m_zone.setPosition((size.x - width()) / 2.f, (size.y - height()) / 2.f);
}

void Modal::open()
{
	m_opened = true;
	m_previousModal = Env::modal;
	Env::modal = this;
	focus();
}

void Modal::close()
{
	if (!isOpen())
		return;

	m_opened = false;
	Env::modal = m_previousModal;
}

bool Modal::isOpen()
{
	return m_opened;
}

////////////////////////////////////////////////////////////////////////////////

}