##
## EPITECH PROJECT, 2018
## NETiles
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.0.0)

########################################

function(PREPEND var prefix)
	set(listVar "")
	foreach(f ${ARGN})
		list(APPEND listVar "${prefix}${f}")
	endforeach(f)
	set(${var} "${listVar}" PARENT_SCOPE)
endfunction(PREPEND)

########################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(NETiles)
add_definitions("-std=c++17")
add_definitions("-W -Wall -Wextra")

########################################

set(SERVER_DIR server/)
set(CLIENT_DIR client/)
set(EDITOR_DIR editor/)

set(SERVER_NAME NETiles_Server)
set(CLIENT_NAME NETiles_Client)
set(EDITOR_NAME NETiles_Editor)

########################################

add_subdirectory(${SERVER_DIR})
add_subdirectory(${CLIENT_DIR})
add_subdirectory(${EDITOR_DIR})