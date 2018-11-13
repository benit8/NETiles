/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Input.cpp
*/

#include "Input.hpp"
#include "../FontLoader.hpp"
#include <cctype>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Input::Input()
: m_cursorIndex(0)
{
	setFont("Consolas");
	setSize(sf::Vector2f(300, 35));
	setCharacterSize(20);

	m_rect.setFillColor(sf::Color::Black);
	m_rect.setOutlineThickness(1);
	m_rect.setOutlineColor(sf::Color(170, 170, 170));

	m_cursor.setFillColor(sf::Color::White);
	m_cursor.setSize(sf::Vector2f(8, 2));

	m_placeholder.setFillColor(sf::Color(100, 100, 100));

	// onHoverIn.connect(this, &Input::onHoverIn_callback);
	// onHoverOut.connect(this, &Input::onHoverOut_callback);
	onFocusIn.connect(this, &Input::onFocusIn_callback);
	onFocusOut.connect(this, &Input::onFocusOut_callback);
	onTextInput.connect(this, &Input::onTextInput_callback);
}

Input::Input(const std::string &placeholder)
: Input()
{
	setPlaceholder(placeholder);
}

////////////////////////////////////////////////////////////////////////////////

void Input::draw(sf::RenderTarget &target)
{
	m_rect.setSize(getSize());
	m_rect.setPosition(getPosition());

	target.draw(m_rect);
	if (m_value.empty())
		target.draw(m_placeholder);
	else
		target.draw(m_text);
	if (isTargeted())
		target.draw(m_cursor);
}

void Input::update()
{
	sf::Text tmp;
	tmp.setFont(m_font);
	tmp.setString("A");
	tmp.setCharacterSize(m_text.getCharacterSize());
	sf::FloatRect bounds = tmp.getLocalBounds();

	sf::Vector2f textPos = getPosition();
	textPos.x += 8;
	textPos.y -= bounds.top;
	textPos.y += ((height() - bounds.height) / 2.f);
	m_placeholder.setPosition(textPos);
	m_text.setPosition(textPos);
	m_cursor.setPosition({textPos.x, top()});
	m_cursor.setSize({2, bounds.height + bounds.top});

	updateCursor();
}

////////////////////////////////////////////////////////////////////////////////

bool Input::setFont(const std::string &fontPath)
{
	sf::Font font;
	bool loaded = FontLoader::loadFromSystem(font, fontPath);
	if (!loaded) {
		loaded = font.loadFromFile(fontPath);
	}

	setFont(font);
	return loaded;
}

void Input::setFont(const sf::Font &font)
{
	m_font = font;
	m_placeholder.setFont(m_font);
	m_text.setFont(m_font);
	update();
}

void Input::setValue(const std::string &value)
{
	m_value = value;
	m_text.setString(m_value);
	m_cursorIndex = value.length();
	updateCursor();
}

const std::string &Input::getValue() const
{
	return m_value;
}

void Input::setPlaceholder(const std::string &placeholder)
{
	m_placeholder.setString(placeholder);
}

const std::string &Input::getPlaceholder() const
{
	static std::string ref;
	ref = m_placeholder.getString();
	return ref;
}


void Input::setCharacterSize(unsigned size)
{
	m_placeholder.setCharacterSize(size);
	m_text.setCharacterSize(size);

	update();
}

////////////////////////////////////////////////////////////////////////////////

void Input::insert(const std::string &content)
{
	m_value.insert(m_cursorIndex, content);
	m_text.setString(m_value);
	m_cursorIndex += content.length();
	updateCursor();
}

void Input::insert(char c)
{
	m_value.insert(m_cursorIndex++, &c, 1);
	m_text.setString(m_value);
	updateCursor();
}

void Input::updateCursor()
{
	unsigned size = m_text.getCharacterSize();

	sf::Vector2f pos;
	for (size_t i = 0; i < std::min(m_cursorIndex, m_value.length()); ++i)
		pos.x += m_font.getGlyph(m_value[i], size, false).advance;
	pos.y += (height() - m_cursor.getSize().y) / 2.f;
	m_cursor.move(pos);
}

////////////////////////////////////////////////////////////////////////////////

void Input::onTextInput_callback(unsigned unicode)
{
	std::cout << (char)unicode << " (" << unicode << ")" << std::endl;

	switch (unicode) {
		case 8:
			if (m_cursorIndex > 0) {
				m_value.erase(--m_cursorIndex, 1);
				m_text.setString(m_value);
				updateCursor();
			}
			break;
		default:
			if (isprint(unicode))
				insert(unicode);
			break;
	}
}

void Input::onHoverIn_callback(sf::Vector2i pos)
{
	m_rect.setOutlineColor(sf::Color(192, 57, 43));
}

void Input::onHoverOut_callback(sf::Vector2i pos)
{
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
}

void Input::onFocusIn_callback()
{
	m_rect.setOutlineColor(sf::Color(231, 76, 60));
}

void Input::onFocusOut_callback()
{
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
}

////////////////////////////////////////////////////////////////////////////////

}