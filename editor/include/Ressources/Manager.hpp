/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Ressources / Manager.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace Ressource {
	class Manager;
}

////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <sys/stat.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Ressources/Container.hpp"
#include "Utils/Singleton.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Ressource
{

const std::string assetsDir = "../assets/";

class Manager : public Singleton
{
public:
	static Manager& getInstance();

	static sf::Font &getFont(const std::string& name, bool isFullPath = false);
	static sf::Image &getImage(const std::string& name, bool isFullPath = false);
	static sf::Texture &getTexture(const std::string& name, bool isFullPath = false);
	static sf::SoundBuffer &getSoundBuffer(const std::string& name, bool isFullPath = false);

private:
	Container<sf::Font> m_fonts;
	Container<sf::Image> m_images;
	Container<sf::Texture> m_textures;
	Container<sf::SoundBuffer> m_soundBuffers;

private:
	Manager() noexcept;
};

}