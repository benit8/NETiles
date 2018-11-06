/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Button.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Button;
}

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../FontLoader.hpp"
#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Button : public Widget
{
public:
	Button();
	Button(const std::string &label);
	virtual ~Button() override = default;

public:
	virtual void draw(sf::RenderTarget &rt) override;

	void setLabel(const std::string &text, bool resize = true);
	const std::string getLabel() const;
	void setLabelSize(unsigned int size, bool resize = true);

	virtual void setSize(const sf::Vector2f &size);

private:
	void centerLabel();

public:
	void onHoverIn_callback(sf::Vector2i pos);
	void onHoverOut_callback(sf::Vector2i pos);
	void onClick_callback(sf::Mouse::Button btn, sf::Vector2i pos);
	void onRelease_callback(sf::Mouse::Button btn, sf::Vector2i pos);

private:
	sf::RectangleShape m_rect;
	sf::Font m_font;
	sf::Text m_label;
};

}