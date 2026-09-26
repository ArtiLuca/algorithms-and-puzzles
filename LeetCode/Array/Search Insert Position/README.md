# Search Insert Position

Problem: [LeetCode](https://leetcode.com/problems/search-insert-position/description/)

Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with $\mathcal{O}(\log n)$ runtime complexity.



Example 1:  
Input: `nums = [1,3,5,6]`, `target = 5`  
Output: `2`

Example 2:  
Input: `nums = [1,3,5,6], target = 2`  
Output: `1`

Example 3:  
Input: `nums = [1,3,5,6]`, `target = 7`  
Output: `4`

## Solution
We are told that  $1 \le \text{nums.length} \le 10^{4}$, that $-10^{4} \le \text{nums[i]} \le 10^{4}$, that  `nums` contains **distinct** values sorted in **ascending** order, and that $-10^{4} \le \text{target} \le 10^{4}$.

Since the vector `nums` is sorted in *increasing* order and contains *distinct* values, I can use a **binary search** approach to implement a solution. In particular, I chose to use an *iterative* version rather than a *recursive* one so as not to allocate any extra *auxiliary space*.

As in the standard **binary search** approach, I use two *index trackers* `low` and `high`, initially set to the first and last element of `nums`, respectively. I then loop as long as the condition $\text{low} \le \text{high}$ holds, and at each iteration: 

 - I compute the middle index `mid`, which is usually done by computing $\text{mid} = \lfloor\frac{\text{low + high}}{2} \rfloor$.
    - However, to avoid potential *overflow*, I can use the safer equivalent: `mid = low + (high - low) / 2`. 

 - I then proceed in three sub-cases:
    - If we have `nums[mid] == target`, then we found the target, so we return it.
    - If we have `nums[mid] < target`, then we narrow the search area by shifting to the right: `low = mid + 1`.
    - Otherwise, if `nums[mid] > target`, then we narrow the search area by shifting left: `high = mid - 1`.

 - At the end of the algorithm, I return the index `low`, which represents the position in `nums` if the `target` were inserted in order.

### Pseudocode

```cpp
int searchInsert(vector<int>& nums, int target) {
        
    // initial index trackers
    int low = 0;
    int high = nums.size() - 1;

    // loop as long as search areas don't "cross"
    while (low <= high) {

        // compute search area's middle index
        int mid = low + (high - low) / 2;

        // if we found our target, we return it
        if (nums[mid] == target) {
            return mid;
        }
        // narrow search area to the right
        else if (nums[mid] < target) {
            low = mid + 1;
        }
        // otherwise, narrow search area to the left
        else {
            high = mid - 1;
        }
    }

    // once out of the loop, 'low' contains the ordered insertion position of target 
    return low;
}
```

#### Complexity

 * Assuming `nums` contains $n$ numbers. The algorithm cuts the search area in half at each iteration; therefore, the *cost* can be given by the recurrence $T(n) = T(n/2) + \Theta(1)$, where $\Theta(1)$ represents the constant cost performed at each step. Therefore, the total **time complexity** is $\mathcal{O}(\log n)$, which can be proven by either *substitution* or by using the *master theorem*.

 * The algorithm performs the search operation *in-place*. Therefore, the total **space complexity** is $\mathcal{O}(1)$.

### Terminal Output

Tests from *SearchInsertPosition.cpp* in `main.cpp`:

```text
Example 0
>nums: [ 1 3 5 6 ]
>target: 5
>output: 2

Example 1
>nums: [ 1 3 5 6 ]
>target: 2
>output: 1

Example 2
>nums: [ 1 3 5 6 ]
>target: 7
>output: 4

Example 3
>nums: [ 1 2 3 6 9 10 11 14 18 ]
>target: 10
>output: 5

Example 4
>nums: [ 3 6 9 11 12 14 16 18 22 23 24 25 ]
>target: 19
>output: 8

Example 5
>nums: [ 1 5 9 10 12 16 18 20 23 25 ]
>target: 24
>output: 9
```
