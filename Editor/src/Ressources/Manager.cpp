/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Ressources / Manager.cpp
*/

#include "Ressources/Manager.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Ressource
{

////////////////////////////////////////////////////////////////////////////////

Manager::Manager() noexcept
: m_fonts("Assets/fonts/", "ttf")
, m_images("Assets/images/", "jpg")
, m_textures("Assets/textures/", "png")
, m_soundBuffers("Assets/sounds/", "ogg")
{}

////////////////////////////////////////////////////////////////////////////////

Manager &Manager::getInstance()
{
	static Manager manager;
	return manager;
}

////////////////////////////////////////////////////////////////////////////////

const sf::Font &Manager::getFont(const std::string& name, bool isFullPath)
{
	return getInstance().m_fonts.get(name, isFullPath);
}

const sf::Image &Manager::getImage(const std::string& name, bool isFullPath)
{
	return getInstance().m_images.get(name, isFullPath);
}

const sf::Texture &Manager::getTexture(const std::string& name, bool isFullPath)
{
	return getInstance().m_textures.get(name, isFullPath);
}

const sf::SoundBuffer &Manager::getSoundBuffer(const std::string& name, bool isFullPath)
{
	return getInstance().m_soundBuffers.get(name, isFullPath);
}

////////////////////////////////////////////////////////////////////////////////

}