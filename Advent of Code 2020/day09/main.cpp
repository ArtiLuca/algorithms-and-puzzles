#include "EncodingError.h"

#include <iostream>

int main() {

    try {

        Cypher xmas("input.txt");
        xmas.readPuzzleInput();

        long long solution1 = xmas.solvePart1();
        std::cout << "Part 1 Solution = First non-valid sum found at number " << solution1 << std::endl;

        long long solution2 = xmas.solvePart2(solution1);
        std::cout << "Part 2 Solution = Sum of smallest and largest in contiguous set found = " << solution2 << std::endl;
    
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; 
    }
    
    return 0;
}
