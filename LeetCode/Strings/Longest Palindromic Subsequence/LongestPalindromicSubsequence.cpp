#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

class Solution {
public:

    int longestPalindromeSubseq(std::string s) {

        int n = s.length();

        // guard
        if (n == 0) {
            return 0;
        }

        // allocate vector for storing lengths found
        std::vector<std::vector<int>> lengths(n+1, std::vector<int>(n+1, 0));
        
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

                // if first and last characters match
                if (s[i - 1] == s[j - 1]) {
                    lengths[i][j] = 2 + lengths[i+1][j-1];
                }

                // otherwise, choose option that maximizes solution
                else {
                    lengths[i][j] = std::max(lengths[i+1][j], lengths[i][j-1]);
                }
            }
        }

        // the length of the longest palindromic subsequence is found in lengths[1][n]
        return lengths[1][n];
    }
};

void printTest(const std::string& label, const std::string& str, int calculatedLen, const std::string& subseq) {
    std::cout << "----------------------------------------\n";
    std::cout << label << "\n";
    std::cout << "  Input String   : " << str << " (Length: " << str.length() << ")\n";
    std::cout << "  Expected       : " << "(e.g., \"" << subseq << "\")\n";
    std::cout << "  Calculated Max : " << calculatedLen << "\n";
}

int main() {

    Solution s;

    std::vector<std::pair<std::string, std::string>> testCases = {
        {"bbbab", "bbbb"},
        {"cbbd", "bb"},
        {"abacdfgaba", "ababa"},
        {"aaaaabaaaaa", "aaaaabaaaaa"},
        {"abcdefg", "a"},
        {"leetcodecasesedocteel", "leetcodeseocteel"},
        {"xyzxyzxyzxyzxyz", "xyzyx"},
        {"paddPADUAmelwlePADUAddapxyzxyzxyzxyz", "paddPADUAmellePADUAddap"} 
    };

    for (int i = 0; i < (int)testCases.size(); i++) {
        std::string label = "Example " + std::to_string(i) + ":";
        std::string str = testCases[i].first;
        std::string subseq = testCases[i].second;
        
        // Pass the actual calculated length directly into printTest
        int len = s.longestPalindromeSubseq(str);
        printTest(label, str, len, subseq); 
    }
    
    std::cout << "----------------------------------------\n";

    return 0;
}