/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Application.cpp
*/

#include "Application.hpp"

////////////////////////////////////////////////////////////////////////////////

Application *Application::s_instance = nullptr;

////////////////////////////////////////////////////////////////////////////////

Application::Application(int argc, char *argv[])
: m_args(argv + 1, argv + argc)
, m_appName(argv[0])
, m_binName(argv[0])
, m_shouldClose(false)
, m_windowMode(Windowed)
, m_windowStartupSize(0, 0)
{
	s_instance = this;

	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	m_windowStartupSize.x = desktopMode.width;
	m_windowStartupSize.y = desktopMode.height;
}

Application::~Application()
{
	if (m_window.isOpen())
		m_window.close();
}

////////////////////////////////////////////////////////////////////////////////

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

void Application::close()
{
	m_shouldClose = true;
}

bool Application::isRunning() const
{
	return !m_shouldClose && m_window.isOpen();
}

void Application::setAppName(const std::string &name)
{
	m_appName = name;
}

const std::string &Application::getAppName() const
{
	return m_appName;
}


void Application::setWindowMode(WindowMode mode, const sf::Vector2u &size)
{
	sf::Vector2u currentSize = m_window.getSize();

	if (m_window.isOpen() && m_windowMode != mode) {
		switch (mode) {
			case Windowed:
				if (size != currentSize)
					m_window.setSize(size);
				else
					m_window.create(m_appName, sf::VideoMode(size.x, size.y));
				break;
			case Borderless:
					m_window.createBorderless(m_appName);
				break;
			case Fullscreen:
				m_window.createFullscreen(m_appName);
				break;
		}
	}
	else if (!m_window.isOpen() && mode == Windowed) {
		m_windowStartupSize = size;
	}

	m_windowMode = mode;
}

////////////////////////////////////////////////////////////////////////////////

void Application::launch()
{
	switch (m_windowMode) {
		case Windowed:
			m_window.create(m_appName, sf::VideoMode(m_windowStartupSize.x, m_windowStartupSize.y));
			break;
		case Borderless:
			m_window.createBorderless(m_appName);
			break;
		case Fullscreen:
			m_window.createFullscreen(m_appName);
			break;
	}

	m_fpsCounter.setLimit(1000);
	m_fpsCounter.reset();
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

////////////////////////////////////////////////////////////////////////////////

Application *Application::Instance()
{
	return s_instance;
}

sf::Vector2u Application::MainWindowSize()
{
	Application *self = Instance();

	return self->m_window.isOpen() ? self->m_window.getSize() : self->m_windowStartupSize;
}

unsigned Application::MainWindowWidth()
{
	return MainWindowSize().x;
}

unsigned Application::MainWindowHeight()
{
	return MainWindowSize().y;
}

void Application::SetCursor(sf::Cursor::Type cursor)
{
	Instance()->m_window.setCursor(cursor);
}