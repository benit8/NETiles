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

#include "FPSCounter.hpp"
#include "StateManager.hpp"

////////////////////////////////////////////////////////////////////////////////

class Application
{
public:
	Application(int argc, char *argv[]);
	~Application();

public:
	int run();

	bool isRunning() const;
	sf::RenderWindow &getWindow();

private:
	void launch();
	void processEvents();

private:
	std::string m_binName;
	std::vector<std::string> m_args;

	bool m_shouldClose;
	sf::RenderWindow m_window;
	FPSCounter m_fpsCounter;
	StateManager m_stateManager;
};