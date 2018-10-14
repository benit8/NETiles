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
	FPSCounter();
	~FPSCounter();

public:
	void reset();
	void addFrameTime(const sf::Time &elapsed);
	void incrementFrameCount();

	unsigned getFPS() const;
	unsigned getRealFPS() const;

private:
	sf::Clock m_clock;
	sf::Time m_secondCounter;
	unsigned m_frames, m_realFps, m_fps;
};