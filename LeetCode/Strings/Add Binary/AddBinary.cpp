#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:

    std::string addBinary(std::string a, std::string b) {

        std::string result = "";    // result string
        int indA = a.length() - 1;  // string a index tracker
        int indB = b.length() - 1;  // string b index tracker
        int carry = 0;              // carry value
        
        // add digits from right-to-left, as long as either string has digits left,
        // or there is any leftover carry
        while (indA >= 0 || indB >= 0 || carry > 0) {

            // account for any leftover carry in current sum
            int sum = carry;

            // update sum with digits from both strings (if there are any)
            if (indA >= 0) {
                sum += a[indA] - '0';
                indA--;
            }
            if (indB >= 0) {
                sum += b[indB] - '0';
                indB--;
            }

            // update carry using integer division
            carry = sum / 2;

            // use modulo to append digit to result string
            result += std::to_string(sum % 2);
        }
        
        // reverse result string before returning
        std::reverse(result.begin(), result.end());
        return result;
    }
};

void printTest(const std::string& label, const std::string& expected, const std::string& a, const std::string& b, const std::string& sum) {

    std::cout << label << std::endl;
    std::cout << expected << std::endl;
    std::cout << "Output: " << sum << "\n" << std::endl;
}

int main() {

    Solution s;

    std::string a1 = "11"; std::string b1 = "1";
    printTest("Example 1:\n'11' + '1' (4)", "Expected: '100'", a1, b1, s.addBinary(a1, b1));

    std::string a2 = "1010"; std::string b2 = "1011";
    printTest("Example 2:\n'1010' + '1011'(21)", "Expected: '10101'", a2, b2, s.addBinary(a2, b2));

    std::string a3 = "001"; std::string b3 = "1001";
    printTest("Example 3:\n'001' + '1001' (10)", "Expected: '1010'", a3, b3, s.addBinary(a3, b3));

    std::string a4 = "11001"; std::string b4 = "111001";
    printTest("Example 4:\n'11001' + '111001' (82)", "Expected: '1010010'", a4, b4, s.addBinary(a4, b4));

    return 0;
}
