/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** App.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class App;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "States.hpp"

////////////////////////////////////////////////////////////////////////////////

class App
{
public:
	App(const std::string &appName, std::vector<std::string> &appArgs);
	~App();

	int run();
	void requestClose();

private:
	void launch();
	void handleEvents();

	template<typename S, typename... Args>
	void pushState(Args&&... args);
	void popState();
	State &currentState();

private:
	bool m_shouldClose;
	bool m_shouldPop;
	std::string m_appName;
	std::vector<std::string> m_appArgs;

	sf::VideoMode m_videoMode;
	sf::ContextSettings m_settings;
	sf::RenderWindow m_window;

	std::vector<std::unique_ptr<State>> m_states;

	const sf::Time frameTime = sf::seconds(1 / 60.0f);
};