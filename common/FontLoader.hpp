/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** FontLoader.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class FontLoader;

////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <SFML/Graphics/Font.hpp>

////////////////////////////////////////////////////////////////////////////////

class FontLoader
{
public:
	struct FontInfo
	{
		FontInfo(std::string _path, std::string _name, std::string _style)
		: path(_path)
		, name(_name)
		, style(_style)
		{}

		std::string path, name, style;
	};

private:
	FontLoader();
	~FontLoader();

public:
	static bool loadFromSystem(const std::string &name, sf::Font &font);

private:
	static bool searchFonts();

private:
	static bool s_loaded;
	static std::vector<FontInfo> s_fonts;
};