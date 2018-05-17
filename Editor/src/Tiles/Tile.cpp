/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Tiles / Tile.cpp
*/

#include "Tiles/Tile.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

////////////////////////////////////////////////////////////////////////////////

Tile::Tile()
: pos(0, 0)
, tex(0, 0)
, tele(false)
, telePos(0, 0)
{
}

Tile::Tile(const sf::Vector2i &pos_)
: pos(pos_)
, tex(0, 0)
, tele(false)
, telePos(0, 0)
{
}

Tile::Tile(const sf::Vector2i &pos_, const sf::Vector2i &tex_)
: pos(pos_)
, tex(tex_)
, tele(false)
, telePos(0, 0)
{
}

Tile::Tile(const sf::Vector2i &pos_, const sf::Vector2i &tex_, const sf::Vector2i &telePos_)
: pos(pos_)
, tex(tex_)
, tele(true)
, telePos(telePos_)
{
}

////////////////////////////////////////////////////////////////////////////////

sf::Color Tile::getColorType()
{
	if (tele)
		return sf::Color::Yellow;
	else if (walkable)
		return sf::Color::Green;
	else
		return sf::Color::Red;
}

////////////////////////////////////////////////////////////////////////////////

}