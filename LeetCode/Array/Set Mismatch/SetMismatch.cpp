#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution {
public:

    // i=0 sorting, i=1 hash set, i=2 cyclic, i=3 mathematical
    std::vector<int> findErrorNums(std::vector<int>& nums, int i = 0) {
        if (i == 0) {
            return findErrorNumsSorting(nums);
        }
        else if (i == 1) {
            return findErrorNumsHashSet(nums);
        }
        else if (i == 2) {
            return findErrorNumsCyclicSorting(nums);
        }
        else if (i == 3) {
            return findErrorNumsMath(nums);
        }
        else {
            return {};
        }
    }


    std::vector<int> findErrorNumsSorting(std::vector<int>& nums) {

        // sort nums in increasing order
        std::sort(nums.begin(), nums.end());

        // set initial variables
        int duplicate = -1;
        int expected = 1;

        for (int i = 0; i < (int)nums.size(); i++) {

            // if past first we check for duplicate
            if (i > 0 && nums[i] == nums[i-1]) {
                duplicate = nums[i];
            }
            // if we find the expected number, we increment to the next one in the sequence
            else if (nums[i] == expected) {
                expected++;
            }
        }

        // once the loop finished, expected contains the missing number
        return {duplicate, expected};
    }
    
    std::vector<int> findErrorNumsHashSet(std::vector<int>& nums) {

        // create hash set and set initial expected/duplicate placeholder values
        std::unordered_set<int> seen;
        int duplicate = -1;
        int missing = 1;

        // populate the hash set and find duplicate number
        for (int num : nums) {

            // if an insertion fails, we found the duplicate number
            if (!seen.insert(num).second) {
                duplicate = num;
            }
        }

        // after populating the hash set, we check from 1 to n to find the missing number
        for (int i = 1; i <= (int)nums.size(); i++) {
            if (seen.find(i) == seen.end()) {
                missing = i;
                break;
            }
        }

        return {duplicate, missing};
    }
    
    std::vector<int> findErrorNumsCyclicSorting(std::vector<int>& nums) {

        int n = nums.size();

        // swap in-place to put each number in correct 0-indexed position
        for (int i = 0; i < n; i++) {
            while (nums[i] != nums[nums[i] - 1]) {
                std::swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // find index of number that does not match expected value
        for (int i = 0; i < n; i++) {
            if (nums[i] != i+1) {
                return {nums[i], i+1};
            }
        }

        // otherwise...
        return {};
    }
    
    std::vector<int> findErrorNumsMath(std::vector<int>& nums) {

        long long n = nums.size();

        // using Gauss summation to get expected and squared sums
        long long expectedSum = n * (n+1) / 2;
        long long expectedSumSquared = n * (n+1) * (2 * n + 1) / 6;

        // find the actual and expected sums
        long long actualSum = 0;
        long long actualSumSquared = 0;

        // iterate vector to compute sums
        for (long long num : nums) {
            actualSum += num;
            actualSumSquared += num * num;
        }

        // compute difference of sums
        long long diff1 = expectedSum - actualSum;
        // compute difference of squared sums
        long long diff2 = expectedSumSquared - actualSumSquared;

        // divide differences to find sum of missing and duplicate number
        long long sumXY = diff2 / diff1;

        // compute missing number
        long long missing = (diff1 + sumXY) / 2;
        // compute duplicate number
        long long duplicate = sumXY - missing;

        // return them
        return {(int)duplicate, (int)missing};
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

    std::vector<std::vector<int>> testCases = {
        {1,2,2,4}, {1,1}, {6,4,3,5,2,8,4,7},
        {3,7,1,4,1,2,6,5}, {5,2,8,3,7,6,3,1},
        {3,4,5,6,7,7,1,9,2}
    };

    std::vector<std::string> approachNames = {
        "Sorting", "Hash Set", "Cyclic Sorting", "Math"
    };

    for (int t = 0; t < (int)testCases.size(); t++) {

        std::cout << "Vector: ";
        printVector(testCases[t]);

        std::cout << "Test Case " << t + 1 << ":\n";
        
        for (int i = 0; i < 4; i++) {
            // Create a copy because sorting and cyclic sort modify the vector in-place
            std::vector<int> numsCopy = testCases[t]; 
            
            // Call the dispatcher method (i=0 sorting, i=1 hash set, i=2 cyclic, i=3 mathematical)
            std::vector<int> result = s.findErrorNums(numsCopy, i);
            
            std::cout << "  " << approachNames[i] << ": [" 
                      << result[0] << ", " << result[1] << "]\n";
        }
        std::cout << "-----------------------\n";
    }
    
    return 0;
}