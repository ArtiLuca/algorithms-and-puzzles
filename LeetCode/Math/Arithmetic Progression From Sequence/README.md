# Can Make Arithmetic Progression From Sequence

Problem: [LeetCode](https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/)

A sequence of numbers is called an **arithmetic progression** if the difference between any two consecutive elements is the same.

Given an array of numbers `arr`, return `true` *if the array can be rearranged* to form an **arithmetic progression**. Otherwise, return `false`.

Example 1:

Input: `arr = [3,5,1]`  
Output: `true`  
Explanation: We can reorder the elements as `[1,3,5]` or `[5,3,1]` with differences of 2 and -2, respectively, between each consecutive element.

Example 2:

Input: `arr = [1,2,4]`  
Output: `false`  
Explanation: There is no way to reorder the elements to obtain an arithmetic progression.


## Solution
We are told that $2 \le \text{arr.length} \le 1000$ and that $-10^{6} \le \text{arr[i]} \le 10^{6}$.

Two different approaches came to mind for solving this problem.

### Approach 1
My first idea was to **sort** the array `arr` in increasing order and then take the difference between the *second* and *first* number in the sorted array `diff = arr[1] - arr[0]`. In order to form an **arithmetic progression**, the remaining numbers in the sorted array must have the same difference. 

Assuming $n = \text{arr.size()}$, this means that $\forall i \in [2 \dots n - 1]$ the condition `arr[i] - arr[i-1] == diff` must evaluate to true: 
- If we find any pair of indices that do not meet this requirement, we immediately return `false`. 
- If the entire *sorted array* is scanned without finding any violations, we then return `true`.  

#### Pseudocode

```cpp
bool canMakeArithmeticProgression_Sorting(vector<int>& arr) {

    // sort 'arr' in increasing order
    sort(arr.begin(), arr.end());

    // find difference between first two elements in sorted array
    int diff = arr[1] - arr[0];

    // iterate through remaining sorted numbers, checking they have the same difference
    for (int i = 2; i <(int)arr.size(); i++) {

        // if we find a mismatch in difference, 'arr' cannot form an arithmetic progression
        if (arr[i] - arr[i-1] != diff) {
            return false;
        }
    }
    // otherwise, 'arr' can form an arithmetic progression
    return true;
}
```

#### Complexity
For this first approach, *sorting* the array has cost $\mathcal{O}(n \log n)$ and scanning the remaining numbers has linear cost. Therefore, the total **time complexity** with this approach is $\mathcal{O}(n \log n) + \mathcal{O}(n)$, which can be simplified to $\mathcal{O}(n \log n)$. 

Disregarding the auxiliary space required by the call stack during *sorting*, the total **space complexity** using this first approach is $\mathcal{O}(1)$.

### Approach 2
The second idea came to me as I was implementing the first one. Assuming `arr` is an array of $n$ numbers that can be rearranged to form an **arithmetic progression**, then the total distance between the *largest* number and the *smallest* number must be perfectly divisible by the number of **gaps** $n-1$ between them: $(largest - smallest) \mod (n-1) = 0$.

- Therefore, we can *skip sorting* and instead find the *largest* number `maxValue` and *smallest* number `minValue` in the array `arr`, representing the *starting point* and *ending point* of the sequence. As we do this, we also **insert** each number into a hash set `unordered_set numbers`.

- After this first phase, if we find that $(maxValue - minValue) \mod (n-1) \ne 0$, then we can immediately return `false` as the array **cannot** form a valid **arithmetic progression**. Otherwise, we store the difference as $diff = (maxValue - minValue) \div (n-1)$.

- If $diff = 0$, this means that $maxValue = minValue$, meaning that the array `arr` was made up entirely of identical elements. Since an array of *identical* numbers has a *constant difference* of 0, it is a valid **arithmetic progression**, so we return `true`.

- Otherwise, if `arr` is a valid **arithmetic progression**, then we should be able to *build* the entire sequence starting from `minValue` and adding `diff` step by step. We can run a loop from $i=0 \dots n-1$ to check if $minValue + i * diff \in \text{numbers}$. If we find an expected number to be missing from our hash set, we return `false`. Otherwise, if we successfully find every expected number $\forall i, 0 \le i < n$, we return `true`.

#### Pseudocode

```cpp
bool canMakeArithmeticProgression_HashSet(vector<int>& arr) {

    int n = arr.size();

    // find minimum and maximum in 'arr'
    int minValue = INT_MAX;
    int maxValue = INT_MIN;
    unordered_set<int> numbers;

    //range-based loop
    for (int num : arr) {
        minValue = min(minValue, num);
        maxValue = max(maxValue, num);
        numbers.insert(num);
    }

    // if total "spread" is not perfectly divisible
    if ((maxValue - minValue) % (n - 1) != 0) {
        // not a valid arithmetic progression
        return false;
    }

    // get common difference ("distance")
    int diff = (maxValue - minValue) / (n - 1);

    // if minValue and maxValue were the same 
    if (diff == 0) {
        // all numbers were identical, valid arithmetic progression
        return true;
    }

    // verify that all expected terms of arithmetic progression are in the hash set
    for (int i = 0; i < n; i++) {
        int val = minValue + i * diff;
        // if a value is not found 
        if (numbers.find(val) == numbers.end()) {
            // not a valid arithmetic progression
            return false;
        }
    }

    // if all expected numbers were found, it is a valid arithmetic progression
    return true;
}
```

#### Complexity
Using the **hash set** approach, assuming there are $n$ numbers in the array `arr`. The cost of finding the minimum and maximum is $\mathcal{O}(n)$. We then loop at most $n$ times to check the elements, with the **hash set** operations having a cost of $\mathcal{O}(1)$ on average. Therefore, the total **time complexity** is: $\mathcal{O}(n) + n \times \mathcal{O}(1)$, which can be simplified to $\mathcal{O}(n)$. 

Since we store $n$ elements in the **hash set**, the total **space complexity** is $\mathcal{O}(n)$.
