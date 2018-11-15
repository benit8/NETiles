/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Application.cpp
*/

#include "Application.hpp"

Application::Application(int argc, char *argv[])
: m_args(argv + 1, argv + argc)
, m_binName(argv[0])
{
	m_appName = m_binName;
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
	sf::Clock timer;
	while (isRunning()) {
		auto &state = getCurrentState();

		sf::Time elapsed = timer.restart();
		updateTimer += elapsed;
		m_fpsCounter.addFrameTime(elapsed);

		bool shouldRender = false;
		while (updateTimer >= m_fpsCounter.getFrameTime()) {
			processEvents();
			state.update(elapsed);
			updateTimer -= m_fpsCounter.getFrameTime();
			shouldRender = true;
		}

		if (shouldRender) {
			m_window.clear();
			 state.render(m_window);
			 m_fpsCounter.render(m_window);
			m_window.display();

			m_fpsCounter.incrementFrameCount();
		}

		updateStates();
	}

	return EXIT_SUCCESS;
}

void Application::launch()
{
	m_shouldClose = false;

	m_window.createDefault(m_appName);
	m_fpsCounter.setLimit(1000);
	m_fpsCounter.reset();
	Window::setMainWindow(&m_window);
}

void Application::processEvents()
{
	auto &state = getCurrentState();

	sf::Event e;
	while (m_window.pollEvent(e)) {
		state.handleEvent(e);
		switch (e.type) {
			case sf::Event::Closed:
				m_shouldClose = true;
				break;
			case sf::Event::Resized:
				m_window.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
				break;
			default:
				break;
		}
	}
}

bool Application::isRunning() const
{
	return !m_shouldClose && m_window.isOpen();
}

void Application::close()
{
	m_shouldClose = true;
}