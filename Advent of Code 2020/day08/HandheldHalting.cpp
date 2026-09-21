#include "HandheldHalting.h"

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <unordered_set>

namespace OperationTypes {
    const std::string ACC = "acc";
    const std::string NOP = "nop";
    const std::string JMP = "jmp";
};

// =============== PUZZLE INPUT ===============

void BootCode::readPuzzleInput() {

    // clear previous
    instructions.clear();

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    // read input line by line, incrementing instruction index 
    std::string line;
    int ind = 0;

    while (std::getline(file, line)) {

        Instruction istr;

        // parse line into Instruction
        std::istringstream ss(line);
        if (ss >> istr.operation >> istr.argument) {
            istr.index = ind;
            ind++;
            instructions.push_back(istr);
        }
    }

    file.close();
}

// =============== PART 1 ===============

int BootCode::solvePart1() const {

    using namespace OperationTypes;

    // guard
    if (instructions.empty()) {
        throw std::runtime_error("No instructions found...");
    }

    // number of instructions
    int n = instructions.size();

    // initialize accumulator, current index, and hash set
    int accumulator = 0;
    int currentIndex = 0;
    std::unordered_set<int> seen;

    // as long as the current index is within bounds
    while (currentIndex >= 0 && currentIndex < n) {

        // check if we already saw this instruction
        if (!seen.insert(currentIndex).second) {
            // if so, we return the accumulator
            return accumulator;
        }

        // otherwise, we take the current instruction as const reference
        const Instruction& currentInstruction = instructions[currentIndex];

        // update depending on instruction type
        if (currentInstruction.operation == ACC) {
            accumulator += currentInstruction.argument;
            currentIndex++;
        }
        else if (currentInstruction.operation == JMP) {
            currentIndex += currentInstruction.argument;
        }
        else if (currentInstruction.operation == NOP) {
            currentIndex++;
        }
    }

    // return accumulator
    return accumulator;
}


// =============== PART 2 ===============

std::pair<int,bool> BootCode::runSimulation() {

    using namespace OperationTypes;

    int n = instructions.size();
    int accumulator = 0;
    int currentIndex = 0;
    std::unordered_set<int> seen;

    // as long as the current index is within bounds
    while (currentIndex >= 0 && currentIndex < n) {

        // check if we already saw this instruction 
        if (!seen.insert(currentIndex).second) {
            // if so, we ecountered an infinite loop
            return {accumulator, false};
        }

        // otherwise, we apply Part 1 logic
        const Instruction& currentInstruction = instructions[currentIndex];

        if (currentInstruction.operation == ACC) {
            accumulator += currentInstruction.argument;
            currentIndex++;
        }
        else if (currentInstruction.operation == JMP) {
            currentIndex += currentInstruction.argument;
        }
        else if (currentInstruction.operation == NOP) {
            currentIndex++;
        }
    }

    // it the currentIndex reaches exactly n, then the simulation ran successfully
    return {accumulator, currentIndex == n};
}

int BootCode::solvePart2() {

    // guard
    if (instructions.empty()) {
        throw std::runtime_error("No instructions found...");
    }

    using namespace OperationTypes;

    // iterate through list of instructions
    for (int i = 0; i < (int)instructions.size(); i++) {

        // skip "acc" instructions
        if (instructions[i].operation == ACC) {
            continue;
        }

        // save original instruction operation before swapping
        std::string originalOperation = instructions[i].operation;

        // perform swap
        if (instructions[i].operation == JMP) {
            instructions[i].operation = NOP;
        }
        else if (instructions[i].operation == NOP) {
            instructions[i].operation = JMP;
        }

        // run simulation after the swap
        std::pair<int,bool> simulation = runSimulation();

        // if simulation was successful
        if (simulation.second) {
            // return the accumulator value
            return simulation.first;
        }

        // otherwise, revert instruction to original operation
        instructions[i].operation = originalOperation;
    }

    // if no swap worked
    throw std::runtime_error("No swap resulted in valid boot code simulation"); 
}