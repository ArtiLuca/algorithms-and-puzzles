#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:

    int findMaxConsecutiveOnes(std::vector<int>& nums) {
        
        int maxCount = 0;  // global maximum
        int tempCount = 0; // local counter

        // range-based loop
        for (int num : nums) {

            // if we find a 1, we increment local counter
            if (num == 1) {
                tempCount++;
                // update global maximum if needed
                maxCount = std::max(tempCount, maxCount);
            }
            // otherwise, if we find a 0 we reset local counter
            else {
                tempCount = 0;
            }
        }
        // return global maximum found
        return maxCount;
    }
};

void printVector(const std::vector<int>& vec) {

    std::cout << "[ ";
    for (int i = 0; i < (int)vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {

    Solution s;

    std::vector<std::vector<int>> nums = { {1,1,0,1,1,1}, {1,0,1,1,0,1}, {0,1,1,1,0,0,1,1,1,1,1,0}, {0,0,0} };

    for (int i = 0; i < (int)nums.size(); i++) {

        std::cout << "Example " << i << ": ";
        printVector(nums[i]);
        std::cout << "Maximum Consecutive 1s = " << s.findMaxConsecutiveOnes(nums[i]) << "\n-----------------" << std::endl;
    }

    return 0;
}