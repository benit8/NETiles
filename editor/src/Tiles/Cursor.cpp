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

Cursor::Cursor()
: m_cursor(sf::Vector2f(1, 1))
, m_selection(sf::Vector2f(0, 0))
, m_showClipboard(true)
, m_grab(false)
, m_textureSelect(false)
{
	m_cursor.setFillColor(sf::Color::Transparent);
	m_cursor.setOutlineColor(sf::Color::White);
	m_cursor.setOutlineThickness(1 / float(Map::TILE_SIZE));

	m_selection.setFillColor(sf::Color::Transparent);
	m_selection.setOutlineColor(sf::Color::White);
	m_selection.setOutlineThickness(1 / float(Map::TILE_SIZE));

	m_clipboard.setClipboard(true);
	m_clipboard.setTile(sf::Vector2i(0, 0), sf::Vector2i(49, 2));
	m_clipboard.setTile(sf::Vector2i(0, 1), sf::Vector2i(49, 3));

	m_tilePosText.setFont(Ressource::Manager::getFont("Consolas"));
	m_tilePosText.setCharacterSize(24);
	m_tilePosText.setPosition(8, 0);

	m_texture.setTexture(Ressource::Manager::getTexture("tileset0"), true);
	m_texture.scale(sf::Vector2f(1 / float(Map::TILE_SIZE), 1 / float(Map::TILE_SIZE)));

	m_tilePosTextBackground.setPosition(0, 0);
	m_tilePosTextBackground.setFillColor(sf::Color(0, 0, 0, 125));


	/// TODO:
	/// When pressing Shift, copy the selection to the clipboard
	/// Else, paste the selection (by default, a single tile)
	/// Clear the clipboard by pressing Space
}

