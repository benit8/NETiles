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

	void setTile(const sf::Vector2i &pos, const sf::Vector2u &tex);
	void removeTile(const sf::Vector2i &pos);
	Tile *getTile(const sf::Vector2i &pos);
	Tile *getTile(int x, int y);
	sf::Vector2f getCenterPoint();
	const std::string &getMapPath();

public:
	static const int TILESET_TILESIZE = 16;

private:
	std::string m_mapPath;
	std::vector<Tile> m_tiles;

	sf::RenderStates m_renderStates;
};

}