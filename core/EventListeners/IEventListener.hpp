/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** IEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class IEventListener;

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <map>
#include <vector>

#include <SFML/Window/Event.hpp>

////////////////////////////////////////////////////////////////////////////////

class IEventListener
{
public:
	virtual ~IEventListener() = default;

public:
	virtual void handleEvent(sf::Event &) = 0;
};