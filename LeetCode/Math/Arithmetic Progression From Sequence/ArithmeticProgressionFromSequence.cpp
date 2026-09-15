#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>

class Solution {
public:

    bool canMakeArithmeticProgression(std::vector<int>& arr, bool useHashSet = false) {

        if (!useHashSet) {
            return arithmeticProgressionSorting(arr);
        }
        else {
            return arithmeticProgressionHashSet(arr);
        }
    }

    bool arithmeticProgressionSorting(std::vector<int>& arr) {

        // sort 'arr' in increasing order
        std::sort(arr.begin(), arr.end());

        // find difference between first two elements in sorted array
        int diff = arr[1] - arr[0];

        // iterate through remaining sorted numbers, checking they have the same difference
        for (int i = 2; i <(int)arr.size(); i++) {

            // if we find mismatch in difference, 'arr' cannot form an arithmetic progression
            if (arr[i] - arr[i-1] != diff) {
                return false;
            }
        }
        // otherwise, 'arr' can for an arithemtic progression
        return true;
    }


    bool arithmeticProgressionHashSet(std::vector<int>& arr) {

        int n = arr.size();

        // find minimum and maximum in 'arr'
        int minValue = INT_MAX;
        int maxValue = INT_MIN;
        std::unordered_set<int> numbers;

        // range based loop
        for (int num : arr) {
            minValue = std::min(minValue, num);
            maxValue = std::max(maxValue, num);
            numbers.insert(num);
        }

        // if total "spread" is not perfectly divisible
        if ((maxValue - minValue) % (n - 1) != 0) {
            // not a valid arithmetic progression
            return false;
        }

        // get common difference ("distance")
        int diff = (maxValue - minValue) / (n - 1);

        // if minValue and maxValue were the same 
        if (diff == 0) {
            // all numbers were identical, valid arithmetic progression
            return true;
        }

        // verify that all expected terms of arithmetic progression are in the hash set
        for (int i = 0; i < n; i++) {
            int val = minValue + i * diff;
            // if a value is not found 
            if (numbers.find(val) == numbers.end()) {
                // not a valid arithmetic progression
                return false;
            }
        }

        // if all expected numbers were found, it is a valid arithmetic progression
        return true;
    }
};

int main() {

    Solution s;

    // Example 1:
    std::vector<int> v1 = {3, 5, 1};
    std::cout << "\nExample 1 (Expected: True)" << std::endl;
    std::cout << "Sorting Approach: " << (s.canMakeArithmeticProgression(v1) ? "True" : "False") << std::endl;

    // Example 2:
    std::vector<int> v2 = {1, 2, 4};
    std::cout << "\nExample 2 (Expected: False)" << std::endl;
    std::cout << "Sorting Approach: " << (s.canMakeArithmeticProgression(v2) ? "True" : "False") << std::endl;

    // Example 3:
    std::vector<int> v3 = {3, 9, 12, 15, 18, 6, 27, 24, 21};
    std::cout << "\nExample 3 (Expected: True)" << std::endl;
    std::cout << "Hash Set Approach: " << (s.canMakeArithmeticProgression(v3,true) ? "True" : "False") << std::endl;

    // Example 4:
    std::vector<int> v4 = {3,3,3,3,3};
    std::cout << "\nExample 4 (Expected: True)" << std::endl;
    std::cout << "Hash Set Approach: " << (s.canMakeArithmeticProgression(v4,true) ? "True" : "False") << std::endl;

    // Example 5:
    std::vector<int> v5a = {1, 3, 10, 20, 5};
    std::vector<int> v5b = {1, 3, 10, 20, 5};
    std::cout << "\nExample 5 (Expected: False)" << std::endl;
    std::cout << "Sorting Approach: " << (s.canMakeArithmeticProgression(v5a) ? "True" : "False") << std::endl;
    std::cout << "Hash Set Approach: " << (s.canMakeArithmeticProgression(v5b,true) ? "True" : "False") << std::endl;

}
