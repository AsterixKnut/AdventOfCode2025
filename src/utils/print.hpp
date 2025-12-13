#pragma once

#include <vector>
#include <iostream>
#include <string>

inline void printVector(std::vector<std::string>& vec) {
    for (auto line : vec) {
        std::cout << line << "\n";
    }
}