/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** IState.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class IState;

////////////////////////////////////////////////////////////////////////////////

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "EventHandler.hpp"

////////////////////////////////////////////////////////////////////////////////

class IState
{
public:
	virtual ~IState() = default;

public:
	virtual void create() {}
	virtual void update(const sf::Time delta) {}
	virtual void render() {}
	virtual void destroy() {}

public:
	void handleEvent(sf::Event &e) {
		m_eventHandler.handleEvent(e);
	}

protected:
	EventHandler m_eventHandler;
};