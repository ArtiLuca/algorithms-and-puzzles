#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    bool isPalindromeA(int x) {
        
        if (x < 0)
            return false;

        std::string str = std::to_string(x);
        int n = str.length();

        for (int i = 0; i < n/2; i++) {
            if (str[i] != str[n - i - 1]) {
                return false;
            }
        }
        return true;         
    }

    bool isPalindromeB(int x) {
        
        // negative number cannot be palindrome
        if (x < 0)
            return false;
        
        // ... and cannot have trailing zeroes
        if (x % 10 == 0 && x != 0)
            return false;
        
        // otherwise, extract second-half
        int reversedHalf = 0;
        while (x > reversedHalf) {
            int lastDigit = x % 10;
            reversedHalf = (reversedHalf * 10) + lastDigit;
            x = x / 10;
        }    

        // deal with both even and odd number of digits
        return ((x == reversedHalf) || (x == reversedHalf / 10));
    }
};

int main() {

    Solution s;

    std::vector<int> S = {
        {1221}, {1456541}, {100},
        {-1001}, {111}, {5612165},
        {5555}, {2191}, {1350}, {148909841}
    };

    for (int i = 0; i < S.size(); i++) {
        std::cout << "(A) Integer " << S[i] << " is " << (s.isPalindromeA(S[i]) ? " a palindrome\n" : " NOT a palindrome\n");
        std::cout << "(B) Integer " << S[i] << " is " << (s.isPalindromeB(S[i]) ? " a palindrome\n" : " NOT a palindrome\n");
    }

    return 0;
}