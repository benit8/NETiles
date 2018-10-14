/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** TestState.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class TestState;

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <iostream>

#include "Application.hpp"
#include "State.hpp"

// Never do that, only villains do that
using namespace std::placeholders;

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState(Application *app)
	: m_app(app)
	{
		m_eventHandler.on(sf::Event::KeyPressed, std::bind(&TestState::closeApp, this, _1, _2), sf::Keyboard::Q, Keyboard::Ctrl);
		m_eventHandler.on(sf::Event::MouseMoved, std::bind(&TestState::whereIsMouse, this, _1, _2));
	}

	~TestState() override
	{}

public:
	void update(const sf::Time delta) override {
		// std::cout << "update" << std::endl;
	}

	void render() override {
		// std::cout << "render" << std::endl;
	}

private:
	void closeApp(int key, int ctrlKeys) {
		m_app->getWindow().close();
	}

	void whereIsMouse(sf::Vector2i pos, sf::Vector2i rel) {
		std::cout << pos.x << " " << pos.y << std::endl;
	}

private:
	Application *m_app;
};