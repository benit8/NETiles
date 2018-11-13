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

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

////////////////////////////////////////////////////////////////////////////////

class FPSCounter
{
public:
	FPSCounter();
	~FPSCounter() = default;

public:
	void reset();
	void addFrameTime(const sf::Time &elapsed);
	void incrementFrameCount();
	void setLimit(unsigned limit);
	void render(sf::RenderTarget &rt);

	unsigned getFPS() const;
	unsigned getRealFPS() const;
	unsigned getLimit() const;
	sf::Time getFrameTime() const;

private:
	sf::Clock m_clock;
	sf::Time m_secondCounter;
	sf::Time m_frameTime;
	unsigned m_limit, m_frames, m_realFps, m_fps;

	sf::Text m_fpsText;
	sf::Font m_fpsTextFont;
	std::string m_fpsTextFontName;
	bool m_fontLoaded;
};