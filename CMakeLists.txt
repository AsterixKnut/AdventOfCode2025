# Simple cmake to start
cmake_minimum_required(VERSION 3.28)

project(AdventOfCode2025)

file(GLOB DAY_SOURCES "src/days/*.cpp")
add_executable(aoc src/main.cpp ${DAY_SOURCES})