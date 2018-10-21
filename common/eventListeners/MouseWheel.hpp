/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** MouseWheelEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class MouseWheelEventListener;

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void(sf::Mouse::Wheel, float, sf::Vector2i)> MouseWheelCallback;

class MouseWheelEventListener : public IEventListener
{
	typedef std::map<sf::Mouse::Wheel, std::vector<MouseWheelCallback>> MouseWheelCallbacks;

public:
	MouseWheelEventListener() {}
	~MouseWheelEventListener() override {}

public:
	void handleEvent(sf::Event &e) {
		sf::Event::MouseWheelScrollEvent data = e.mouseWheelScroll;
		if (m_callbacks.find(data.wheel) == m_callbacks.end())
			return;

		for (std::vector<MouseWheelCallback>::iterator it = m_callbacks[data.wheel].begin(); it != m_callbacks[data.wheel].end(); ++it) {
			(*it)(data.wheel, data.delta, sf::Vector2i(data.x, data.y));
		}
	}

	void registerCallback(MouseWheelCallback callback, sf::Mouse::Wheel wheel) {
		m_callbacks[wheel].push_back(callback);
	}

private:
	MouseWheelCallbacks m_callbacks;
};