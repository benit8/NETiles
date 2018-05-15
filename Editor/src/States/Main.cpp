/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** States / Main.cpp
*/

#include "States/Main.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace States
{

////////////////////////////////////////////////////////////////////////////////

Main::Main(const std::string &mapPath, sf::RenderWindow &window)
: State()
, m_tileMap(mapPath)
, m_tileCursor(Tiles::Map::TILEMAP_TILE_SIZE)
, m_tileTypesFilter(false)
, m_window(window)
, m_view(window.getView())
{
	m_tileMap.loadFromFile();

	m_view.setCenter(sf::Vector2f(m_tileMap.getCenter()));
}

Main::~Main()
{
}

////////////////////////////////////////////////////////////////////////////////

void Main::handleEvent(sf::Event &e)
{
	switch (e.type) {
		case sf::Event::KeyPressed:
			onKeydown(e.key.code);
		break;
		case sf::Event::KeyReleased:
			onKeyup(e.key.code);
		break;
		case sf::Event::MouseWheelScrolled:
			if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
				if (e.mouseWheelScroll.delta < 0)
					m_view.zoom(2.0f);
				else
					m_view.zoom(0.5f);
			}
		break;
		case sf::Event::MouseButtonPressed:
			m_tileCursor.startGrab(
				mapWinToTileAbs(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)),
				e.mouseButton.button
			);
		break;
		case sf::Event::MouseButtonReleased:
			actionToSelectionRegion(m_tileCursor.endGrab());
		break;
		case sf::Event::MouseMoved:
			onMouseMoved(sf::Vector2i(e.mouseMove.x, e.mouseMove.y));
		break;
		default:
		break;
	}
}

void Main::update()
{
}

void Main::render(sf::RenderWindow &target)
{
	target.setView(m_view);

	m_tileMap.render(target, m_tileTypesFilter);
	m_tileCursor.render(target);
}

////////////////////////////////////////////////////////////////////////////////

void Main::onKeydown(sf::Keyboard::Key key)
{
	switch (key) {
		case sf::Keyboard::Escape:
			m_requestingClose = true;
		break;
		case sf::Keyboard::W:
			if (!m_tileCursor.isGrabbing())
				m_tileTypesFilter = !m_tileTypesFilter;
		break;
		case sf::Keyboard::Space:
			// if (!m_grab) {
			// 	m_textureSelect = true;
			// 	m_textureSelectStartPos = mapWinToTileAbs(sf::Mouse::getPosition(m_window));
			// }
		break;
		case sf::Keyboard::Return:
			if (m_tileMap.saveToFile())
				std::cout << "Saved map to '" << m_tileMap.getMapPath() << "'" << std::endl;
			else
				std::cout << "Could not save map to '" << m_tileMap.getMapPath() << "'" << std::endl;
		break;
		default:
		break;
	}
}

void Main::onKeyup(sf::Keyboard::Key key)
{
	switch (key) {
		case sf::Keyboard::Space:
			// if (!m_grab)
			// 	m_textureSelect = false;
		break;
		default:
		break;
	}
}

void Main::onMouseMoved(sf::Vector2i mouseWindowPos)
{
	sf::Vector2i mouseTilePos = mapWinToTileAbs(mouseWindowPos);

	if (m_tileCursor.isGrabbing()) {
		if (m_tileCursor.getGrabButton() == sf::Mouse::Middle)
			m_view.move(sf::Vector2f(m_tileCursor.getGrabStartPosition() - mouseTilePos));
		else {
			m_tileCursor.setPosition(
				std::min(mouseTilePos.x, m_tileCursor.getGrabStartPosition().x),
				std::min(mouseTilePos.y, m_tileCursor.getGrabStartPosition().y)
			);
			m_tileCursor.setSize(
				abs(mouseTilePos.x - m_tileCursor.getGrabStartPosition().x) + Tiles::Map::TILEMAP_TILE_SIZE,
				abs(mouseTilePos.y - m_tileCursor.getGrabStartPosition().y) + Tiles::Map::TILEMAP_TILE_SIZE
			);
		}
	}
	// else if (m_textureSelect) {
	// 	sf::IntRect textureRect = m_area.getTextureRect();
	// 	sf::Vector2i diff((mouseTilePos - m_textureSelectStartPos) / Tiles::Map::TILEMAP_TILE_SIZE * Tiles::Map::TILESET_TILE_SIZE);
	// 	textureRect.left += diff.x;
	// 	textureRect.top += diff.y;
	// 	m_area.setTextureRect(textureRect);
	// }
	else {
		m_tileCursor.reset();
		m_tileCursor.setPosition(mouseTilePos);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Main::actionToSelectionRegion(sf::IntRect region)
{
	if (m_tileCursor.getGrabButton() == sf::Mouse::Middle)
		return;

	for (int y = region.top; y < region.height + region.top; ++y) {
		for (int x = region.left; x < region.width + region.left; ++x) {
			sf::Vector2i pos(x, y);
			Tiles::Tile *t = m_tileMap.getTile(pos);

			if (m_tileTypesFilter) {
				if (t) t->walkable = !t->walkable;
			}
			else {
				if (m_tileCursor.getGrabButton() == sf::Mouse::Left)
					m_tileMap.setTile(pos, m_tileCursor.getTilePos());
				else if (m_tileCursor.getGrabButton() == sf::Mouse::Right)
					m_tileMap.removeTile(pos);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

sf::Vector2i Main::mapWinToTileAbs(sf::Vector2i windowPos)
{
	sf::Vector2f fpos(m_window.mapPixelToCoords(windowPos, m_view));
	return sf::Vector2i(
		floor(fpos.x / Tiles::Map::TILEMAP_TILE_SIZE) * Tiles::Map::TILEMAP_TILE_SIZE,
		floor(fpos.y / Tiles::Map::TILEMAP_TILE_SIZE) * Tiles::Map::TILEMAP_TILE_SIZE
	);
}

sf::Vector2i Main::mapWinToTileRel(sf::Vector2i windowPos)
{
	return mapWinToTileAbs(windowPos) / Tiles::Map::TILEMAP_TILE_SIZE;
}

sf::Vector2i Main::mapTileAbsToTileRel(sf::Vector2i tileAbsPos)
{
	return tileAbsPos / Tiles::Map::TILEMAP_TILE_SIZE;
}

sf::Vector2i Main::mapTileRelToTileAbs(sf::Vector2i tileRelPos)
{
	return tileRelPos * Tiles::Map::TILEMAP_TILE_SIZE;
}

////////////////////////////////////////////////////////////////////////////////

}