/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Utils / Singleton.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class Singleton
{
public:
	Singleton(Singleton &other) = delete;
	Singleton(Singleton &&other) = delete;
	Singleton &operator =(Singleton &other) = delete;
	Singleton &operator =(Singleton &&other) = delete;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;
};