Cursor::~Cursor()
{
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::update(const sf::Vector2i &mouseTilePos)
{
	if (m_grab && m_grabType != Move) {
		m_selection.setPosition(sf::Vector2f(
			std::min(mouseTilePos.x, m_grabStartPos.x),
			std::min(mouseTilePos.y, m_grabStartPos.y)
		));
		m_selection.setSize(sf::Vector2f(
			std::abs(mouseTilePos.x - m_grabStartPos.x) + 1,
			std::abs(mouseTilePos.y - m_grabStartPos.y) + 1
		));
	}

	m_cursor.setPosition(sf::Vector2f(mouseTilePos));

	updateText();
}

void Cursor::updateText()
{
	std::ostringstream oss;

	oss << "Cursor:" << std::endl;
	oss << "  at ["
	    << (m_cursor.getPosition().x)
	    << ","
	    << (m_cursor.getPosition().y)
	    << "]" << std::endl;
	if (hasSelection()) {
		oss << "Selection:" << std::endl;
		oss << "  at ["
		    << (m_selection.getPosition().x)
		    << ","
		    << (m_selection.getPosition().y)
		    << "]" << std::endl;
		oss << "size ["
		    << (m_selection.getSize().x)
		    << ","
		    << (m_selection.getSize().y)
		    << "]";
	}

	m_tilePosText.setString(oss.str());
	m_tilePosTextBackground.setSize(sf::Vector2f(
		m_tilePosText.getLocalBounds().width + m_tilePosText.getPosition().x + 20,
		m_tilePosText.getLocalBounds().height + m_tilePosText.getPosition().y + 20
	));
}

void Cursor::render(sf::RenderWindow &target)
{
	if (hasSelection()) {
		if (m_showClipboard) {
			m_clipboard.setOffset(sf::Vector2i(m_selection.getPosition()));
			m_clipboard.renderRepeated(target, sf::Vector2i(m_selection.getSize()));
		}
		target.draw(m_selection);
	}

	if (m_textureSelect)
		target.draw(m_texture);

	if (m_showClipboard && !hasSelection()) {
		m_clipboard.setOffset(sf::Vector2i(m_cursor.getPosition()));
		m_clipboard.renderRepeated(target, sf::Vector2i(m_cursor.getSize()));
	}

	if (!m_grab)
		target.draw(m_cursor);

	if (!m_textureSelect) {
		Display::drawAbsolute(m_tilePosTextBackground);
		Display::drawAbsolute(m_tilePosText);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::setTexturePos(const sf::Vector2i &texturePos)
{
	// m_clipboard.setTile(sf::Vector2i(0, 0), texturePos);
	m_cursor.setTextureRect(sf::IntRect(texturePos.x, texturePos.y, 1, 1));
}

void Cursor::setTexturePos(int x, int y)
{
	setTexturePos(sf::Vector2i(x, y));
}

sf::Vector2i Cursor::getTexturePos()
{
	return sf::Vector2i(
		m_cursor.getTextureRect().left,
		m_cursor.getTextureRect().top
	);
}

sf::Vector2i Cursor::getGrabStartPosition()
{
	return m_grabStartPos;
}

sf::IntRect Cursor::getSelection()
{
	return sf::IntRect(
		m_selection.getPosition().x,
		m_selection.getPosition().y,
		m_selection.getSize().x,
		m_selection.getSize().y
	);
}

Cursor::GrabType Cursor::getGrabType()
{
	return m_grabType;
}

////////////////////////////////////////////////////////////////////////////////

void Cursor::startGrab(const sf::Vector2i &mouseTilePos, GrabType type)
{
	if (m_textureSelect || m_grab)
		return;

	m_grab = true;
	m_grabType = type;
	m_grabStartPos = mouseTilePos;

	switch (type) {
		case Move:
			m_selection.setOutlineColor(sf::Color::Transparent);
			showClipboard(false);
		break;
		case Delete:
			m_selection.setFillColor(sf::Color(255, 0, 0, 50));
			showClipboard(false);
		break;
		case Copy:
			showClipboard(false);
		break;
		default:
		break;
	}

	update(mouseTilePos);
}

void Cursor::endGrab(const sf::Vector2i &mouseTilePos)
{
	if (!m_grab)
		return;

	m_grab = false;

	switch (m_grabType) {
		case Move:
			m_selection.setOutlineColor(sf::Color::White);
			showClipboard(true);
		break;
		case Delete:
			m_selection.setFillColor(sf::Color::Transparent);
			showClipboard(true);
		break;
		case Copy:
			showClipboard(true);
		break;
		default:
		break;
	}

	update(mouseTilePos);
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
	m_cursor.setSize(sf::Vector2f(1, 1));
	m_cursor.setOutlineColor(sf::Color::Red);

	sf::Vector2f pos(m_cursor.getPosition());
	Tile *t = m_clipboard.getTile(m_clipboard.getTopLeftPosition());
	if (t)
		pos -= sf::Vector2f(t->tex);
	m_texture.setPosition(pos);
}

void Cursor::disableTextureSelect()
{
	if (!m_textureSelect)
		return;

	m_textureSelect = false;
	m_cursor.setOutlineColor(sf::Color::White);
	// setTexturePos(sf::Vector2i(m_cursor.getPosition() - m_texture.getPosition()));
	m_clipboard.clear();
	m_clipboard.setTile(sf::Vector2i(0, 0), sf::Vector2i(m_cursor.getPosition() - m_texture.getPosition()));
}

bool Cursor::isSelectingTexture()
{
	return m_textureSelect;
}

////////////////////////////////////////////////////////////////////////////////

Map &Cursor::getClipboard()
{
	return m_clipboard;
}

void Cursor::showClipboard(bool show)
{
	m_showClipboard = show;
}

bool Cursor::isClipboardShown()
{
	return m_showClipboard;
}

bool Cursor::hasSelection()
{
	sf::Vector2i size(m_selection.getSize());

	return size.x > 0 && size.y > 0;
}

void Cursor::resetSelection()
{
	m_selection.setSize(sf::Vector2f(0, 0));
}

void Cursor::copySelection(Map &from)
{
	if (!hasSelection())
		return;

	sf::IntRect region = getSelection();
	m_clipboard.clear();

	for (int y = region.top; y < region.height + region.top; ++y) {
		for (int x = region.left; x < region.width + region.left; ++x) {
			Tile *t = from.getTile(x, y);
			if (!t)
				continue;
			m_clipboard.setTile(
				sf::Vector2i(x - region.left, y - region.top),
				t->tex
			);
		}
	}

	resetSelection();
}

////////////////////////////////////////////////////////////////////////////////

}