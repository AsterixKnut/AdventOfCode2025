#include <iostream>
#include <vector>
#include <functional>

namespace day01 { void solve(); }
namespace day02 { void solve(); }
namespace day03 { void solve(); }
namespace day04 { void solve(); }
namespace day05 { void solve(); }

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./aoc <day>\n";
        return 1;
    }

    int day = std::stoi(argv[1]);

    // Solver table
    std::vector<std::function<void()>> solvers = {
        nullptr, // index 0 unsused
        day01::solve,
        day02::solve,
        day03::solve,
        day04::solve,
        day05::solve
    };

    // Warn if selected day is not implemented:
    if (day <= 0 || day >= solvers.size() || !solvers[day]) {
        std::cerr << "Day " << day << " is not implemented\n";
        return 1;
    }

    // Solve
    solvers[day]();

    return 0;
}