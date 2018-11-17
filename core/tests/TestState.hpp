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

#include <SFML/Graphics.hpp>

#include "../Application.hpp"
#include "../State.hpp"
#include "../Window.hpp"
#include "../GUI/Box.hpp"
#include "../GUI/Input.hpp"
#include "TestStateN.hpp"

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState(Application *app);
	~TestState() override = default;

public:
	void update(const sf::Time &delta) override;

private:
	void closeOnEscape();
	void onResize_callback(sf::Vector2u pos);
	void onEnter(const std::string &value);

private:
	Application *m_app;
	GUI::Box m_box;
	GUI::Input m_1;
};