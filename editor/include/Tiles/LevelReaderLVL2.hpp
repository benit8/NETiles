/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Tiles / LevelReaderLVL2.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace Tiles {
	class LevelReaderLVL2;
}

////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <cstring>
#include <fstream>
#include <sstream>

#include "Tiles/ILevelReader.hpp"
#include "Tiles/Tile.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

class LevelReaderLVL2 : public ILevelReader
{
public:
	LevelReaderLVL2() = default;
	~LevelReaderLVL2() = default;

public:
	static bool check(std::ifstream &stream);

	bool loadMapFromStream(std::ifstream &stream, TileArray &tiles);
};

}