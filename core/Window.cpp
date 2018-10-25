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


unsigned Window::getWidth() const
{
	return getSize().x;
}

void Window::setWidth(int width)
{
	setSize(sf::Vector2u(width, getHeight()));
}

unsigned Window::getHeight() const
{
	return getSize().y;
}

void Window::setHeight(int height)
{
	setSize(sf::Vector2u(getWidth(), height));
}


int Window::getLeft() const
{
	return getPosition().y;
}

void Window::setLeft(int left)
{
	setPosition(sf::Vector2i(getTop(), left));
}

int Window::getTop() const
{
	return getPosition().y;
}

void Window::setTop(int top)
{
	setPosition(sf::Vector2i(top, getLeft()));
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