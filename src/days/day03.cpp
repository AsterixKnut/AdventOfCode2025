#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>
#include <algorithm>

#include "utils/input.hpp"

namespace day03 {

class Arrow {
public:
    Arrow(int index, char highest) {
        index_ = index;
        prevHighest_ = '\0';
        highest_ = highest;
    }

    void setHighest(char newHighest) {
        prevHighest_ = highest_;
        highest_ = newHighest;
    }

    int index_;
    char highest_;
    char prevHighest_;
};

unsigned long long getFirstMax(std::string& string, int numBatteries, std::vector<char>& maxValues) {
    unsigned long long sum = 0ull;
    unsigned long long power = 1;

    int lastIndex = string.size() - 1;

    for (int i = 0; i < numBatteries; i++) {
        sum += (string[lastIndex - i]-'0') * power;
        maxValues.push_back(string[lastIndex - i]); // Add current max values

        power *= 10;
    }

    std::reverse(maxValues.begin(), maxValues.end());

    return sum;
}

unsigned long long calculateSum(char newValue, std::vector<char>& values) {
    unsigned long long sum = 0;
    unsigned long long power = 1;

    int lastIndex = values.size() - 1;

    for (int i = lastIndex; i >= 0; i--) {
        sum += (values[i] - '0') * power;
        power *= 10;
    }

    sum += (newValue - '0') * power;

    return sum;
}

void solve() {
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day03.txt");

    std::vector<unsigned long long> joltages{};
    joltages.reserve(lines.size());

    // ========================= PART 1 ==================================0

    for (auto line : lines) {
        Arrow left(0, line[0]);
        Arrow right(line.size() - 1, line[line.size() - 1]);

        // Move arrows until they are next to each other:
        while (right.index_ - left.index_ > 1) {
            // Choose wether to move left or right arrow:
            int indexShift = 1;
            Arrow* selectedArrow = &left;

            if (left.highest_ > right.highest_) {
                indexShift = -1;
                selectedArrow = &right;
            }

            // Move arrow and update highest if neccessary:
            selectedArrow->index_ += indexShift;
            char newValue = line[selectedArrow->index_];
            if (newValue > selectedArrow->highest_) {
                selectedArrow->setHighest(newValue);
            }
        }

        // Three possible sets of highest numbers:   
        int leftNumber, middleNumber, rightNumber;
        middleNumber = (left.highest_ - '0')*10 + (right.highest_ - '0');
        leftNumber = (left.prevHighest_ == '\0') ? 0 : (left.prevHighest_ - '0')*10 + (left.highest_ - '0');
        rightNumber = (right.prevHighest_ == '\0') ? 0 : (right.highest_ - '0')*10 + (right.prevHighest_ - '0');
        
        // Comparison:
        int highest = leftNumber;
        if (middleNumber > leftNumber) highest = middleNumber;
        if (rightNumber > middleNumber) highest = rightNumber;

        joltages.push_back(static_cast<unsigned long long>(highest));
    }

    int sum = std::accumulate(joltages.begin(), joltages.end(), 0);

    std::cout << "Day 03, part 1: " << sum << std::endl;

    // ================================ PART 2 =========================================
    joltages.clear();
    joltages.reserve(lines.size());

    for (auto line : lines) {
        int numBatteries = 12;
        std::vector<char> maxValues{};
        unsigned long long maxJoltage = getFirstMax(line, numBatteries - 1, maxValues);

        int index = line.size() - numBatteries;
        for (index; index >= 0; index--) {
            unsigned long long newMax = calculateSum(line[index], maxValues);

            if (newMax <= maxJoltage) continue;

            maxJoltage = newMax;
            auto newMaxValues = maxValues;
            char currentBattery = line[index];

            for (int i = 0; i < maxValues.size(); i++) {
                if (currentBattery < maxValues[i]) break; // Only update the maxValue (and all following it) if the current battery is equal or larger

                newMaxValues[i] = currentBattery;
                currentBattery = maxValues[i];
            }

            maxValues = newMaxValues;
        }

        joltages.push_back(maxJoltage);
    }

    unsigned long long sum2 = std::accumulate(joltages.begin(), joltages.end(), 0ULL);

    std::cout << "Day 03, part 2: " << sum2 << std::endl;
}

}