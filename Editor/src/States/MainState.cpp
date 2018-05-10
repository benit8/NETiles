/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** States / MainState.cpp
*/

#include "States/MainState.hpp"

////////////////////////////////////////////////////////////////////////////////

MainState::MainState(App &app)
: State(app)
{
}

MainState::~MainState()
{
}

////////////////////////////////////////////////////////////////////////////////

void MainState::handleEvent(sf::Event &e)
{
	switch (e.type) {
		case sf::Event::KeyPressed:
			onKeydown(e.key.code);
			break;
		default:
			break;
	}
}

void MainState::update()
{
}

void MainState::render(sf::RenderWindow &target)
{
}

////////////////////////////////////////////////////////////////////////////////

void MainState::onKeydown(sf::Keyboard::Key key)
{
	switch (key) {
		case sf::Keyboard::Escape:
			m_parent.requestClose();
			break;
		default:
			break;
	}
}