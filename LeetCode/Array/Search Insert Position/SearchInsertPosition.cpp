#include <iostream>
#include <vector>
#include <utility>
#include <string>

class Solution {
public:

    int searchInsert(std::vector<int>& nums, int target) {
        
        // initial index trackers
        int low = 0;
        int high = nums.size() - 1;

        // loop as long as search areas don't "cross"
        while (low <= high) {

            // compute search areas's middle index
            int mid = low + (high - low) / 2;

            // if we found our target, we return it
            if (nums[mid] == target) {
                return mid;
            }
            // narrow search area to the right
            else if (nums[mid] < target) {
                low = mid + 1;
            }
            // otherwise, narrow search area to the left
            else {
                high = mid - 1;
            }
        }

        // once out of the loop, 'low' contains ordered insert position of target 
        return low;
    }
};

void printTest(const std::string& label, const std::vector<int>& nums, int target, int output) {

    std::cout << label << std::endl;
    std::cout << ">nums: [ ";
    for (const int& num : nums) std::cout << num << " ";
    std::cout << "]" << std::endl;
    std::cout << ">target: " << target << std::endl;
    std::cout << ">output: " << output << std::endl;
}

int main() {

    Solution s;

    std::vector<std::pair<std::vector<int>, int>> nums = {
        {{1,3,5,6}, 5},
        {{1,3,5,6}, 2},
        {{1,3,5,6}, 7},
        {{1,2,3,6,9,10,11,14,18}, 10},
        {{3,6,9,11,12,14,16,18,22,23,24,25}, 19},
        {{1,5,9,10,12,16,18,20,23,25}, 24}
    };

    for (int i = 0; i < (int)nums.size(); i++) {

        auto test = nums[i];
        std::string lbl = "Example " + std::to_string(i);
        printTest(lbl, test.first, test.second, s.searchInsert(test.first, test.second));
        std::cout << "\n";
    }

    return 0;
}