/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Tiles / LevelFactory.cpp
*/

#include "Tiles/LevelFactory.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace
{
	void ensureDefaultReadersWritersRegistered()
	{
		static bool registered = false;

		if (!registered) {
			Tiles::LevelFactory::registerReader<Tiles::LevelReaderLVL2>();
			registered = true;
		}
	}
}

namespace Tiles
{

LevelFactory::ReaderFactoryArray LevelFactory::s_readers;
LevelFactory::WriterFactoryArray LevelFactory::s_writers;

////////////////////////////////////////////////////////////////////////////////

ILevelReader *LevelFactory::getReaderFromStream(std::ifstream &stream)
{
	ensureDefaultReadersWritersRegistered();

	stream.seekg(0);

	for (ReaderFactoryArray::const_iterator it = s_readers.begin(); it != s_readers.end(); ++it) {
		if (it->check(stream))
			return it->create();
	}

	std::cerr << "Failed to read level file: Unknown header magic" << std::endl;
	return NULL;
}

ILevelWriter *LevelFactory::getLastestWriter()
{
	ensureDefaultReadersWritersRegistered();

	return s_writers.back().create();
}

////////////////////////////////////////////////////////////////////////////////

}