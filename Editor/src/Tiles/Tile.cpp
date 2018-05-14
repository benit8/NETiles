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

Tile::Tile(const sf::Vector2i &pos_)
: pos(pos_)
{
}

Tile::Tile(const sf::Vector2i &pos_, const sf::Vector2u &tex_)
: pos(pos_)
, tex(tex_)
{
}

Tile::Tile(const sf::Vector2i &pos_, const sf::Vector2u &tex_, const sf::Vector2i &telePos_)
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
	// return sf::Color(128, 128, 128);
}

////////////////////////////////////////////////////////////////////////////////

}