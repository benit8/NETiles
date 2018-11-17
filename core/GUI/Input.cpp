/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Input.cpp
*/

#include "Input.hpp"
#include "../FontLoader.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Input::Input()
: m_cursorIndex(0)
, m_valueOffset(0)
, m_valueLength(0)
{
	setFont("Consolas");
	setSize(sf::Vector2f(300, 35));
	setCharacterSize(20);

	m_rect.setFillColor(sf::Color(0, 0, 0, 175));
	m_rect.setOutlineThickness(1);
	m_rect.setOutlineColor(sf::Color(170, 170, 170));

	m_cursor.setFillColor(sf::Color::White);
	m_placeholder.setFillColor(sf::Color(100, 100, 100));

	onFocusIn.connect(this, &Input::onFocusIn_callback);
	onFocusOut.connect(this, &Input::onFocusOut_callback);
	onTextInput.connect(this, &Input::onTextInput_callback);

	m_eventDispatcher.onKeyDown(BIND(Input::cursorToLeft), sf::Keyboard::Left);
	m_eventDispatcher.onKeyDown(BIND(Input::cursorToRight), sf::Keyboard::Right);
	m_eventDispatcher.onKeyDown(BIND(Input::cursorToBegin), sf::Keyboard::Up);
	m_eventDispatcher.onKeyDown(BIND(Input::cursorToBegin), sf::Keyboard::Home);
	m_eventDispatcher.onKeyDown(BIND(Input::cursorToEnd), sf::Keyboard::Down);
	m_eventDispatcher.onKeyDown(BIND(Input::cursorToEnd), sf::Keyboard::End);

	update();
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
	else {
		sf::RectangleShape border;
		sf::FloatRect bounds = m_text.getLocalBounds();
		sf::Vector2f pos = m_text.getPosition();
		border.setPosition(pos + sf::Vector2f(bounds.left, bounds.top));
		border.setSize({bounds.width, bounds.height});
		border.setOutlineThickness(1);
		border.setOutlineColor((bounds.width > width() - 16) ? sf::Color::Green : sf::Color::Red);
		border.setFillColor(sf::Color::Transparent);

		target.draw(m_text);
		target.draw(border);
	}
	if (isTargeted())
		target.draw(m_cursor);
}

void Input::update()
{
	sf::Text tmp("l", m_font, m_text.getCharacterSize());
	sf::FloatRect bounds = tmp.getLocalBounds();
	sf::Vector2f textPos = getPosition();
	textPos.x += 8;
	textPos.y -= bounds.top;
	textPos.y += ((height() - bounds.height) / 2.f);
	m_placeholder.setPosition(textPos);
	m_text.setPosition(textPos);
	m_cursor.setPosition({textPos.x, top()});
	m_cursor.setSize({2, bounds.height + bounds.top * 2});

	updateTextOffset();
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
	m_cursorIndex = value.length();
	updateTextOffset();
}

const std::string &Input::getValue() const
{
	return m_value;
}

void Input::setPlaceholder(const std::string &placeholder)
{
	m_placeholder.setString(placeholder);
}

void Input::setCharacterSize(unsigned size)
{
	m_placeholder.setCharacterSize(size);
	m_text.setCharacterSize(size);

	update();
}

unsigned Input::getCharacterSize() const
{
	return m_text.getCharacterSize();
}

////////////////////////////////////////////////////////////////////////////////

void Input::insert(const std::string &content)
{
	m_value.insert(m_cursorIndex, content);
	m_cursorIndex += content.length();
	updateTextOffset();
}

void Input::insert(char c)
{
	m_value.insert(m_cursorIndex++, &c, 1);
	updateTextOffset();
}

void Input::updateTextOffset()
{
	unsigned size = getCharacterSize();
	std::size_t maxTextWidth = width() - 16;
	std::size_t textWidth = 0;

	size_t i = m_valueOffset;
	for (; i < m_value.length() && textWidth > maxTextWidth; ++i)
		textWidth -= m_font.getGlyph(m_value[i], size, false).advance;
	m_valueOffset = i;

	m_text.setString(m_value.substr(m_valueOffset, m_value.length() - m_valueOffset));
	updateCursor();
}

void Input::updateCursor()
{
	unsigned size = getCharacterSize();
	size_t max = std::min(m_cursorIndex + m_valueOffset, m_value.length());

	sf::Vector2f cursorPos(m_text.getPosition().x, top());
	for (size_t i = m_valueOffset; i < max; ++i)
		cursorPos.x += m_font.getGlyph(m_value[i], size, false).advance;
	cursorPos.y += (height() - m_cursor.getSize().y) / 2.f;
	m_cursor.setPosition(cursorPos);
}

////////////////////////////////////////////////////////////////////////////////

void Input::onTextInput_callback(unsigned unicode)
{
	char c = static_cast<char>(unicode);

	switch (unicode) {
		case 8: // Backspace
			if (m_cursorIndex > 0) {
				m_value.erase(m_cursorIndex, 1);
				cursorToLeft();
				updateTextOffset();
			}
			break;
		case 9: // Tab
			update();
			break;
		case 13: // Enter
			onEnter.emit(getValue());
			break;
		case 127: // Delete
			if (m_cursorIndex < m_value.length()) {
				m_value.erase(m_cursorIndex, 1);
				updateTextOffset();
			}
			break;
		default:
			if (isprint(c))
				insert(c);
			break;
	}
}

void Input::onFocusIn_callback()
{
	m_rect.setOutlineColor(sf::Color(231, 76, 60));
}

void Input::onFocusOut_callback()
{
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
}


void Input::cursorToLeft()
{
	if (isTargeted() && m_cursorIndex > 0) {
		m_cursorIndex--;
		updateCursor();
	}
}

void Input::cursorToRight()
{
	if (isTargeted() && m_cursorIndex < m_value.length()) {
		m_cursorIndex++;
		updateCursor();
	}
}

void Input::cursorToBegin()
{
	if (isTargeted()) {
		m_cursorIndex = m_valueOffset = 0;
		m_valueLength = 0;

		unsigned size = getCharacterSize();
		std::size_t maxTextWidth = width() - 16;
		size_t textWidth = 0;
		for (int i = 0; i < m_value.length() && textWidth > maxTextWidth; ++i) {
			textWidth += m_font.getGlyph(m_value[i], size, false).advance;
			m_valueLength++;
		}

		m_text.setString(m_value.substr(m_valueOffset, m_valueLength));

		updateCursor();
	}
}

void Input::cursorToEnd()
{
	if (isTargeted()) {
		m_cursorIndex = m_value.length();
		m_valueLength = 0;

		unsigned size = getCharacterSize();
		std::size_t maxTextWidth = width() - 16;
		size_t textWidth = 0;
		for (int i = m_value.length() - 1; i > 0 && textWidth > maxTextWidth; --i) {
			textWidth += m_font.getGlyph(m_value[i], size, false).advance;
			m_valueLength++;
		}

		m_text.setString(m_value.substr(m_valueOffset, m_valueLength));

		updateCursor();
	}
}

////////////////////////////////////////////////////////////////////////////////

}