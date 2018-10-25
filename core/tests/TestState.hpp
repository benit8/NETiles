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

////////////////////////////////////////////////////////////////////////////////

#define BIND(C) std::bind(&(C), this)
#define BIND1(C) std::bind(&(C), this, _1)
#define BIND2(C) std::bind(&(C), this, _1, _2)
#define BIND3(C) std::bind(&(C), this, _1, _2, _3)

////////////////////////////////////////////////////////////////////////////////

class TestState : public State
{
public:
	TestState(Application *app)
	: m_app(app)
	{
		m_eventHandler.onMouseMove(BIND2(TestState::mouseMove));
		m_eventHandler.onMouseDown(BIND2(TestState::mouseDown), sf::Mouse::Left);
		m_eventHandler.onMouseUp(BIND2(TestState::mouseUp), sf::Mouse::Left);
		m_eventHandler.onMouseWheel(BIND3(&TestState::mouseScroll));
		m_eventHandler.onMouseIn(BIND(&TestState::mouseIn));
		m_eventHandler.onMouseOut(BIND(&TestState::mouseOut));

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

private:
	Application *m_app;

	sf::CircleShape m_circle;
};