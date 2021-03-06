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

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "EventHandler.hpp"
#include "GUI/GUI.hpp"

////////////////////////////////////////////////////////////////////////////////

class State
{
public:
	State() = default;
	virtual ~State() = default;

public:
	virtual void handleEvent(sf::Event &e) {
		m_guiRoot.handleEvent(e, true);
		m_eventHandler.dispatchEvent(e);
	}

	virtual void update(const sf::Time &) {}

	virtual void render(sf::RenderTarget &renderTarget) {
		m_guiRoot.render(renderTarget, true);
	}

protected:
	EventHandler m_eventHandler;
	GUI::Widget m_guiRoot;
};