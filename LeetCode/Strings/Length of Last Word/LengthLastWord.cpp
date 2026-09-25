#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Solution {
public:

    int lengthOfLastWord(std::string s, bool useStringStream = false) {

        if (useStringStream) {
            return lengthLastStringStream(s);
        }
        else {
            return lengthLastIndexTracker(s);
        }
    }

    int lengthLastStringStream(std::string s) {
        
        std::stringstream ss(s);
        std::string str;

        while (ss >> str) {
            // keep overwriting each word
        }

        return str.length();
    }

    int lengthLastIndexTracker(std::string s) {

        // intial setup
        int ind = s.length() - 1;
        int lengthLast = 0;

        // skip any trailing whitespace characters
        while (ind >= 0 && s[ind] == ' ') {
            ind--;
        }

        // when I find the last character of last word, I count how many characters are in it
        while (ind >= 0 && s[ind] != ' ') {
            lengthLast++;
            ind--;
        }

        return lengthLast;
    }
};

void testPrint(const std::string& label, const std::string& s, int lenA, int lenB) {

    std::cout << label << std::endl;
    std::cout << "String: " << s << std::endl;
    std::cout << "Length of last word" << std::endl;
    std::cout << "Using stringstream = " << lenA << std::endl;
    std::cout << "Using index tracking = " << lenB << std::endl;
}

int main() {

    Solution s;

    std::vector<std::string> strings = {
        {"Hello World"},
        {"   fly me   to   the moon  "},
        {"luffy is still joyboy"},
        {" I eat  bland pasta for everysinglemeal     "},
        {"all allong the watchtower b"}
    };

    for (int i = 0; i < (int)strings.size(); i++) {

        std::string label = "Example " + std::to_string(i) + ":";
        testPrint(label, strings[i], s.lengthOfLastWord(strings[i], true), s.lengthOfLastWord(strings[i], false));
        std::cout << "\n";

    }

    return 0;
}