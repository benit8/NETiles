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

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "States/State.hpp"
#include "Ressources/Manager.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace States
{

class Main : public State
{
public:
	Main();
	~Main() override;

	void handleEvent(sf::Event &e) override;
	void update() override;
	void render(sf::RenderWindow &target) override;

private:
	void onKeydown(sf::Keyboard::Key key);

private:
	// sf::VertexArray m_va;
};

}