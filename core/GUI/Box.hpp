/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Box.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Box;
}

////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Box : public Widget
{
public:
	enum BackgroundMode
	{
		Contains,
		Cover,
		Tiled
	};

public:
	Box();

public:
	virtual void update() override;
	virtual void draw(sf::RenderTarget &rt) override;

public:
	void setBackgroundImage(const std::string &path, BackgroundMode mode = Cover);
	void setBackgroundImage(const sf::Image &image, BackgroundMode mode = Cover);
	void setBackgroundColor(const sf::Color &color);
	void setBackgroundMode(BackgroundMode mode);
	void setBorderColor(const sf::Color &color);
	void setBorderSize(float size);

private:
	sf::RectangleShape m_rect;
	sf::Texture m_background;
	BackgroundMode m_backgroundMode;
};

}