#include <iostream>
#include <vector>
#include <string>
#include <numeric>

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

void solve() {
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day03.txt");

    std::vector<int> joltages{};
    joltages.reserve(lines.size());

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

        joltages.push_back(highest);
    }

    int sum = std::accumulate(joltages.begin(), joltages.end(), 0);

    std::cout << "Day 03, part 1: " << sum << std::endl;
}

}