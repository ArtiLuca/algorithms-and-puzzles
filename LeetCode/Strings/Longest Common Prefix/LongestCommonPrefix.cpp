#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {

        if (strs.empty() || strs[0].empty()) {
          return "";
        }

        int n = strs.size();

        for (int i = 0; i < (int)strs[0].length(); i++) {

          char c = strs[0][i];

          for (int j = 1; j < n; j++) {

              // if we find empty string
              if (strs[j].empty()) {
                  return strs[0].substr(0,i);
              }

              // if we find string that is too short
              if (i >= (int)strs[j].length()) {
                  return strs[0].substr(0,i);
              }

              // if we find mismatch
              if (strs[j][i] != c) {
                    return strs[0].substr(0,i);
              }
          }
      }

      // otherwise, entire first string is result
      return strs[0];
    }
};


int main() {

    Solution s;

    /* Example 1: 
    Input: strs = ["flower","flow","flight"]
    Output: "fl"    
    */
   std::vector<std::string> strs1 = {{"flower"},{"flow"},{"flight"}};
   std::cout << "ex1: " << s.longestCommonPrefix(strs1) << std::endl;

    /* Example 2: 
    Input: strs = ["dog","racecar","car"]
    Output: ""
    Explanation: There is no common prefix among the input strings.
    */
   std::vector<std::string> strs2 = {{"dog"},{"racecar"},{"car"}};
   std::cout << "ex2: " << s.longestCommonPrefix(strs2) << std::endl;

    return 0;

}