/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** TestState.cpp
*/

#include "TestState.hpp"

////////////////////////////////////////////////////////////////////////////////

TestState::TestState(Application *app)
: m_app(app)
{
	m_eventHandler.onResize(BIND1(TestState::onResize_callback));
	m_eventHandler.onKeyDown(BIND(TestState::closeOnEscape), sf::Keyboard::Escape);

	m_guiRoot.addChild(&m_box);
	m_box.setSize(1280, 720);
	m_box.setBackgroundImage("bg.png");

	m_box.addChild(&m_1);
	m_1.setPosition({(1280 - m_1.width()) / 2.f, 250});
	m_1.setSize({600, 60});
	m_1.setPlaceholder("Type text here...");
	m_1.setCharacterSize(30);
	m_1.setValue("abcdefghijklmnopqrstuvwxyzmlkakfjri");

	m_1.onEnter.connect(this, &TestState::onEnter);
}

////////////////////////////////////////////////////////////////////////////////

void TestState::update(const sf::Time &delta)
{
}

////////////////////////////////////////////////////////////////////////////////

void TestState::closeOnEscape()
{
	m_app->close();
}

void TestState::onResize_callback(sf::Vector2u size)
{
	m_box.setSize(size.x, size.y);
	m_1.setPosition({(size.x - m_1.width()) / 2.f, 250});
}

void TestState::onEnter(const std::string &value)
{
	std::cout << "'" << value << "'" << std::endl;
}