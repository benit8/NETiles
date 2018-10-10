##
## EPITECH PROJECT, 2018
## NETiles / Editor
## File description:
## CMakeLists
##

set(EDITOR_SOURCE_DIR src/)
set(EDITOR_INCLUDE_DIR include/)

PREPEND(EDITOR_SOURCES ${EDITOR_SOURCE_DIR}
	App.cpp
	Display.cpp
	Main.cpp
	Ressources/Manager.cpp
	States/Main.cpp
	Tiles/Cursor.cpp
	Tiles/LevelFactory.cpp
	Tiles/LevelReaderLVL2.cpp
	Tiles/Map.cpp
	Tiles/Tile.cpp
)

PREPEND(EDITOR_INCLUDES ${EDITOR_INCLUDE_DIR}
	App.hpp
	Display.hpp
	Ressources/Container.hpp
	Ressources/Manager.hpp
	States/All.hpp
	States/Main.hpp
	States/Menu.hpp
	States/State.hpp
	Tiles/Cursor.hpp
	Tiles/ILevelReader.hpp
	Tiles/ILevelWriter.hpp
	Tiles/LevelFactory.hpp
	Tiles/LevelReaderLVL2.hpp
	Tiles/Map.hpp
	Tiles/Tile.hpp
	Utils/Singleton.hpp
)

add_executable(${EDITOR_NAME} ${EDITOR_SOURCES} ${EDITOR_INCLUDES})
target_include_directories(${EDITOR_NAME} PUBLIC ${EDITOR_INCLUDE_DIR})
target_link_libraries(${EDITOR_NAME} sfml-audio sfml-graphics sfml-system sfml-window sfgui)