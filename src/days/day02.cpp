#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#include "utils/input.hpp"

namespace day02 {

void solve() {
    std::vector<unsigned long long> invalidIDs{};

    auto line = readLines(std::string(PROJECT_DIR) + "/input/day02.txt");
    auto ranges = splitString(line[0], ','); // Only one long line in input-file

    //unsigned long long sum = 0;

    for (auto range : ranges) {
        
        const auto minMaxStrs = splitString(range, '-');
        const unsigned long long min = std::stoull(minMaxStrs[0]);
        const unsigned long long max = std::stoull(minMaxStrs[1]);


        for (unsigned long long i = min; i <= max; i++) {
            std::string currentID = std::to_string(i);
            const int digitCount = currentID.size();

            if (digitCount % 2 != 0) {
                continue; // Only IDs with even digit count can be wrong
            }

            std::string currentIDleft = currentID.substr(0, digitCount/2);
            std::string currentIDright = currentID.substr(digitCount/2, digitCount/2);

            if (currentIDleft == currentIDright) {
                invalidIDs.push_back(i);
                //sum += i;
                //std::cout << currentID << "\t" << currentIDleft << "\t" << currentIDright << "\t" << sum << std::endl;
            }
        }
    }

    const unsigned long long sum = std::accumulate(invalidIDs.begin(), invalidIDs.end(), 0ULL);

    std::cout << "Day 2, part 1: " << sum << std::endl;

}

}