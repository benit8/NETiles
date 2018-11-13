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

	m_guiRoot.addChild(&m_box);
	m_box.setSize(1280, 720);

	m_box.addChild(&m_btn1);
	m_box.addChild(&m_btn2);
	m_box.addChild(&m_btn3);

	m_btn1.setLabel("TEST BUTTON 1");
	m_btn2.setLabel("TEST BUTTON 2");
	m_btn3.setLabel("TEST BUTTON 3");

	m_btn1.setSize({400, 50});
	m_btn2.setSize({400, 50});
	m_btn3.setSize({400, 50});

	m_btn1.setPosition((m_box.width() - m_btn1.width()) / 2, 100);
	m_btn2.setPosition((m_box.width() - m_btn2.width()) / 2, 175);
	m_btn3.setPosition((m_box.width() - m_btn3.width()) / 2, 250);

	m_btn1.onClick.connect(this, &TestState::onClick_callback1);
	m_btn2.onClick.connect(this, &TestState::onClick_callback2);
	m_btn3.onClick.connect(this, &TestState::onClick_callback3);
}

////////////////////////////////////////////////////////////////////////////////

void TestState::update(const sf::Time &delta)
{
}

////////////////////////////////////////////////////////////////////////////////

void TestState::onClick_callback1(sf::Mouse::Button btn, sf::Vector2i pos) {
	m_app->pushState<TestStateN>(m_app, 1);
}

void TestState::onClick_callback2(sf::Mouse::Button btn, sf::Vector2i pos) {
	m_app->pushState<TestStateN>(m_app, 2);
}

void TestState::onClick_callback3(sf::Mouse::Button btn, sf::Vector2i pos) {
	m_app->pushState<TestStateN>(m_app, 3);
}

void TestState::onResize_callback(sf::Vector2u size)
{
	m_box.setSize(size.x, size.y);
	m_btn1.setPosition((m_box.width() - m_btn1.width()) / 2, 100);
	m_btn2.setPosition((m_box.width() - m_btn2.width()) / 2, 175);
	m_btn3.setPosition((m_box.width() - m_btn3.width()) / 2, 250);
}