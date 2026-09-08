#pragma once

#include <string>
#include <vector>

struct Password {
    int low;
    int high;
    char c;
    std::string psw;

    bool isValidPart1() const;
    bool isValidPart2() const;
};

class Database {

public:

    // constructor
    Database(const std::string& input) : puzzleInput(input) {}

    void readPuzzleInput();
    int solvePart1() const;
    int solvePart2() const;

private:

    std::string puzzleInput;
    std::vector<Password> password;

};