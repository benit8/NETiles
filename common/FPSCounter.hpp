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

////////////////////////////////////////////////////////////////////////////////

class FPSCounter
{
public:
	FPSCounter()
	: m_fpsTextFontPath("/usr/share/fonts/deepin-font-install/Consolas/Consolas.ttf")
	, m_fontLoaded(false)
	{
		reset();
		setLimit(60);

		if (!m_fpsTextFont.loadFromFile(m_fpsTextFontPath))
			std::cerr << "Could not load font '" << m_fpsTextFontPath << "'" << std::endl;
		else {
			m_fontLoaded = true;
			m_fpsText.setFont(m_fpsTextFont);
			m_fpsText.setCharacterSize(18);
			m_fpsText.setPosition(8, 4);
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
	std::string m_fpsTextFontPath;
	bool m_fontLoaded;
};