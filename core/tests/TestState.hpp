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
#include "../GUI/GUI.hpp"

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState(Application *app);
	~TestState() override = default;

private:
	void updatePositions(sf::Vector2u pos);
	void closeOnEscape();
	void onEnter(const std::string &);
	void onClick(sf::Vector2i);

private:
	Application *m_app;
	GUI::Box m_box;
	GUI::Input m_input;
	GUI::Button m_button;
	GUI::MessageBox *m_msgBox;
};