#pragma once

#include <string>
#include <vector>

// represents XMAS cypher
class Cypher {

public:
    
    // constructor
    Cypher(const std::string& input) : puzzleInput(input) {}

    // read numbers from input
    void readPuzzleInput();

    // returns first non-valid number
    long long solvePart1() const;

    // return sum of smallest and largest in contiguous set that sums to Part 1's solution
    long long solvePart2(long long target) const;

private:

    // private helper for checking if current number is sum of previous preamble
    bool hasValidSum(long long target, int start) const;

    std::string puzzleInput;
    std::vector<long long> numbers;
};