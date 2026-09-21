# Advent of Code 2020 - Day 6: Custom Customs

[Day 6: Custom Customs](https://adventofcode.com/2020/day/6)

As your flight approaches the regional airport where you'll switch to a much larger plane, customs declaration forms are distributed to the passengers.

The form asks a series of 26 yes-or-no questions marked a through z. All you need to do is identify the questions for which anyone in your group answers "yes". Since your group is just you, this doesn't take very long.

## Part 1
In Part 1, we are given as input the answers to a series of 26 *yes-or-no questions* marked *a* through *z*. The answers given to us belong to **groups** of people, with each group in the input file being separated by a **blank line**. Each group contains *one or more people*, with each **single line** of the group containing the answers for a *single person*.

We are asked to identify the questions for which **anyone in the group** answers *"yes"*.

For example, in the **groups** below:

```text
abcx
abcy
abcz
```

The group has *three* people, and there are *6* questions to which anyone in the group answered *"yes"*: questions *a, b, c, x, y, z*.  
(**duplicate answers** to the same question don't count extra; each question counts *at most once.*).

We are asked to count, *for each group*, the number of questions to which anyone answered *"yes"* and return the **total sum** of those counts.


### Idea
The first part of Day 6, like in Day 4, is parsing the input. We can read the input in a similar way we did regarding **passport data** by defining a struct `Group` to represent a single **group** read from input. Since I don't know the usual "twist" Part 2 will give, I decided to also store the answers of each person in the group in a `vector<string> groupAnswers`, as well as the number of people `passengerCount` within the group. 

Given that each group may contain more than one person, we want to avoid counting **duplicate answers** to the same question. To implement this, we can map each **unique** question answered to its relative frequency within a given group. We can implement this using an `unordered_map<char,int> answersCounts` which maps each question (*key*) to the corresponding frequency (*value*). And since `unordered_map` does not allow duplicate keys, this handles the requirement of **counting each question at most once** quite nicely. 

```cpp
// represents a single group read from input
struct Group {

    std::vector<std::string> groupAnswers;
    std::unordered_map<char,int> answersCount;
    int passengerCount = 0;
};
```

The reading phase is similar to Day 4. We can track the state of each **group** being processed by using a boolean flag `hasAnswers` (initially set to `false`). We read the input file *line by line*, processing one group at a time. 

For each new person found, we increment `passengerCount`, store the raw text line containing their answers, and process their answers. When processing a person's answers, we update `answersCount` by processing each answer `ch` found. To do this, we can use `answersCount[ch]++`:  
 - if the answer `ch` is already in the map, we simply increment its relative frequency.
 - if the answer `ch` was not present in the group, we **insert** it with a frequency of 1.  

Whenever we finish parsing a single person's line, we set the flag `hasAnswers` to `true`. Each time we encounter a **blank line**, only if `hasAnswers` is also set to `true`, we can then push the fully parsed **group** into a vector `vector<Group> allGroups`. As in Day 4, to ensure we don't skip the *very last group*, we do a final *sanity check* using our boolean flag, just in case the input file does not end with a **blank line**. 

Once we have fully parsed and processed each **group**, since we used `unordered_map<char,int>` to map each **unique** question answered and its relative frequency, the *total number of questions to which anyone answered "yes"* corresponds to the size of the map, meaning the number of **unique** *key:value* pairs. So, to find Part 1's solution, we can simply sum up the sizes of each group's `answersCount.size()`.

#### Pseudocode

Assuming we use a class `Customs` which has `string puzzleInput` and `vector<Group> allGroups` as private members:

```cpp
void readPuzzleInput() {

    // clear previous
    allGroups.clear();

    ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw runtime_error("Could not read puzzle input");
    }

    // read input line by line, parsing each group, using boolean flag 
    string line;
    Group current;

    // indicates if a group has been fully parsed or is empty
    bool hasAnswers = false;

    while (getline(file, line)) {

        // if we encounter a blank line
        if (line.empty()) {

            // and the current group has been fully processed
            if (hasAnswers) {

                // we push into vector and reset for next group
                allGroups.push_back(current);
                current = Group();
                hasAnswers = false;
            }
        }
        else { // otherwise, process each person in the group

            current.passengerCount++;
            current.groupAnswers.push_back(line);

            for (char ch : line) {

                // update (question -> frequency) map
                current.answersCount[ch]++;
            }

            // set boolean flat to true
            hasAnswers = true;
        }
    }

    // sanity check, as to not skip very last group
    if (hasAnswers) {
        allGroups.push_back(current);
    }

    file.close();
}

int solvePart1() const {

    // guard
    if (allGroups.empty()) {
        return -1;
    }

    int count = 0;
    for (const Group& group : allGroups) {
        
        // add each group's distinct (key,value) pairs
        count += group.answersCount.size();
    }

    return count;
}
```

#### Complexity
Assuming there are $n$ characters in total across all lines in the input file, and that there are in total $g$ groups. Reading each line has a cost proportional to its length, and operations on `unordered_map` have a cost of $\mathcal{O}(1)$ on average. After parsing, iterating through all groups to sum the *map* takes $\mathcal{O}(g)$ time. Since $g \le n$, the total **time complexity** is bounded by $\mathcal{O}(n)$.

Since we actually store all raw text lines inside the struct `Group` in Part 1, the total **space complexity** is $\mathcal{O}(n)$.



## Part 2
In Part 2, we are told that we actually want to count, for each **group**, the *total number of questions to which everyone answered "yes"*. 

Since, for solving Part 2, we don't actually need to store the raw text lines containing each person's answers, we can remove the member `groupAnswers` from the struct `Group`. 

### Idea
Since we mapped each **unique** question answered with *"yes"* to its relative frequency for each group using `unordered_map<char,int> answersCount`, this makes things easy. 

To find the question to which **all** members of a group answered *"yes"*, this means finding the question in our map `answersCount` that has a value (*frequency*) that is the same as the number of people in the group, which we store in `passengerCount`. 

Solving Part 2 only means changing the counting logic slightly. Since, under the hood, each *key:value* pair in `unordered_map<char,int>` is seen as a `pair<char,int>`, we can use a *range-based* loop to find all the questions with `pair.second` (*frequency*) that is equal to the total number of people in the group, `passengerCount`. For clarity, I implemented this counting logic through a helper `answeredByAll` in the struct `Group`.

#### Pseudocode

```cpp
int Group::answeredByAll() const {

    // guard
    if (answersCount.empty()) {
        return 0;
    }

    int count = 0;
    // range-based loop
    for (const pair<const char, int>& answers : answersCount) {

        // check if all people in group answered
        if (answers.second == passengerCount) {

            // if so, increment total count
            count++; 
        }
    }    
    return count;
}


int solvePart2() const {

    // guard
    if (allGroups.empty()) {
        return -1;
    }

    int count = 0;
    // range-based loop
    for (const Group& group : allGroups) {

        // count all questions answered by all people in each group
        count += group.answeredByAll();
    }    
    return count;
}
```

#### Complexity
Assuming there are $n$ characters in total across all lines in the input file, and that there are in total $g$ groups, the total **time complexity** in Part 2 remains unchanged. Iterating through all groups has a cost of $\mathcal{O}(g)$, and at each iteration, the work done is strictly bounded by the alphabet size of 26. Therefore, the total cost of iterating all groups is $\mathcal{O}(g \times 26) = \mathcal{O}(g)$, meaning an overall **time complexity** of $\mathcal{O}(n)$.

In Part 2, the private struct member `groupAnswers` is removed; the space used is bounded by the maximum alphabet size of 26 used by `answersCount`. Therefore, the total **space complexity** for Part 2 is reduced to $\mathcal{O}(g)$.

### Build
Tested using
```text
g++ -std=c++17 main.cpp CustomCustoms.cpp -o main.exe
./main.exe    
```
