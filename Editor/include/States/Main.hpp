/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** States / Main.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace States {
	class Main;
}

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "States/State.hpp"
#include "Ressources/Manager.hpp"
#include "Tiles/Map.hpp"
#include "Tiles/Tile.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace States
{

class Main : public State
{
public:
	Main(const std::string &mapPath, sf::RenderWindow &window);
	~Main() override;

	void handleEvent(sf::Event &e) override;
	void update() override;
	void render(sf::RenderWindow &target) override;

private:
	void onKeydown(sf::Keyboard::Key key);
	void onMouseMoved(sf::Vector2i mousePos);

	void grabStart(sf::Vector2i mousePos, sf::Mouse::Button button);
	void grabEnd();
	void grabAction();

private:
	Tiles::Map m_tileMap;
	bool m_displayTileTypes;

	sf::RenderWindow &m_window;
	sf::View m_view;

	sf::RectangleShape m_mouseTile;

	bool m_grab;
	sf::Vector2i m_grabStartPos;
	sf::Mouse::Button m_grabButton;
};

}