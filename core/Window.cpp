/*
** EPITECH PROJECT, 2018
** Netiles
** File description:
** Window.cpp
*/

#include "Window.hpp"

////////////////////////////////////////////////////////////////////////////////

Window *Window::s_mainWindow = nullptr;

void Window::setMainWindow(Window *window)
{
	s_mainWindow = window;
}

Window *Window::getMainWindow()
{
	return s_mainWindow;
}

////////////////////////////////////////////////////////////////////////////////

Window::Window()
: sf::RenderWindow()
{
}

Window::Window(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, sf::ContextSettings settings)
: sf::RenderWindow(videoMode, title, styles, settings)
{
}

////////////////////////////////////////////////////////////////////////////////

void Window::create(const std::string &title, sf::VideoMode videoMode, sf::Uint32 styles, sf::ContextSettings settings)
{
	sf::RenderWindow::create(videoMode, title, styles, settings);
}

void Window::createDefault(const std::string &title)
{
	sf::RenderWindow::create(sf::VideoMode(1280, 720), title, sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 0));
}

void Window::createFullscreen(const std::string &title)
{
	sf::RenderWindow::create(sf::VideoMode::getFullscreenModes()[0], title, sf::Style::Fullscreen, sf::ContextSettings(24, 8, 0, 3, 0));
}

void Window::createBorderless(const std::string &title)
{
	sf::RenderWindow::create(sf::VideoMode::getFullscreenModes()[0], title, sf::Style::None, sf::ContextSettings(24, 8, 0, 3, 0));
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