# Simple cmake to start
cmake_minimum_required(VERSION 3.28)

project(AdventOfCode2025)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB DAY_SOURCES "src/days/*.cpp")
add_executable(aoc src/main.cpp ${DAY_SOURCES})

target_include_directories(aoc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_definitions(aoc PRIVATE PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")