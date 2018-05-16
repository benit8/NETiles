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
	void updateText(sf::Vector2i mouseWindowPos);
	void render(sf::RenderWindow &target);

	void setPosition(sf::Vector2i pos);
	void setPosition(int x, int y);
	void setSize(sf::Vector2i size);
	void setSize(int w, int h);
	void setTexturePos(sf::Vector2i pos);
	void setTexturePos(int x, int y);

	sf::Vector2i getTexturePos();
	sf::Vector2i getGrabStartPosition();
	sf::Mouse::Button getGrabButton();
	sf::IntRect getRegion();

	void startGrab(sf::Vector2i mouseTilePos, sf::Mouse::Button button);
	sf::IntRect endGrab(sf::Vector2i mouseTilePos, sf::Mouse::Button button);
	bool isGrabbing();

	void enableTextureSelect();
	void disableTextureSelect();
	bool isSelectingTexture();

private:
	sf::Vector2f getScaledTexturePos();

private:
	int m_size;
	int m_scale;
	sf::RectangleShape m_area;

	bool m_grab;
	sf::Mouse::Button m_grabButton;
	sf::Vector2i m_grabStartPos;

	bool m_textureSelect;
	sf::Sprite m_texture;

	sf::Text m_tilePosText;
};

}