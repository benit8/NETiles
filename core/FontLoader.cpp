/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** FontLoader.cpp
*/

#include <iostream>
#include "FontLoader.hpp"

bool FontLoader::s_loaded = false;
std::vector<FontLoader::FontInfo> FontLoader::s_fonts;

bool FontLoader::loadFromSystem(sf::Font &font, const std::string &name)
{
	searchFonts();

	for (std::vector<FontInfo>::iterator it = s_fonts.begin(); it != s_fonts.end(); ++it) {
		if (it->name == name)
			return font.loadFromFile(it->path);
	}
	return false;
}


static std::string exec(const char *cmd)
{
	char buffer[128];
	std::string result;
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
	if (!pipe)
		throw std::runtime_error("popen() failed");
	while (!feof(pipe.get())) {
		if (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr)
			result += buffer;
	}
	return result;
}

bool FontLoader::searchFonts()
{
	if (s_loaded)
		return true;

	std::string rawFonts;
	try {
		rawFonts = exec("fc-list");
	} catch (...) {
		std::cerr << "Could not search system fonts" << std::endl;
		return false;
	}

	std::istringstream iss(rawFonts);
	std::string line;
	while (std::getline(iss, line)) {
		std::vector<std::string> rawInfos;
		boost::split(rawInfos, line, boost::is_any_of(":"), boost::token_compress_on);

		while (rawInfos[1].find(' ') == 0)
			rawInfos[1].erase(0, 1);
		std::size_t n;
		if ((n = rawInfos[2].find("style=")) != std::string::npos)
			rawInfos[2].erase(n, 6);

		s_fonts.emplace_back(rawInfos[0], rawInfos[1], rawInfos[2]);
	}

	s_loaded = true;
	return true;
}