/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** FPSCounter.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class FPSCounter;

////////////////////////////////////////////////////////////////////////////////

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

////////////////////////////////////////////////////////////////////////////////

class FPSCounter
{
public:
	FPSCounter() {
		reset();
		setLimit(60);
	}

	~FPSCounter() = default;

public:
	void reset() {
		m_frames = 0;
		m_secondCounter = sf::Time::Zero;
		m_clock.restart();
	}

	void addFrameTime(const sf::Time &elapsed) {
		m_secondCounter += elapsed;

		if (m_secondCounter >= sf::seconds(1)) {
			m_realFps = m_frames;
			reset();
		}
	}

	void incrementFrameCount() {
		m_frames++;
		m_fps = m_frames / m_clock.getElapsedTime().asSeconds();
	}

	void setLimit(unsigned limit) {
		m_limit = limit;
		m_frameTime = sf::seconds(1.0 / (float)m_limit);
	}


	unsigned getFPS() const {
		return m_fps;
	}

	unsigned getRealFPS() const {
		return m_realFps;
	}

	unsigned getLimit() const {
		return m_limit;
	}

	sf::Time getFrameTime() const {
		return m_frameTime;
	}

private:
	sf::Clock m_clock;
	sf::Time m_secondCounter;
	sf::Time m_frameTime;
	unsigned m_limit, m_frames, m_realFps, m_fps;
};