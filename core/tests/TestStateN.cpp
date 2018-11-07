/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** TestStateN.cpp
*/

#include "TestStateN.hpp"

////////////////////////////////////////////////////////////////////////////////

TestStateN::TestStateN(Application *app, int n)
: m_app(app)
, m_n(n)
{
	std::cout << n << std::endl;
	m_eventHandler.onMouseDown(BIND2(TestStateN::quit), sf::Mouse::Button::Left);

	m_guiRoot.addChild(&m_box);
	m_box.setSize(Window::getMainWindow()->getWidth(), Window::getMainWindow()->getHeight());
}

////////////////////////////////////////////////////////////////////////////////

void TestStateN::update(const sf::Time &delta)
{
}

void TestStateN::render(sf::RenderTarget &renderTarget)
{
	m_guiRoot.render(renderTarget);
}

////////////////////////////////////////////////////////////////////////////////

void TestStateN::quit(sf::Mouse::Button btn, sf::Vector2i pos)
{
	m_app->getStateManager().pop();
}