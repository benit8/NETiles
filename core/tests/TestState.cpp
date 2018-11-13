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
	// m_eventHandler.onResize(BIND1(TestState::onResize_callback));
	m_eventHandler.onKeyDown(BIND2(TestState::closeOnEscape), sf::Keyboard::Escape);

	// m_guiRoot.addChild(&m_box);
	// m_box.setSize(1280, 720);

	m_guiRoot.addChild(&m_1);
	m_guiRoot.addChild(&m_2);
	m_guiRoot.addChild(&m_3);

	m_1.setPlaceholder("Type text here...");
	m_2.setPlaceholder("Type text here...");
	m_3.setPlaceholder("Type text here...");

	m_2.setCharacterSize(32);
	m_3.setCharacterSize(50);

	m_2.setSize({400, 50});
	m_3.setSize({600, 75});

	m_1.setPosition({(1280 - m_1.width()) / 2, 100});
	m_2.setPosition({(1280 - m_2.width()) / 2, 165});
	m_3.setPosition({(1280 - m_3.width()) / 2, 250});
}

////////////////////////////////////////////////////////////////////////////////

void TestState::update(const sf::Time &delta)
{
}

////////////////////////////////////////////////////////////////////////////////

void TestState::closeOnEscape(sf::Keyboard::Key key, int ctrlKeys)
{
	m_app->close();
}

void TestState::onResize_callback(sf::Vector2u size)
{
	m_1.setPosition({(size.x - m_1.width()) / 2, 100});
	m_2.setPosition({(size.x - m_2.width()) / 2, 175});
	m_3.setPosition({(size.x - m_3.width()) / 2, 250});
}