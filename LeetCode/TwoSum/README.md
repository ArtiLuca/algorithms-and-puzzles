# Two Sum

[Two Sum](https://leetcode.com/problems/two-sum/description/).

You are given an array of integers `nums` and an integer `target`, return *indices of the two numbers such that they add up to `target`*.
You may assume that each input would have ***exactly* one solution**, and you may not use the *same* element twice.
You can return the answer in any order.

## Solution

### Idea 1: Using two-pointer sum approach

The two-pointer sum approach requires that the array of integers `nums` be sorted in increasing order.

In particular, since the problem asks to return the indices of the two numbers found, we must store the original values and indices in 
an auxiliary structure, and then sort this in increasing order.

For example, we can use `std::vector<std::pair<int,int>> aux` to store the original pairs of values and indices $(v,i)$. 
We then sort `aux` in increasing order and apply the two-pointer sum starting with `i=0` and `j=nums.size()-1`.  

We can then check at each step if `aux[i].first + aux[j].first == target`.
If so, we return `{aux[i].second, aux[j].second}` since we found a pair that reached the target sum.  

Otherwise, we increase index `i` if the sum is too small or decrement index `j` if the sum is too large. 
In the case that no pair is found for the given target number, we simply return `{}`.

#### Pseudocode

```cpp
vector<int> twoSumA(vector<int>& nums, int target) {
        
        std::vector<std::pair<int,int>> aux;
        for (int i = 0; i < nums.size(); i++) 
            aux.push_back({nums[i], i});
        
        std::sort(aux.begin(), aux.end());

        int i = 0;
        int j = aux.size() - 1;

        while (i < j) {

            long long sum = (long long)aux[i].first + aux[j].first;

            if (sum == target) {
                return {aux[i].second, aux[j].second};
            }
            else if (sum < target) {
                i++;
            }
            else {
                j--;
            }
        }

        return {};
    }    
```      

#### Complexity

The sorting has a cost $\Theta(n \log n)$, and the while loop runs in $\Theta(n)$ time.
Therefore, the total **time complexity** is $\Theta(n \log n)$.

The total **space complexity** is $\Theta(n)$ since we work with a sorted auxiliary data structure that maintains the original values and indexes.


### Idea 2: Using a hashing-based approach

We can completely skip the sorting and instead rely on a hashing-based approach to look up elements in linear time.

#### Pseudocode

```cpp
vector<int> twoSumB(vector<int>& nums, int target) {

        // maps value -> index
        std::unordered_map<int,int> seen;

        for (int i = 0; i < nums.size(); i++) {
            int needed = target - nums[i];
            
            if (seen.find(needed) != seen.end()) {
                return {seen[needed], i};
            }

            seen[nums[i]] = i;
        }

        return {};
    }
```    

### Complexity

The total **time complexity** is $\Theta(n)$ since the for loop runs $\Theta(n)$ times.
The hashing structure requires a total **space complexity** of $\Theta(n)$.


