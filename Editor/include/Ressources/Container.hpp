/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Ressources / Container.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////

namespace Ressource
{

template<typename T>
class Container
{
public:
	Container(const std::string& folder, const std::string& ext)
	: m_folder(folder)
	, m_ext(ext)
	{}

	T& get(const std::string& filename, bool isFullPath = false)
	{
		if (!exists(filename))
			addResource(filename, isFullPath);

		return m_resources[filename];
	}

	void remove(const std::string& filename)
	{
		m_resources.erase(filename);
	}

private:
	void addResource(const std::string& name, bool isFullPath = false)
	{
		T r;
		std::string fullpath(isFullPath ? name : buildPath(name));

		if (!r.loadFromFile(fullpath))
			r.loadFromFile(buildPath("_fail_"));
		m_resources.emplace(name, r);
	}

	std::string buildPath(const std::string& filename) const
	{
		return m_folder + filename + "." + m_ext;
	}

	bool exists(const std::string& filename) const
	{
		return m_resources.find(filename) != m_resources.end();
	}

private:
	std::unordered_map<std::string, T> m_resources;
	std::string m_folder, m_ext;
};

}