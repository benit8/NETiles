/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Modal.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Modal;
}

////////////////////////////////////////////////////////////////////////////////

#include "Widget.hpp"
#include "Box.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Modal : public Widget
{
public:
	Modal();
	virtual ~Modal();

public:
	virtual void draw(sf::RenderTarget &rt) override;
	virtual void updatePositions(sf::Vector2u size);

	virtual void open();
	virtual void close();

	bool isOpen();

private:
	Widget *m_previousModal;
	Box m_back;
	bool m_opened;
};

}