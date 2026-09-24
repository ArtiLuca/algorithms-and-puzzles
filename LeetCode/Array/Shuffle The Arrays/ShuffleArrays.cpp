#include <iostream>
#include <vector>

class Solution {
public:

    std::vector<int> shuffle(std::vector<int>& nums, int n) {  
        
        // allocate new vector of size 2n
        std::vector<int> result(2*n);

        // index trackers for x elements and y elements
        int x = 0;
        int y = n;

        // apply modulo rule for populating
        for (int i = 0; i < (int)result.size(); i++) {

            // if even index (or index 0), we take from x elements
            if (i % 2 == 0) {
                result[i] = nums[x++];
            }
            // if odd index, we take from y elements
            else {
                result[i] = nums[y++];
            }
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

    std::vector<int> v1 = {2,5,1,3,4,7}; int n1 = 3;
    std::cout << "Example 1 Input: ";
    printVector(v1);
    std::cout << "Expected Output: [ 2 3 5 4 1 7 ]" << std::endl;
    std::cout << "Output:          ";
    printVector(s.shuffle(v1, n1));

    std::vector<int> v2 = {1,2,3,4,4,3,2,1}; int n2 = 4;
     std::cout << "Example 2 Input: ";
    printVector(v2);
    std::cout << "Expected Output: [ 1 4 2 3 3 2 4 1 ]" << std::endl;
    std::cout << "Output:          ";
    printVector(s.shuffle(v2,n2));

    std::vector<int> v3 = {1,1,2,2};
    int n3 = 2;
     std::cout << "Example 3 Input: ";
    printVector(v3);
    std::cout << "Expected Output: [ 1 2 1 2 ]" << std::endl;
    std::cout << "Output:          ";
    printVector(s.shuffle(v3,n3));

    std::vector<int> v4 = {2,3,10,12,7, 1,4,11,8,5};
    int n4 = 5;
     std::cout << "Example 4 Input: ";
    printVector(v4);
    std::cout << "Expected Output: [ 2 1 3 4 10 11 12 8 7 5 ]" << std::endl;
    std::cout << "Output:          ";
    printVector(s.shuffle(v4,n4));

    return 0;
}
