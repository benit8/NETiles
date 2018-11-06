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

#include <SFML/Graphics/RectangleShape.hpp>

#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Box : public Widget
{
public:
	Box();
	virtual ~Box() override = default;

public:
	virtual void draw(sf::RenderTarget &rt) override;

private:
	void onHoverIn_callback(sf::Vector2i pos);
	void onHoverOut_callback(sf::Vector2i pos);

private:
	sf::RectangleShape m_rect;
};

}