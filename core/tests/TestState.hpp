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
	void closeOnEscape(sf::Keyboard::Key key, int ctrlKeys);
	void onResize_callback(sf::Vector2u pos);

private:
	Application *m_app;
	GUI::Box m_box;
	GUI::Input m_1;
	GUI::Input m_2;
	GUI::Input m_3;
};