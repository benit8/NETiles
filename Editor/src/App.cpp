/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** App.cpp
*/

#include "App.hpp"

////////////////////////////////////////////////////////////////////////////////

App::App(const std::string &appName, std::vector<std::string> &appArgs)
: m_shouldClose(false)
, m_shouldPop(false)
, m_appName(appName)
, m_appArgs(appArgs)
{
	m_videoMode = sf::VideoMode::getDesktopMode();
	m_settings = sf::ContextSettings(24, 8, 0, 3, 0);
}

App::~App()
{
	if (m_window.isOpen())
		m_window.close();
}

////////////////////////////////////////////////////////////////////////////////

int App::run()
{
	int exitCode = EXIT_FAILURE;

	launch();

	if (m_states.empty()) {
		throw std::runtime_error("No states are registered");
	}

	while (m_window.isOpen() && !m_states.empty()) {
		handleEvents();

		currentState().update();
		m_window.clear(sf::Color::Black);
		currentState().render(m_window);
		m_window.display();

		if (m_shouldPop) {
			m_shouldPop = false;
			m_states.pop_back();
		}
		if (m_shouldClose) {
			exitCode = EXIT_SUCCESS;
			break;
		}
	}

	if (m_window.isOpen())
		m_window.close();

	return exitCode;
}

void App::requestClose()
{
	m_shouldClose = true;
}

////////////////////////////////////////////////////////////////////////////////

void App::launch()
{
	m_window.create(m_videoMode, "Voxel Engine", sf::Style::Default, m_settings);
	m_window.setActive(true);
	m_window.setFramerateLimit(60);

	pushState<MainState>();
}

void App::handleEvents()
{
	sf::Event e;

	while (m_window.pollEvent(e)) {
		switch (e.type) {
			case sf::Event::Closed:
				m_shouldClose = true;
				break;
			default:
				break;
		}

		currentState().handleEvent(e);
	}
}

template<typename S, typename... Args>
void App::pushState(Args&&... args)
{
	m_states.push_back(std::make_unique<S>(*this, std::forward<Args>(args)...));
}

void App::popState()
{
	m_shouldPop = true;
}

State &App::currentState()
{
	return *m_states.back();
}