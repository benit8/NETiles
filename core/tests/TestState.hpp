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

#include "../State.hpp"
#include "../Application.hpp"

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState(Application *app);
	~TestState() override = default;

public:
	void update(const sf::Time &delta) override;

private:
	void updatePositions(sf::Vector2u pos);
	void closeOnEscape();
	void onEnter(const std::string &value);
	void onClick(sf::Vector2i pos);

private:
	Application *m_app;
	GUI::Box m_box;
	GUI::Input m_input;
	GUI::Button m_button;
};