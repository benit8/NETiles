/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Button.cpp
*/

#include <algorithm>
#include "Button.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Button::Button()
{
	m_rect.setFillColor(sf::Color(0, 0, 0, 175));
	m_rect.setOutlineThickness(1);
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
	m_rect.setSize(sf::Vector2f(30, 10));

	if (!FontLoader::loadFromSystem(m_font, "Noto Sans"))
		std::cerr << "Failed to load GUI::Button font" << std::endl;
	m_label.setFont(m_font);

	setLabel("Button");
	setLabelSize(18);

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
	m_rect.setSize(getSize());
	m_rect.setPosition(getPosition());
	centerLabel();

	rt.draw(m_rect);
	rt.draw(m_label);
}

////////////////////////////////////////////////////////////////////////////////

void Button::setLabel(const std::string &text, bool resize)
{
	m_label.setString(text);

	if (resize) {
		sf::FloatRect labelBounds = m_label.getLocalBounds();
		setSize({labelBounds.width + 32, labelBounds.height + 14});
	}
}

const std::string Button::getLabel() const
{
	return m_label.getString();
}

void Button::setLabelSize(unsigned int size, bool resize)
{
	m_label.setCharacterSize(size);

	if (resize) {
		sf::FloatRect labelBounds = m_label.getLocalBounds();
		setSize({labelBounds.width + 32, labelBounds.height + 14});
	}
}

void Button::setSize(const sf::Vector2f &requestedSize)
{
	sf::FloatRect labelBounds = m_label.getLocalBounds();
	sf::Vector2f size(requestedSize);
	size.x = std::max(size.x, labelBounds.width);
	size.y = std::max(size.y, labelBounds.height);

	m_zone.width = size.x;
	m_zone.height = size.y;
}


void Button::centerLabel()
{
	sf::FloatRect labelBounds = m_label.getLocalBounds();

	sf::Vector2f pos(m_zone.left, m_zone.top);
	pos += sf::Vector2f((m_zone.width - labelBounds.width) / 2.f, (m_zone.height - labelBounds.height) / 2.f);
	pos -= sf::Vector2f(labelBounds.left, labelBounds.top);

	m_label.setPosition(pos);
}

////////////////////////////////////////////////////////////////////////////////

void Button::onHoverIn_callback(sf::Vector2i pos)
{
	m_rect.setOutlineColor(sf::Color::White);
	Window::getMainWindow()->setCursor(sf::Cursor::Hand);
}

void Button::onHoverOut_callback(sf::Vector2i pos)
{
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
	Window::getMainWindow()->setCursor(sf::Cursor::Arrow);
}

void Button::onClick_callback(sf::Vector2i pos)
{
	m_rect.setFillColor(sf::Color::White);
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
	m_label.setFillColor(sf::Color::Black);
}

void Button::onRelease_callback(sf::Vector2i pos)
{
	m_rect.setFillColor(sf::Color(0, 0, 0, 175));
	m_rect.setOutlineColor(sf::Color(170, 170, 170));
	m_label.setFillColor(sf::Color::White);
}

////////////////////////////////////////////////////////////////////////////////

}