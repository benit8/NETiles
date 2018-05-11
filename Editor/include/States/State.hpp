/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** States / State.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace States {
	class State;
}

////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

////////////////////////////////////////////////////////////////////////////////

namespace States
{

class State
{
protected:
	State() = default;

public:
	virtual ~State() = default;

	virtual void handleEvent(sf::Event &e) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &target) = 0;

	bool isRequestingClose()
	{
		return m_requestingClose;
	}

protected:
	bool m_requestingClose = false;
};

}