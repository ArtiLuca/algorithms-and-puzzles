#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSumA(vector<int>& nums, int target) {
        
        std::vector<std::pair<int,int>> aux;
        for (int i = 0; i < nums.size(); i++) {
            aux.push_back({nums[i], i});
        }

        std::sort(aux.begin(), aux.end());

        int i = 0;
        int j = aux.size() - 1;

        while (i < j) {
            long long sum = (long long)aux[i].first + aux[j].first;

            if (sum == target) {
                return {aux[i].second, aux[j].second};
            }
            else if (sum < target) {
                i++;
            }
            else {
                j--;
            }
        }

        return {};
    }

    vector<int> twoSumB(vector<int>& nums, int target) {

        // maps value -> index
        std::unordered_map<int,int> seen;

        for (int i = 0; i < nums.size(); i++) {
            int needed = target - nums[i];
            
            if (seen.find(needed) != seen.end()) {
                return {seen[needed], i};
            }

            seen[nums[i]] = i;
        }

        return {};
    }
};

int main() {

    std::vector<int> v = {4, 6, 1, 2, 9, 10, 22, 30, 5, 13};

    Solution s1;
    Solution s2; 

    std::cout << "Idea 1:\n";
    std::vector<int> v1 = s1.twoSumA(v, 19);
    std::cout << "19 = " << v[v1[0]] << " + " << v[v1[1]] << std::endl;

    std::cout << "Idea 2:\n";
    std::vector<int> v2 = s2.twoSumB(v, 19);
    std::cout << "19 = " << v[v2[0]] << " + " << v[v2[1]] << std::endl;

    return 0;
}
