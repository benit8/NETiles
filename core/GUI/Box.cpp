/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Box.cpp
*/

#include "Box.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Box::Box()
: m_backgroundMode(Cover)
{
}

////////////////////////////////////////////////////////////////////////////////

void Box::update()
{
	sf::Vector2u imgSize = m_background.getSize();
	if (imgSize.x == 0 && imgSize.y == 0)
		return;

	sf::IntRect tRect(0, 0, imgSize.x, imgSize.y);
	float imageAspectRatio = (float)tRect.width / (float)tRect.height;
	float boxAspectRatio = width() / height();
	float diff = boxAspectRatio / imageAspectRatio;

	if (m_backgroundMode == Tiled) {
		sf::Vector2f f(width() / imgSize.x, height() / imgSize.y);
		tRect.width *= f.x;
		tRect.height *= f.y;
		tRect.left = -(width() - imgSize.x) / 2.f;
		tRect.top = -(height() - imgSize.y) / 2.f;
	}
	else if ((m_backgroundMode == Cover && boxAspectRatio < imageAspectRatio) ||
	         (m_backgroundMode == Contains && boxAspectRatio > imageAspectRatio)) {
		int oldWidth = tRect.width;
		tRect.width *= diff;
		tRect.left = (oldWidth - tRect.width) / 2.f;
	}
	else {
		int oldHeight = tRect.height;
		tRect.height /= diff;
		tRect.top = (oldHeight - tRect.height) / 2.f;
	}

	m_zone.setTextureRect(tRect);
}

void Box::draw(sf::RenderTarget &rt)
{
	rt.draw(m_zone);
}

////////////////////////////////////////////////////////////////////////////////

void Box::setBackgroundImage(const std::string &path, BackgroundMode mode)
{
	sf::Image image;
	if (image.loadFromFile(path))
		setBackgroundImage(image, mode);
}

void Box::setBackgroundImage(const sf::Image &image, BackgroundMode mode)
{
	if (!m_background.loadFromImage(image)) {
		std::cerr << "Failed to load box background" << std::endl;
		return;
	}

	m_backgroundMode = mode;
	m_background.setRepeated(m_backgroundMode == Tiled);
	m_zone.setTexture(&m_background);

	update();
}

void Box::setBackgroundMode(BackgroundMode mode)
{
	m_backgroundMode = mode;
	m_background.setRepeated(m_backgroundMode == Tiled);
	update();
}

void Box::setBackgroundColor(const sf::Color &color)
{
	m_zone.setFillColor(color);
}

void Box::setBorderColor(const sf::Color &color)
{
	m_zone.setOutlineColor(color);
}

void Box::setBorderSize(float size)
{
	m_zone.setOutlineThickness(size);
}

////////////////////////////////////////////////////////////////////////////////

}