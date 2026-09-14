#include "BinaryBoarding.h"

#include <iostream>

int main() {

    try {
        
        Plane plane("input.txt");
        plane.readPuzzleInput();
        
        int solution1 = plane.solvePart1();
        std::cout << "Part 1 Solution: Highest Seat ID = " << solution1 << std::endl;

        int solution2 = plane.solvePart2();
        std::cout << "Part 2 Solution: Out seat has ID = " << solution2 << std::endl;

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }

    return 0;
}