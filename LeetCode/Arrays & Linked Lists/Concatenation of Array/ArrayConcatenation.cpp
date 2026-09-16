#include <iostream>
#include <vector>

class Solution {
public:
    
    std::vector<int> getConcatenation(std::vector<int>& nums) {
        
        int n = nums.size();

        std::vector<int> result(2 * n);

        for (int i = 0; i < n; i++) {
            result[i] = nums[i];
            result[i + n] = nums[i];
        }

        return result;
    }
};

void printVector(const std::vector<int>& vec) {

    std::cout << "[ ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << "]\n";
}


int main() {

    Solution s;

    // Example 1:
    std::vector<int> v1 = {1,2,1};
    std::cout << "\nExample 1:\nInput:  [ 1 2 1 ]\nOutput: ";  
    printVector(s.getConcatenation(v1));

    // Example 2:
    std::vector<int> v2 = {1,3,2,1};
    std::cout << "\nExample 2:\nInput:  [ 1 3 2 1 ]\nOutput: ";
    printVector(s.getConcatenation(v2));

    // Example 3:
    std::vector<int> v3 = {1,5,2,6,8,10,4,21,100,22,15,12,44};
    std::cout << "\nExample 3:\nInput:  [ 1 5 2 6 8 10 4 21 100 22 15 12 44 ]\nOutput: ";
    printVector(s.getConcatenation(v3));

    return 0;
}