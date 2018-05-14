/*
** EPITECH PROJECT, 2018
** NETiles / Editor
** File description:
** Main.cpp
*/

#include "App.hpp"

int main(int argc, const char **argv)
{
	std::vector<std::string> args(argv, argv + argc);

	if (args.size() != 2) {
		std::cerr << "Usage: " << args[0] << " mapPath" << std::endl;
		return EXIT_FAILURE;
	}

	App *app = new App("NETiles Editor", args);
	int exitCode = app->run();
	delete app;

	return exitCode;
}