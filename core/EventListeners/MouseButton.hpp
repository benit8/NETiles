/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** MouseButtonEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class MouseButtonEventListener;

////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void(sf::Mouse::Button, sf::Vector2i)> MouseButtonCallback;

class MouseButtonEventListener : public IEventListener
{
	typedef std::map<sf::Mouse::Button, std::vector<MouseButtonCallback>> MouseButtonCallbacks;

public:
	MouseButtonEventListener() {}
	~MouseButtonEventListener() override {}

public:
	void handleEvent(sf::Event &e) override
	{
		sf::Mouse::Button btn = e.mouseButton.button;
		if (m_callbacks.find(btn) == m_callbacks.end())
			return;

		sf::Vector2i pos(e.mouseButton.x, e.mouseButton.y);
		for (std::vector<MouseButtonCallback>::iterator it = m_callbacks[btn].begin(); it != m_callbacks[btn].end(); ++it)
			(*it)(btn, pos);
	}

	void registerCallback(MouseButtonCallback callback, sf::Mouse::Button button) {
		m_callbacks[button].push_back(callback);
	}

private:
	MouseButtonCallbacks m_callbacks;
};