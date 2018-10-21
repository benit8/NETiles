/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Application.cpp
*/

#include "Application.hpp"

Application::Application(int argc, char *argv[])
: m_binName(argv[0])
, m_args(argv + 1, argv + argc)
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
		auto &state = m_stateManager.getCurrentState();

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

		m_stateManager.tryPop();
	}

	return EXIT_SUCCESS;
}

void Application::launch()
{
	m_shouldClose = false;

	m_window.create(
		// sf::VideoMode::getDesktopMode(),
		sf::VideoMode(1280, 720),
		m_appName,
		sf::Style::Default,
		sf::ContextSettings(24, 8, 0, 3, 0));
	m_fpsCounter.setLimit(1000);
	m_fpsCounter.reset();
}

void Application::processEvents()
{
	auto &state = m_stateManager.getCurrentState();

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
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Escape)
					m_shouldClose = true;
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

sf::RenderWindow &Application::getWindow()
{
	return m_window;
}