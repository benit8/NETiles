/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** MouseMoveEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class MouseMoveEventListener;

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <map>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void(sf::Vector2i, sf::Vector2i)> MouseMoveCallback;

class MouseMoveEventListener : public IEventListener
{
	typedef std::vector<std::pair<sf::IntRect, MouseMoveCallback>> MouseMoveCallbacks;

public:
	MouseMoveEventListener()
	: m_lastPos(0, 0)
	{}

	~MouseMoveEventListener() override
	{}

public:
	void handleEvent(sf::Event &e) override
	{
		sf::Vector2i pos(e.mouseMove.x, e.mouseMove.y);

		for (unsigned i = 0; i < m_callbacks.size(); ++i) {
			if (m_callbacks[i].first.contains(pos))
				(m_callbacks[i].second)(pos, pos - m_lastPos);
		}

		m_lastPos = pos;
	}

	void registerCallback(MouseMoveCallback callback, sf::IntRect zone) {
		m_callbacks.push_back(std::make_pair(zone, callback));
	}

private:
	MouseMoveCallbacks m_callbacks;
	sf::Vector2i m_lastPos;
};