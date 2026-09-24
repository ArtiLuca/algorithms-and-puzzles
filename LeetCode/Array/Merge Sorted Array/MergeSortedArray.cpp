#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:

    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {

        // index trackers 
        int i = m - 1; // m = nums1.length();
        int j = n - 1; // n = nums2.length();

        for (int k = m + n - 1; k >= 0; k--) {

            // if no elements from nums2, nums1 is already sorted
            if (j < 0) {
                // so we can break from the loop
                break;
            } 

            // if no elements from nums1 remain or nums2 contains the largest
            if (i < 0 || nums2[j] > nums1[i]) {
                nums1[k] = nums2[j];
                j--;
            }

            // otherwise, we insert from nums1
            else {
                nums1[k] = nums1[i];
                i--;
            }
        }
    }
};

void printArray(const std::vector<int>& vec) {

    if (vec.empty()) {
        std::cout << "[ ]" << std::endl;
        return;
    }

    std::cout << "[ ";
    for (int i = 0; i < (int)vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {

    Solution s;

    std::vector<int> v1 = {1,2,3,0,0,0};
    std::vector<int> v2 = {2,5,6};

    std::vector<int> v3 = {1};
    std::vector<int> v4 = {};

    std::cout << "Example 1:\n";
    s.merge(v1,3,v2,3);
    printArray(v1);

    std::cout << "Example 2:\n";
    s.merge(v3,1,v4,0);
    printArray(v3);

    std::cout << "Another example:\n";
    std::vector<int> vec1 = {1, 5, 6, 9, 10, 21, 0, 0, 0, 0, 0, 0};
    std::vector<int> vec2 = {2, 5, 7, 15, 28, 50};
    s.merge(vec1,6,vec2,6);
    printArray(vec1);

    return 0;
}


