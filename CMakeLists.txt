cmake_minimum_required(VERSION 2.8)

project(MQTT_BROKER)

OPTION(DEBUG "add debug flags" OFF)

if (DEBUG)
    message(STATUS "Configuring build for debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wunused -Werror -std=c11 -O3 -pedantic -luuid -ggdb -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -pg")
else (DEBUG)
    message(STATUS "Configuring build for production")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wunused -Werror -Wextra -std=c11 -O3 -pedantic -luuid")
endif (DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

file(GLOB SOURCES src/*.c)

# Executable
add_executable(MQTT_BROKER ${SOURCES})