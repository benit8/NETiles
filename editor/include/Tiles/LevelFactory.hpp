/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Tiles / LevelFactory.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace Tiles {
	namespace priv {}

	class LevelFactory;
}

////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <iostream>
#include <vector>

#include "Tiles/ILevelReader.hpp"
#include "Tiles/ILevelWriter.hpp"
#include "Tiles/LevelReaderLVL2.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Tiles
{

namespace priv
{
	template <typename T>
	ILevelReader *createReader() {
		return new T();
	}

	template <typename T>
	ILevelWriter *createWriter() {
		return new T();
	}
}

class LevelFactory
{
public:
	template <typename T>
	static void registerReader()
	{
		unregisterReader<T>();

		FactoryReader factory;
		factory.check = &T::check;
		factory.create = &priv::createReader<T>;

		s_readers.push_back(factory);
	}

	template <typename T>
	static void unregisterReader()
	{
		for (ReaderFactoryArray::iterator it = s_readers.begin(); it != s_readers.end(); ) {
			if (it->create == &priv::createReader<T>)
				it = s_readers.erase(it);
			else
				++it;
		}
	}

	template <typename T>
	static void registerWriter()
	{
		unregisterWriter<T>();

		FactoryWriter factory;
		factory.check = &T::check;
		factory.create = &priv::createWriter<T>;

		s_writers.push_back(factory);
	}

	template <typename T>
	static void unregisterWriter()
	{
		for (WriterFactoryArray::iterator it = s_writers.begin(); it != s_writers.end(); ) {
			if (it->create == &priv::createWriter<T>)
				it = s_writers.erase(it);
			else
				++it;
		}
	}


	static ILevelReader *getReaderFromStream(std::ifstream &stream);
	static ILevelWriter *getLastestWriter();

private:
	struct FactoryReader
	{
		bool (*check)(std::ifstream &stream);
		ILevelReader *(*create)();
	};
	typedef std::vector<FactoryReader> ReaderFactoryArray;

	struct FactoryWriter
	{
		bool (*check)();
		ILevelWriter *(*create)();
	};
	typedef std::vector<FactoryWriter> WriterFactoryArray;

	static ReaderFactoryArray s_readers;
	static WriterFactoryArray s_writers;
};

}