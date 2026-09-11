#include <iostream>
#include <string>

class Solution {
public:
    int strStr(std::string haystack, std::string needle) {

        if (needle.length() > haystack.length()) {
            return -1;
        }

        size_t firstIndex = haystack.find(needle);
        if (firstIndex != std::string::npos) {
            return firstIndex;
        }
        else {
            return -1;
        }
        
    }
};


int main() {

    Solution s;

    /* Example 1:
    Input: haystack = "sadbutsad", needle = "sad"
    Output: 0
    Explanation: "sad" occurs at index 0 and 6.
    The first occurrence is at index 0, so we return 0.
    */
    std::string h1 = "sadbutsad", n1 = "sad";
    std::cout << "k  = " << s.strStr(h1, n1) << std::endl; 


    /* Example 2:
    Input: haystack = "leetcode", needle = "leeto"
    Output: -1
    Explanation: "leeto" did not occur in "leetcode", so we return -1.
    */
    std::string h2 = "leetcode", n2 = "leeto";
    std::cout << "k  = " << s.strStr(h2, n2) << std::endl; 

    /* Example 3: */
    std::string h3 = "precipitevolissimevolmente", n3 = "lissime";
    std::cout << "k  = " << s.strStr(h3, n3) << std::endl; 

    return 0;

}