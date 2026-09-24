#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

class Solution {

public:

    std::vector<int> exclusiveTime(int n, std::vector<std::string>& logs) {

        // allocate vector to store exclusive times of functions by ID (initially all set to 0)
        std::vector<int> exclusiveTimes(n, 0);
        // allocate stack structure for storing IDs of functions currently executing
        std::stack<int> currentIDs;
        // intial previous time is 0
        int prevTime = 0;

        // iterate through the log stream
        for (const std::string& log : logs) {

            // parse each log based on given format
            std::istringstream ss(log);
            std::string strID, status, strTimestamp;
            
            std::getline(ss, strID, ':');
            std::getline(ss, status, ':');
            std::getline(ss, strTimestamp, ':');

            int functionID = std::stoi(strID);
            int currentTime = std::stoi(strTimestamp);

            // if it's a "start" log
            if (status == "start") {
                
                // if there is an active function on top
                if (!currentIDs.empty()) {
                    // credit it for elapsed time 
                    exclusiveTimes[currentIDs.top()] += currentTime - prevTime;
                }
                // store new log ID in stack, and set previous time to current time
                currentIDs.push(functionID);
                prevTime = currentTime;
            }
            // otherwise, if it's an "end" log
            else {
                // credit active function for elapsed time plus the ending timestamp unit
                exclusiveTimes[currentIDs.top()] += currentTime - prevTime + 1;
                // pop from stack and set previous time to current time, plus 1 for inclusivity
                currentIDs.pop();
                prevTime = currentTime + 1;
            }
        }

        // return solution
        return exclusiveTimes;
    }
    
};

void testPrint(
    const std::string& label, 
    const std::vector<std::string>& logs, 
    const std::vector<int>& times) {

    std::cout << label << "\nLogs: [ ";
    for (const std::string& log : logs) {
        std::cout << log << " ";
    }
    std::cout << "]" << std::endl;
    
    std::cout << "Exclusive Times: [ ";
    for (const int& time : times) {
        std::cout << time << " ";
    }
    std::cout << "]\n\n" << std::endl;
}

int main() {

    Solution s;

    std::vector<std::string> logs1 = {"0:start:0","1:start:2","1:end:5","0:end:6"};
    std::vector<std::string> logs2 = {"0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"};
    std::vector<std::string> logs3 = {"0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"};
    std::vector<std::string> logs4 = {"0:start:0","1:start:2","2:start:3","2:end:4","1:end:5","0:start:7","0:end:8","0:end:9"};

    testPrint("Example 1:", logs1, s.exclusiveTime(2, logs1));

    //std::cout << "Example 2:" << std::endl;
    testPrint("Example 2:", logs2, s.exclusiveTime(1, logs2));
    
    //std::cout << "Example 3:" << std::endl;
    testPrint("Example 3:", logs3, s.exclusiveTime(2, logs3));

    //std::cout << "Example 4 (Complex Stack):" << std::endl;
    testPrint("Example 4:", logs4, s.exclusiveTime(3, logs4));

    return 0;
}