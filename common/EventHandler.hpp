/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** EventHandler.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class EventHandler;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <functional>
#include <map>
#include <vector>

#include <SFML/Window/Event.hpp>

#include "KeyDownEventListener.hpp"
#include "MouseMoveEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

class EventHandler
{
	typedef std::map<int, std::unique_ptr<IEventListener>> EventListeners;

public:
	EventHandler() {
		m_eventListeners[sf::Event::KeyPressed] = std::make_unique<KeyDownEventListener>();
		m_eventListeners[sf::Event::MouseMoved] = std::make_unique<MouseMoveEventListener>();
	}
	~EventHandler() {}

public:
	void dispatchEvent(sf::Event &e)
	{
		EventListeners::iterator it = m_eventListeners.find(e.type);
		if (it != m_eventListeners.end())
			it->second->handleEvent(e);
	}


	void onKeyDown(KeyDownCallback callback, int key, int ctrlKeys = 0) {
		EventListeners::iterator it = m_eventListeners.find(sf::Event::KeyPressed);
		if (it != m_eventListeners.end())
			dynamic_cast<KeyDownEventListener *>(it->second.get())->registerCallback(callback, key, ctrlKeys);
	}

	void onMouseMove(MouseMoveCallback callback, sf::IntRect zone = sf::IntRect(0, 0, 1280, 720)) {
		EventListeners::iterator it = m_eventListeners.find(sf::Event::MouseMoved);
		if (it != m_eventListeners.end())
			dynamic_cast<MouseMoveEventListener *>(it->second.get())->registerCallback(callback, zone);
	}

private:
	EventListeners m_eventListeners;
};