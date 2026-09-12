#include "PassportProcessing.h"

#include <iostream>

int main() {

    try {
     
        Scanner scan("input.txt");
        scan.readPuzzleInput();

        int solution1 = scan.solvePart1();
        std::cout << "Part 1: Number of valid passports = " << solution1 << std::endl;

        int solution2 = scan.solvePart2();
        std::cout << "Part 2: Number of valid passports = " << solution2 << std::endl;
        
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }
    
    return 0;
}