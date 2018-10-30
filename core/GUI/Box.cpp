/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Box.cpp
*/

#include <stdio.h>
#include "Box.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Box::Box()
{
	m_mode = Mode::Draggable;

	m_position = sf::Vector2i(50, 50);
	m_size = sf::Vector2u(200, 100);

	m_rect.setSize(sf::Vector2f(m_size.x, m_size.y));
	m_rect.setPosition(sf::Vector2f(m_position));
	m_rect.setFillColor(sf::Color(255, 0, 0, 100));
}


void Box::draw(sf::RenderTarget &rt)
{
	m_rect.setSize(sf::Vector2f(m_size.x, m_size.y));
	m_rect.setPosition(sf::Vector2f(m_position));
	rt.draw(m_rect);
}


void Box::onHoverIn()
{
	std::cout << "onHoverIn" << std::endl;
	m_rect.setFillColor(sf::Color(0, 255, 0, 100));
}

void Box::onHoverOut()
{
	std::cout << "onHoverOut" << std::endl;
	m_rect.setFillColor(sf::Color(255, 0, 0, 100));
}

void Box::onClick()
{
	std::cout << "onClick" << std::endl;
	m_rect.setFillColor(sf::Color(0, 255, 0, 255));
}

void Box::onRelease()
{
	std::cout << "onRelease" << std::endl;
	m_rect.setFillColor(sf::Color(0, 255, 0, 100));
}

void Box::onDragBegin()
{
	std::cout << "onDragBegin" << std::endl;
	m_rect.setFillColor(sf::Color(127, 255, 0, 175));
}

void Box::onDragEnd()
{
	std::cout << "onDragEnd" << std::endl;
	m_rect.setFillColor(sf::Color(0, 255, 0, 100));
}


////////////////////////////////////////////////////////////////////////////////

}