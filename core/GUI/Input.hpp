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
	void clearPlaceholder();
	void setCharacterSize(unsigned size);

	Signal<const std::string &> onEnter;

private:
	void insert(const std::string &content);
	void insert(char c);
	void updateCursor();

	void onTextInput_callback(unsigned unicode);
	void onHoverIn_callback(sf::Vector2i pos);
	void onHoverOut_callback(sf::Vector2i pos);
	void onFocusIn_callback();
	void onFocusOut_callback();
	void cursorToLeft(sf::Keyboard::Key key, int ctrlKeys);
	void cursorToRight(sf::Keyboard::Key key, int ctrlKeys);
	void cursorToBegin(sf::Keyboard::Key key, int ctrlKeys);
	void cursorToEnd(sf::Keyboard::Key key, int ctrlKeys);

private:
	sf::RectangleShape m_rect;
	sf::RectangleShape m_cursor;
	std::size_t m_cursorIndex;

	sf::Font m_font;
	sf::Text m_placeholder;
	sf::Text m_text;
	std::string m_value;
};

}