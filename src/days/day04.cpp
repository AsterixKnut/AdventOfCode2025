#include <iostream>

#include "utils/input.hpp"

namespace day04 {

void solve() {
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day04.txt");

    // ============================== PART 1 =========================================

    int accessibleRolls = 0;

    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines[row].size(); col++) {
            // For each roll, we check availability in each adjacent (8 neighburing squares).
            // Count it as accessible if three or less neighbours are occupied
            bool isPaperRoll = lines[row][col] == '@';
            if (!isPaperRoll) continue; // Only check the spots that contain paper rolls.

            int occupiedNeighbours = 0;

            for (int r = row - 1; r <= row + 1; r++) {
                for (int c = col - 1; c <= col + 1; c++) {
                    bool isOutOfBounds = r < 0 || r >= lines.size() || c < 0 || c >= lines[row].size();
                    bool isSelf = r == row && c == col;
                    if (isOutOfBounds || isSelf) continue; // In these edge cases the spots are free

                    bool isFree = lines[r][c] == '.';
                    if (isFree) continue;

                    occupiedNeighbours++;
                }
            }

            if (occupiedNeighbours <= 3) {
                accessibleRolls++;
            }
        }
    }

    std::cout << "Day04, part 1: " << accessibleRolls << "\n";

    // ============================ PART 2 ==============================================
    
    int removedRollsTotal = 0;
    auto linesCopy = lines;

    // Do while loop that runs as long as each pass removes some number of rolls:
    do {
        // Reset variables for each pass:
        accessibleRolls = 0;

        // Do a pass:
        for (int row = 0; row < lines.size(); row++) {
            for (int col = 0; col < lines[row].size(); col++) {
                // For each roll, we check availability in each adjacent (8 neighburing squares).
                // Count it as accessible if three or less neighbours are occupied
                bool isPaperRoll = lines[row][col] == '@';
                if (!isPaperRoll) continue; // Only check the spots that contain paper rolls.

                int occupiedNeighbours = 0;

                for (int r = row - 1; r <= row + 1; r++) {
                    for (int c = col - 1; c <= col + 1; c++) {
                        bool isOutOfBounds = r < 0 || r >= lines.size() || c < 0 || c >= lines[row].size();
                        bool isSelf = r == row && c == col;
                        if (isOutOfBounds || isSelf) continue; // In these edge cases the spots are free

                        bool isFree = lines[r][c] == '.';
                        if (isFree) continue;

                        occupiedNeighbours++;
                    }
                }

                if (occupiedNeighbours <= 3) {
                    accessibleRolls++;
                    linesCopy[row][col] = '.'; // Remove the roll in our copy
                }
            }
        }

        // Update totals and map of rolls:
        removedRollsTotal += accessibleRolls;
        lines = linesCopy;

    } while (accessibleRolls != 0);

    std::cout << "Day04, part 2: " << removedRollsTotal << "\n";
}

}