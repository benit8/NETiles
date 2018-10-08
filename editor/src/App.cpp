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
}

App::~App()
{
	if (Display::isOpen())
		Display::close();
}

////////////////////////////////////////////////////////////////////////////////

int App::run()
{
	int exitCode = EXIT_FAILURE;

	launch();

	if (m_states.empty()) {
		throw std::runtime_error("No states are registered");
	}

	while (Display::isOpen() && !m_states.empty()) {
		handleEvents();

		currentState().update();

		Display::clear();
		currentState().render(Display::getWindow());
		sfgui.Display(Display::getWindow());
		Display::refresh();

		if (m_shouldPop) {
			m_shouldPop = false;
			m_states.pop_back();
		}
		if (m_shouldClose || currentState().isRequestingClose()) {
			exitCode = EXIT_SUCCESS;
			break;
		}
	}

	if (Display::isOpen())
		Display::close();

	return exitCode;
}

////////////////////////////////////////////////////////////////////////////////

void App::launch()
{
	Display::create();

	pushState<States::Main>(m_appArgs[1]);
}

void App::handleEvents()
{
	sf::Event e;

	while (Display::pollEvent(e)) {
		switch (e.type) {
			case sf::Event::Closed:
				m_shouldClose = true;
				break;
			case sf::Event::Resized:
				Display::setViewSize(e.size.width, e.size.height);
				break;
			default:
				currentState().handleEvent(e);
				break;
		}
	}
}

template<typename S, typename... Args>
void App::pushState(Args&&... args)
{
	m_states.push_back(std::make_unique<S>(std::forward<Args>(args)...));
}

void App::popState()
{
	m_shouldPop = true;
}

States::State &App::currentState()
{
	return *m_states.back();
}