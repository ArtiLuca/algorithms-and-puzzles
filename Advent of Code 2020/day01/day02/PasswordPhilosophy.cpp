#include "PasswordPhilosophy.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

// =============== PUZZLE INPUT ===============

void Database::readPuzzleInput() {

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    std::string str;
    while (std::getline(file, str)) {
        
        int i, j;
        char ch, dash, colon;
        std::string s;

        std::istringstream ss(str);

        ss >> i >> dash >> j >> ch >> colon >> s;
        Password p;
        p.low = i; 
        p.high = j; 
        p.c = ch; 
        p.psw = s; 
        password.push_back(p);
    }
}

// =============== PART 1 ===============

bool Password::isValidPart1() const {

    if (psw.empty()) return false;

    int count = 0;
    for (int i = 0; i < (int)psw.length(); i++) 
        if (psw[i] == c)
            count++;

    return (count >= low && count <= high);        

}

int Database::solvePart1() const {

    if (password.empty()) 
        return -1;
    
    int valid = 0;
    for (int i = 0; i < (int)password.size(); i++) 
        if (password[i].isValidPart1())
            valid++;
    
    return valid;
}

// =============== PART 2 ===============

bool Password::isValidPart2() const {

    if (psw.empty()) 
        return false;

    else 
        return (psw[low-1] == c) != (psw[high-1] == c);  
}

int Database::solvePart2() const {

    if (password.empty()) 
        return -1;
    
    int valid = 0;
    for (int i = 0; i < (int)password.size(); i++) {
        if (password[i].isValidPart2()) {
            valid++;
        }
    }
    return valid;
}