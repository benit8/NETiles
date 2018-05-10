/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** States / MainState.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class MainState;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "States.hpp"

////////////////////////////////////////////////////////////////////////////////

class MainState : public State
{
public:
	MainState(App &app);
	~MainState() override;

	void handleEvent(sf::Event &e) override;
	void update() override;
	void render(sf::RenderWindow &target) override;

private:
	void onKeydown(sf::Keyboard::Key key);
};