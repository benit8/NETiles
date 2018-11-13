/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** FPSCounter.cpp
*/

#include "FPSCounter.hpp"
#include "FontLoader.hpp"

////////////////////////////////////////////////////////////////////////////////

FPSCounter::FPSCounter()
: m_fpsTextFontName("Consolas")
, m_fontLoaded(false)
{
	reset();
	setLimit(60);

	if (!FontLoader::loadFromSystem(m_fpsTextFont, m_fpsTextFontName))
		std::cerr << "Could not load font '" << m_fpsTextFontName << "'" << std::endl;
	else {
		m_fontLoaded = true;
		m_fpsText.setFont(m_fpsTextFont);
		m_fpsText.setCharacterSize(16);
		m_fpsText.setFillColor(sf::Color::White);
	}
}

////////////////////////////////////////////////////////////////////////////////

void FPSCounter::reset()
{
	m_frames = 0;
	m_secondCounter = sf::Time::Zero;
	m_clock.restart();
}

void FPSCounter::addFrameTime(const sf::Time &elapsed)
{
	m_secondCounter += elapsed;

	if (m_secondCounter >= sf::seconds(1)) {
		m_realFps = m_frames;
		reset();
	}
}

void FPSCounter::incrementFrameCount()
{
	m_frames++;
	m_fps = m_frames / m_clock.getElapsedTime().asSeconds();
}

void FPSCounter::setLimit(unsigned limit)
{
	m_limit = limit;
	m_frameTime = (m_limit > 0) ? sf::seconds(1.0 / (float)m_limit) : sf::Time::Zero;
}

void FPSCounter::render(sf::RenderTarget &target)
{
	if (m_fontLoaded) {
		m_fpsText.setString(std::to_string(m_fps) + " FPS");
		m_fpsText.setPosition(target.getSize().x - m_fpsText.getLocalBounds().width - 8, 4);
		target.draw(m_fpsText);
	}
}


unsigned FPSCounter::getFPS() const {
	return m_fps;
}

unsigned FPSCounter::getRealFPS() const {
	return m_realFps;
}

unsigned FPSCounter::getLimit() const {
	return m_limit;
}

sf::Time FPSCounter::getFrameTime() const {
	return m_frameTime;
}