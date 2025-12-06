#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

#include "utils/input.hpp"
#include "utils/print.hpp"

namespace day06 {

void solve() {
    // Read data
    auto lines = readLines(std::string(PROJECT_DIR) + "/input/day06.txt");

    // ============================= PART 1 ======================================

    // Transform each row into separate strings containing data
    std::vector<std::vector<std::string>> rows = {};
    for (auto line : lines) {
        rows.push_back(splitString(line, ' '));
    }

    // Create a vector contaning empty problems
    std::vector<std::vector<std::string>> problems = {};
    int numProblems = rows[0].size(); // Every row has an equal amount of data entries
    for (int i = 0; i < numProblems; i++) {
        problems.push_back(std::vector<std::string>{}); // Create empty problems for us to fill out
    }

    // Fill problems, so it is easier to work with each problem separately
    for (auto row : rows) {
        for (int i = 0; i < row.size(); i++) {
            problems[i].push_back(row[i]);
        }
    }

    // Calculate the result of each problem:
    std::vector<unsigned long long> sums = {};
    for (auto problem : problems) {
        // Get operation:
        std::string operation = problem.back();
        problem.pop_back();

        unsigned long long sum = 0;
        if (operation == "*") sum = 1;

        for (auto number : problem) {
            unsigned long long num = std::stoull(number);

            if (operation == "+") sum += num;
            else if (operation == "*") sum *= num;
        }

        sums.push_back(sum);
        problem.push_back(operation);
    }

    unsigned long long grandTotal = std::accumulate(sums.begin(), sums.end(), 0ULL);
    std::cout << "Day06, part 1: " << grandTotal << "\n";


    // ============================== PART 2 =========================================

    // We need to preserve spaces now, to be able to generate the correct numbers.
    // The first column in a problem ALWAYS includes the operation to be used.
    // We read until a column, is completely blank, this will be our delimiter

    problems.clear();

    // Generate problems based on new rules:
    std::vector<std::string> currentProblem = {};
    
    for (int col = lines[0].length() - 1; col >= 0; col--) {
        std::string columnStr = "";
        std::string operation = "";
        
        // Generate string containing the numbers (and store operation as last element in currentProblem)
        for (int row = 0; row < lines.size(); row++) {
            char c = lines[row][col];

            if (c == ' ') {
                continue;
            }
            else if (c == '+' || c == '*') {
                operation += c;
            }
            else {
                columnStr += c;
            }
        }

        // Ignore empty strings:
        if (columnStr.empty()) {
            continue;
        }

        // Push the column to the current problem:
        currentProblem.push_back(columnStr);

        // Finally, add operation to the end if it was found, then push our current problem to problems
        if (!operation.empty()) {
            currentProblem.push_back(operation);
            problems.push_back(currentProblem);
            currentProblem.clear();
        }
    }

    // Calculate new sums
    sums.clear();
    for (auto problem : problems) {
        std::string operation = problem.back();
        problem.pop_back();

        unsigned long long sum = 0;
        if (operation == "*") sum = 1;

        for (auto number : problem) {
            unsigned long long num = std::stoull(number);

            if (operation == "+") sum += num;
            else if (operation == "*") sum *= num;
        }

        sums.push_back(sum);
        problem.push_back(operation);
    }

    grandTotal = std::accumulate(sums.begin(), sums.end(), 0ULL);
    std::cout << "Day06, part 1: " << grandTotal << "\n";

}

}