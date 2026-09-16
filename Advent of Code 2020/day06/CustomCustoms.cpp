#include "CustomCustoms.h"

#include <fstream>
#include <stdexcept>

// =============== PUZZLE INPUT & HELPERS ===============

void Customs::readPuzzleInput() {

    // clear previous
    allGroups.clear();

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    // read input line by line, parsing each group, using boolean flag 
    std::string line;
    Group current;
    // indicates if a group has been fully parsed or is empty
    bool hasAnswers = false;

    while (std::getline(file, line)) {

        // if we encounter a blank line
        if (line.empty()) {
            // and the current group has been fully processed
            if (hasAnswers) {
                // we push into vector and reset for next group
                allGroups.push_back(current);
                current = Group();
                hasAnswers = false;
            }
        }
        else { // otherwise, process each person in the group
            current.passengerCount++;
            current.groupAnswers.push_back(line);
            for (char ch : line) {
                // update (question -> frequency) map
                current.answersCount[ch]++;
            }

            // set boolean flat to true
            hasAnswers = true;
        }
    }

    // sanity check, as to not skip very last group
    if (hasAnswers) {
        allGroups.push_back(current);
    }

    file.close();
}


// =============== PART 1 ===============

int Customs::solvePart1() const {

    // guard
    if (allGroups.empty()) {
        return -1;
    }

    int count = 0;

    for (const Group& group : allGroups) {
        
        // add each group's distinct (key,value) pairs
        count += group.answersCount.size();
    }

    return count;
}


// =============== PART 2 ===============

int Group::answeredByAll() const {

    // guard
    if (answersCount.empty()) {
        return 0;
    }

    int count = 0;
    
    // range-based loop
    for (const std::pair<const char, int>& answers : answersCount) {
        // check if all people in group answered
        if (answers.second == passengerCount) {
            // if so, increment total count
            count++; 
        }
    }
    
    return count;
}


int Customs::solvePart2() const {

    // guard
    if (allGroups.empty()) {
        return -1;
    }

    int count = 0;

    // range-based loop
    for (const Group& group : allGroups) {
        // count all questions answered by all people in each group
        count += group.answeredByAll();
    }
    
    return count;
}