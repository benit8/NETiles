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
	m_eventHandler.onMouseDown(BIND2(TestStateN::quit), sf::Mouse::Button::Left);

	m_guiRoot.addChild(&m_box);
	m_box.setSize(Window::getMainWindow()->getWidth(), Window::getMainWindow()->getHeight());
	m_box.setBackgroundColor(sf::Color(25 + 75 * n, 0, 0, 100));

	FontLoader::loadFromSystem(m_font, "Consolas");
	m_text.setFont(m_font);
	m_text.setString(std::to_string(n));
	m_text.setCharacterSize(150);

	sf::FloatRect textBounds = m_text.getLocalBounds();
	m_text.setPosition({
		(m_box.width() - textBounds.width) / 2.f,
		(m_box.height() - textBounds.height) / 2.f - textBounds.top
	});
}

////////////////////////////////////////////////////////////////////////////////

void TestStateN::update(const sf::Time &delta)
{
}

void TestStateN::render(sf::RenderTarget &renderTarget) {
	m_guiRoot.render(renderTarget, true);
	renderTarget.draw(m_text);
}

////////////////////////////////////////////////////////////////////////////////

void TestStateN::quit(sf::Mouse::Button btn, sf::Vector2i pos)
{
	m_app->popState();
}