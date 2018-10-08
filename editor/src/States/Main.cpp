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
, m_initialZoomFactor(2 * Tiles::Map::TILE_SIZE)
{
	m_SFGDesktop.SetProperty("Window", "BackgroundColor", "#000000af");
	m_SFGDesktop.SetProperty("Window", "BorderWidth", 0);
	m_SFGDesktop.SetProperty("Window > Label", "FontSize", 24.f);

	m_SFGWindow = sfg::Window::Create(sfg::Window::BACKGROUND);
	m_SFGWindow->SetTitle("DEBUG");
	m_SFGWindow->SetRequisition(sf::Vector2f(Display::getWindowSize().x, 50.f));
	m_SFGWindow->SetPosition(sf::Vector2f(0, Display::getWindowSize().y - m_SFGWindow->GetRequisition().y));

	m_SFGLabel = sfg::Label::Create();
	m_SFGLabel->SetText("");

	m_SFGWindow->Add(m_SFGLabel);
	m_SFGDesktop.Add(m_SFGWindow);

	m_tileMap.loadFromFile();

	Display::setViewCenter(m_tileMap.getCenter());
	Display::zoomView(1 / m_initialZoomFactor);
}

Main::~Main()
{
}

////////////////////////////////////////////////////////////////////////////////

void Main::handleEvent(sf::Event &e)
{
	m_SFGWindow->HandleEvent(e);

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
	m_SFGLabel->SetText(m_tileCursor.getDebugText());

	m_SFGWindow->Update(0.f);
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

		case sf::Keyboard::Up:
			moveMap(0, -1);
		break;
		case sf::Keyboard::Down:
			moveMap(0, 1);
		break;
		case sf::Keyboard::Right:
			moveMap(1, 0);
		break;
		case sf::Keyboard::Left:
			moveMap(-1, 0);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		if (e.wheel == sf::Mouse::VerticalWheel) {
			if (e.delta < 0)
				Display::zoomView(2.0f);
			else
				Display::zoomView(0.5f);
		}
	}
	else {
		if (e.wheel == sf::Mouse::VerticalWheel) {
			if (e.delta < 0)
				moveMap(0, 1);
			else
				moveMap(0, -1);
		}
		else if (e.wheel == sf::Mouse::HorizontalWheel) {
			if (e.delta < 0)
				moveMap(1, 0);
			else
				moveMap(-1, 0);
		}
	}
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

void Main::moveMap(sf::Vector2f offset)
{
	sf::View v = Display::getView();
	v.move(offset * (Display::getZoom() * m_initialZoomFactor));
	Display::setView(v);
}

void Main::moveMap(float x, float y)
{
	moveMap(sf::Vector2f(x, y));
}

////////////////////////////////////////////////////////////////////////////////

sf::Vector2i Main::mapWinToTileAbs(sf::Vector2i windowPos)
{
	sf::Vector2f fpos(Display::getWindow().mapPixelToCoords(windowPos));
	return sf::Vector2i(floor(fpos.x), floor(fpos.y));
}

////////////////////////////////////////////////////////////////////////////////

}