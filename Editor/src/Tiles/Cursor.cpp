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
, m_scale(size / Map::TILESET_TILE_SIZE)
, m_area(sf::Vector2f(m_size, m_size))
, m_grab(false)
, m_textureSelect(false)
{
	reset();
	setTexturePos(0, 0);

	m_tilePosText.setFont(Ressource::Manager::getFont("Consolas"));
	m_tilePosText.setFillColor(sf::Color::White);
	m_tilePosText.setCharacterSize(12);

	m_texture.setTexture(Ressource::Manager::getTexture("tileset0"), true);
	m_texture.scale(m_scale, m_scale);
}

Cursor::~Cursor()
{
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::reset()
{
	m_area.setTexture(&Ressource::Manager::getTexture("tileset0"));
	m_area.setFillColor(sf::Color(255, 255, 255, 128));
	m_area.setOutlineColor(sf::Color::White);
	m_area.setOutlineThickness(1);

	setSize(m_size, m_size);
}

void Cursor::update(sf::Vector2i mouseTilePos)
{
	if (m_grab && m_grabButton != sf::Mouse::Middle) {
		setPosition(
			std::min(mouseTilePos.x, m_grabStartPos.x),
			std::min(mouseTilePos.y, m_grabStartPos.y)
		);
		setSize(
			abs(mouseTilePos.x - m_grabStartPos.x) + m_size,
			abs(mouseTilePos.y - m_grabStartPos.y) + m_size
		);
	}
	else {
		setPosition(mouseTilePos);
	}

	updateText(mouseTilePos);
}

void Cursor::updateText(sf::Vector2i mouseTilePos)
{
	std::ostringstream oss;
	oss << "[" << (mouseTilePos.x / m_size) << "," << (mouseTilePos.y / m_size) << "]";

	if (m_grab)
		oss << "\n[" << getRegion().width << "," << getRegion().height << "]";

	m_tilePosText.setPosition(mouseTilePos.x + m_size + 8, mouseTilePos.y);
	m_tilePosText.setString(oss.str());
}

void Cursor::render(sf::RenderWindow &target)
{
	if (m_textureSelect)
		target.draw(m_texture);
	else
		target.draw(m_tilePosText);

	target.draw(m_area);
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

void Cursor::setTexturePos(sf::Vector2i texturePos)
{
	texturePos *= Map::TILESET_TILE_SIZE;

	m_area.setTextureRect(sf::IntRect(
		texturePos.x, texturePos.y,
		Map::TILESET_TILE_SIZE, Map::TILESET_TILE_SIZE
	));
}

void Cursor::setTexturePos(int x, int y)
{
	setTexturePos(sf::Vector2i(x, y));
}

sf::Vector2i Cursor::getTexturePos()
{
	return sf::Vector2i(
		m_area.getTextureRect().left,
		m_area.getTextureRect().top
	) / Map::TILESET_TILE_SIZE;
}

sf::Vector2f Cursor::getScaledTexturePos()
{
	return sf::Vector2f(
		m_area.getTextureRect().left,
		m_area.getTextureRect().top
	) * float(m_scale);
}

sf::Vector2i Cursor::getGrabStartPosition()
{
	return m_grabStartPos;
}

sf::Mouse::Button Cursor::getGrabButton()
{
	return m_grabButton;
}

sf::IntRect Cursor::getRegion()
{
	return sf::IntRect(
		m_area.getPosition().x / m_size,
		m_area.getPosition().y / m_size,
		m_area.getSize().x / m_size,
		m_area.getSize().y / m_size
	);
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::startGrab(sf::Vector2i mouseTilePos, sf::Mouse::Button button)
{
	if (m_textureSelect || m_grab)
		return;

	m_grab = true;
	m_grabButton = button;
	m_grabStartPos = mouseTilePos;

	if (button == sf::Mouse::Right) {
		m_area.setTexture(NULL);
		m_area.setFillColor(sf::Color(255, 0, 0, 50));
	}
}

sf::IntRect Cursor::endGrab(sf::Vector2i mouseTilePos, sf::Mouse::Button button)
{
	if (!m_grab || m_grabButton != button)
		return sf::IntRect();

	m_grab = false;

	sf::IntRect region = getRegion();
	reset();
	update(mouseTilePos);

	return region;
}

bool Cursor::isGrabbing()
{
	return m_grab;
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::enableTextureSelect()
{
	if (m_grab || m_textureSelect)
		return;

	m_textureSelect = true;
	m_area.setFillColor(sf::Color(255, 255, 255, 0));
	m_area.setOutlineColor(sf::Color::Red);
	m_texture.setPosition(m_area.getPosition() - getScaledTexturePos());
}

void Cursor::disableTextureSelect()
{
	if (!m_textureSelect)
		return;

	m_textureSelect = false;
	m_area.setFillColor(sf::Color(255, 255, 255, 128));
	m_area.setOutlineColor(sf::Color::White);

	setTexturePos(sf::Vector2i(m_area.getPosition() - m_texture.getPosition()) / m_size);
}

bool Cursor::isSelectingTexture()
{
	return m_textureSelect;
}

////////////////////////////////////////////////////////////////////////////////

}