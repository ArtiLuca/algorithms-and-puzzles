#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {

        // guard
        if (nums.empty()) {
            return -1;
        }

        int k = 1;
        for (int i = 1; i < (int)nums.size(); i++) {

            // if distinct value
            if (nums[i] != nums[i-1]) {
                // overwrite
                nums[k] = nums[i];
                k++;
            }
        }
        return k;
        
    }
};


int main() {

    Solution s;

    /* Example 1:

    Input: nums = [1,1,2]
    Output: 2, nums = [1,2,_]
    Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
    It does not matter what you leave beyond the returned k (hence they are underscores).
    */
    std::vector<int> nums1 = {1,1,2};
    std::cout << "k = " << s.removeDuplicates(nums1) << std::endl;


    /* Example 2:
    Input: nums = [0,0,1,1,1,2,2,3,3,4]
    Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
    Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
    It does not matter what you leave beyond the returned k (hence they are underscores).
    */
    std::vector<int> nums2 = {0,0,1,1,1,2,2,3,3,4};
    std::cout << "k = " << s.removeDuplicates(nums2) << std::endl;

    /* Example 3: */
    std::vector<int> nums3 = {1,2,3,3,4,5,5,6,7,7,9};
    std::cout << "k = " << s.removeDuplicates(nums3) << std::endl;

    return 0;

}

