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
	void handleEvent(sf::Event &e)
	{
		EventListeners::iterator it = m_eventListeners.find(e.type);
		if (it != m_eventListeners.end())
			it->second->handleEvent(e);
	}

	template <typename F, typename... Args>
	void on(sf::Event::EventType type, F callback, Args&&... args)
	{
		EventListeners::iterator it = m_eventListeners.find(type);
		if (it == m_eventListeners.end())
			return;

		it->second->registerCallback(callback, std::forward<Args>(args)...);
		// https://stackoverflow.com/questions/5871722/how-to-achieve-virtual-template-function-in-c/5872226
	}

private:
	EventListeners m_eventListeners;
};