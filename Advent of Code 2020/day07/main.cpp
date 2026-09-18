#include "HandyHaversacks.h"

#include <iostream>

int main() {

    try {
     
        Haversacks haversacks("input.txt");
        haversacks.readPuzzleInput();

        int solution1 = haversacks.solvePart1();
        std::cout << "Part 1 Solution: Number of bags that can hold out shiny gold bag = " << solution1 << std::endl;

        int solution2 = haversacks.solvePart2();
        std::cout << "Part 2 Solution: Required number of bags inside shiny gold bag = " << solution2 << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }
    
    return 0;
}