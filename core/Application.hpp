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

class Application
{
public:
	Application(int argc, char *argv[]);
	~Application();

public:
	int run();

	bool isRunning() const;

private:
	void launch();
	void processEvents();

protected:
	std::string m_appName;
	std::vector<std::string> m_args;
	std::string m_binName;

	bool m_shouldClose;
	Window m_window;
	FPSCounter m_fpsCounter;
	StateManager m_stateManager;
};