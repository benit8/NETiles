/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** CloseEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class CloseEventListener;

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void()> CloseCallback;

class CloseEventListener : public IEventListener
{
	typedef std::vector<CloseCallback> CloseCallbacks;

public:
	CloseEventListener() {}
	~CloseEventListener() override {}

public:
	void handleEvent(sf::Event &) {
		for (CloseCallbacks::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			(*it)();
	}

	void registerCallback(CloseCallback callback) {
		m_callbacks.push_back(callback);
	}

private:
	CloseCallbacks m_callbacks;
};