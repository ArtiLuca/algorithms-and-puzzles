#include "HandyHaversacks.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include <queue>

// =============== PUZZLE INPUT & HELPERS ===============

void Haversacks::readPuzzleInput() {

    // clear previous
    childToParents.clear();

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    // read input line by line
    std::string line;
    while (std::getline(file, line)) {

        // parse single line
        std::istringstream ss(line);
        
        // parse parent bag
        std::string parentAdjective;
        std::string parentColor;
        std::string dummy;

        ss >> parentAdjective >> parentColor >> dummy >> dummy;
        std::string parentName = parentAdjective + " " + parentColor;

        std::string quantityStr;
        // parse potential child bags

        while (ss >> quantityStr) {
        
            // check for actual quantity
            if (quantityStr == "no") {
                break;
            }

            // otherwise, parse child bag
            int quantity = std::stoi(quantityStr); // added for Part 2

            std::string childAdjective;
            std::string childColor;
            ss >> childAdjective >> childColor >> dummy;
            std::string childName = childAdjective + " " + childColor;

            // map child bag to its parent
            childToParents[childName].push_back(parentName);

            // added for Part 2
            parentToChildren[parentName].push_back({childName, quantity});
        }
    }
    file.close();   
}

// =============== PART 1 ===============

int Haversacks::solvePart1() const {

    // guard
    if (childToParents.empty()) {
        throw std::runtime_error("Child -> Parents map is empty.");
    }

    // initialize empty hash set and queue
    std::unordered_set<std::string> visited;
    std::queue<std::string> q;

    // we track starting from "shiny gold bag" going backwards
    q.push("shiny gold");
    
    // process until queue is empty
    while (!q.empty()) {

        //
        std::string current = q.front();
        q.pop();

        // check the direct parents of current
        auto it = childToParents.find(current);
        // if we find one
        if (it != childToParents.end()) {

            // try inserting into hash set
            for (const std::string& parent : it->second) {
                // if we find a unique (unvisited) parent, we push into queue
                if (visited.insert(parent).second) {
                    q.push(parent);
                }
            }
        }
    }

    // the size of the hash set is Part 1's solution
    return visited.size();
}

// =============== PART 2 ===============

int Haversacks::countNestedBags(const std::string& currentColor) const {

    int total = 0;

    // lookup children of current color
    auto it = parentToChildren.find(currentColor);

    // if no children, return 0 
    if (it == parentToChildren.end()) {
        
        // no nested bags
        return 0;
    }

    // otherwise, we look at each child associated to the current color
    for (const ColorCodedBag& child : it->second) {

        // count the child bags themselves and recursively count their contents
        total += child.quantity + (child.quantity * countNestedBags(child.color));
    }

    // return total sum of nested bags found
    return total;
}

int Haversacks::solvePart2() const {

    // guard
    if (parentToChildren.empty()) {
        throw std::runtime_error("Parent -> Children map is empty.");
    }

    // use recursive helper directly on shiny gold bag
    return countNestedBags("shiny gold");
}