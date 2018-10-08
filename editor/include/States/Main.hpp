/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** States / Main.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace States {
	class Main;
}

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include "Display.hpp"
#include "States/State.hpp"
#include "Ressources/Manager.hpp"
#include "Tiles/Map.hpp"
#include "Tiles/Tile.hpp"
#include "Tiles/Cursor.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace States
{

class Main : public State
{
public:
	Main(const std::string &mapPath);
	~Main() override;

	void handleEvent(sf::Event &e) override;
	void update() override;
	void render(sf::RenderWindow &target) override;

private:
	void onKeyDown(sf::Keyboard::Key key);
	void onKeyUp(sf::Keyboard::Key key);
	void onMouseMoved(const sf::Vector2i &mousePos);
	void onMouseDown(const sf::Event::MouseButtonEvent &e);
	void onMouseUp(const sf::Event::MouseButtonEvent &e);
	void onMouseScrolled(const sf::Event::MouseWheelScrollEvent &e);

	void moveMap(sf::Vector2f offset);
	void moveMap(float x, float y);

	void actionToSelection(sf::IntRect tileRegion);
	void copyCurrentTile();

	sf::Vector2i mapWinToTileAbs(sf::Vector2i windowPos);

private:
	Tiles::Map m_tileMap;
	Tiles::Cursor m_tileCursor;
	bool m_tileTypesFilter;
	float m_initialZoomFactor;

	sfg::Desktop m_SFGDesktop;
	sfg::Window::Ptr m_SFGWindow;
	sfg::Label::Ptr m_SFGLabel;
};

}