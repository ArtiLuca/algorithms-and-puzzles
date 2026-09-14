#include "BinaryBoarding.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>

namespace SeatingLetters {

    constexpr char FRONT = 'F';
    constexpr char BACK = 'B';
    constexpr char LEFT = 'L';
    constexpr char RIGHT = 'R';
};

// =============== PUZZLE INPUT & HELPERS ===============

int BoardingPass::binarySeatPartitioning(int idx, int p, int r) {

    using namespace SeatingLetters;

    // base case
    if (p == r) {
        return p;
    }

    // calculate midpoint 
    int q = p + (r - p) / 2;

    // if character is 'F' or 'L' we take lower half
    if (pass[idx] == FRONT || pass[idx] == LEFT) {

        return binarySeatPartitioning(idx + 1, p, q);
    }
    // otherwise, if character is 'B' or 'R' we take upper half 
    else { 

        return binarySeatPartitioning(idx + 1, q+1, r);
    }
}

void BoardingPass::findSeatID() {

    // find seat row and column
    row = binarySeatPartitioning(0, 0, 127);
    col = binarySeatPartitioning(7, 0, 7);

    // only update unique seat ID if row and column were successfully found
    if (row >= 0 && col >= 0) {
        ID = (row * 8) + col;
    }
}

void Plane::readPuzzleInput() {

    // clear previous
    boardingPasses.clear();

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    std::string line;
    while (std::getline(file, line)) {
        
        BoardingPass current;
        current.pass = line;
        current.findSeatID();
        if (current.ID == -1) {
            throw std::runtime_error("Computed invalid seat ID");
        }
        else {
            boardingPasses.push_back(current);
        }
    }

    file.close();
}

// =============== PART 1 ===============

int Plane::solvePart1() {

    // use first boarding pass as initial max
    int maxID = boardingPasses[0].ID;

    // iterate all boarding passes 
    for (int i = 1; i < (int)boardingPasses.size(); i++) {
        if (boardingPasses[i].ID > maxID) {
            
            // update if we find a higher seat ID
            maxID = boardingPasses[i].ID;
        }
    }

    return maxID;
}

// =============== PART 2 ===============

bool BoardingPass::operator<(const BoardingPass& other) const {

    return this->ID < other.ID;
}

int Plane::solvePart2() {

    // sort all boarding passes in increasing order of seat ID
    std::sort(boardingPasses.begin(), boardingPasses.end());
    
    // iterate all 
    for (int i = 0; i < (int)boardingPasses.size() - 2; i++) {

        // if we find two seats that have ID exactly 1 empty seat between them
        if (boardingPasses[i+1].ID - boardingPasses[i].ID == 2) {

            // we found our seat, so we return
            return boardingPasses[i+1].ID - 1;
        }
    }
    
    // if our seat was somehow not found
    return -1;
}