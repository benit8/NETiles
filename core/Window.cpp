/*
** EPITECH PROJECT, 2018
** Netiles
** File description:
** Window.cpp
*/

#include "Window.hpp"

////////////////////////////////////////////////////////////////////////////////

Window::Window()
: sf::RenderWindow()
{
}

Window::Window(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, const sf::ContextSettings &settings)
: sf::RenderWindow(videoMode, title, styles, settings)
{
}

////////////////////////////////////////////////////////////////////////////////

void Window::create(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, const sf::ContextSettings &settings)
{
	sf::RenderWindow::create(videoMode, title, styles, settings);
}

void Window::create(const std::string &title, const sf::Vector2u &windowSize, sf::Uint32 styles, const sf::ContextSettings &settings)
{
	create(title, sf::VideoMode(windowSize.x, windowSize.y), styles, settings);
}

void Window::createBorderless(const std::string &title)
{
	create(title, sf::VideoMode::getFullscreenModes()[0], sf::Style::None);
}

void Window::createFullscreen(const std::string &title)
{
	create(title, sf::VideoMode::getFullscreenModes()[0], sf::Style::Fullscreen);
}


unsigned Window::width() const
{
	return getSize().x;
}

void Window::width(int width)
{
	setSize(sf::Vector2u(width, height()));
}

unsigned Window::height() const
{
	return getSize().y;
}

void Window::height(int height)
{
	setSize(sf::Vector2u(width(), height));
}


int Window::left() const
{
	return getPosition().y;
}

void Window::left(int left)
{
	setPosition(sf::Vector2i(top(), left));
}

int Window::top() const
{
	return getPosition().y;
}

void Window::top(int top)
{
	setPosition(sf::Vector2i(top, left()));
}


void Window::setIcon(const std::string &path)
{
	sf::Image icon;

	if (!icon.loadFromFile(path)) {
		std::cerr << "Could not open '" << path << "' for window icon" << std::endl;
		return;
	}

	sf::Vector2u size = icon.getSize();
	sf::RenderWindow::setIcon(size.x, size.y, icon.getPixelsPtr());
}

void Window::setCursor(sf::Cursor::Type type)
{
	sf::Cursor cursor;

	if (cursor.loadFromSystem(type))
		setMouseCursor(cursor);
}