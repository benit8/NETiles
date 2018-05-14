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
, m_displayTileTypes(false)
, m_window(window)
, m_view(window.getView())
, m_mouseTile(sf::Vector2f(1, 1))
, m_grab(false)
, m_grabStartPos(0, 0)
{
	m_tileMap.loadFromFile();

	m_view.setCenter(m_tileMap.getCenterPoint());
	m_view.zoom(1 / 32.f);

	m_mouseTile.setTexture(&Ressource::Manager::getTexture("tileset0"));
	m_mouseTile.setTextureRect(sf::IntRect(0, 0, 16, 16));
	m_mouseTile.setFillColor(sf::Color(255, 255, 255, 175));
	m_mouseTile.setOutlineColor(sf::Color::White);
	m_mouseTile.setOutlineThickness(0.025f);
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
		case sf::Event::MouseWheelScrolled:
			if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
				if (e.mouseWheelScroll.delta < 0)
					m_view.zoom(2.0f);
				else
					m_view.zoom(0.5f);
			}
		break;
		case sf::Event::MouseButtonPressed:
			grabStart(sf::Vector2i(e.mouseButton.x, e.mouseButton.y), e.mouseButton.button);
		break;
		case sf::Event::MouseButtonReleased:
			grabEnd();
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
	if (m_grab) {
		if (m_grabButton == sf::Mouse::Middle) {
			sf::Vector2i pos(m_mouseTile.getPosition());
			sf::Vector2i diff(pos - m_grabStartPos);
			m_view.move(sf::Vector2f(-diff));
		}
	}
}

void Main::render(sf::RenderWindow &target)
{
	target.setView(m_view);

	m_tileMap.render(target, m_displayTileTypes);

	target.draw(m_mouseTile);
}

////////////////////////////////////////////////////////////////////////////////

void Main::onKeydown(sf::Keyboard::Key key)
{
	switch (key) {
		case sf::Keyboard::Escape:
			m_requestingClose = true;
		break;
		case sf::Keyboard::W:
			m_displayTileTypes = !m_displayTileTypes;
		break;
		case sf::Keyboard::D:
			printf("Tile at (%.1f, %.1f)\n", m_mouseTile.getPosition().x, m_mouseTile.getPosition().y);
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

void Main::onMouseMoved(sf::Vector2i mousePos)
{
	sf::Vector2f fpos(m_window.mapPixelToCoords(mousePos, m_view));
	sf::Vector2i pos(floor(fpos.x), floor(fpos.y));

	if (m_grab && m_grabButton != sf::Mouse::Middle) {
		m_mouseTile.setPosition(sf::Vector2f(std::min(pos.x, m_grabStartPos.x), std::min(pos.y, m_grabStartPos.y)));
		m_mouseTile.setSize(sf::Vector2f(abs(pos.x - m_grabStartPos.x) + 1, abs(pos.y - m_grabStartPos.y) + 1));
	}
	else {
		m_mouseTile.setPosition(sf::Vector2f(pos));
		m_mouseTile.setSize(sf::Vector2f(1, 1));
	}
}

////////////////////////////////////////////////////////////////////////////////

void Main::grabStart(sf::Vector2i mousePos, sf::Mouse::Button button)
{
	m_grab = true;
	m_grabButton = button;
	m_grabStartPos = sf::Vector2i(m_window.mapPixelToCoords(mousePos, m_view));
}

void Main::grabEnd()
{
	m_grab = false;

	if (m_grabButton != sf::Mouse::Middle) {
		grabAction();
	}

	m_grabButton = sf::Mouse::ButtonCount;
	m_grabStartPos = sf::Vector2i(0, 0);
}

void Main::grabAction()
{
	for (size_t y = 0; y < m_mouseTile.getSize().y; ++y) {
		for (size_t x = 0; x < m_mouseTile.getSize().x; ++x) {
			sf::Vector2i pos(m_mouseTile.getPosition().x + x, m_mouseTile.getPosition().y + y);
			Tiles::Tile *t = m_tileMap.getTile(pos);

			if (!m_displayTileTypes) {
				if (m_grabButton == sf::Mouse::Left)
					m_tileMap.setTile(pos, sf::Vector2u(m_mouseTile.getTextureRect().top, m_mouseTile.getTextureRect().left));
				else if (m_grabButton == sf::Mouse::Right)
					m_tileMap.removeTile(pos);
			}
			else if (t && m_displayTileTypes)
				t->walkable = !t->walkable;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

}