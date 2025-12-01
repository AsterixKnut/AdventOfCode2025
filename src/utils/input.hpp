#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ios>

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