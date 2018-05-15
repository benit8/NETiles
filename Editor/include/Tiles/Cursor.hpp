/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Tiles / Cursor.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace Tiles {
	class Cursor;
}

////////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include <SFML/Graphics.hpp>

#include "Ressources/Manager.hpp"
#include "Tiles/Map.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

class Cursor
{
public:
	Cursor(int size);
	~Cursor();

	void reset();
	void update(sf::Vector2i mouseWindowPos);
	void render(sf::RenderWindow &target);

	void setPosition(sf::Vector2i pos);
	void setPosition(int x, int y);
	void setSize(sf::Vector2i size);
	void setSize(int w, int h);

	sf::Vector2u getTilePos();
	sf::Vector2i getGrabStartPosition();
	sf::Mouse::Button getGrabButton();

	void startGrab(sf::Vector2i mouseWindowPos, sf::Mouse::Button button);
	sf::IntRect endGrab();
	bool isGrabbing();

private:
	int m_size;
	sf::RectangleShape m_area;

	bool m_grab;
	sf::Mouse::Button m_grabButton;
	sf::Vector2i m_grabStartPos;

	sf::Text m_tilePosText;
};

}