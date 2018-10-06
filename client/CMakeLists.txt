##
## EPITECH PROJECT, 2018
## NETiles / Client
## File description:
## CMakeLists
##

set(CLIENT_SOURCE_DIR src/)
set(CLIENT_INCLUDE_DIR include/)

PREPEND(CLIENT_SOURCES ${CLIENT_SOURCE_DIR}
	Main.cpp
)

PREPEND(CLIENT_INCLUDES ${CLIENT_INCLUDE_DIR}
	Client.hpp
)

add_executable(${CLIENT_NAME} ${CLIENT_SOURCES} ${CLIENT_INCLUDES})
target_include_directories(${CLIENT_NAME} PUBLIC ${CLIENT_INCLUDE_DIR})
# target_link_libraries(${CLIENT_NAME} sfml-graphics sfml-system sfml-window)