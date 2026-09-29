#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

class Solution {
public:
    
    std::string longestPalindrome(std::string s) {

        // length of string, and check for early return
        int n = s.length();
        if (n <= 1) {
            return s;
        }

        // allocate vector for storing lengths found
        std::vector<std::vector<int>> lengths(n+1, std::vector<int>(n+1, 0));

        // trackers for starting index and length of longest palindromic substring found
        int startInd = 0;
        int maxLen = 1;
    
        // handle base cases
        for (int i = 1; i <= n; i++) {

            // empty subsequence
            lengths[i][i-1] = 0;
            // single character subsequence
            lengths[i][i] = 1;
        }

        // fill table calculating intervals of increasing length
        for (int len = 2; len <= n; len++) {
            for (int i = 1; i <= n - len + 1; i++) {

                int j = i + len - 1;

                // if characters match and internal substring is fully palindromic
                if ( (s[i-1] == s[j-1]) && (lengths[i+1][j-1] == j - i - 1) ) {
                    lengths[i][j] = 2 + lengths[i+1][j-1];

                    // update starting index and length of maximum found, if needed 
                    if (lengths[i][j] > maxLen) {
                        maxLen = lengths[i][j];
                        startInd = i - 1;
                    }   
                }
                
                // otherwise, maximize length based on sub-intervals
                else {
                    lengths[i][j] = std::max(lengths[i+1][j], lengths[i][j-1]);
                }
            }
        }

        return s.substr(startInd, maxLen);
    }
};

void printTestCase(const std::string& label, const std::string& str, const std::string& substr, const std::string& found) {

    std::cout << label << std::endl;
    std::cout << "Input string: '" << str << "'" << std::endl;
    std::cout << "Expected: '" << substr << "' (length = " << substr.length() << ")" << std::endl;
    std::cout << "Found: '" << found << "' (length = " << found.length() << ")" << std::endl;
    std::cout << "-------------------------------------------\n" << std::endl;  
}

int main() {

    Solution s;

    std::vector<std::pair<std::string, std::string>> testCases = {
        {"babad", "bab"}, 
        {"cbbd", "bb"},
        {"hyperionnoirepyhxyzabcdeffedcbax", "hyperionnoirepyh"},
        {"abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba", "abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba"},
        {"mississippiimississippi", "ississi"},
        {"solosolosolostartupadventureracecaroutdoors", "solosolosolos"}  
    };

    for (int i = 0; i < (int)testCases.size(); i++) {

        std::string label = "Example " + std::to_string(i+1);
        std::string str = testCases[i].first;
        std::string substr = testCases[i].second;
        std::string found = s.longestPalindrome(testCases[i].first);
        printTestCase(label, str, substr, found);
    }
}