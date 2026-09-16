#include "CustomCustoms.h"

#include <iostream>

int main() {

    try {
     
        Customs customs("input.txt");
        customs.readPuzzleInput();

        int solution1 = customs.solvePart1();
        std::cout << "Part 1 Solution: Total Questions Answered = " << solution1 << std::endl;

        int solution2 = customs.solvePart2();
        std::cout << "Part 2 Solution: Total Questions Answered by all group members = " << solution2 << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }
    
    return 0;
}