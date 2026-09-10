#include <iostream>
#include <vector>
#include <climits>

class Solution {
public:

    int maxProfit(std::vector<int>& prices) {

        if (prices.empty()) {
            return 0;
        }

        int minPrice = INT_MAX;
        int maxProfit = 0;

        for (int i = 0; i < (int)prices.size(); i++) {

            if (prices[i] < minPrice) {
                minPrice = prices[i];
            }
            else if (prices[i] - minPrice > maxProfit) {
                maxProfit = prices[i] - minPrice;
            }
        }
        return maxProfit;
    }
};

int main() {

    Solution s;

    std::vector<int> p1 = {7,1,5,3,6,4};
    std::vector<int> p2 = {7,6,4,3,1};
    std::vector<int> p3 = {2,1,3};
    std::vector<int> p4 = {10,3,8,4,9,21,5,11,15,19,6,70};

    std::cout << "Example 1: " << s.maxProfit(p1) << std::endl;
    std::cout << "Example 2: " << s.maxProfit(p2) << std::endl;
    std::cout << "Example 3: " << s.maxProfit(p3) << std::endl;
    std::cout << "Example 4: " << s.maxProfit(p4) << std::endl;

    return 0;
}
