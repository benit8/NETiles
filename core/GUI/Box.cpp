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
}


void Box::setBackgroundColor(const sf::Color &color)
{
	m_rect.setFillColor(color);
}

void Box::setBorderColor(const sf::Color &color)
{
	m_rect.setOutlineColor(color);
}

void Box::setBorderSize(float size)
{
	m_rect.setOutlineThickness(size);
}

////////////////////////////////////////////////////////////////////////////////

void Box::draw(sf::RenderTarget &rt)
{
	m_rect.setSize(getSize());
	m_rect.setPosition(getPosition());

	rt.draw(m_rect);
}

////////////////////////////////////////////////////////////////////////////////

}