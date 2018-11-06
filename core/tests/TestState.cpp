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
	GUI::getRoot()->addChild(&m_box);
	m_box.setSize(1280, 720);

	m_box.addChild(&m_btn);
	m_btn.setLabel("TEST BUTTON");
	m_btn.setSize({400, 50});
	m_btn.setPosition((m_box.getWidth() - m_btn.getWidth()) / 2, 100);
	m_btn.onClick.connect(this, &TestState::onClick_callback);
}

////////////////////////////////////////////////////////////////////////////////

void TestState::update(const sf::Time delta)
{
}

void TestState::render(sf::RenderTarget &renderTarget)
{
	m_box.render(renderTarget);
}

////////////////////////////////////////////////////////////////////////////////

void TestState::onClick_callback(sf::Mouse::Button btn, sf::Vector2i pos)
{
	std::cout << "button clicked" << std::endl;
}