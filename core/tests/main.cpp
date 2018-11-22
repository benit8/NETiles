/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** Core / tests / main.cpp
*/

#include "../Application.hpp"
#include "TestState.hpp"

int main(int argc, char *argv[])
{
	Application app(argc, argv);
	app.setAppName("NETiles");
	app.pushState<TestState>(&app);
	app.setWindowMode(Application::Windowed, {1280, 720});

	return app.run();
}