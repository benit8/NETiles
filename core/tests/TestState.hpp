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

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState(Application *app)
	: m_app(app)
	{
		GUI::getRoot()->addChild(&m_box);
		m_box.setSize(250, 100);

		// m_box.addChild(m_btn);
		// m_btn.setPosition(10, 10);
		// m_btn.setLabel("TEST BUTTON");
		// m_btn.onClick.connect(this, &TestState::callback_ButtonClicked);
	}

	~TestState() override
	{}

public:
	void update(const sf::Time delta) override {
	}

	void render(sf::RenderTarget &renderTarget) override {
		m_box.render(renderTarget);
	}

private:
	void callback_ButtonClicked(sf::Mouse::Button btn, sf::Vector2i pos)
	{
		std::cout << "button clicked" << std::endl;
	}

private:
	Application *m_app;
	GUI::Box m_box;
	// GUI::Button m_btn;
};