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
#include "../GUI/Box.hpp"
#include "../GUI/Button.hpp"

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState(Application *app);
	~TestState() override = default;

public:
	void update(const sf::Time delta) override;
	void render(sf::RenderTarget &renderTarget) override;

private:
	void onClick_callback(sf::Mouse::Button btn, sf::Vector2i pos);

private:
	Application *m_app;
	GUI::Box m_box;
	GUI::Button m_btn;
};