/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Tiles / LevelReaderLVL2.cpp
*/

#include "Tiles/LevelReaderLVL2.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

bool LevelReaderLVL2::check(std::ifstream &stream)
{
	std::byte headerMagic[4];

	stream.read((char *)headerMagic, 4);
	if (stream.gcount() != 4)
		return false;
	if (std::memcmp(headerMagic, "LVL2", 4) != 0)
		return false;

	return true;
}

bool LevelReaderLVL2::loadMapFromStream(std::ifstream &stream, TileArray &tiles)
{
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty())
			continue;

		std::istringstream iss(line);
		Tile t;
		iss >> t.pos.x;
		iss >> t.pos.y;
		iss >> t.tex.x;
		iss >> t.tex.y;
		iss >> t.walkable;

		if (iss.peek() != -1) {
			t.tele = true;
			iss >> t.telePos.x;
			iss >> t.telePos.y;
		}

		tiles.push_back(t);
	}

	return true;
}

}