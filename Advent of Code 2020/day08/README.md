# Advent of Code 2020 - Day 8: Handheld Halting

[Day 8: Handheld Halting](https://adventofcode.com/2020/day/8)

Your flight to the major airline hub reaches cruising altitude without incident. While you consider checking the in-flight menu for one of those drinks that come with a little umbrella, you are interrupted by the kid sitting next to you.

Their handheld game console won't turn on! They ask if you can take a look.

## Part 1
We are given the *boot code* of a handheld gaming console as input, which seems to be stuck in an infinite loop.  
The boot code is given as a list of **instructions**. Each line represents a single instruction, with each instruction specifying the type of **operation** and an **argument** (a signed number such as +4 or -20).

We are told that the operations are exactly of three types:

 1. An **acc** instruction increases or decreases a single global value (the *accumulator*) by the value given in the argument. After doing so, it moves to the instruction immediately below it.
 2. A **jmp** instruction moves to a new instruction relative to itself, using the argument value as the *offset*. 
 3. A **nop** instruction does nothing, and simply moves to the instruction immediately below it.

We are asked to simulate running our boot code to find the infinite loop.  
Immediately before any instruction is executed a second time, we want to return the value in the **accumulator**.

### Idea
I decided to parse the puzzle input line by line, parsing each line into a dedicated  struct `Instruction`.  
This struct stores the instruction *index* (which tracks its position in the program line order), the *operation type*, and the *argument value*.

```cpp
struct Instruction {
    int index;
    string operation;
    int argument;
};
```

After parsing the input, all instructions are stored in the private member `vector<Instruction> instructions` of the class `BootCode`.

I decided to use a **hash set** approach, using a temporary object `unordered_set<int> seen` to implement a solution for Part 1.  
Every time an instruction is executed, I insert its `index` into `seen`. Since `unordered_set` does not allow duplicate values, whenever I find an **insert operation** that fails, I can *break*, since I found the start of the *infinite loop*.

 - While simulating the *boot code*, I used two variables `accumulator` and `currentIndex` to represent the current value of the accumulator and the current index. These are updated depending on the instruction being executed. 
 - I keep simulating the *boot code* as long as `currentIndex` is within bounds, meaning within 0 and n.
 -  For each instruction, I first check if it was already executed by trying to insert its `currentIndex` into the **hash set** `seen`. If this **insert operation** fails, I have found the loop, so I can return the `accumulator` for Part 1's solution.
 - Otherwise, I take the `currentInstruction` as a constant reference and check the operation type:
 
   - If it is an **acc** instruction, I update `accumulator` with the argument of the current instruction and increment the current index.
   - If it is a **nop** instruction, I simply increment `currentIndex`. 
   - If it is a **jmp** instruction, I set the current index by adding the (possibly negative) argument of the current instruction.

Eventually, one of the **insert operations** into the **hash set** will fail, at which point I return the `accumulator` value, which is the solution to Part 1.  

```cpp
int solvePart1() const {

    // guard
    if (instructions.empty()) {
        throw runtime_error("No instructions found...");
    }

    // number of instructions
    int n = instructions.size();

    // initialize accumulator, current index, and hash set
    int accumulator = 0;
    int currentIndex = 0;
    unordered_set<int> seen;

    // as long as the current index is within bounds
    while (currentIndex >= 0 && currentIndex < n) {

        // check if we already saw this instruction
        if (!seen.insert(currentIndex).second) {
            // if so, we return the accumulator
            return accumulator;
        }

        // otherwise, we take the current instruction as const reference
        const Instruction& currentInstruction = instructions[currentIndex];

        // update depending on instruction type
        if (currentInstruction.operation == "acc") {
            // if "acc" instruction, update accumulator and current index
            accumulator += currentInstruction.argument;
            currentIndex++;
        }
        else if (currentInstruction.operation == "jmp") {
            // if "jmp" instruction, jump to index
            currentIndex += currentInstruction.argument;
        }
        else if (currentInstruction.operation == "nop") {
            // if "nop" instruction, increment current index
            currentIndex++;
        }
    }

    // return accumulator
    return accumulator;
}
```

#### Complexity

 * Assuming there are $n$ instructions in the input file, excluding the cost of the initial input read, the algorithm iterates at most $n$ times, with **insert** operations on the **hash set** having a cost of $\mathcal{O}(1)$ on average. Therefore, the total **time complexity** is $\mathcal{O}(n)$.

 * Since we use a **hash set** for Part 1's solution, the total **space complexity** is $\mathcal{O}(n)$.

--- 

## Part 2
In Part 2, we are told that the *boot code* is corrupted. Somewhere in the code, either a **nop** is supposed to be a **jmp**, or a **jmp** is supposed to be a **nop**. 

All the **acc** instructions are correct, and the *boot code* is supposed to terminate correctly by trying to execute the instruction immediately following the last one.

We need to *swap* a **jmp** or **nop** instruction to have the program terminate correctly, and then return the value of the accumulator.

### Idea
Since the number of instructions is relatively small, a *brute force* approach could work. I can iterate through all instructions, skipping all **acc** instructions and swapping any **jmp** or **nop** instructions I find.

 - To not influence future simulations, I first save the operation of an instruction before performing the swap. After performing the swap, I can use a helper `runSimulation` by implementing slightly modified logic used for Part 1's solution.
 - The helper `runSimulation` applies the same logic as `solvePart1` but uses an object `pair<int,bool>` as the return type. This is used to indicate the value of the accumulator and whether or not the simulation ended successfully.
 - After applying a *swap* and running a simulation, whenever I encounter an *infinite loop*, I return the pair `{accumulator,false}` to indicate the simulation failed. Whenever I run a simulation and find that `currentIndex == n`, this means the simulation terminates successfully
 
Once I perform a *swap* and find a simulation that terminates successfully, I can return the first value of the pair: the **accumulator** value, which is Part 2's solution.

#### Pseudocode

```cpp
pair<int,bool> runSimulation() {

    int n = instructions.size();
    int accumulator = 0;
    int currentIndex = 0;
    unordered_set<int> seen;

    // as long as the current index is within bounds
    while (currentIndex >= 0 && currentIndex < n) {

        // check if we already saw this instruction 
        if (!seen.insert(currentIndex).second) {
            // if so, we encountered an infinite loop
            return {accumulator, false};
        }

        // otherwise, we apply Part 1 logic
        const Instruction& currentInstruction = instructions[currentIndex];

        if (currentInstruction.operation == "acc") {
            accumulator += currentInstruction.argument;
            currentIndex++;
        }
        else if (currentInstruction.operation == "jmp") {
            currentIndex += currentInstruction.argument;
        }
        else if (currentInstruction.operation == "nop") {
            currentIndex++;
        }
    }

    // if the currentIndex reaches exactly n, then the simulation ran successfully
    return {accumulator, currentIndex == n};
}

int solvePart2() {

    // guard
    if (instructions.empty()) {
        throw runtime_error("No instructions found...");
    }

    // iterate through list of instructions
    for (int i = 0; i < (int)instructions.size(); i++) {

        // skip "acc" instructions
        if (instructions[i].operation == "acc") {
            continue;
        }

        // save original instruction operation before swapping
        string originalOperation = instructions[i].operation;

        // perform swap
        if (instructions[i].operation == "jmp") {
            instructions[i].operation = "nop";
        }
        else if (instructions[i].operation == "nop") {
            instructions[i].operation = "jmp";
        }

        // run simulation after the swap
        pair<int,bool> simulation = runSimulation();

        // if simulation was successful
        if (simulation.second) {
            // return the accumulator value
            return simulation.first;
        }

        // otherwise, revert instruction to original operation
        instructions[i].operation = originalOperation;
    }

    // if no swap worked
    throw runtime_error("No swap resulted in valid boot code simulation"); 
}
```

#### Complexity

 * Assuming there are $n$ instructions in the input file, excluding the cost of the initial input read, the algorithm used in Part 2 uses a * brute-force* approach by swapping each **jmp** or **nop** instruction found. Each simulation has cost $\mathcal{O}(n)$, with operations performed on the **hash set** having cost $\mathcal{O}(1)$ on average. Therefore, the resulting total **time complexity** is quadratic: $\mathcal{O}(n^2)$. 

 * Since we use a temporary **hash set** every simulation, the total **space complexity** is $\mathcal{O}(n)$.
 
### Build
Tested using:

```text
g++ -std=c++17 main.cpp HandheldHalting.cpp -o main.exe
./main.exe
```
