#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ios>
#include <sstream>


inline std::vector<std::string> readLines(const std::string& filepath) {
    std::vector<std::string> lines{};
    lines.reserve(1024);
    std::string line;

    std::ifstream readFile(filepath);
    if (!readFile) {
        std::cerr << "Failed to read " << filepath << std::endl;
        return lines;
    }

    while (std::getline(readFile, line)) {
        lines.push_back(line);
    }

    readFile.close();

    return lines;
}

inline std::vector<std::string> splitString(const std::string& string, const char delim) {
    std::vector<std::string> splits{};
    std::string split;

    std::stringstream ss(string);

    while (std::getline(ss, split, delim)) {
        splits.push_back(split);
    }

    return splits;
}