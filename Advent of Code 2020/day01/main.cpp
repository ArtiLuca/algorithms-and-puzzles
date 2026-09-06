#include "ReportRepair.h"

#include <iostream>

int main() {

    try {
        ExpenseReport e("input.txt");
        e.readPuzzleInput();

        int target = 2020;
        long long solution1 = e.solvePart1(target);
        std::cout << "Part 1 Solution = " << solution1 << std::endl;
        long long solution2 = e.solvePart2(target, true);
        std::cout << "Part 2 Solution = " << solution2 << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }

    return 0;
}