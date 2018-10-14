/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** KeyDownEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class KeyDownEventListener;

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <map>
#include <vector>

#include <SFML/Window/Event.hpp>

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


class KeyDownEventListener : public IEventListener
{
	typedef std::function<void(int, int)> KeyDownCallback;
	typedef std::map<std::pair<int, int>, std::vector<KeyDownCallback>> KeyDownCallbacks;

public:
	KeyDownEventListener() {}
	~KeyDownEventListener() override {}

public:
	void handleEvent(sf::Event &e) override
	{
		auto key = keyFromEvent(e.key);
		KeyDownCallbacks::iterator it = m_callbacks.find(key);
		if (it != m_callbacks.end()) {
			for (unsigned i = 0; i < m_callbacks[key].size(); ++i)
				(m_callbacks[key][i])(key.first, key.second);
		}
	}

	template <typename F>
	void registerCallback(F callback, int key, int ctrlKeys = 0) {
		m_callbacks[std::make_pair(key, ctrlKeys)].push_back(callback);
	}

private:
	std::pair<int, int> keyFromEvent(sf::Event::KeyEvent &e)
	{
		std::pair<int, int> p;

		p.first = e.code;
		if (e.control) p.second |= Keyboard::Ctrl;
		if (e.shift)   p.second |= Keyboard::Shift;
		if (e.alt)     p.second |= Keyboard::Alt;
		if (e.system)  p.second |= Keyboard::System;

		return p;
	}

private:
	KeyDownCallbacks m_callbacks;
};