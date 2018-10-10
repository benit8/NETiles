/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** EventHandler.cpp
*/

#include "EventHandler.hpp"

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}


void EventHandler::handleEvent(sf::Event &e)
{
	switch (e.type) {
		case sf::Event::KeyPressed:
			triggerKeyDown(e.key);
			break;
	}
}


void EventHandler::onKeyDown(int key, int controlKeys, inputCallback callback)
{
	m_keybinds[std::make_pair(key, controlKeys)].push_back(callback);
}


void EventHandler::triggerKeyDown(sf::Event::KeyEvent &key)
{
	auto p = std::make_pair<int, int>(key.code, 0);
	if (key.control) p.second |= Ctrl;
	if (key.shift)   p.second |= Shift;
	if (key.alt)     p.second |= Alt;
	if (key.system)  p.second |= System;

	for (size_t i = 0; i < m_keybinds[p].size(); ++i) {
		m_keybinds[p][i]();
	}
}