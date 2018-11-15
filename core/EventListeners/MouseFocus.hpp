/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** MouseFocusEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class MouseFocusEventListener;

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void()> MouseFocusCallback;

class MouseFocusEventListener : public IEventListener
{
	typedef std::vector<MouseFocusCallback> MouseFocusCallbacks;

public:
	MouseFocusEventListener() {}
	~MouseFocusEventListener() override {}

public:
	void handleEvent(sf::Event &e) {
		for (MouseFocusCallbacks::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			(*it)();
	}

	void registerCallback(MouseFocusCallback callback) {
		m_callbacks.push_back(callback);
	}

private:
	MouseFocusCallbacks m_callbacks;
};