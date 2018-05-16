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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

class Tile
{
public:
	Tile() = default;
	Tile(const sf::Vector2i &);
	Tile(const sf::Vector2i &, const sf::Vector2i &);
	Tile(const sf::Vector2i &, const sf::Vector2i &, const sf::Vector2i &);

	sf::Color getColorType();

	sf::Vector2i pos;
	sf::Vector2i tex;
	bool walkable = true;
	bool tele = false;
	sf::Vector2i telePos;
};

}