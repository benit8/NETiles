/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Tiles / Map.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace Tiles {
	class Map;
};

////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Ressources/Manager.hpp"
#include "Tiles/Tile.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

class Map
{
public:
	Map();
	Map(const std::string &mapPath);
	~Map() = default;

	bool loadFromFile(const std::string &mapPath = "");
	bool saveToFile(const std::string &mapPath = "");

	void clear();
	void render(sf::RenderWindow &target, bool displayTileTypes = false);
	void renderRepeated(sf::RenderWindow &target, const sf::Vector2i &area, bool displayTileTypes = false);

	void setOffset(int x, int y);
	void setOffset(const sf::Vector2i &offset);

	void setTile(const Tile &tile);
	void setTile(const sf::Vector2i &pos, const sf::Vector2i &tex);
	void deleteTile(const sf::Vector2i &pos);
	void deleteTile(int x, int y);
	Tile *getTile(const sf::Vector2i &pos);
	Tile *getTile(int x, int y);

	const std::string &getMapPath();
	sf::Vector2i getSize();
	sf::Vector2i getCenter();
	sf::Vector2i getTopLeftPosition();
	sf::Vector2i getBottomRightPosition();

	void setClipboard(bool isClipboard);
	bool isClipboard();

private:
	void sortTiles();
	void reposition();

public:
	static const int TILE_SIZE = 16;

private:
	std::string m_mapPath;
	std::vector<Tile> m_tiles;

	sf::Vector2i m_offset;

	sf::RenderStates m_renderStates;

	bool m_sorted = false;
	bool m_isClipboard = false;
};

}