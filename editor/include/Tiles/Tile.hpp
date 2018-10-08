/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Tiles / Tile.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace Tiles {
	class Tile;
}

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

class Tile
{
public:
	Tile();
	Tile(const sf::Vector2i &pos);
	Tile(const sf::Vector2i &pos, const sf::Vector2i &tex);
	Tile(const sf::Vector2i &pos, const sf::Vector2i &tex, const sf::Vector2i &telePos);

public:
	sf::Color getColorType();

public:
	sf::Vector2i pos;
	sf::Vector2i tex;
	bool walkable;
	bool tele;
	sf::Vector2i telePos;
};

typedef std::vector<Tile> TileArray;

}