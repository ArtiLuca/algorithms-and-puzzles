#include <iostream>
#include <vector>
#include <string>
#include <utility>

class Solution {
public:
    
    std::vector<std::string> buildArray(std::vector<int>& target, int n) {

        // allocate stack operations vector 
        std::vector<std::string> stackOperations;
        // set initial index tracker
        int ind = 0;

        // iterate through input stream target
        for (int i = 1; i <= n; i++) {

            // if index tracker matches input stream size, we matched all values
            if (ind == target.size()) {
                break;
            }

            // if value is smaller than target, "Push" and "Pop" 
            if (i < target[ind]) {
                stackOperations.push_back("Push");
                stackOperations.push_back("Pop");
            }

            // if value matches target in input stream, we "Push" and increment index tracker
            else if (i == target[ind]) {
                stackOperations.push_back("Push");
                ind++;
            }
        }

        // return stack operations vector found
        return stackOperations;
    }
};


void printStackOperations(const std::vector<int>& target, int n, const std::vector<std::string>& result) {

    std::cout << "Target: [ ";
    for (int num : target) {
        std::cout << num << " ";
    }
    std::cout << "], n = " << n << "\n"; 
    
    std::cout << "Output: [ ";
    for (const std::string& op : result) {
        std::cout << op << " ";
    }

    std::cout << "]\n";
    std::cout << "----------------------------------------\n";
}

int main() {

    Solution s;

    std::vector<std::pair<std::vector<int>, int>> test = {
        {{1,3}, 3}, 
        {{1,2,3},3}, 
        {{1,2},4}, 
        {{2,3,5,6}, 6}, 
        {{1,3,5,6,7,9}, 9}
    };

    for (int i = 0; i < (int)test.size(); i++) {
        
        std::cout << "Example " << i << std::endl;
        std::vector<int> testCase = test[i].first;
        int n = test[i].second;
        std::vector<std::string> testResult = s.buildArray(testCase, n);
        printStackOperations(testCase, n, testResult);
    }

    return 0;
}