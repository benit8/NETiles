/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / GUI.cpp
*/

#include "GUI.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

Widget *getRoot()
{
	return &Env::root;
}

void handleEvent(sf::Event &e)
{
	getRoot()->handleEvent(e);
}

////////////////////////////////////////////////////////////////////////////////

}