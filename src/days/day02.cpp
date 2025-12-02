#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <array>
#include <unordered_set>

#include "utils/input.hpp"

namespace day02 {

void solve() {
    std::unordered_set<unsigned long long> invalidIDs{};

    auto line = readLines(std::string(PROJECT_DIR) + "/input/day02.txt");
    auto ranges = splitString(line[0], ','); // Only one long line in input-file

    // ============================== PART 1 ====================================

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
                invalidIDs.insert(i);
                //sum += i;
                //std::cout << currentID << "\t" << currentIDleft << "\t" << currentIDright << "\t" << sum << std::endl;
            }
        }
    }

    const unsigned long long sum1 = std::accumulate(invalidIDs.begin(), invalidIDs.end(), 0ULL);
    std::cout << "Day 2, part 1: " << sum1 << std::endl;

    // ============================================ PART 2 ============================================================

    invalidIDs.clear();

    for (auto range : ranges) {
        
        const auto minMaxStrs = splitString(range, '-');
        const unsigned long long min = std::stoull(minMaxStrs[0]);
        const unsigned long long max = std::stoull(minMaxStrs[1]);

        for (unsigned long long i = min; i <= max; i++) {
            std::string currentID = std::to_string(i);
            const int digitCount = currentID.size();

            for (int numSplits = 2; numSplits <= digitCount; numSplits++) {
                if (digitCount % numSplits != 0) {
                    continue; // there can only be repeats if numSplits plits the word into equal parts
                }

                std::vector<std::string> splits{};
                for (int i = 0; i < numSplits; i++) {
                    int offset = digitCount / numSplits;
                    int start = i * offset;
                    splits.push_back(currentID.substr(start, offset));
                }

                // Comparison
                bool isEqual = true;
                for (int i = 1; i < numSplits; i++) {
                    if (splits[0] != splits[i]) {
                        isEqual = false;
                        break;
                    }
                }

                if (isEqual) {
                    invalidIDs.insert(i);
                    break;
                }
            }
        }
    }

    const unsigned long long sum2 = std::accumulate(invalidIDs.begin(), invalidIDs.end(), 0ULL);
    std::cout << "Day 2, part 2: " << sum2 << std::endl;

}

}