# How Many Numbers Are Smaller Than the Current Number

Problem: [LeetCode](https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/description/)

Given the array `nums`, for each $\text{nums[i]}$ find out how many numbers in the array are smaller than it. That is, for each $\text{nums[i]}$ you have to count the number of valid $j$'s such that $j \ne i$ **and** $\text{nums[j]} < \text{nums[i]}$.

Return the answer in an array.

Example 1:  
Input: $nums = [8,1,2,2,3]$  
Output: $[4,0,1,1,3]$  
Explanation:
 - For $nums[0]=8$ there exist four smaller numbers than it (1, 2, 2 and 3).
 - For $nums[1]=1$ does not exist any smaller number than it.
 - For $nums[2]=2$ there exist one smaller number than it (1).
 - For $nums[3]=2$ there exist one smaller number than it (1).
 - For $nums[4]=3$ there exist three smaller numbers than it (1, 2 and 2).

Example 2:  
Input: $nums = [6,5,4,8]$  
Output: $[2,1,0,3]$

Example 3:  
Input: $nums = [7,7,7,7]$  
Output: $[0,0,0,0]$


## Solution
We are told that $2 \le \text{nums.length} \le 500$ and that $0 \le \text{nums[i]} \le 100$.

My first idea was to sort the vector `nums`, but this would mean losing the values of the original indices plus the additional cost of sorting (which is not *optimal*). 

After discarding that option, I thought of using the logic implemented in the algorithm **Counting Sort**. In particular, the idea of using an *occurrence array* to keep track of how many elements are smaller than the current one.

---

In the standard **Counting Sort** algorithm: 

 1. We create a vector $C[0 \dots k]$ (with $k$ being the maximum value), and count how many times each number appears in the input vector $A$.
 
 2. We modify $C$ by adding elements such that $C[i]$ tells us the exact *ending position* of element $i$ by doing $C[i] \text{ += } C[i-1]$. This tracks how many elements are less than or equal to $i$.

3. We loop backwards through $A$, placing each element directly into its correct sorted slot in the output vector $B$ using the position stored in $C$, decrementing $C$ as it goes.
 
In our case, `nums` is the input vector $A$. The vector `result` is the output vector $B$, matching the size of `nums`. The value of $k$ is 100.  
The vector `count` is the occurrence array $C$ of size $101$ initialized to all zeros and representing the indices $0 \dots 100$. 

---

We can adapt the standard **Counting Sort** logic by making two small adjustments:

 - Instead of calculating in `count` the *less than or equal to* positions, we modify `count` using a **running sum** so that `count[i]` stores elements *strictly smaller than* `i`.
 
 - We keep the output vector `result` in its original layout. We loop through `nums` *left-to-right* from $j=0 \dots \text{nums.size()}- 1$, using `count[nums[j]]` as a **direct lookup table** to populate `result[j]`.

#### Pseudocode

```cpp
vector<int> smallerNumbersThanCurrent(vector<int>& nums) {

    // allocate occurrence vector of size 101, all initially with value 0
    int k = 100;
    vector<int> count(k+1, 0);

    // count occurrences of each number
    for (int i = 0; i < (int)nums.size(); i++) {
        count[nums[i]]++;
    }

    // modify count vector by storing strictly smaller than counts, using a running sum
    int sum = 0;
    for (int i = 0; i <= k; i++) {

        // get num. occurrences of current element
        int current = count[i];
        // update it by storing how many numbers were strictly smaller than it
        count[i] = sum;
        // accumulate for next numbers
        sum += current;
    }

    // map values back to output vector, keeping the original order
    vector<int> result(nums.size());
    for (int j = 0; j < (int)nums.size(); j++) {
        result[j] = count[nums[j]];
    }

    // return output vector
    return result;

}
```

#### Complexity

* Assuming the vector `nums` contains $n$ elements, the algorithm has a time complexity of $\mathcal{O}(n+k)$. Since $k$ is a fixed constant, we can simplify the total **time complexity** to $\mathcal{O}(n)$.

* We allocate the vector `result` with the same size as `nums`. Therefore, the total **space complexity** is $\mathcal{O}(n)$.
