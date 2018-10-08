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
#include <math.h>

#include <SFML/Graphics.hpp>

#include "Display.hpp"
#include "Ressources/Manager.hpp"
#include "Tiles/Map.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

class Cursor
{
public:
	enum GrabType
	{
		None = 0,
		Move,
		Fill,
		Delete,
		Copy
	};

public:
	Cursor();
	~Cursor();

	void update(const sf::Vector2i &mouseWindowPos);
	void render(sf::RenderWindow &target);

	void setTexturePos(const sf::Vector2i &pos);
	void setTexturePos(int x, int y);

	sf::Vector2i getTexturePos();
	sf::Vector2i getGrabStartPosition();
	sf::IntRect getSelection();
	GrabType getGrabType();

	void startGrab(const sf::Vector2i &mouseTilePos, GrabType type);
	void endGrab(const sf::Vector2i &mouseTilePos);
	bool isGrabbing();

	void enableTextureSelect();
	void disableTextureSelect();
	bool isSelectingTexture();

	Map &getClipboard();
	void showClipboard(bool show);
	bool isClipboardShown();
	bool hasSelection();
	void resetSelection();
	void copySelection(Map &from);

	std::string getDebugText();

private:
	sf::Vector2f getScaledTexturePos();

private:
	sf::RectangleShape m_cursor;
	sf::RectangleShape m_selection;
	Map m_clipboard;
	bool m_showClipboard;

	bool m_grab;
	GrabType m_grabType;
	sf::Vector2i m_grabStartPos;

	bool m_textureSelect;
	sf::Sprite m_texture;
};

}