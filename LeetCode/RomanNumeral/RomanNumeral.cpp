#include <iostream>
#include <string>
#include <unordered_map>

class Solution {
public:

    int romanToInt(std::string s) {
        
        std::unordered_map<char,int> romanNumeral = {
            {'I', 1}, {'V', 5}, {'X', 10}, 
            {'L', 50}, {'C', 100}, {'D', 500}, 
            {'M', 1000}
        };

        int total = 0;
        int n = s.length();

        for (int i = 0; i < n; i++) {

            if (i+1 < n && (romanNumeral[s[i]] < romanNumeral[s[i+1]])) {
                total = total - romanNumeral[s[i]];
            }
            else {
                total = total + romanNumeral[s[i]];
            }
        }
        return total;
    }
};


int main() {

    std::string s1 = "XII";
    std::string s2 = "XXVII";
    std::string s3 = "LVIII";
    std::string s4 = "III";
    std::string s5 = "MCMXCIV";

    Solution s;
    std::cout << "s1 = " << s1 << " = " << s.romanToInt(s1) << std::endl;
    std::cout << "s2 = " << s2 << " = " << s.romanToInt(s2) << std::endl;
    std::cout << "s3 = " << s3 << " = " << s.romanToInt(s3) << std::endl;
    std::cout << "s4 = " << s4 << " = " << s.romanToInt(s4) << std::endl;
    std::cout << "s5 = " << s5 << " = " << s.romanToInt(s5) << std::endl;
}
