#include "TobogganTrajectory.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

// =============== PUZZLE INPUT ===============

void Toboggan::readPuzzleInput() {

    // cleanup previous
    grid.clear();

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    std::string str;
    while (std::getline(file, str)) {
        if (!str.empty()) {
            grid.push_back(str);
        }
    }
}

// =============== PART 1 ===============

long long Toboggan::solvePart1() const {

    long long treeCount = 0;
    int rows = grid.size();
    int cols = grid[0].length();

    int r = 0;
    int c = 0;

    while (r < rows) {

        if (grid[r][c % cols] == TREE) {
            treeCount++;
        }

        r += 1;
        c += 3;
    }
    return treeCount;
}

// =============== PART 2 ===============

long long Toboggan::countTrees(int right, int down) const {

    long long treeCount = 0;
    int rows = grid.size();
    int cols = grid[0].length();

    int r = 0;
    int c = 0;

    while (r < rows) {

        // check if we landed on a tree
        if (grid[r][c % cols] == TREE) {
            treeCount++;
        }

        // move down slope
        r += down;
        c += right;
    }
    return treeCount;
}

long long Toboggan::solvePart2() const {

    // guard
    if (grid.empty()) {
        return 0;
    }

    long long tc1 = countTrees(1,1);
    long long tc2 = countTrees(3,1);
    long long tc3 = countTrees(5,1);
    long long tc4 = countTrees(7,1);
    long long tc5 = countTrees(1,2);

    return tc1 * tc2 * tc3 * tc4 * tc5;
}