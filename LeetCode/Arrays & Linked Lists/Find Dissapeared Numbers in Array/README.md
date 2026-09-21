# Find All Numbers Disappeared in an Array

Problem: [LeetCode](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array)

Given an array `nums` of $n$ integers where `nums[i]` is in the range $[1 \dots n]$, return an *array of all the integers in the range* $[1 \dots n]$ that do not appear in `nums`.


Example 1:  
Input: $nums = [4,3,2,7,8,2,3,1]$  
Output: $[5,6]$

Example 2:  
Input: nums = $[1,1]$  
Output: $[2]$


## Solution
We are told that $n = \text{nums.length}$, that $1 \le n \le 10^{5}$, and that $1 \le \text{nums[i]} \le n$.

The most *intuitive* idea that came to mind was using a **hash set** to inspect what numbers in the vector `nums` were missing from the expected sequence $1 \dots n$: 

 - We use a `unordered_set<int> seen` as our **hash set** and initially populate it with the numbers found in `nums`.
 - We then inspect the **hash set** by checking the expected sequence of numbers $1 \dots n$ and *pushing* any expected number that was not found in the `missing` vector returned as the result.

```cpp
vector<int> findDisappearedNumbers(vector<int>& nums) {

        // create hash set, and insert numbers found in nums
        unordered_set<int> seen;
        for (int num : nums) {
            // skipping duplicate values
            seen.insert(num);
        }

        // allocate result vector, and inspect against sequence 1 to n
        vector<int> missing;
        for (int i = 1; i <= nums.size(); i++) {
            // if an expected number from sequence is missing
            if (seen.find(i) == seen.end()) {
                // we push into result vector
                missing.push_back(i);
            }
        }
        return missing;
    }
```

 * We perform two linear scans, with the operations performed on the **hash set** having a cost of $\mathcal{O}(1)$ on average. Therefore, the total **time complexity** is $\mathcal{O}(n)$.
 
 * Since we use a **hash set**, twe use total **space complexity** of $\mathcal{O}(n)$ to store it.

---

We are asked as a follow-up question:

> Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

For this follow-up question, two approaches that operate **in-place** came to mind:

 1. **Cyclic Sorting**
 2. **Using Sign Modification**

#### Approach 1: Cyclic Sorting
I had already used this approach to implement a solution for the *Set Mismatch* problem. 

 - Since the vector `nums` contains the numbers strictly from 1 to n, we can use its indices as a *hash map*. For each number $x$ from 1 to n, we iterate over `nums` and place it in its correct *0-indexed* position $x-1$. We apply this *cyclic sorting* by doing a single pass and continuing to swap elements until each one is in its correct position.
 
  - After *sorting* the vector `nums`, we can then perform a second pass to find all the *disappearing* numbers. Whenever we find that $nums[i] \ne i+1$, we found a *disappearing* number, so we push $i+1$ into the vector `missing` returned at the end of the algorithm.

```cpp
vector<int> findDisappearedNumbers(vector<int>& nums) {

        int n = nums.size();

        // iterate over nums, applying cyclic sorting
        for (int i = 0; i < n; i++) {

            // until each number is in its correct 0-indexed position
            while (nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // allocate result vector, and iterate over the now sorted vector nums
        vector<int> missing;
        for (int i = 0; i < n; i++) {

            // each time we find the index of a number that does not match 
            // the expected value, we push into result vector
            if (nums[i] != i+1) {
                missing.push_back(i+1);
            }
        }
        return missing;
    }
```

**Note**: At first glance, the time complexity seems quadratic (at least for me...) since the algorithm uses a nested loop in the first *sorting phase*. 

 * We iterate $n$ times in the outer loop, swapping elements into their correct positions. Since each swap places *at least* one number in its correct position, the inner loop iterates *at most* $n$ times. Therefore, the first phase has a cost of $\mathcal{O}(n) + \mathcal{O}(n) = \mathcal{O}(n)$. Since the second scan is also linear, the total **time complexity** is $\mathcal{O}(n)$.
 
 * Since the *sorting* is done *in-place*, the total **space complexity** is $\mathcal{O}(1)$.

---

#### Approach 2: Using Sign Modification
Since we know that the vector `nums` contains numbers from 1 to n, this means that each number corresponds directly to a *valid index* within the vector (subtracting 1 to adjust for *0-indexing*).  

We then implement a solution by performing two linear scans.

 - In the first scan, for each number we encounter, we find its corresponding *0-indexed* position within the vector and store the negated number in that position. If we encounter duplicates, these are skipped and remain positive.
 
 - In the second scan, we iterate over the vector `nums` and check the *sign* of the stored number. We skip *negative* numbers, while any *positive* number found corresponds to a *disappearing* number. For every *positive* number found, we store the corresponding missing expected number for that index in the vector `missing` returned at the end of the algorithm.

```cpp
vector<int> findDisappearedNumbers(vector<int>& nums) {

        // iterate over vector, marking "seen" numbers
        for (int i = 0; i < (int)nums.size(); i++) {

            // find the 0-index position of current number
            int index = abs(nums[i]) - 1;

            // insert negated number in 0-index position
            // we skip negative numbers (index already visited/marked)
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }

        // allocate result vector, and iterate over "marked" vector
        vector<int> missing;
        for (int i = 0; i < (int)nums.size(); i++) {

            // every positive value found is a duplicate, meaning a "disappearing" number
            // for every positive number found, we increment it by 1 and push into result vector
            if (nums[i] > 0) {
                missing.push_back(i+1);
            }
        }
        return missing;
    }
```
 
 * We perform two linear scans. One for marking *seen* numbers with their negated values and a second one to find the *disappearing* numbers. Therefore, the total **time complexity** is $\mathcal{O}(n)$.
 
 * Since we do not use an *auxiliary space*, the total **space complexity** is $\mathcal{O}(1)$ using this second approach as well.
 
