#include "EncodingError.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>

int constexpr PREAMBLE_SIZE = 25;

// =============== PUZZLE INPUT ===============

void Cypher::readPuzzleInput() {

    // clear previous
    numbers.clear();

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    std::string line;
    while (std::getline(file, line)) {

        if (!line.empty()) {
            long long num = std::stoll(line);
            numbers.push_back(num);
        }
    }

    file.close();
}

// =============== PART 1 ===============

bool Cypher::hasValidSum(long long target, int start) const {

    // check if any two pair of different numbers sum to target 
    for (int i = start; i < start + PREAMBLE_SIZE; i++) {
        for (int j = i + 1; j < start + PREAMBLE_SIZE; j++) {
            
            // if any pair of different numbers sum to target, we have a valid sum
            if (numbers[i] + numbers[j] == target && numbers[i] != numbers[j]) {
                return true;
            }    
        }
    }
    // otherwise, we have found the first non-valid sum
    return false;
}

long long Cypher::solvePart1() const {

    // guard
    if (numbers.empty()) {
        throw std::runtime_error("XMAS data was not found");
    }

    // we start after the initial preamble
    for (int i = PREAMBLE_SIZE; i < numbers.size(); i++) {

        // the current element considers the 25 previous numbers
        int start = i - PREAMBLE_SIZE;
    
        // check for first number that does not have a valid sum
        if (!hasValidSum(numbers[i], start)) {
            return numbers[i];
        }
    }

    // fallback, no solution found
    return -1;
}

// =============== PART 2 ===============

long long Cypher::solvePart2(long long target) const {

    // guard 
    if (numbers.empty() || target < 0) {
        throw std::runtime_error("XMAS data was not found or reveived non-valid target.");
    }
    
    // initialize index trackers and running sum
    int left = 0;
    int right = 0;
    long long runningSum = 0;

    while (right < numbers.size()) {

        // add number indexed by 'right' to running sum and increment 'right' by 1
        runningSum += numbers[right];
        right++;

        // if running sum exceeds target and index trackers have not yet "crossed"
        // we loop until it becomes smaller than the target (or we find the solution)
        while (runningSum > target && left < right - 1) {

            // subtract number indexed by 'left' from running sum and increment 'left' by 1
            runningSum -= numbers[left];
            left++;
        }

        // if running sum matches target and has at least two elements, we found the solution
        if (runningSum == target && (right - left) >= 2) {

            // set temporary min/max
            long long smallest = numbers[left];
            long long largest = numbers[left];
            
            // loop through set to find smallest and largest
            for (int i = left + 1; i <= right; i++) {

                if (numbers[i] < smallest) {
                    // update smallest
                    smallest = numbers[i];
                }
                if (numbers[i] > largest) {
                    // update largest
                    largest = numbers[i];
                }
            }

            return smallest + largest;
        }
    }

    // if no solution was found, fallback to -1
    return -1;
}

