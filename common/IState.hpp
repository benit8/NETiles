/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** IState.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class IState;

////////////////////////////////////////////////////////////////////////////////

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "EventHandler.hpp"

////////////////////////////////////////////////////////////////////////////////

class IState
{
public:
	virtual ~IState() = default;

public:
	virtual void create() = 0;
	virtual void update(const sf::Time delta) = 0;
	virtual void handleEvent(sf::Event &e) = 0;
	virtual void render(sf::RenderTarget &renderTarget) = 0;
	virtual void destroy() = 0;
};