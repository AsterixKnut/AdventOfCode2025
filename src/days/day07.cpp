#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

#include "utils/input.hpp"

namespace day07 {

void part1() {
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day07.txt");

    // Store indices for each tachyon beam in the row.
    // We will go down the manifold line by line, updating this vector as we go.
    std::unordered_set<int> beamIndices = {};

    int totalSplits = 0;

    // Setup. We find the index where the beam starts, and update our beam indices:
    beamIndices.insert(lines[0].find('S'));

    // Loop for each line, and update beam indices as they get split:
    for (int row = 1; row < lines.size(); row++) {
        auto beamIndicesCopy = beamIndices; // for modifying while looping over each element

        for (int col : beamIndices) {
            char manifoldType = lines[row][col]; // Free space . or splitter ^ below a beam

            if (manifoldType == '.') continue; // beam continues down (no update neccessary)
            else if (manifoldType == '^') {
                // Remove current beam index, but add a new beam to the left and right
                beamIndicesCopy.insert(col-1);
                beamIndicesCopy.insert(col+1);
                beamIndicesCopy.erase(col);

                totalSplits++;
            }
        }

        beamIndices = beamIndicesCopy;
    }

    std::cout << "Day07, part 1: " << totalSplits << "\n";
}

unsigned long long newBeam(std::vector<std::string>& lines, std::vector<std::vector<unsigned long long>>& computedSplitters, int row, int beamIndex) {
    // Go down until beam hits a splitter
    row++;
    while (row < lines.size()) {
        if (lines[row][beamIndex] == '^') {
            // If we haven't computed the timelines from this splitter yet:
            if (computedSplitters[row][beamIndex] == 0) {
                unsigned long long timelines = 0;

                timelines += newBeam(lines, computedSplitters, row, beamIndex - 1);
                timelines += newBeam(lines, computedSplitters, row, beamIndex + 1);

                computedSplitters[row][beamIndex] = timelines;
                return timelines;
            }
            else {
                return computedSplitters[row][beamIndex];
            }
        }
        row++;
    }

    // If we never split, we reahced the bottom, and the beam only has one timeline
    return 1ULL;
}

void part2() {
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day07.txt");

    // Now, we only need to store one beam index. As we reach a splitter, we will call a recursive
    // function returning all possible timelines from that point.
    int beamIndex = lines[0].find('S');

    // We also need a cache of already calculated timelines, to save redoing many branches again and again.
    int rows = lines.size();
    int cols = lines[0].size();
    std::vector<std::vector<unsigned long long>> computedSplitters(rows, std::vector<unsigned long long>(cols, 0));
    
    unsigned long long totalTimelines = newBeam(lines, computedSplitters, 1, beamIndex);

    std::cout << "Day07, part 2: " << totalTimelines << "\n";
}

void solve () {
    part1();
    part2();
}

}