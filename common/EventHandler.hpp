/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** EventHandler.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class EventHandler;

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <map>
#include <vector>

#include <SFML/Window/Event.hpp>

////////////////////////////////////////////////////////////////////////////////

class EventHandler
{
public:
	enum ControlKey
	{
		Ctrl	= (1 << 0),
		Shift	= (1 << 1),
		Alt	= (1 << 2),
		System	= (1 << 3),
	};

	typedef std::function<void()> inputCallback;

public:
	EventHandler();
	~EventHandler();

public:
	void handleEvent(sf::Event &e);

	void onKeyDown(int key, int controlKeys, inputCallback callback);
	// void onKeyUp(int key, int controlKeys, inputCallback callback);

	void triggerKeyDown(sf::Event::KeyEvent &key);

private:
	std::map<std::pair<int, int>, std::vector<inputCallback>> m_keybinds;
};