/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Input.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Input;
}

////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Input : public Widget
{
public:
	Input();
	Input(const std::string &placeholder);

public:
	void draw(sf::RenderTarget &target) override;
	void update() override;

	bool setFont(const std::string &fontPath);
	void setFont(const sf::Font &font);
	void setValue(const std::string &value);
	const std::string &getValue() const;
	void setPlaceholder(const std::string &placeholder);
	void setCharacterSize(unsigned size);
	unsigned getCharacterSize() const;

	Signal<const std::string &> onEnter;

private:
	void insert(const std::string &content);
	void insert(char c);
	void updateTextOffset();
	void updateCursor();

	void onTextInput_callback(unsigned unicode);
	void onFocusIn_callback();
	void onFocusOut_callback();
	void cursorToLeft();
	void cursorToRight();
	void cursorToBegin();
	void cursorToEnd();

private:
	sf::RectangleShape m_rect;
	sf::RectangleShape m_cursor;
	std::size_t m_cursorIndex;
	std::size_t m_valueOffset;
	std::size_t m_valueLength;

	sf::Font m_font;
	sf::Text m_placeholder;
	sf::Text m_text;
	std::string m_value;
};

}