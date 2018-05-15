/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Tiles / Cursor.cpp
*/

#include "Tiles/Cursor.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

////////////////////////////////////////////////////////////////////////////////

Cursor::Cursor(int size)
: m_size(size)
, m_area(sf::Vector2f(m_size, m_size))
, m_grab(false)
{
	// m_area.setTexture(&Ressource::Manager::getTexture("tileset0"));
	reset();

	m_tilePosText.setFont(Ressource::Manager::getFont("Consolas"));
	m_tilePosText.setCharacterSize(12);
}

Cursor::~Cursor()
{
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::reset()
{
	// m_area.setTextureRect(sf::IntRect(0, 0, Map::TILESET_TILE_SIZE, Map::TILESET_TILE_SIZE));
	// m_area.setPosition(sf::Vector2f(mouseTilePos));
	m_area.setSize(sf::Vector2f(m_size, m_size));
	m_area.setFillColor(sf::Color(255, 255, 255, 0));
	m_area.setOutlineColor(sf::Color::White);
	m_area.setOutlineThickness(1);
}

void Cursor::update(sf::Vector2i mouseTilePos)
{
	std::ostringstream oss;
	oss << "[" << mouseTilePos.x / Map::TILEMAP_TILE_SIZE << "," << mouseTilePos.y / Map::TILEMAP_TILE_SIZE << "]";

	m_tilePosText.setPosition(mouseTilePos.x + Map::TILEMAP_TILE_SIZE + 8, mouseTilePos.y);
	m_tilePosText.setString(oss.str());
}

void Cursor::render(sf::RenderWindow &target)
{
	target.draw(m_area);
	target.draw(m_tilePosText);
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::setPosition(sf::Vector2i pos)
{
	m_area.setPosition(sf::Vector2f(pos));
}

void Cursor::setPosition(int x, int y)
{
	setPosition(sf::Vector2i(x, y));
}

void Cursor::setSize(sf::Vector2i size)
{
	m_area.setSize(sf::Vector2f(size));
}

void Cursor::setSize(int w, int h)
{
	setSize(sf::Vector2i(w, h));
}


sf::Vector2u Cursor::getTilePos()
{
	// return sf::Vector2u(m_area.getTextureRect().left, m_area.getTextureRect().top);
	return sf::Vector2u(0, 0);
}

sf::Vector2i Cursor::getGrabStartPosition()
{
	return m_grabStartPos;
}

sf::Mouse::Button Cursor::getGrabButton()
{
	return m_grabButton;
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::startGrab(sf::Vector2i mouseTilePos, sf::Mouse::Button button)
{
	m_grab = true;
	m_grabButton = button;
	m_grabStartPos = mouseTilePos;
}

sf::IntRect Cursor::endGrab()
{
	m_grab = false;

	return sf::IntRect(
		m_area.getPosition().x / Map::TILEMAP_TILE_SIZE,
		m_area.getPosition().y / Map::TILEMAP_TILE_SIZE,
		m_area.getSize().x / Map::TILEMAP_TILE_SIZE,
		m_area.getSize().y / Map::TILEMAP_TILE_SIZE
	);
}

bool Cursor::isGrabbing()
{
	return m_grab;
}

////////////////////////////////////////////////////////////////////////////////

}