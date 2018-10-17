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

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "../IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void(sf::Vector2i, sf::Vector2i)> MouseMoveCallback;

class MouseMoveEventListener : public IEventListener
{
	typedef std::vector<MouseMoveCallback> MouseMoveCallbacks;

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

		for (MouseMoveCallbacks::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
			(*it)(pos, pos - m_lastPos);
		}

		m_lastPos = pos;
	}

	void registerCallback(MouseMoveCallback callback) {
		m_callbacks.push_back(callback);
	}

private:
	MouseMoveCallbacks m_callbacks;
	sf::Vector2i m_lastPos;
};