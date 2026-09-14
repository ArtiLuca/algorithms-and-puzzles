#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> plusOne(std::vector<int>& digits) {
        
        int n = digits.size();

        // loop digits from right to left
        for (int i = n - 1; i >= 0; i--) {

            // increment digit
            digits[i]++;

            // if after increment no carry, we are done
            if (digits[i] < 10) {
                return digits;
            }

            // if there was a carry, we set current digit to 0 and carry over to next iteration
            digits[i] = 0;
        }

        // if we reach this point, it means all digits were '9'
        // therefore, we must add a leading '1' and a trailing '0'
        digits[0] = 1;
        digits.push_back(0);
        return digits;
    }
};


void printResult(const std::vector<int>& v) {

    std::cout << "[ ";
    for (int i = 0; i < (int)v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "]\n" << std::endl;
}

int main() {

    Solution s;

    // Example 1
    std::vector<int> digits1 = {1,2,3};
    std::cout << "Example 1:\nExpected Output: [ 1 2 4 ]" << std::endl;
    std::vector<int> v1 = s.plusOne(digits1);
    std::cout << "Output:          ";
    printResult(v1);

    // Example 2
    std::vector<int> digits2 = {4,3,2,1};
    std::cout << "Example 2:\nExpected Output: [ 4 3 2 2 ]" << std::endl;
    std::vector<int> v2 = s.plusOne(digits2);
    std::cout << "Output:          ";
    printResult(v2);

    // Example 3
    std::vector<int> digits3 = {9};
    std::cout << "Example 3:\nExpected Output: [ 1 0 ]" << std::endl;
    std::vector<int> v3 = s.plusOne(digits3);
    std::cout << "Output:          ";
    printResult(v3);

    // Example 4
    std::vector<int> digits4 = {1, 0, 9, 0, 1, 9, 9};
    std::cout << "Example 4:\nExpected Output: [ 1 0 9 0 2 0 0 ]" << std::endl;
    std::vector<int> v4 = s.plusOne(digits4);
    std::cout << "Output:          ";
    printResult(v4);

    return 0;
}
