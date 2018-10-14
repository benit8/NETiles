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

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "EventHandler.hpp"
#include "IState.hpp"

////////////////////////////////////////////////////////////////////////////////

class State : public IState
{
public:
	~State() override {}

public:
	void create() override {}
	void update(const sf::Time delta) override {}
	void render() override {}
	void destroy() override {}

public:
	void handleEvent(sf::Event &e) {
		m_eventHandler.handleEvent(e);
	}

protected:
	EventHandler m_eventHandler;
};