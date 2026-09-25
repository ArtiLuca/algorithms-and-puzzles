#include <iostream>
#include <string>
#include <vector>
#include <stack>

class Solution {
public:

    bool isValid(std::string s) {
        
        // initialize stack structure for processing parentheses
        std::stack<char> parentheses;

        // loop through 's' in left-to-right order
        for (char c : s) {

            // handle opening parentheses
            if (c == '(' || c == '[' || c == '{') {
                parentheses.push(c);
            }
            else {
                // if the stack is empty, the input is not valid
                if (parentheses.empty()) {
                    return false;
                }
                
                // handle closing parentheses by checking if their type match
                char openingParenthesis = parentheses.top();
                // if they match, pop from stack and continue
                if ((c == ')' && openingParenthesis == '(') || 
                    (c == ']' && openingParenthesis == '[') || 
                    (c == '}' && openingParenthesis == '{')) {
                    parentheses.pop();
                }
                // if they did not match, the input is not valid
                else {
                    return false;
                }
            }
        }

        // after processing the entire input string, if the stack is empty, then the input was valid
        return parentheses.empty();
    }
};

void printTest(const std::string& s, bool valid) {

    std::cout << "Input string: " << s << std::endl;
    std::cout << "Output: " << (valid ? "valid\n" : "NOT valid\n") << std::endl;
}

int main() {

    Solution s;

    std::vector<std::string> str = {
        {"()"},
        {"()[]{}"},
        {"(]"},
        {"([])"},
        {"([)]"},
        {"(([{([{}])}]))"},
        {"{{[[((])]]}}"}
    };

    for (int i = 0; i < (int)str.size(); i++) {

        printTest(str[i], s.isValid(str[i]));
    }

    return 0;
}