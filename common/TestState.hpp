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
#include "IState.hpp"

////////////////////////////////////////////////////////////////////////////////

class TestState : public IState
{
public:
	TestState(Application *app)
	: m_app(app)
	{
		m_eventHandler.onKeyDown(sf::Keyboard::Q, EventHandler::Ctrl, std::bind(&TestState::closeApp, this));
	}

	~TestState() override
	{}

public:
	void update(const sf::Time delta) override {
		std::cout << "update" << std::endl;
	}

	void render() override {
		std::cout << "render" << std::endl;
	}

private:
	void closeApp() {
		m_app->getWindow().close();
	}

private:
	Application *m_app;
};