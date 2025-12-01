#include <iostream>

#include "utils/input.hpp"

namespace day01 {

void solve() {
    // Get lines from input file
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day01.txt");

    // Variables to find solution:
    int count = 0;
    int dial = 50;
    const int lowestNum = 0;
    const int highestNum = 99;
    const int totalNumbers = highestNum + 1 - lowestNum;

    // Loop thorugh each line
    for (const auto& line : lines) {
        const char dir = line[0];
        int num = std::stoi(line.substr(1));

        // If first letter is L, we should rotate to the left. This is the same as adding -num:
        if (dir == 'L') num = -num;

        // Roate the dial
        dial += num;

        // Make sure the dial points to a legal number:
        while (dial> highestNum) { dial -= totalNumbers; }
        while (dial < 0) { dial += totalNumbers; }

        // Update count if we are at 0:
        if (dial == 0) count++;
    }

    std::cout << "Day 1, part 1: " << count << std::endl;
}

}