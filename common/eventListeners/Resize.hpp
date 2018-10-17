/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** ResizeEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class ResizeEventListener;

////////////////////////////////////////////////////////////////////////////////

#include "../IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void(sf::Vector2u)> ResizeCallback;

class ResizeEventListener : public IEventListener
{
	typedef std::vector<ResizeCallback> ResizeCallbacks;

public:
	ResizeEventListener() {}
	~ResizeEventListener() override {}

public:
	void handleEvent(sf::Event &e) {
		sf::Vector2u size(e.size.width, e.size.height);
		for (ResizeCallbacks::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
			(*it)(size);
		}
	}

	void registerCallback(ResizeCallback callback) {
		m_callbacks.push_back(callback);
	}

private:
	ResizeCallbacks m_callbacks;
};