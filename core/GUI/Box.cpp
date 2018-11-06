/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Box.cpp
*/

#include "Box.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Box::Box()
{
	m_rect.setFillColor(sf::Color(255, 255, 255, 100));

	// onHoverIn.connect(this, &Box::onHoverIn_callback);
	// onHoverOut.connect(this, &Box::onHoverOut_callback);
}


void Box::draw(sf::RenderTarget &rt)
{
	m_rect.setSize(getSize());
	m_rect.setPosition(getPosition());

	rt.draw(m_rect);
}

void Box::onHoverIn_callback(sf::Vector2i pos)
{
	m_rect.setFillColor(sf::Color::White);
}

void Box::onHoverOut_callback(sf::Vector2i pos)
{
	m_rect.setFillColor(sf::Color(255, 255, 255, 100));
}

////////////////////////////////////////////////////////////////////////////////

}