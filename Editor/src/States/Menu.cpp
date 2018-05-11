/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** States / Menu.cpp
*/

#include "States/Menu.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace States
{

////////////////////////////////////////////////////////////////////////////////

Menu::Menu()
: State()
{
}

Menu::~Menu()
{
}

////////////////////////////////////////////////////////////////////////////////

void Menu::handleEvent(sf::Event &e)
{
	switch (e.type) {
		case sf::Event::MouseButtonPressed:
			// if (e.mouseButton.button == sf::Mouse::Left)
			// 	m_menu.handleMouseClick(sf::Vector2<int>(e.mouseButton.x, e.mouseButton.y));
		break;
		case sf::Event::MouseMoved:
			// m_menu.handleMousePos(sf::Vector2<int>(e.mouseMove.x, e.mouseMove.y));
		break;
		default:
		break;
	}
}

void Menu::update()
{
}

void Menu::render(sf::RenderWindow &target)
{
}

////////////////////////////////////////////////////////////////////////////////

// void Menu::onMousePressed(sf::Keyboard::Key key)
// {
// }

////////////////////////////////////////////////////////////////////////////////

}