#include "PasswordPhilosophy.h"

#include <iostream>

int main() {

    try {
        Database db("input.txt");
        db.readPuzzleInput();
        int solution1 = db.solvePart1();
        std::cout << "Part 1 Solution = " << solution1 << std::endl;
        int solution2 = db.solvePart2();
        std::cout << "Part 2 Solution = " << solution2 << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }
    return 0;
}