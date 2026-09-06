#include "ReportRepair.h"

#include <fstream>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>

void ExpenseReport::readPuzzleInput() {

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    int x;
    while (file >> x) 
        report.push_back(x);
    
    file.close();  
}

long long ExpenseReport::solvePart1(int target) const {

    std::vector<int> copy = report;
    std::sort(copy.begin(), copy.end());

    int i = 0;
    int j = copy.size() - 1;

    while (i < j) {

        int sum = copy[i] + copy[j];
        
        if (sum == target) {
            // found target sum, multiply for final answer
            return (long long)copy[i] * copy[j];
        }
        else if (sum < target) {
            i++;
        }
        else {
            j--;
        }
    }
    // if target sum was not found
    return -1;
}


long long ExpenseReport::solvePart2_TwoPointer(int target) const{

    std::vector<int> copy = report;
    std::sort(copy.begin(), copy.end());

    int n = copy.size();

    for (int k = 0; k < n-2; k++) {

        int i = k+1;
        int j = n-1;
        int requiredSum = target - copy[k];

        while (i < j) {
            int sum = copy[i] + copy[j];
            
            if (sum == requiredSum) {
                return (long long)copy[k] * copy[i] * copy[j];
            }
            else if (sum < requiredSum) {
                i++;
            } 
            else {
                j--;
            }
        }
    }
    return -1;
}

long long ExpenseReport::solvePart2_HashingSet(int target) const {

    int n = report.size();

    for (int i = 0; i < n - 2; i++) {

        std::unordered_set<int> st;
        
        for (int j = i+1; j < n; j++) {
            
            int second = target - report[i] - report[j];

            if (st.find(second) != st.end()) {
                return (long long)report[i] * second * report[j];
            }
            st.insert(report[j]);
        }
    }
    return -1;
}

long long ExpenseReport::solvePart2(int target, bool useHashing) const {

    if (!useHashing)
        return solvePart2_TwoPointer(target);
    else 
        return solvePart2_HashingSet(target);    
}
