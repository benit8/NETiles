/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Display.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Utils/Singleton.hpp"

////////////////////////////////////////////////////////////////////////////////

class Display : public Singleton
{
public:
	static void create();
	static void create(const sf::Vector2i &windowSize);
	static void create(const sf::VideoMode &videoMode);
	static void close();
	static bool isOpen();
	static void clear(sf::Color color = sf::Color::Black);
	static void refresh();
	static bool pollEvent(sf::Event &e);
	static void draw(const sf::Drawable &object);
	static void drawAbsolute(const sf::Drawable &object);

	static sf::RenderWindow &getWindow();
	static sf::Vector2u getWindowSize();
	static const sf::View &getView();
	static void setView(const sf::View &view);
	static void setDefaultView();
	static void setViewSize(int width, int height);
	static void setViewSize(const sf::Vector2i &size);
	static void setViewCenter(int x, int y);
	static void setViewCenter(const sf::Vector2i &center);
	static void zoomView(float factor);

	static sf::Vector2i getMousePosition();
	static void setMousePosition(int x, int y);
	static void setMousePosition(const sf::Vector2i& pos);

private:
	Display();

private:
	static sf::RenderWindow m_window;

	static float m_zoom;
};