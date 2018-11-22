/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Window.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class Window;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

////////////////////////////////////////////////////////////////////////////////

class Window : public sf::RenderWindow
{
public:
	Window();
	Window(const std::string &title,
	       sf::VideoMode videoMode = sf::VideoMode::getDesktopMode(),
	       sf::Uint32 styles = sf::Style::Default,
	       const sf::ContextSettings &settings = sf::ContextSettings(24, 8, 0, 3, 0));
	~Window() = default;

public:
	void create(const std::string &title,
	            sf::VideoMode videoMode = sf::VideoMode::getDesktopMode(),
	            sf::Uint32 styles = sf::Style::Default,
	            const sf::ContextSettings &settings = sf::ContextSettings(24, 8, 0, 3, 0));

	void create(const std::string &title,
	            const sf::Vector2u &windowSize,
	            sf::Uint32 styles = sf::Style::Default,
	            const sf::ContextSettings &settings = sf::ContextSettings(24, 8, 0, 3, 0));

	void createBorderless(const std::string &title);
	void createFullscreen(const std::string &title);

	unsigned width() const;
	void width(int width);
	unsigned height() const;
	void height(int height);

	int top() const;
	void top(int top);
	int left() const;
	void left(int left);

	void setIcon(const std::string &path);
	void setCursor(sf::Cursor::Type type);
};