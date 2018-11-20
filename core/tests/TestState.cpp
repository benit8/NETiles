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
	m_eventHandler.onResize(BIND1(TestState::updatePositions));
	m_eventHandler.onKeyDown(BIND(TestState::closeOnEscape), sf::Keyboard::Escape);

	m_guiRoot.addChild(&m_box);
	m_box.setBackgroundImage("bg.png");

	m_box.addChild(&m_input);
	m_input.setSize({600, 60});
	m_input.setPlaceholder("Type text here...");
	m_input.setCharacterSize(30);
	m_input.setValue("abcdefghijklmnopqrstuvwxyzmlkakfjri");
	m_input.onEnter.connect(this, &TestState::onEnter);

	m_box.addChild(&m_button);
	m_button.setSize({600, 60});
	m_button.setLabel("Click here");
	m_button.setLabelSize(24);
	m_button.onClick.connect(this, &TestState::onClick);

	updatePositions({1280, 720});
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

void TestState::updatePositions(sf::Vector2u size)
{
	m_box.setSize(size.x, size.y);
	m_input.setPosition({(size.x - m_input.width()) / 2.f, 250});
	m_button.setPosition({(size.x - m_button.width()) / 2.f, 340});
}

void TestState::onEnter(const std::string &value)
{
	std::cout << "'" << value << "'" << std::endl;
}

void TestState::onClick(sf::Vector2i pos)
{
	std::cout << "'" << m_input.getValue() << "'" << std::endl;
}