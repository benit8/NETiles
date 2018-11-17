/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** KeyEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class KeyEventListener;

////////////////////////////////////////////////////////////////////////////////

#include "IEventListener.hpp"

////////////////////////////////////////////////////////////////////////////////

class Keyboard
{
public:
	enum CtrlKey
	{
		Ctrl	= (1 << 0),
		Shift	= (1 << 1),
		Alt	= (1 << 2),
		System	= (1 << 3),
	};
};

typedef std::function<void()> KeyCallback;

class KeyEventListener : public IEventListener
{
	typedef std::map<std::pair<sf::Keyboard::Key, int>, std::vector<KeyCallback>> KeyCallbacks;

public:
	KeyEventListener() {}
	~KeyEventListener() override {}

public:
	void handleEvent(sf::Event &e) override
	{
		auto key = keyFromEvent(e.key);
		KeyCallbacks::iterator it = m_callbacks.find(key);
		if (it != m_callbacks.end()) {
			for (unsigned i = 0; i < m_callbacks[key].size(); ++i)
				(m_callbacks[key][i])();
		}
	}

	void registerCallback(KeyCallback callback, sf::Keyboard::Key key, int ctrlKeys = 0) {
		m_callbacks[std::make_pair(key, ctrlKeys)].push_back(callback);
	}

private:
	std::pair<sf::Keyboard::Key, int> keyFromEvent(sf::Event::KeyEvent &e)
	{
		std::pair<sf::Keyboard::Key, int> p;

		p.first = e.code;
		if (e.control) p.second |= Keyboard::Ctrl;
		if (e.shift)   p.second |= Keyboard::Shift;
		if (e.alt)     p.second |= Keyboard::Alt;
		if (e.system)  p.second |= Keyboard::System;

		return p;
	}

private:
	KeyCallbacks m_callbacks;
};