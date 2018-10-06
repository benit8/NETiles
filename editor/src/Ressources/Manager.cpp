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
: m_fonts(assetsDir + "fonts/", "ttf")
, m_images(assetsDir + "images/", "jpg")
, m_textures(assetsDir + "textures/", "png")
, m_soundBuffers(assetsDir + "sounds/", "ogg")
{}

////////////////////////////////////////////////////////////////////////////////

Manager &Manager::getInstance()
{
	static Manager manager;
	return manager;
}

////////////////////////////////////////////////////////////////////////////////

sf::Font &Manager::getFont(const std::string& name, bool isFullPath)
{
	return getInstance().m_fonts.get(name, isFullPath);
}

sf::Image &Manager::getImage(const std::string& name, bool isFullPath)
{
	return getInstance().m_images.get(name, isFullPath);
}

sf::Texture &Manager::getTexture(const std::string& name, bool isFullPath)
{
	return getInstance().m_textures.get(name, isFullPath);
}

sf::SoundBuffer &Manager::getSoundBuffer(const std::string& name, bool isFullPath)
{
	return getInstance().m_soundBuffers.get(name, isFullPath);
}

////////////////////////////////////////////////////////////////////////////////

}