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
#include "../GUI/Button.hpp"
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
	void onClick_callback1(sf::Mouse::Button btn, sf::Vector2i pos);
	void onClick_callback2(sf::Mouse::Button btn, sf::Vector2i pos);
	void onClick_callback3(sf::Mouse::Button btn, sf::Vector2i pos);
	void onResize_callback(sf::Vector2u pos);

private:
	Application *m_app;
	GUI::Box m_box;
	GUI::Button m_btn1;
	GUI::Button m_btn2;
	GUI::Button m_btn3;
};