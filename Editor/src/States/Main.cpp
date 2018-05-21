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

Main::Main(const std::string &mapPath)
: State()
, m_tileMap(mapPath)
, m_tileCursor()
, m_tileTypesFilter(false)
{
	m_tileMap.loadFromFile();

	Display::setViewCenter(m_tileMap.getCenter());
	Display::zoomView(1 / 32.0f);
}

Main::~Main()
{
}

////////////////////////////////////////////////////////////////////////////////

void Main::handleEvent(sf::Event &e)
{
	switch (e.type) {
		case sf::Event::KeyPressed:
			onKeyDown(e.key.code);
		break;
		case sf::Event::KeyReleased:
			onKeyUp(e.key.code);
		break;
		case sf::Event::MouseMoved:
			onMouseMoved(sf::Vector2i(e.mouseMove.x, e.mouseMove.y));
		break;
		case sf::Event::MouseButtonPressed:
			onMouseDown(e.mouseButton);
		break;
		case sf::Event::MouseButtonReleased:
			onMouseUp(e.mouseButton);
		break;
		case sf::Event::MouseWheelScrolled:
			onMouseScrolled(e.mouseWheelScroll);
		break;
		default:
		break;
	}
}

void Main::update()
{
	m_tileCursor.update(mapWinToTileAbs(Display::getMousePosition()));
}

void Main::render(sf::RenderWindow &target)
{
	m_tileMap.render(target, m_tileTypesFilter);

	m_tileCursor.render(target);
}

////////////////////////////////////////////////////////////////////////////////

void Main::onKeyDown(sf::Keyboard::Key key)
{
	switch (key) {
		case sf::Keyboard::Escape:
			m_requestingClose = true;
		break;
		case sf::Keyboard::Tab:
			m_tileCursor.enableTextureSelect();
		break;
		case sf::Keyboard::Return:
			if (m_tileMap.saveToFile())
				std::cout << "Saved map to '" << m_tileMap.getMapPath() << "'" << std::endl;
			else
				std::cout << "Could not save map to '" << m_tileMap.getMapPath() << "'" << std::endl;
		break;
		case sf::Keyboard::Space:
			m_tileCursor.resetSelection();
		break;
		case sf::Keyboard::W:
			if (!m_tileCursor.isGrabbing() && !m_tileCursor.isSelectingTexture())
				m_tileTypesFilter = !m_tileTypesFilter;
		break;
		default:
		break;
	}
}

void Main::onKeyUp(sf::Keyboard::Key key)
{
	switch (key) {
		case sf::Keyboard::Tab:
			m_tileCursor.disableTextureSelect();
		break;
		default:
		break;
	}
}

void Main::onMouseMoved(const sf::Vector2i &mouseWindowPos)
{
	if (m_tileCursor.isGrabbing() && m_tileCursor.getGrabType() == Tiles::Cursor::Move) {
		sf::View v = Display::getView();
		v.move(sf::Vector2f(m_tileCursor.getGrabStartPosition() - mapWinToTileAbs(mouseWindowPos)));
		Display::setView(v);
	}
}

void Main::onMouseDown(const sf::Event::MouseButtonEvent &e)
{
	Tiles::Cursor::GrabType type = Tiles::Cursor::None;
	if (m_tileTypesFilter)
		type = Tiles::Cursor::None;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		type = Tiles::Cursor::Copy;
	else if (e.button == sf::Mouse::Left)
		type = Tiles::Cursor::Fill;
	else if (e.button == sf::Mouse::Middle)
		type = Tiles::Cursor::Move;
	else if (e.button == sf::Mouse::Right)
		type = Tiles::Cursor::Delete;

	m_tileCursor.startGrab(mapWinToTileAbs(sf::Vector2i(e.x, e.y)), type);
}

void Main::onMouseUp(const sf::Event::MouseButtonEvent &e)
{
	m_tileCursor.endGrab(mapWinToTileAbs(sf::Vector2i(e.x, e.y)));

	actionToSelection(m_tileCursor.getSelection());
	m_tileCursor.resetSelection();
}

void Main::onMouseScrolled(const sf::Event::MouseWheelScrollEvent &e)
{
	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		if (e.wheel == sf::Mouse::VerticalWheel) {
			if (e.delta < 0)
				Display::zoomView(2.0f);
			else
				Display::zoomView(0.5f);
		}
	// }
}

////////////////////////////////////////////////////////////////////////////////

void Main::actionToSelection(sf::IntRect region)
{
	if (m_tileCursor.getGrabType() == Tiles::Cursor::Move)
		return;

	if (m_tileTypesFilter) {
		for (int y = region.top; y < region.height + region.top; ++y) {
			for (int x = region.left; x < region.width + region.left; ++x) {
				Tiles::Tile *t = m_tileMap.getTile(x, y);
				if (!t)
					continue;
				t->walkable = !t->walkable;
			}
		}
	}
	else if (m_tileCursor.getGrabType() == Tiles::Cursor::Fill) {
		sf::Vector2i clipboardSize = m_tileCursor.getClipboard().getSize();
		for (int y = region.top; y < region.height + region.top; ++y) {
			for (int x = region.left; x < region.width + region.left; ++x) {
				Tiles::Tile *t = m_tileCursor.getClipboard().getTile((x - region.left) % clipboardSize.x, (y - region.top) % clipboardSize.y);
				if (!t)
					continue;
				m_tileMap.setTile(sf::Vector2i(x, y), t->tex);
			}
		}
	}
	else if (m_tileCursor.getGrabType() == Tiles::Cursor::Delete) {
		for (int y = region.top; y < region.height + region.top; ++y)
			for (int x = region.left; x < region.width + region.left; ++x)
				m_tileMap.deleteTile(x, y);
	}
	else if (m_tileCursor.getGrabType() == Tiles::Cursor::Copy) {
		m_tileCursor.copySelection(m_tileMap);
	}
}

void Main::copyCurrentTile()
{
	sf::IntRect region = m_tileCursor.getSelection();
	Tiles::Tile *t = m_tileMap.getTile(region.left, region.top);

	if (!t)
		return;

	m_tileCursor.setTexturePos(t->tex);
}

////////////////////////////////////////////////////////////////////////////////

sf::Vector2i Main::mapWinToTileAbs(sf::Vector2i windowPos)
{
	sf::Vector2f fpos(Display::getWindow().mapPixelToCoords(windowPos));
	return sf::Vector2i(floor(fpos.x), floor(fpos.y));
}

////////////////////////////////////////////////////////////////////////////////

}