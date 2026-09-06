#pragma once

#include <string>
#include <vector>

class ExpenseReport {

public:

    // constructor
    ExpenseReport(const std::string& input) : puzzleInput(input) {}
    
    // read puzzle input (expense report)
    void readPuzzleInput();

    // solves Part 1 using two-pointer approach 
    long long solvePart1(int target) const;

    // uses two-pointer approach with first element of triplet fixed
    long long solvePart2_TwoPointer(int target) const;
    // uses hash set approach
    long long solvePart2_HashingSet(int target) const;
    // wrapper for solving Part 2
    long long solvePart2(int target, bool useHashing = false) const;

private:

    // private members
    std::string puzzleInput;
    std::vector<int> report;
};

