/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Button.cpp
*/

#include "Button.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Button::Button()
{
	m_mode = Mode::Clickable;
	m_rect.setFillColor(sf::Color::Black);
	m_rect.setOutlineThickness(1);
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
	m_rect.setSize(sf::Vector2f(30, 10));
	m_label.setString("Button");
	m_label.setCharacterSize(20);

	if (!FontLoader::loadFromSystem("Noto Sans", m_font))
		std::cerr << "Failed to load GUI::Button font" << std::endl;
	m_label.setFont(m_font);

	onHoverIn.connect(this, &Button::onHoverIn_callback);
	onHoverOut.connect(this, &Button::onHoverOut_callback);
	onClick.connect(this, &Button::onClick_callback);
	onRelease.connect(this, &Button::onRelease_callback);
}

Button::Button(const std::string &label)
: Button()
{
	setLabel(label);
}

////////////////////////////////////////////////////////////////////////////////

void Button::draw(sf::RenderTarget &rt)
{
	m_rect.setPosition(getPosition());
	m_label.setPosition(getPosition() + sf::Vector2f(6, 1));

	rt.draw(m_rect);
	rt.draw(m_label);
}

////////////////////////////////////////////////////////////////////////////////

void Button::setLabel(const std::string &text)
{
	m_label.setString(text);

	sf::FloatRect labelBounds = m_label.getLocalBounds();
	sf::Vector2f size = sf::Vector2f(labelBounds.width + 16, labelBounds.height + 14);
	m_rect.setSize(size);
	setSize(size);
}

const std::string Button::getLabel() const
{
	return m_label.getString();
}

////////////////////////////////////////////////////////////////////////////////

void Button::onHoverIn_callback(sf::Vector2i pos)
{
	m_rect.setOutlineColor(sf::Color::White);
}

void Button::onHoverOut_callback(sf::Vector2i pos)
{
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
}

void Button::onClick_callback(sf::Mouse::Button btn, sf::Vector2i pos)
{
	m_rect.setFillColor(sf::Color::White);
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
	m_label.setFillColor(sf::Color::Black);
}

void Button::onRelease_callback(sf::Mouse::Button btn, sf::Vector2i pos)
{
	m_rect.setFillColor(sf::Color::Black);
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
	m_label.setFillColor(sf::Color::White);
}

////////////////////////////////////////////////////////////////////////////////

}