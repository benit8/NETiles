/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** TextEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class TextEventListener;

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

typedef std::function<void(unsigned)> TextCallback;

class TextEventListener : public IEventListener
{
	typedef std::vector<TextCallback> TextCallbacks;

public:
	TextEventListener() {}
	~TextEventListener() override {}

public:
	void handleEvent(sf::Event &e) {
		for (TextCallbacks::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			(*it)(e.text.unicode);
	}

	void registerCallback(TextCallback callback) {
		m_callbacks.push_back(callback);
	}

private:
	TextCallbacks m_callbacks;
};