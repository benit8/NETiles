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
	Main(const std::string &mapPath, sf::RenderWindow &window);
	~Main() override;

	void handleEvent(sf::Event &e) override;
	void update() override;
	void render(sf::RenderWindow &target) override;

private:
	void onKeydown(sf::Keyboard::Key key);
	void onKeyup(sf::Keyboard::Key key);
	void onMouseMoved(sf::Vector2i mousePos);

	void actionToSelectionRegion(sf::IntRect tileRegion);
	void copyCurrentTile();

	sf::Vector2i mapWinToTileAbs(sf::Vector2i windowPos);
	sf::Vector2i mapWinToTileRel(sf::Vector2i windowPos);
	sf::Vector2i mapTileAbsToTileRel(sf::Vector2i tileAbsPos);
	sf::Vector2i mapTileRelToTileAbs(sf::Vector2i tileRelPos);

private:
	Tiles::Map m_tileMap;
	Tiles::Cursor m_tileCursor;
	bool m_tileTypesFilter;

	sf::RenderWindow &m_window;
	sf::View m_view;
};

}