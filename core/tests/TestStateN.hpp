/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** TestStateN.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class TestStateN;

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../Application.hpp"
#include "../State.hpp"
#include "../Window.hpp"
#include "../GUI/Box.hpp"

////////////////////////////////////////////////////////////////////////////////

class TestStateN : public State
{
public:
	TestStateN(Application *app, int n);
	~TestStateN() override = default;

public:
	void update(const sf::Time &delta) override;
	void render(sf::RenderTarget &renderTarget) override;

private:
	void quit(sf::Mouse::Button btn, sf::Vector2i pos);

private:
	Application *m_app;
	GUI::Box m_box;

	sf::Font m_font;
	sf::Text m_text;

	int m_n;
};