# Advent of Code 2020 - Day 9: Encoding Error

[Day 9: Encoding Error](https://adventofcode.com/2020/day/9)

With your neighbor happily enjoying their video game, you turn your attention to an open data port on the little screen in the seat in front of you.

Though the port is non-standard, you manage to connect it to your computer through the clever use of several paperclips. Upon connection, the port outputs a series of numbers (your puzzle input).

## Part 1
In Part 1, we are given as input a series of numbers encrypted with the *eXchange-Masking Addition System* (**XMAS**).

We are told that *XMAS* starts by transmitting a **preamble** of 25 numbers. After that, each number we receive should be the *sum of any two of the 25 immediately previous numbers*. There could be more than one pair of numbers, although the two numbers in the pair must be *different*. 

To solve Part 1, we must find the first number in the list (after the initial **preamble**) which is *not* the sum of the 25 numbers before it.

### Idea
For Part 1, I need to preserve the original order of the input numbers because checking whether a given number $\text{num}$ has a valid sum using its 25 previous numbers means preserving their original order. 

To not overcomplicate things, I decided to read the input data line by line and read each number into a `vector<long long> numbers`, stored as a private member in my class `Cypher`. I chose to use `long long` instead of `int` since, looking at the puzzle input, I noticed the numbers getting progressively much larger, large enough to possibly cause **integer overflow**. 

After reading in each number, I decided to implement a private helper `hasValidSum(long long target, int start)` in the class `Cypher`. This helper returns `true` if the list of numbers going from index $\text{start}$ to $\text{start + 25}$ contains a pair of different numbers that sum up to `target`. 

I can then implement this helper in the main algorithm for solving Part 1: 

 - I start *after* the initial *preamble*, meaning from the 26th number `numbers[25]`.
 - I then iterate through the list `numbers` from $i=25 \dots n$.
 - For each number $i$, I check if the helper `hasValidSum` returns `false` when called on the number `target[i]` using `i - 25` as the starting index (since we need to consider the previous 25 numbers to verify the sum).
 - The first time this helper returns `false`, I can return `target` as it is the first number in the list for which there was no valid sum using its previous 25 numbers.

#### Pseudocode

```cpp
// read puzzle input
void readPuzzleInput() {

    // clear previous
    numbers.clear();

    // guard
    ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw runtime_error("Could not read puzzle input");
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            long long num = stoll(line);
            numbers.push_back(num);
        }
    }
    file.close();
}

// private helper for Part 1 solution 
bool hasValidSum(long long target, int start) const {

    // check if any two pairs of different numbers sum to target 
    for (int i = start; i < start + 25; i++) {
        for (int j = i + 1; j < start + 25; j++) {
            
            // if any pair of different numbers sums to target, we have a valid sum
            if (numbers[i] + numbers[j] == target && numbers[i] != numbers[j]) {
                return true;
            }    
        }
    }
    // otherwise, we have found the first non-valid sum
    return false;
}

long long solvePart1() const {

    // guard
    if (numbers.empty()) {
        throw runtime_error("XMAS data was not found");
    }

    // we start after the initial preamble
    for (int i = 25; i < numbers.size(); i++) {

        // the current element considers the 25 previous numbers
        int start = i - 25;
    
        // check for the first number that does not have a valid sum
        if (!hasValidSum(numbers[i], start)) {
            return numbers[i];
        }
    }

    // fallback, no solution found
    return -1;
}
```

#### Complexity

 * If we disregard the cost of initially reading the input. Assuming there are $n$ numbers in the vector `numbers`, the algorithm iterates at most $n-25$ times. For each number, the cost of the operations performed by `hasValidSum` remains constant since the two nested loops iterate at most a fixed constant number of times. Therefore, the total **time complexity** is $\mathcal{O}(n)$.

 * Since we actually store the $n$ numbers read from input in the vector `numbers`, the total **space complexity** is $\mathcal{O}(n)$.

---

## Part 2
In Part 2, we are asked to take the **invalid number** found from Part 1 and find a *contiguous set* of *at least* two numbers in the list that sum to the **invalid number**.

Once we find the set of numbers, the solution to Part 2 is given by adding the *smallest* and *largest* in the set.


### Idea
Again, I cannot rely on a *sorting-based* solution since I must preserve the order of the original list. Since I don't know how the numbers are sorted within the list, I cannot use the standard **two-pointer** algorithm, which requires the vector to be sorted.  

However, I can use a **sliding window** approach, using two *index trackers* `right` and `left` to keep track of the sliding window, and a variable `runningSum` to keep an updated sum of the contiguous set $\text{numbers}[left \dots right]$ being considered. 

 - In particular, my initial instinct about the potential **integer overflow** turned out to be true, as the value of `runningSum` becomes too large to be represented using `int`. Therefore, I used the type `long long` to deal with this. All three of these are initially set to 0. 

     - The algorithm `solvePart2(long long target)` takes Part 1's answer as input (to avoid unnecessary recomputations) and iterates over the list `numbers`. It does so as long as the index `right` is less than the end of the list: $\text{right} < \text{numbers.size}$.
     - At each step, I update the `runningSum` by adding `numbers[right]` and then incrementing the `right` index by 1.
     - If this addition results in a value for `runningSum` that surpasses the `target`, and $\text{left } < \text{right } - 1$, then I must subtract the value `numbers[left]` from it and also increment the `left` index by 1. 
 
 - After each *addition* and/or *subtraction* I then check if $\text{runningSum = target}$.
     - If this happens **and** the condition $\text{right} - \text{left} \ge 2$ is also true we then found the solution. 
     (**Note**: the second condition is needed to enforce the requirement of a **contiguous set* of *at least* two numbers).
     - When both of the conditions above are met, I can then quickly loop through `numbers` within the solution set, meaning:  
     $\text{numbers}[left \dots right]$.
     - This last loop finds the *smallest* and *largest* numbers in the set, adds them, and returns their sum as Part 2's solution.
     - If the target was never reached, I indicate this by returning $-1$. 

#### Pseudocode

```cpp
long long solvePart2(long long target) const {

    // guard 
    if (numbers.empty() || target < 0) {
        throw runtime_error("XMAS data was not found or reveived non-valid target.");
    }
    
    // initialize index trackers and running sum
    int left = 0;
    int right = 0;
    long long runningSum = 0;

    while (right < numbers.size()) {

        // add number indexed by 'right' to running sum and increment 'right' by 1
        runningSum += numbers[right];
        right++;

        // if running sum exceeds target and index trackers have not yet "crossed"
        // we loop until it becomes smaller than the target (or we find the solution)
        while (runningSum > target && left < right - 1) {

            // subtract number indexed by 'left' from running sum and increment 'left' by 1
            runningSum -= numbers[left];
            left++;
        }

        // if running sum matches target and has at least two elements, we found the solution
        if (runningSum == target && (right - left) >= 2) {

            // set temporary min/max
            long long smallest = numbers[left];
            long long largest = numbers[left];
            
            // loop through set to find smallest and largest
            for (int i = left + 1; i <= right; i++) {

                if (numbers[i] < smallest) {
                    // update smallest
                    smallest = numbers[i];
                }
                if (numbers[i] > largest) {
                    // update largest
                    largest = numbers[i];
                }
            }
            return smallest + largest;
        }
    } // if no solution was found, fallback to -1  
    return -1; 
}
```

#### Complexity

 * We pass the `target` as a parameter in Part 2's algorithm, therefore skipping the cost given by Part 1. The algorithm for Part 2 iterates the list `numbers` by either *incrementing* one of the two index trackers `left` or `right`. Assuming there are $n$ numbers, we increment either `left` or `right` at most $n + (n-1) = 2n - 1$ times, meaning $\mathcal{O}(2n)$ iterations. Therefore, we can simplify this for a total **time complexity** of $\mathcal{O}(n)$.
 
 * We do not use any extra *auxiliary space*. However, as in Part 1, we do work with the stored list of numbers. Therefore, the total **space complexity** remains $\mathcal{O}(n)$ if we take into account the cost of storing the vector `numbers`. Disregarding this, the total **space complexity** would be constant $\mathcal{O}(1)$.
 
### Build
Tested using

```text
g++ -std=c++17 main.cpp EncodingError.cpp -o main.exe
./main.exe
```
