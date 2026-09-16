#pragma once 

#include <string>
#include <vector>
#include <unordered_map>

// represents a single group of passengers and their answers
struct Group {

    // removed after seeing Part 2
    std::vector<std::string> groupAnswers;
    
    std::unordered_map<char, int> answersCount;
    int passengerCount = 0;

    // helper for Part 2, returns number of questions answered by all members ogf group
    int answeredByAll() const;
};

// represents the customs processing for the puzzle input
class Customs {

public:

    Customs(const std::string& input) : puzzleInput(input) {}

    void readPuzzleInput();

    int solvePart1() const;
    int solvePart2() const;

private:

    std::string puzzleInput;
    std::vector<Group> allGroups;
};