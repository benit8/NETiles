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
	       sf::ContextSettings settings = sf::ContextSettings(24, 8, 0, 3, 0));
	~Window() = default;

public:
	static void setMainWindow(Window *window);
	static Window *getMainWindow();

public:
	void create(const std::string &title,
	            sf::VideoMode videoMode = sf::VideoMode::getDesktopMode(),
	            sf::Uint32 styles = sf::Style::Default,
	            sf::ContextSettings settings = sf::ContextSettings(24, 8, 0, 3, 0));

	void createDefault(const std::string &title);
	void createFullscreen(const std::string &title);
	void createBorderless(const std::string &title);

	unsigned getWidth() const;
	void setWidth(int width);
	unsigned getHeight() const;
	void setHeight(int height);

	int getTop() const;
	void setTop(int top);
	int getLeft() const;
	void setLeft(int left);

	void setIcon(const std::string &path);

private:
	static Window *s_mainWindow;
};