#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    
    // i=0 hash set; i=1 cyclic sorting; i=2 sign modification
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums, int i = 0) {
        
        if (i == 0) {
            return usingHashSet(nums);
        }
        else if (i == 1) {
            return usingCyclicSorting(nums);
        }
        else if (i == 2) {
            return usingSignModification(nums);
        }
        else {
            return {};
        }
    }

    std::vector<int> usingHashSet(std::vector<int>& nums) {

        // create hash set, and insert numbers found in nums
        std::unordered_set<int> seen;
        for (int num : nums) {
            // skipping duplicate values
            seen.insert(num);
        }

        // allocate result vector, and inspect against sequence 1 to n
        std::vector<int> missing;
        for (int i = 1; i <= nums.size(); i++) {
            // if we an expected number from sequence is missing
            if (seen.find(i) == seen.end()) {
                // we push into result vector
                missing.push_back(i);
            }
        }

        return missing;
    }

    std::vector<int> usingCyclicSorting(std::vector<int>& nums) {

        int n = nums.size();

        // iterate over nums, applying cyclic sorting
        for (int i = 0; i < n; i++) {
            // until each number is in its correct 0-indexed position
            while (nums[i] != nums[nums[i] - 1]) {
                std::swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // allocate result vector, and iterate over the now sorted vector nums
        std::vector<int> missing;
        for (int i = 0; i < n; i++) {
            // each time we find index of number that does not match expected value, we push into result vector
            if (nums[i] != i+1) {
                missing.push_back(i+1);
            }
        }

        return missing;
    }


    std::vector<int> usingSignModification(std::vector<int>& nums) {

        // iterate over vector, marking "seen" numbers
        for (int i = 0; i < (int)nums.size(); i++) {
            // find the 0-index position of current number
            int index = std::abs(nums[i]) - 1;
            // insert negated number in 0-index position, skipping positive numbers (duplicates) 
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }

        // allocate result vector, and iterate over "marked" vector
        std::vector<int> missing;
        for (int i = 0; i < (int)nums.size(); i++) {
            // every positive value found is a duplicate, meaning a "dissapearing" number
            // for every positive number found, we increment it by 1 and push into result vector
            if (nums[i] > 0) {
                missing.push_back(i+1);
            }
        }
        return missing;
    }
};

void printVector(const std::string& label, const std::vector<int>& vec) {

    std::cout << label << ": [ ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {

    Solution s;

    std::vector<std::vector<int>> nums = {
        {4,3,2,7,8,2,3,1}, {1,1}, {1,1,1,3,5},
        {1,5,4,2,8,9,9,2,2,2}, {1,2,3,4,5,6,7,8,9,1},
        {1,5,6,2,9,10,12,5,4,2,11,10}
    };

    for (int i = 0; i < (int)nums.size(); i++) {

        std::cout << "Example " << i << std::endl;
        printVector("Input ", nums[i]);
        printVector("Output (Uisng Hash Set)", s.findDisappearedNumbers(nums[i], 0));
        printVector("Output (Cyclic Sorting)", s.findDisappearedNumbers(nums[i], 1));
        printVector("Output (Sign Modific. )", s.findDisappearedNumbers(nums[i], 2));
        std::cout << "----------------" << std::endl;
    }

    return 0;
}