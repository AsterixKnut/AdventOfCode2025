#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "utils/input.hpp"


namespace day05 {

struct Range {
    unsigned long long start;
    unsigned long long end;
};

void printRanges(std::vector<Range>& ranges) {
    for (Range range : ranges) {
        std::cout << range.start << "\t" << range.end << "\n";
    }
}

void solve() {

    // Read data
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day05.txt");

    // Split data into ranges and IDs
    std::vector<Range> unmergedRanges = {};
    std::vector<unsigned long long> IDs = {};

    bool blankLineReached = false;
    for (auto line : lines) {
        if (line == "") {
            blankLineReached = true;
            continue;
        }

        if (!blankLineReached) {
            // Split range start and end and store that in a Range struct:
            auto rangesStr = splitString(line, '-');

            unsigned long long start = std::stoull(rangesStr[0]);
            unsigned long long end = std::stoull(rangesStr[1]);

            unmergedRanges.emplace_back(Range{start, end});
        }
        else {
            IDs.push_back(std::stoull(line));
        }
    }

    // ============================ PART 1 ======================================

    // Create merged ranges:
    std::vector<Range> ranges = {};

    std::sort(unmergedRanges.begin(), unmergedRanges.end(), [](const Range& a, const Range& b) {return a.start < b.start; }); // Sort based on start

    unsigned long long currentStart = unmergedRanges[0].start;
    unsigned long long currentEnd = unmergedRanges[0].end;

    for (int i = 1; i < unmergedRanges.size(); i++) {
        bool shouldMerge = unmergedRanges[i].start <= currentEnd + 1;

        if (shouldMerge) {
            currentEnd = std::max(currentEnd, unmergedRanges[i].end);
        }
        else {
            ranges.emplace_back(Range{currentStart, currentEnd});
            currentStart = unmergedRanges[i].start;
            currentEnd = unmergedRanges[i].end;
        }
    }
    ranges.emplace_back(Range{currentStart, currentEnd});

    unsigned long long numFreshIngredients = 0;

    for (auto ID : IDs) {
        // Binary search to check if each ID is in any range:
        int left = 0;
        int right = ranges.size() - 1;

        while (left <= right) {
            // Calculate mid-point:
            int middle = left + (right - left) / 2;

            // Chek if ID is in range:
            bool isInRange = ID >= ranges[middle].start && ID <= ranges[middle].end;
            if (isInRange) {
                numFreshIngredients++;
                break;
            }

            // Move to the left or right based on if the range was lower or higher:
            bool moveLeft = ID < ranges[middle].start;
            bool moveRight = ID > ranges[middle].end;

            if (moveLeft) {
                right = middle - 1;
            }
            else if (moveRight) {
                left = middle + 1;
            }
        }
    }

    std::cout << "Day05, part 1: " << numFreshIngredients << "\n";

    // ============================= Part 2 ====================================

    // We have already merged the ingredient list, so getting the number of fresh ingredient IDs is trivial:
    unsigned long long numFreshIngedientIDs = 0;
    for (Range range : ranges) {
        numFreshIngedientIDs += range.end - range.start + 1;
    }

    std::cout << "Day05, part 2: " << numFreshIngedientIDs << "\n";
}

}