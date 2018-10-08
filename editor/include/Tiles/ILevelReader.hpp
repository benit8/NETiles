/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Tiles / ILevelReader.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace Tiles {
	class ILevelReader;
}

////////////////////////////////////////////////////////////////////////////////

#include <fstream>

#include "Tiles/LevelFactory.hpp"
#include "Tiles/Tile.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

class ILevelReader
{
public:
	virtual ~ILevelReader() = default;

public:
	virtual bool loadMapFromStream(std::ifstream &stream, TileArray &tiles) = 0;
};

}