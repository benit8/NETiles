##
## EPITECH PROJECT, 2018
## NETiles / Server
## File description:
## CMakeLists
##

set(SERVER_SOURCE_DIR src/)
set(SERVER_INCLUDE_DIR include/)

PREPEND(SERVER_SOURCES ${SERVER_SOURCE_DIR}
	Main.cpp
)

PREPEND(SERVER_INCLUDES ${SERVER_INCLUDE_DIR}
	Server.hpp
)

add_executable(${SERVER_NAME} ${SERVER_SOURCES} ${SERVER_INCLUDES})
target_include_directories(${SERVER_NAME} PUBLIC ${SERVER_INCLUDE_DIR})
# target_link_libraries(${SERVER_NAME} sfml-graphics sfml-system sfml-window)