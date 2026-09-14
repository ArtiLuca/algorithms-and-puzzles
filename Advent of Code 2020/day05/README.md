# Advent of Code 2020 - Day 5: Binary Boarding

[Day 5: Binary Boarding](https://adventofcode.com/2020/day/5)

## Part 1
We are given a list of **boarding passes** in the format $FBFBBFFRLR$. Each **boarding pass** can be used to determine its corresponding unique **seat ID**. 

For each boarding pass, the **first 7** characters determine one of the 128 rows on the plane **row**, while the last three characters are used to determine 1 of the 8 columns on the plane. The plane uses **binary space partitioning** to seat people, where **F** means *front*, **B** means *back*, **L** means *left*, and **R** means *right*.

The first **7** characters are guaranteed to be either **F** or **B**, and these specify 1 of the 128 rows on the plane $0 \dots 127$. In particular, each letter specifies which half of a region of the plane our seat is in (*front* or *back*). For example, the first letter specifies if our seat is in the *front* ($0 \dots 63$) or the *back* ($64 \dots 127$). The second letter then specifies which half of that region our seat is in, and so on until we are left with **exactly one row**. 

The unique **seat ID** is then found by multiplying the seat's row by 8 and then adding its column.

The last three characters are guaranteed to be either **L** or **R** and use the same logic as above to determine the column ($0 \dots 7$) for the corresponding row found. 

For example, the boarding pass $FBFBBFFRLR$ uses the *first 7 characters* $FBFBBFF$ to find row 44, and then the *last three characters* $RLR$ to find column 5. The unique **seat ID** for the given **boarding pass** is therefore 44 * 8 + 5 = 357.

In Part 1, we are asked to look through the list of **boarding passes** (our puzzle input) and find the **highest seat ID** among all boarding passes.

### Idea
Initially, my idea was to create a single class `Plane` and simply store the boarding passes in a vector of strings. However, knowing how Part 2 usually gives some unexpected twist, I decided to model each **boarding pass** using a struct `BoardingPass`. 

This way, each **boarding pass** has the relative string read from input stored as well as the corresponding seat row, seat column, and unique **seat ID**, initially set to default values.

// represents a single boarding pass read from input
```cpp
struct BoardingPass {

    std::string pass;
    int row;
    int col;
    int ID;

    int binarySeatPartitioning(int idx, int p, int r);
    void findSeatID();
};
```

Once we read all boarding passes in an `std::vector<BoardingPass> passes`, we can then use a *divide and conquer* approach for computing the seat's row, columns, and unique ID. To do this, I implemented a *recursive* helper `int binarySeatPartitioning(int idx, int p, int r)` to *recursively* compute the row, column, and unique **seat ID**.

I decided to compute the row, column, and unique seat ID during the initial read phase in `readPuzzleInput`. This way, once all boarding passes have been correctly read and processed, we can get Part 1's solution by doing a single linear pass to find the **highest seat ID**.

#### Pseudocode

Assuming we store the boarding passes in a vector `std::vector<BoardingPass> boardinPasses`, we can find each seat's row, column, and unique ID during the initial read phase:

```cpp
int BoardingPass::binarySeatPartitioning(int idx, int p, int r) {

    if (p == r) {
        return p;
    }

    int q = p + (r - p) / 2;
    
    if (pass[idx] == 'F' || pass[idx] == 'L') {
        return binarySeatPartitioning(idx + 1, p, q);
    }
    else { // pass[idx] == 'B' || pass[idx] == 'R'
        return binarySeatPartitioning(idx + 1, q+1, r);
    }
}

void BoardingPass::findSeatID() {

    row = binarySeatPartitioning(0, 0, 127);
    col = binarySeatPartitioning(7, 0, 7);
    ID = (row * 8) + col;
}
```

Once we have read and processed all boarding passes, finding the maximum seat ID can be done with a single linear scan:

```cpp
int Plane::solvePart1() {

    // use first boarding pass as initial max
    int maxID = boardingPasses[0].ID;

    for (int i = 1; i < (int)boardingPasses.size(); i++) {
        if (boardingPasses[i].ID > maxID) {
            
            // updated if we find a higher seat ID
            maxID = boardingPasses[i].ID;
        }
    }

    return maxID;
}
```

#### Complexity
Assuming there are $n$ boarding passes, the cost of finding the seat ID for a single boarding pass remains constant $\mathcal{O}(1)$, since the recursive helper is bounded by the same fixed lengths of each boarding pass. Since we read and process $n$ boarding passes in total, this initial phase has a cost of $n \times \mathcal{O}(1) = \mathcal{O}(n)$. Finding the maximum seat ID after having processed all boarding passes is done with a single linear scan. Therefore, the total **time complexity** is $\mathcal{O}(n) + \mathcal{O}(n) = \mathcal{O}(n)$.

The total **space complexity** is also $\mathcal{O}(n)$ since we store $n$ boarding passes in our `boardingPasses` vector, and the maximum recursion depth when processing each boarding pass remains constant at $7$ (meaning $\mathcal{O}(1)$).

**Note**  
Only after finishing Part 1, I realized that there might be an alternative solution using binary digits. For example, if we look at the first 5 boarding passes in the input file:   
  1. BBFFBFFRRR; Row: 100; Col: 7; ID: 807
  2. FBBFFBBLRR; Row: 51; Col: 3; ID: 411
  3. FFBFBFBRRR; Row: 21; Col: 7; ID: 175
  4. FFFBFBFRRR; Row: 10; Col: 7; ID: 87
  5. BBFFBBFLRR; Row: 102; Col: 3; ID: 819

If we assign binary digits for the rows as B=1, F=0, R=1, L=0, we can notice that, when converting from binary to decimal, the results match the ones found in the solution above: 

  1. BBFFBFFRRR: Row = 1100100 = 100 and Column = 111 = 7;
  2. FBBFFBBLRR; Row = 0110011 = 51 and Column = 011 = 3; 
  3. FFBFBFBRRR; Row = 0010101 = 21 and Column = 111 = 7; 
  4. FFFBFBFRRR; Row = 000101 = 10 and Column = 111 = 7; 
  5. BBFFBBFLRR; Row = 1100110 = 102 and Column = 011 = 3; 

In any case, I have less experience in *bitwise* operations, so I will leave my solution for Part 1 as is.  

## Part 2
In Part 2, we are told that our seat is the only one missing, and that some of the seats at the very front and back of the plane don't exist on the plane, so they'll be missing from the list as well.

Our seat is not at the very front or back, though, but is between the two seats with **seat IDs** that are *+1* and *-1* from ours in the list.

## Idea
Since we already processed each boarding pass in Part 1, we already have the entire list of **seat ID's**. Therefore, to find our seat, we can *sort* our vector `boardingPasses` in increasing order of **seat ID's**. We can do this using `std::sort` after redefining the *less than* operator for the struct `BoardingPass`. A *lambda* works too, but coming from C, the overloaded operator feels more natural.

Once we sorted the vector by **seat ID**, we can perform a single scan on $i = 0 \dots n-2$, checking whether `boardingPasses[i+1].ID - boardingPasses[i].ID == 2`. Once we find the two seats that satisfy this condition, we can return `boardingPasses[i+1].ID - 1` as our  **seat ID**, the solution for Part 2.

#### Pseudocode

```cpp
// overloaded operator for sorting BoardingPass
bool BoardingPass::operator<(const BoardingPass& other) const {
    
    return this->ID < other.ID;
}

int solvePart2() {

    // sort all boarding passes in increasing order of seat ID
    std::sort(boardingPasses.begin(), boardingPasses.end());
    
    // iterate all 
    for (int i = 0; i < (int)boardingPasses.size() - 2; i++) {

        // if we find two seats that have IDs with exactly 1 missing ID in between 
        if (boardingPasses[i+1].ID - boardingPasses[i].ID == 2) {

            // we found our seat, so we return
            return boardingPasses[i+1].ID - 1;
        }
    }
    
    // if our seat was somehow not found
    return -1;
}
```

#### Complexity
Assuming there are $n$ boarding passes, the sorting phase has a complexity of $\mathcal{O}(n \log n)$. We then perform a linear scan to find our seat. Therefore, the total **time complexity** for Part 2 is $\mathcal{O}(n \log n) + \mathcal{O}(n) = \mathcal{O}(n \log n)$.

The total **space complexity** for Part 2 remains the same as Part 1: $\mathcal{O}(n)$.

### Build
Tested using:

```
g++ -std=c++17 main.cpp BinaryBoarding.cpp -o main.exe
./main.exe
```
