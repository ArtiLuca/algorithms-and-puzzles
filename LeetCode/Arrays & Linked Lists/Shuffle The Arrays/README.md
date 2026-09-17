# Shuffle the Array

Problem: [LeetCode](https://leetcode.com/problems/shuffle-the-array/)

Given the array `nums` consisting of `2n` elements in the form $[x_1,x_2, \dots ,x_n, y_1,y_2, \dots ,y_n]$.

*Return the array in the form* $[x_1,y_1,x_2,y_2, \dots ,x_n,y_n]$.


Example 1:

Input: $nums = [2,5,1,3,4,7]$, $n = 3$  
Output: $[2,3,5,4,1,7]$  
Explanation: Since $x_1=2, x_2=5, x_3=1, y_1=3, y_2=4, y_3=7$ then the answer is $[2,3,5,4,1,7]$.

Example 2:

Input: $nums = [1,2,3,4,4,3,2,1]$, $n = 4$  
Output: $[1,4,2,3,3,2,4,1]$

Example 3:

Input: $nums = [1,1,2,2]$, $n = 2$  
Output: $[1,2,1,2]$


## Solution
We are told that $1 \le n \le 500$, that $\text{nums.length} = 2n$, and $1 \le \text{nums[i]} \le 10^{3}$.

My first idea was to perform the *shuffling* in-place using a boolean flag to alternate between taking elements on the left side ($x_i$)and elements on the right side ($y_j$). However, this is not necessary, since the resulting vector after *shuffling* has a specific rule regarding its indices from where it takes its values. 

In the final vector, for each index $i \in [0 \dots 2n - 1]$:  
 - all the elements from the left part of `nums` ($x_1 \dots x_n$) end up in even-value indices (including index 0).
 - all the elements from the right part of `nums` ($y_1 \dots y_n$) end up in odd-value indices. 

Knowing this, we can allocate a new vector `result` of size $2n$ and populate it by applying the rule above while iterating from index `i` to `2*n-1`, using two indices `x` and `y`, initially set to `x=0` and `y=n`, to track the current index for the *x* elements and *y* elements in the original vector `nums`. Then, for each index `i` we use the *modulo operator*:  
 - if `i % 2 == 0`, then we populate `result[i]` using `nums[x]` and increment `x` by 1.
 - if `i % 2 != 0`, then we populate `result[i]` using `nums[y]` and increment `y` by 1. 

 #### Pseudocode

```cpp
vector<int> shuffle(std::vector<int>& nums, int n) {  
        
        // allocate new vector of size 2n
        vector<int> result(2*n);

        // index trackers for x elements and y elements
        int x = 0;
        int y = n;

        // apply modulo rule for populating
        for (int i = 0; i < (int)result.size(); i++) {

            // if even index (or index 0), we take from x elements
            if (i % 2 == 0) {
                result[i] = nums[x++];
            }
            // if odd index, we take from y elements
            else {
                result[i] = nums[y++];
            }
        }

        return result;
    }
```

#### Complexity
Since we iterate the entire `result` vector at most $2n$ times, the total **time complexity** is $\mathcal{O}(2n)$, which can be simplified to $\mathcal{O}(n)$.

Since we allocate a new vector of size $2n$ the total **space complexity** is also $\mathcal{O}(n)$.