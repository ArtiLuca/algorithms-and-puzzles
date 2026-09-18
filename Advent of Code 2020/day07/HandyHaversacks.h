#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// represents a single color-coded bag 
struct ColorCodedBag {

    std::string color;
    int quantity;
};

// represents all rules and color-coded bag rules
class Haversacks {

public:

    Haversacks(const std::string& input) : puzzleInput(input) {}

    void readPuzzleInput();

    int solvePart1() const;
    int solvePart2() const;

private:

    // input
    std::string puzzleInput;

    // represents "child to parents" reverse graph
    std::unordered_map<std::string, std::vector<std::string>> childToParents;
    // represents "parent to children" forward graph added for Part 2
    std::unordered_map<std::string, std::vector<ColorCodedBag>> parentToChildren;

    // private helper for implementing Part 2 recursive logic
    int countNestedBags(const std::string& currentColor) const;
};