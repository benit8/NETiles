/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Application.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class Application;

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Window.hpp"
#include "FPSCounter.hpp"
#include "StateManager.hpp"

////////////////////////////////////////////////////////////////////////////////

class Application : public StateManager
{
public:
	enum WindowMode
	{
		Windowed,
		Borderless,
		Fullscreen
	};

public:
	Application(int argc, char *argv[]);
	~Application();

public:
	int run();
	void close();

	bool isRunning() const;
	void setAppName(const std::string &name);
	const std::string &getAppName() const;

	void setWindowMode(WindowMode mode, const sf::Vector2u &size = sf::Vector2u(0, 0));

	static sf::Vector2u MainWindowSize();
	static unsigned MainWindowWidth();
	static unsigned MainWindowHeight();
	static void SetCursor(sf::Cursor::Type cursor);

private:
	void launch();
	void processEvents();

	static Application *Instance();

protected:
	std::vector<std::string> m_args;
	std::string m_appName;
	std::string m_binName;
	bool m_shouldClose;

	Window m_window;
	WindowMode m_windowMode;
	sf::Vector2u m_windowStartupSize;
	FPSCounter m_fpsCounter;

	static Application *s_instance;
};