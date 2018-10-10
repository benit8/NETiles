/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "TestState.hpp"

Application::Application(int argc, char *argv[])
: m_binName(argv[0])
, m_args(argv + 1, argv + argc)
{
	m_stateManager.push<TestState>(this);
}

Application::~Application()
{
	if (m_window.isOpen())
		m_window.close();
}


int Application::run()
{
	launch();

	sf::Time updateTimer = sf::Time::Zero;
	sf::Time frameTime = sf::seconds(1.0 / 60.0);
	sf::Clock timer;
	while (isRunning()) {
		auto &state = m_stateManager.getCurrentState();
		sf::Time elapsed = timer.restart();
		updateTimer += elapsed;

		bool shouldRender = false;
		while (updateTimer >= frameTime) {
			processEvents();
			state.update(elapsed);
			updateTimer -= frameTime;
			shouldRender = true;
		}

		if (shouldRender) {
			m_window.clear();
			state.render();
			m_window.display();
		}

		m_stateManager.tryPop();
	}

	return 0;
}

void Application::launch()
{
	m_isRunning = true;

	m_window.create(
		sf::VideoMode::getDesktopMode(),
		m_binName,
		sf::Style::Default,
		sf::ContextSettings(24, 8, 0, 3, 0)
	);
}

void Application::processEvents()
{
	auto &state = m_stateManager.getCurrentState();

	sf::Event e;
	while (m_window.pollEvent(e)) {
		state.handleEvent(e);
		switch (e.type) {
			case sf::Event::Closed:
				m_isRunning = false;
				break;
			default:
				break;
		}
	}
}

bool Application::isRunning() const
{
	return m_isRunning && m_window.isOpen();
}

sf::RenderWindow &Application::getWindow()
{
	return m_window;
}