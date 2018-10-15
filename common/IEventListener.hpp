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

#include <iostream>
#include <SFML/Window/Event.hpp>

////////////////////////////////////////////////////////////////////////////////

class IEventListener
{
public:
	virtual ~IEventListener() = default;

public:
	virtual void handleEvent(sf::Event &e) = 0;

	// virtual void registerCallback(F callback, Args&&... args) = 0;
	// template <typename F, typename... Args>
	// void registerCallback(F callback, Args&&... args)
	// {
	// 	std::cout << "yoinkers" << std::endl;
	// }
};