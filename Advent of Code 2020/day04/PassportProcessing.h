#pragma once

#include <string>
#include <vector>

struct Passport {

    // passport fields
    std::string byr, iyr, eyr, hgt, hcl, ecl, pid, cid;

    // helper for setting parsed input
    void setField(const std::string& key, const std::string& value);

    // validates passport with Part 1 constraints
    bool isValidPart1() const;


    // validates passport with Part 2 constraints, using helpers below
    bool isValidPart2() const;

    // checks if string is made up entirely of digits
    bool isAllDigits(const std::string& str) const; 
    // validates year fields
    bool isValidYear(const std::string& str, int min, int max) const;
    // validates height field
    bool isValidHeight() const;
    // validates hair color field
    bool isValidHairColor() const;
    // validates eye color field
    bool isValidEyeColor() const;
    // validates passport id field
    bool isValidPassportID() const;
};

class Scanner {

public:

    // constructor
    Scanner(const std::string& input) : puzzleInput(input) {}

    // parses all passports and their data    
    void readPuzzleInput();

    // returns total valid passports for Part 1    
    int solvePart1() const;

    // returns total valid passports for Part 2    
    int solvePart2() const;


private:

    // private members
    std::string puzzleInput;
    std::vector<Passport> passports;
};