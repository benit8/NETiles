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

#include "Application.hpp"
#include "State.hpp"

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState(Application *app)
	: m_app(app)
	{
		m_eventHandler.onMouseMove(std::bind(&TestState::mouseMove, this, _1, _2));
		m_eventHandler.onMouseDown(std::bind(&TestState::mouseDown, this, _1, _2), sf::Mouse::Left);
		m_eventHandler.onMouseUp(std::bind(&TestState::mouseUp, this, _1, _2), sf::Mouse::Left);
		m_eventHandler.onMouseWheel(std::bind(&TestState::mouseScroll, this, _1, _2, _3));
		m_eventHandler.onMouseIn(std::bind(&TestState::mouseIn, this));
		m_eventHandler.onMouseOut(std::bind(&TestState::mouseOut, this));
		m_eventHandler.onText(std::bind(&TestState::text, this, _1));

		m_circle.setRadius(50);
		m_circle.setFillColor(sf::Color::Green);
	}

	~TestState() override
	{}

public:
	void update(const sf::Time delta) override {
	}

	void render(sf::RenderTarget &renderTarget) override {
		renderTarget.draw(m_circle);
	}

private:
	void mouseMove(sf::Vector2i pos, sf::Vector2i rel) {
		m_circle.setPosition(pos.x - m_circle.getRadius(), pos.y - m_circle.getRadius());
	}

	void mouseDown(sf::Mouse::Button btn, sf::Vector2i pos) {
		m_circle.setFillColor(sf::Color::Red);
	}

	void mouseUp(sf::Mouse::Button btn, sf::Vector2i pos) {
		m_circle.setFillColor(sf::Color::Green);
	}

	void mouseScroll(sf::Mouse::Wheel wheel, float delta, sf::Vector2i pos) {
		m_circle.setRadius(m_circle.getRadius() + delta);
		m_circle.setPosition(pos.x - m_circle.getRadius(), pos.y - m_circle.getRadius());
	}

	void mouseIn() {
		m_circle.setFillColor(sf::Color::Green);
	}

	void mouseOut() {
		m_circle.setFillColor(sf::Color::Yellow);
	}

	void text(unsigned c) {
		std::cout << "char: " << c << std::endl;
	}

private:
	Application *m_app;

	sf::CircleShape m_circle;
};