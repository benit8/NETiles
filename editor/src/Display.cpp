/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Display.cpp
*/

#include "Display.hpp"

////////////////////////////////////////////////////////////////////////////////

sf::RenderWindow Display::m_window;
float Display::m_zoom = 1.0f;

////////////////////////////////////////////////////////////////////////////////

void Display::create()
{
	create(sf::VideoMode::getDesktopMode());
}

void Display::create(const sf::Vector2i &windowSize)
{
	create(sf::VideoMode(windowSize.x, windowSize.y, 32));
}

void Display::create(const sf::VideoMode &videoMode)
{
	sf::ContextSettings settings(24, 8, 0, 3, 0);

	m_window.create(videoMode, "NETiles Editor", sf::Style::Default, settings);
	m_window.setFramerateLimit(60);
	m_window.setKeyRepeatEnabled(false);
}

void Display::close()
{
	m_window.close();
}

bool Display::isOpen()
{
	return m_window.isOpen();
}

void Display::clear(sf::Color color)
{
	m_window.clear(color);
}

void Display::refresh()
{
	m_window.display();
}

bool Display::pollEvent(sf::Event &e)
{
	return m_window.pollEvent(e);
}

void Display::draw(const sf::Drawable &object)
{
	m_window.draw(object);
}

void Display::drawAbsolute(const sf::Drawable &object)
{
	sf::View savedView = getView();
	setDefaultView();
	draw(object);
	setView(savedView);
}

////////////////////////////////////////////////////////////////////////////////

sf::RenderWindow &Display::getWindow()
{
	return m_window;
}

sf::Vector2u Display::getWindowSize()
{
	return m_window.getSize();
}

const sf::View &Display::getView()
{
	return m_window.getView();
}

void Display::setView(const sf::View &view)
{
	m_window.setView(view);
}

void Display::setDefaultView()
{
	sf::View view(sf::FloatRect(0, 0, m_window.getSize().x, m_window.getSize().y));
	m_window.setView(view);
}

void Display::setViewSize(int width, int height)
{
	sf::View v = getView();
	v.setSize(width, height);
	v.zoom(m_zoom);
	setView(v);
}

void Display::setViewSize(const sf::Vector2i &size)
{
	setViewSize(size.x, size.y);
}

void Display::setViewCenter(int x, int y)
{
	sf::View v = getView();
	v.setCenter(x, y);
	setView(v);
}

void Display::setViewCenter(const sf::Vector2i &center)
{
	setViewCenter(center.x, center.y);
}

void Display::zoomView(float factor)
{
	sf::View v = m_window.getView();
	m_zoom *= factor;
	v.zoom(factor);
	m_window.setView(v);
}

float Display::getZoom()
{
	return m_zoom;
}

////////////////////////////////////////////////////////////////////////////////

sf::Vector2i Display::getMousePosition()
{
	return sf::Mouse::getPosition(m_window);
}

void Display::setMousePosition(int x, int y)
{
	setMousePosition(sf::Vector2i(x, y));
}

void Display::setMousePosition(const sf::Vector2i &pos)
{
	sf::Mouse::setPosition(pos, m_window);
}