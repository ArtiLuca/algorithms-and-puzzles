#include <iostream>
#include <vector>
#include <string>
#include <stack>

class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens) {

        // allocate stack structure for evalutating expression
        std::stack<int> stackRPN;

        // iterate through given expression
        for (const std::string& ch : tokens) {

            // if we find an operator, we pop two operands
            if (ch == "+" || ch == "-" || ch == "*" || ch == "/") {

                int op1 = stackRPN.top();
                stackRPN.pop();

                int op2 = stackRPN.top();
                stackRPN.pop();

                // perform arithmetic operation, using left-to-right order 
                int result;
                if (ch == "+") { result = op2 + op1; }
                else if (ch == "-") { result = op2 - op1; }
                else if (ch == "*") { result = op2 * op1; }
                else if (ch == "/") { result = op2 / op1; }

                // and push the result onto the stack
                stackRPN.push(result);
            }
            
            // if we find an operand
            else {
                // we convert to integer and push it onto the stack
                int num = std::stoi(ch);
                stackRPN.push(num);
            }
        }
        // once we evaluate each token, the top of the stack contains the result
        return stackRPN.top();
    }
};

void printInput(const std::vector<std::string>& input) {
    std::cout << "[ ";
    for (const std::string& str : input) {
        std::cout << str << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {

    Solution s;

    std::vector<std::vector<std::string>> tokens = {
        {"2","1","+","3","*"}, 
        {"4","13","5","/","+"},
        {"10","6","9","3","+","-11","*","/","*","17","+","5","+"},
        {"15", "7", "1", "1", "+", "-", "/", "3", "*", "2", "11", "+", "-"},
        {"3", "4", "+", "2", "*", "7", "/", "8", "2", "/", "5", "*", "+"},
        {"-50", "3", "/", "10", "*", "100", "12", "7", "-", "/", "-", "42", "+"}
    };

    for (int i = 0; i < (int)tokens.size(); i++) {

        std::cout << "Example " << i << "\nInput: ";
        printInput(tokens[i]);
        std::cout << "Output: " << s.evalRPN(tokens[i]) << std::endl;
        std::cout << "------------------" << std::endl;
    }

    return 0;
}