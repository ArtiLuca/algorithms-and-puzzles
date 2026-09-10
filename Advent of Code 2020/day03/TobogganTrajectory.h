#pragma once

#include <string>
#include <vector>

const char EMPTY_SPACE = '.';
const char TREE = '#';

class Toboggan {

public:

    Toboggan(const std::string& input) : puzzleInput(input) {}
    void readPuzzleInput();

    long long solvePart1() const;
    long long solvePart2() const;

private:

    long long countTrees(int right, int down) const;

    std::string puzzleInput;
    std::vector<std::string> grid;
};