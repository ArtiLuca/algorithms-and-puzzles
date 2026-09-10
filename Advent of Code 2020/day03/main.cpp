#include "TobogganTrajectory.h"

#include <iostream>

int main() {

    try {
     
        Toboggan T("input.txt");
        T.readPuzzleInput();

        long long solution1 = T.solvePart1();
        std::cout << "Part 1 Tree Count = " << solution1 << std::endl;

        long long solution2 = T.solvePart2();
        std::cout << "Part 2 Tree Count = " << solution2 << std::endl;
        
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }
    
    return 0;
}