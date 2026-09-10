# Advent of Code 2020 - Day 3: Toboggan Trajectory

[Day 3: Toboggan Trajectory](https://adventofcode.com/2020/day/3)

## Part 1
We are traversing a 2D grid using a toboggan from the top row to the bottom row.  
The 2D grid is given as input and marks *empty spaces* with `.` and **trees** with `#`. 

We are also told that the 2D grid repeats the same pattern to the right many times, so theoretically we can always move to the right until we reach the bottom. 
We want to find the number of **trees** we would encounter while descending the grid from the top-left *empty space* all the way to the bottom, always following a slope of **right 3** and **down 1**. 

### Idea 
Assuming that we store the grid read from input as a `vector<string> grid` object, our starting position is `grid[0][0]`  
(or $row j=0$, $column i=0$). We want to descend until we pass the last row of the grid.

Since the grid repeats the same pattern going **right**, we can use the *modulo* operator to mimic this infinitely repeating pattern.

In other words, if we store the grid read from input as `vector<string> grid`, we can interpret:  

 - `grid.size()` as $r$, the total number of **rows** (the **height** of the grid).
 - `grid[0].length()` as $c$, the total number of **columns** (the **width** of the grid).
 
If we move an arbitrary number of times going **right 3** and **down 1** and find ourselves at the column index $i$,  
we can determine our actual horizontal position inside the original pattern using the *modulo* operator and the total number of columns:

$i = i (\mod c)$,   where $c$ is the **width** (total columns) of our 2D grid.

Knowing this, we can count the total number of trees found down the slope by using a counter `treeCount` and traversing the grid  
starting from row $j=0$ and column $i=0$, meaning `grid[0][0]`.

At each step, we check if the current coordinate `grid[j][i % c]` contains a tree and update `treeCount` if it does.  
Then, we advance to the next position by moving right 3 (`i = i + 3`) and down 1 (`j = j + 1`).  
Once we hit the last row, meaning `j >= r`, we stop and return `treeCount` as Part 1's solution. 

#### Pseudocode
Assuming we stored the grid as `std::vector<std::string> grid`:  

```cpp
long long solvePart1() const {

    // guard
    if (grid.empty()) {
        return 0;
    }

    long long treeCount = 0;
    int rows = grid.size();
    int cols = grid[0].length();

    int r = 0, c = 0;

    while (r < rows) {

        // check if tree  
        if (grid[r][c % cols] == '#') {
            treeCount++;
        }

        // Right 3, Down 1
        r += 1; c += 3;
    }
    return treeCount;
}
```

#### Complexity
Assuming the grid contains $n$ rows and $m$ columns, and not taking into account the initial input reading phase,  
the total **time complexity** is linear with the total number of rows in the grid $\mathcal{O}(n)$.

The total **space complexity** is $\mathcal{O}(n \times m)$ since we store a copy of the grid as a private member.

## Part 2
In Part 2, we are given four other possible slopes to consider alongside the one from Part 1.  
We are told to consider how many trees we would encounter if we traversed the 2D grid considering five different slopes:

 - Right 1, down 1.
 - Right 3, down 1. (This is the slope we already checked.)
 - Right 5, down 1.
 - Right 7, down 1.
 - Right 1, down 2.

To find Part 2's solution, we need to count the total number of trees encountered following each different slope and then multiply the five resulting tree counts.

### Idea
Since the 2D grid is the same for each slope considered, we can implement a similar logic to Part 1, using the *modulo* operator to deal with the repeated pattern on the right of the grid.

The only difference now is the number of positions we move **right** and how many we move **down**.  
We can generalize Part 1's algorithm to also take as parameters `right` and `down`, and then implement a helper  
`countTrees(int right, int down)` to traverse and count the number of trees encountered for each slope.

Since the number could be quite big, we use `long long` as the return value, so as not to run into *integer overflow* when multiplying the five results. 
The base logic remains mostly unchanged.  

We can then count the total trees encountered when traversing all five slopes using our helper and multiply the results to get Part 2's solution.

#### Pseudocode

```cpp
long long countTrees(int right, int down) const {

    long long treeCount = 0;
    int rows = grid.size();
    int cols = grid[0].length();

    int r = 0, c = 0;

    while (r < rows) {

        // check if tree  
        if (grid[r][c % cols] == '#') {
            treeCount++;
        }

        // move based on slope
        r += down; c += right;
    }
    return treeCount;
}

long long solvePart2() const {

    // guard
    if (grid.empty()) {
        return 0;
    }

    long long tc1 = countTrees(1,1);
    long long tc2 = countTrees(3,1);
    long long tc3 = countTrees(5,1);
    long long tc4 = countTrees(7,1);
    long long tc5 = countTrees(1,2);

    return tc1 * tc2 * tc3 * tc4 * tc5;
}
```

#### Complexity
The cost of a single call to the helper `countTrees` remains linear with the total number of rows $n$ in the grid, so a single call has a complexity in time of $\mathcal{O}(n)$.  
The time complexity for the first four slopes is $\mathcal{O}(n)$, while the cost for the fifth slope is $\mathcal{O}(\frac{n}{2})$.  
The total **time complexity** for all five calls can be simplified to $\mathcal{O}(n)$.

The total **space complexity** remains the same as in Part 1 $\mathcal{O}(n \times m)$, since we store a copy of the grid. 

### Build
Tested using:

```text
g++ -std=c++17 main.cpp TobogganTrajectory.cpp -o main.exe
./main.exe
```
