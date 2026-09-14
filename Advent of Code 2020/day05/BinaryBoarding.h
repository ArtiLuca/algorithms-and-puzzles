#pragma once 

#include <string>
#include <vector>
#include <stdexcept>

struct BoardingPass {

    std::string pass;
    int row = -1;
    int col = -1;
    int ID = -1;

    int binarySeatPartitioning(int idx, int p, int r);
    void findSeatID();

    bool operator<(const BoardingPass& other) const;
};


class Plane {

public:

    Plane(const std::string& input) : puzzleInput(input) {}

    void readPuzzleInput();

    int solvePart1();
    int solvePart2();

private:

    std::string puzzleInput;
    std::vector<BoardingPass> boardingPasses;

};