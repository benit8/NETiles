/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** FPSCounter.cpp
*/

#include "FPSCounter.hpp"

FPSCounter::FPSCounter()
{
	reset();
}

FPSCounter::~FPSCounter()
{
}


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
	++m_frames;

	m_fps = m_frames / m_clock.getElapsedTime().asSeconds();
}

unsigned FPSCounter::getFPS() const
{
	return m_fps;
}

unsigned FPSCounter::getRealFPS() const
{
	return m_realFps;
}