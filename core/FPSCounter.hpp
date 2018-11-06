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

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "FontLoader.hpp"

////////////////////////////////////////////////////////////////////////////////

class FPSCounter
{
public:
	FPSCounter()
	: m_fpsTextFontName("Consolas")
	, m_fontLoaded(false)
	{
		reset();
		setLimit(60);

		if (!FontLoader::loadFromSystem(m_fpsTextFontName, m_fpsTextFont))
			std::cerr << "Could not load font '" << m_fpsTextFontName << "'" << std::endl;
		else {
			m_fontLoaded = true;
			m_fpsText.setFont(m_fpsTextFont);
			m_fpsText.setCharacterSize(16);
			m_fpsText.setFillColor(sf::Color::White);
		}
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
		m_frameTime = (m_limit > 0) ? sf::seconds(1.0 / (float)m_limit) : sf::Time::Zero;
	}

	void render(sf::RenderTarget &rt) {
		if (m_fontLoaded) {
			m_fpsText.setString(std::to_string(m_fps) + " FPS");
			m_fpsText.setPosition(rt.getSize().x - m_fpsText.getLocalBounds().width - 8, 4);
			rt.draw(m_fpsText);
		}
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

	sf::Text m_fpsText;
	sf::Font m_fpsTextFont;
	std::string m_fpsTextFontName;
	bool m_fontLoaded;
};