# Advent of Code 2020 - Day 1: Report Repair

## Part 1
In Part 1 we are given an expense report containing a list of integer numbers.  
Our goal is to find the two numbers in the report that sum to **2020** and then multiply the two numbers found to get Part 1's solution.

### Idea
For the first part we can implement a two-pointer sum approach, which requires that the list of numbers be sorted in increasing order.
We can work with a copy of the list, and then work with the sorted copy to implement the two-pointer sum technique.

Using our sorted copy, we start with `i=0` and `j=copy.size()-1`. 
We then loop as long as `i < j` and check if `sum = copy[i] + copy[j]` is equal to our target. 
If it is, we found the two required numbers so we multiply them to have Part 1's solution.
If `sum < target` then we increment `i` as the sum is too small, otherwise we decrement `j` as the sum was too large.
If no solution was found, we simply return `-1` to indicate this. 

### Pseudocode

```cpp
solvePart1(target, report)
    
    copy = report
    sort copy in increasing order
    
    i = 0
    j = copy.size() - 1

    while (i < j) 

        sum = copy[i] + copy[j]
        if (sum == target)
            return copy[i] * copy[j]
        else if (sum < target)
            i++
        else 
            j--

    // if target sum never reached
    return -1
```                    

### Complexity
The **time complexity** is given by the sorting time $\Theta(n \log n)$ plus the linear scan $\Theta(n)$
which is absorbed by the sorting time.
The **space complexity** is $\Theta(n)$ since we work with a copy of the original list (expense report).

---

## Part 2
In Part 2 we are told that we are to find three numbers in the expense report that sum to **2020**.

### Idea
Since we are looking for a triplet that sums to **2020** we can use two approaches.

In the first approach, we can extend the two-pointer sum approach used in Part 1 by working with a sorted copy of the list.
We search by fixing the first element `report[k]` and then applying our two-pointer sum logic by searching for the target sum
`sum = target - report[k]` within `report[k+1...n-1]`. 

If we find `report[i] + report[j] = sum` we then found our triplet, so we multiply these three together and have Part 2's solution.
Otherwise, no triplet was found, so we return `-1`.

Alternatively, we can use a hashing approach by fixing the first element `report[i]` for the triplet.

For each fixed element `report[i]` we use a hash set to store the potential second elements and run another loop inside it from `i+1` to `n-1`, checking if `target - report[i] - report[j]` is present in the hash set.
If it is, then we found our triplet, se we multiply these three together and have Part 2's solution. 
Otherwise, no triplet was found so we return `-1`.

### Pseudocode

```cpp
// approach 1
solvePart2(target, report)

    copy = report
    sort copy in increasing order

    n = copy.size()

    for k = 0 to n-2
        
        i = k + 1
        j = n - 1

        sum = target - copy[k]

        while (i < j)
            if (copy[i] + copy[j] == sum)
                return copy[i] * copy[j] * copy[k]
            else if (copy[i] + copy[j] < sum) 
                i++
            else 
                j--      

    // if no triplet found
    return -1
```


```cpp
// approach 2
solvePart2(target, report)

    n = report.size()

    for i=0 to n-2
        unordered_set<int> st

        for j = i+1 to n-1
            second = target - report[i] - report[j]

            if (st.find(second) != st.end())
                return report[i] * second * report[j]

            st.insert(report[j])    

    // if no triplet was found
    return -1
```   

### Complexity
The **time complexity** for the sorting + two-pointer approach is given by the sorting time $\Theta(n \log n)$ as well as the nested loops which result in the quadratic runnting time $\Theta(n^2)$. Since the nested loops *dominate* the running time, the total time complexity in both approaches is $\Theta(n^2)$.  

In both approaches, the **space complexity** is $\Theta(n)$ due to the copy of the list used in the sorting + two pointer approach, as well as for the use of the set in the hashing-based approach. 

