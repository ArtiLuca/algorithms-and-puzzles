#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> smallerNumbersThanCurrent(std::vector<int>& nums) {
        
        int k = 100; // given by constraints

        // allocate occurrence vector of size 101, all initially with value 0
        std::vector<int> count(k+1, 0);

        // count occurrences of each number in nums
        for (int i = 0; i < (int)nums.size(); i++) {
           count[nums[i]]++;    
        }

        // modify count vector by storing strictly smaller than counts, using a running sum
        int sum = 0;
        for (int i = 0; i <= k; i++) {

            // get num. occurrences of current element
            int current = count[i];
            // update it by storing how many numbers were strictly smaller than it
            count[i] = sum;
            // accumulate for next numbers
            sum += current;
        }

        // map values back to output vector, keeping the original order
        std::vector<int> result(nums.size());
        for (int j = 0; j < (int)nums.size(); j++) {
            result[j] = count[nums[j]];
        }

        // return output vector
        return result;
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

    std::vector<std::vector<int>> nums = {
        {8,1,2,2,3}, {6,5,4,8}, {7,7,7,7},
        {2,4,1,5,9,10,4,7}, {1,5,4,3,9,11,23,20,9,8,7,6,3,1}
    };

    for (int i = 0; i < (int)nums.size(); i++) {

        std::cout << "Example " << i << ": ";
        printVector(nums[i]);
        std::cout << "Output: ";
        printVector(s.smallerNumbersThanCurrent(nums[i]));
        std::cout << "-----------------" << std::endl;
    }

    return 0;
}