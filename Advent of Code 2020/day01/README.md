# Advent of Code 2020 - Day 1: Report Repair

## Part 1
In Part 1 we are given an expense report containing a list of integers.  
Our goal is to find the two numbers in the report that sum to **2020** and then multiply the two numbers found to get Part 1's solution.

### Idea
For the first part, we can implement a two-pointer sum approach, which requires that the list of numbers be sorted in increasing order.
We can work with a copy of the list, and then work with the sorted copy to implement the two-pointer sum technique.

Using our sorted copy, we start with `i=0` and `j=copy.size()-1`. 
We then loop as long as `i < j` and:

 - if `sum = copy[i] + copy[j]` is equal to our target, we found the two required numbers so we multiply them to have Part 1's solution.
 - if `sum < target` then we increment `i` as the sum is too small.
 - if `sum > target` we decrement `j` as the sum is too large.
 - if no solution was found, we simply return `-1` to indicate this. 

### Pseudocode

```cpp
long long solvePart1(int target, vector<int> report) {
    
    vector<int> copy = report;
    sort(copy.begin(), copy.end());
    
    int i = 0;
    int j = copy.size() - 1;

    while (i < j) {
        long long sum = copy[i] + copy[j];

        if (sum == target)
            return (long long) copy[i] * copy[j];
        else if (sum < target)
            i++;
        else 
            j--;
    }
    // if target sum never reached
    return -1;
}
```                    

### Complexity
The **time complexity** is given by the sorting time $\Theta(n \log n)$ plus the linear scan $\Theta(n)$, which is absorbed by the sorting time.

The **space complexity** is $\Theta(n)$ since we work with a copy of the original list (expense report).

---

## Part 2
In Part 2, we are told that we are to find three numbers in the expense report that sum to **2020**.

### Idea
Since we are looking for a triplet that sums to **2020**, we can use two approaches.

In the first approach, we can extend the two-pointer sum approach used in Part 1 by working with a sorted copy of the list. 
We search by fixing the first element `report[k]` and then applying our two-pointer sum logic by searching for the target sum 
`sum = target - report[k]` within `report[k+1...n-1]`. 
If we find `report[i] + report[j] = sum` we have found our triplet, so we multiply these three together and have Part 2's solution.
Otherwise, no triplet was found, so we return `-1`.

Alternatively, we can use a hashing approach by fixing the first element `report[i]` for the triplet.
For each fixed element `report[i]` we use a hash set to store the potential second elements and run another loop inside it from `i+1` to `n-1`.
At each iteration, we check if `target - report[i] - report[j]` is present in the hash set.
If it is, then we found our triplet, so we multiply these three together and have Part 2's solution. 
Otherwise, no triplet was found, so we return `-1`.

### Pseudocode

#### Two-Pointer Approach

```cpp
// approach 1
long long solvePart2(int target, vector<int> report) {

    vector<int> copy = report;
    sort(copy.begin(), copy.end()); 

    int n = copy.size();

    for (int k = 0; k < n-2; k++) {
        
        int i = k + 1;
        int j = n - 1;

        long long sum = target - copy[k];

        while (i < j) {
            if (copy[i] + copy[j] == sum)
                return (long long) copy[i] * copy[j] * copy[k];
            else if (copy[i] + copy[j] < sum) 
                i++;
            else 
                j--;      
        }
    }

    // if no triplet found
    return -1;
}
```

#### Hash Set Approach

```cpp
// approach 2
long long solvePart2(int target, vector<int> report) {

    int n = report.size();

    for (int i=0; i < n-2; i++) {
        unordered_set<int> st;

        for (int j = i+1; j < n; j++) {
            int second = target - report[i] - report[j];

            if (st.find(second) != st.end()) {
                return (long long)report[i] * second * report[j]; 
            }

            st.insert(report[j]);
        }
    }     
    // if no triplet was found
    return -1;
}
```   

### Complexity
The **time complexity** for the sorting + two-pointer approach is given by the sorting time $\Theta(n \log n)$ as well as the nested loops, which result in the quadratic running time $\Theta(n^2)$. Since the nested loops *dominate* the running time, the total time complexity in both approaches is $\Theta(n^2)$.  

In both approaches, the **space complexity** is $\Theta(n)$ due to the copy of the list used in the sorting + two-pointer approach, as well as the use of the set in the hashing-based approach. 

