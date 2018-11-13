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

#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Box : public Widget
{
public:
	Box();

public:
	void setBackgroundColor(const sf::Color &color);
	void setBorderColor(const sf::Color &color);
	void setBorderSize(float size);

public:
	virtual void draw(sf::RenderTarget &rt) override;

private:
	sf::RectangleShape m_rect;
};

}