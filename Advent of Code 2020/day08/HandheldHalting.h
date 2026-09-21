#pragma once 

#include <string>
#include <vector>
#include <utility>

// represents a single instruction parsed from input
struct Instruction {

    int index;               // index in program line order
    std::string operation;   // operation type
    int argument;            // operation value
};


// represents boot code for handhelo gaming console
class BootCode {

public:

    // constructor
    BootCode(const std::string& input) : puzzleInput(input) {}

    // read and parse puzzle input
    void readPuzzleInput();

    // returns accumulator value before start of infinite loop
    int solvePart1() const;
    // returns accumulator value after correctly swapping a single "nop" or "jmp" instruction
    int solvePart2();

private:

    // helper for solving Part 2, returns accumulator value and whether or not infinite loop was detected
    std::pair<int,bool> runSimulation();

    // private members
    std::string puzzleInput;
    std::vector<Instruction> instructions;
};