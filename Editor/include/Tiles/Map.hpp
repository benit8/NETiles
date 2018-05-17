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

	void render(sf::RenderWindow &target, bool displayTileTypes);

	void setTile(const sf::Vector2i &pos, const sf::Vector2i &tex);
	void removeTile(const sf::Vector2i &pos);
	Tile *getTile(const sf::Vector2i &pos);
	Tile *getTile(int x, int y);
	sf::Vector2i getCenter();
	const std::string &getMapPath();

private:
	void sortTiles();
	void reposition();

public:
	static const int TILESET_TILE_SIZE = 16;
	static const int TILEMAP_TILE_SIZE = 32;

private:
	std::string m_mapPath;
	std::vector<Tile> m_tiles;

	sf::RenderStates m_renderStates;

	bool m_sorted = false;
};

}