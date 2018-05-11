/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** States / Menu.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace States {
	class Menu;
}

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "States/State.hpp"
#include "Ressources/Manager.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace States
{

class Menu : public State
{
public:
	Menu();
	~Menu() override;

	void handleEvent(sf::Event &e) override;
	void update() override;
	void render(sf::RenderWindow &target) override;

private:
};

}