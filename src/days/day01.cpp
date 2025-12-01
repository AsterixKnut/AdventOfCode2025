#include <iostream>

#include "utils/input.hpp"

namespace day01 {

void solve() {
    // Get lines from input file
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day01.txt");

    // ============================= PART 1 =========================================

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
        while (dial > highestNum) dial -= totalNumbers;
        while (dial < 0) dial += totalNumbers;

        // Update count if we are at 0:
        if (dial == 0) count++;
    }

    std::cout << "Day 1, part 1: " << count << std::endl;

    // ============================ PART 2 =============================================
    count = 0;
    dial = 50;

    // Loop thorugh each line
    for (const auto& line : lines) {
        const char dir = line[0];
        int num = std::stoi(line.substr(1));

        int rotateDirection = 1;
        if (dir == 'L') rotateDirection = -1;

        for (int i = 0; i < std::abs(num); i++) {
            dial += rotateDirection;
            
            if (dial < lowestNum) dial += totalNumbers;
            else if (dial > highestNum) dial -= totalNumbers;

            if (dial == 0) count++;
        }
    }

    std::cout << "Day 1, part 2: " << count << std::endl;
}

}