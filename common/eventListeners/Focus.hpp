/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** FocusEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class FocusEventListener;

////////////////////////////////////////////////////////////////////////////////

#include "../IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void()> FocusCallback;

class FocusEventListener : public IEventListener
{
	typedef std::vector<FocusCallback> FocusCallbacks;

public:
	FocusEventListener() {}
	~FocusEventListener() override {}

public:
	void handleEvent(sf::Event &e) {
		for (FocusCallbacks::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
			(*it)();
		}
	}

	void registerCallback(FocusCallback callback) {
		m_callbacks.push_back(callback);
	}

private:
	FocusCallbacks m_callbacks;
};