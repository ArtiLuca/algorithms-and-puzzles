#include <iostream>

class Solution {
public:
    bool isUgly(int n) {
        
        // negative numbers and 0 cannot be ugly 
        if (n <= 0) {
            return false;
        }

        // strip out prime factors     
        while (n % 2 == 0) { n = n / 2; }
        while (n % 3 == 0) { n = n / 3; }
        while (n % 5 == 0) { n = n / 5; }

        // if resulting n is 1, it is an ugly number
        return n == 1;
    }
};

int main() {
    
    Solution s;

    // Examples
    int num[] = {6, 1, 14, 120, 150, 78, 67};

    for (int i = 0; i < 7; i++) {

        std::cout << "Example " << i+1 << ": " << num[i] 
                  << (s.isUgly(num[i]) ? " is an ugly number." : " is NOT an ugly number") 
                  << std::endl;
    }

    return 0;
}