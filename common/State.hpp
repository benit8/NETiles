/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** State.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class State;

////////////////////////////////////////////////////////////////////////////////

#include "IState.hpp"

// Only for callbacks binding
using namespace std::placeholders;

////////////////////////////////////////////////////////////////////////////////

class State : public IState
{
public:
	State() {}
	~State() override {}

public:
	void handleEvent(sf::Event &e) {
		m_eventHandler.dispatchEvent(e);
	}

	void update(const sf::Time delta) override {}
	void render(sf::RenderTarget &renderTarget) override {}

protected:
	EventHandler m_eventHandler;
};