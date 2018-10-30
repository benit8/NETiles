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

#include "Object.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Box : public Object
{
public:
	Box();
	virtual ~Box() override = default;

public:
	virtual void draw(sf::RenderTarget &rt) override;

	virtual void onHoverIn() override;
	virtual void onHoverOut() override;
	virtual void onClick() override;
	virtual void onRelease() override;
	virtual void onDragBegin() override;
	virtual void onDragEnd() override;

private:
	sf::RectangleShape m_rect;
};

}