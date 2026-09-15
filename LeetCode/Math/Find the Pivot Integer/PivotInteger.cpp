#include <iostream>
#include <cmath>

class Solution {
public:

    int pivotIntegerA(int n) {

        // compute total sum with Gauss summation
        int totalSum = n * (n + 1) / 2;
        int leftSum = 0;

        // for each number i from 1 to n
        for (int i = 1; i <= n; i++) {

            // compute leftSum and rightSum
            leftSum += i;
            int rightSum = totalSum - leftSum + i;

            // if they match we found the pivot integer
            if (leftSum == rightSum) {
                return i;
            }
        }

        // otherwise the pivot integer cannot be found
        return -1;
    }

    int pivotIntegerB(int n) {

        // compute total sum from 1 to n
        int totalSum = n * (n + 1) / 2;

        // find the square root of the total sum
        int x = std::sqrt(totalSum);

        // if x squared is equal to the total sum
        if (x * x == totalSum) {
            // we found our pivot integer
            return x;
        }

        // otherwise, it was not found
        return -1;
    }
};


int main() {

    Solution s;

    // Example 1:
    int n1 = 8;
    std::cout << "Pivot Integer A for n = " << n1 << ": " << s.pivotIntegerA(n1) << std::endl;

    // Example 2:
    int n2 = 4;
    std::cout << "Pivot Integer A for n = " << n2 << ": " << s.pivotIntegerA(n2) << std::endl;

    // Example 3:
    int n3 = 49;
    std::cout << "Pivot Integer (using square root) for n = " << n3 << ": " << s.pivotIntegerB(n3) << std::endl;

    // Example 4:
    int n4 = 288;
    std::cout << "Pivot Integer (using square root) for n = " << n4 << ": " << s.pivotIntegerB(n4) << std::endl;

    return 0;
}