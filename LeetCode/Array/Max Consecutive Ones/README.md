# Max Consecutive Ones

Problem: [LeetCode](https://leetcode.com/problems/max-consecutive-ones/)

Given a binary array `nums`, return the maximum number of consecutive 1's in the array.

Example 1:  
Input: $nums = [1,1,0,1,1,1]$  
Output: $3$  
Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.

Example 2:  
Input: $nums = [1,0,1,1,0,1]$  
Output: $2$


## Solution
We are told that $1 \le \text{nums.length} \le 10^{5}$ and that $\text{nums[i]}$ is either 0 or 1.

We can find the *maximum number of ones* by performing a single linear scan while updating a global maximum `maxCount`, initially set to 0. As we loop through `nums` we keep a local counter `tempCount`. 

 - Each time we encounter a $1$ we increment `tempCount` and compare it with `maxCount`, updating the global maximum if needed. 
 - Whenever we find a $0$, the consecutive sequence of 1s finished, so we reset `tempCount` and start counting again. 
 - When we reach the end of the vector `nums` the counter `maxCount` holds the global maximum found.

#### Pseudocode

```cpp

int findMaxConsecutiveOnes(std::vector<int>& nums) {
        
    int maxCount = 0;  // global maximum
    int tempCount = 0; // local counter

    // range-based loop
    for (int num : nums) {

        // if we find a 1, we increment local counter
        if (num == 1) {
            tempCount++;
            // update global maximum if needed
            maxCount = std::max(tempCount, maxCount);
        }
        // otherwise, if we find a 0 we reset local counter
        else {
            tempCount = 0;
        }
    }
    // return global maximum found
    return maxCount;
}
```

#### Complexity
We perform a linear scan, therefore the total **time complexity** is $\mathcal{O}(n)$. 

Since we do not use any auxiliary space, the total **space complexity** is $\mathcal{O}(1)$.
