#include "HandheldHalting.h"

#include <iostream>

int main() {

    try {

        BootCode boot("input.txt");
        boot.readPuzzleInput();
        int solution1 = boot.solvePart1();
        std::cout << "Part 1 Solution: Accumulator value before infinite loop = " << solution1 << std::endl;

        int solution2 = boot.solvePart2();
        std::cout << "Part 2 Solution: Accumulator value after successful swap = " << solution2 << std::endl;
     
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }
    
    return 0;
}

