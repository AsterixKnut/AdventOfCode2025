#include <iostream>
#include <string>
#include <vector>

#include "utils/input.hpp"

namespace day02 {

void solve() {
    std::string str = "ABC,DEF";
    auto strs = splitString(str, ',');
    std::cout << strs[0] << "\t" << strs[1] << std::endl;
}

}