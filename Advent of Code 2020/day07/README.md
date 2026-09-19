# Advent of Code 2020 - Day 7: Handy Haversacks

[Day 7: Handy Haversacks](https://adventofcode.com/2020/day/7)

You land at the regional airport in time for your next flight. All flights are currently delayed due to issues in luggage processing: recent aviation regulations dictate that bags must be color-coded and contain specific quantities of other color-coded bags.

## Part 1

We are given a list of rules regarding bags and their contents. Each rule dictates what color-coded bags (and in what quantities) a parent bag must contain.

For example:

```text
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.

```

The goal of Part 1 is to determine how many different bag colors can eventually contain at least one **shiny gold bag**.

### Idea

Day 7 brought a significant difficulty spike compared to the previous days because it requires modeling a **Directed Acyclic Graph (DAG)**.

The rules form a structural hierarchy where a parent bag contains child bags. Since we want to find all outer bags that can hold a shiny gold bag, we need to traverse this hierarchy **backwards** (from children to parents).

I initially considered a doubly linked list, but a child bag can belong to multiple parent bags, meaning the relationships aren't linear. This led me to implement a DAG. Because Part 1 only asks for the *containment chain* (ignoring quantities), I modeled the child-to-parent relationships by mapping each child bag to its parents using a `std::unordered_map<std::string, std::vector<std::string>> childToParents`.

This reversed graph maps relationships like this:


$$\text{"shiny gold"} \rightarrow \text{\{"bright white", "muted yellow"\}}$$

To parse the input, I read it line by line, extracting the parent bag and its children while skipping irrelevant tokens like "bags", "contain", or the numerical quantities. The child bag's name becomes the map's **key**, and the parent bag's name is appended to the **value** vector.

With the reverse graph built, I used a **Breadth-First Search (BFS)** starting exclusively with the shiny gold bag. A `std::queue<std::string>` tracks the bags to process, and a `std::unordered_set<std::string> visited` keeps track of unique valid outer bags.

> **Note:** I discovered that inserting into a `std::unordered_set` returns a pair, where the `second` element is a boolean indicating if the insertion was successful (i.e., the element was unique). I used `visited.insert(parentName).second` to only push previously unvisited parents into the queue.

When the queue runs empty, the size of the `visited` set gives us the total number of valid candidate outer bags.

### Pseudocode

```cpp
void readPuzzleInput() {

    // clear previous
    childToParents.clear();

    ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw runtime_error("Could not read puzzle input");
    }

    // read input line by line
    string line;
    while (getline(file, line)) {

        // parse single line
        istringstream ss(line);

        // parse parent bag
        string parentAdjective, parentColor, dummy;
        ss >> parentAdjective >> parentColor >> dummy >> dummy;
        string parentName = parentAdjective + " " + parentColor;

        string quantityStr;
        // parse potential child bags
        while (ss >> quantityStr) {

            // check for actual quantity
            if (quantityStr == "no") {
                break;
            }

            // otherwise, create the child
            string childAdjective, childColor;
            ss >> childAdjective >> childColor >> dummy;
            string childName = childAdjective + " " + childColor;

            // map child bag to its parent
            childToParents[childName].push_back(parentName);
        }
    }
    file.close();   
}

int solvePart1() const {

    // guard
    if (childToParents.empty()) {
        throw runtime_error("Child -> Parents map is empty.");
    }

    // initialize empty hash set and queue
    unordered_set<string> visited;
    queue<string> q;

    // we track starting from "shiny gold bag" going backwards
    q.push("shiny gold");

    // process until queue is empty
    while (!q.empty()) {

        string current = q.front();
        q.pop();

        // check the direct parents of current
        auto it = childToParents.find(current);

        // if we find one
        if (it != childToParents.end()) {

            // try inserting into hash set
            for (const string& parent : it->second) {
                // if we find a unique (unvisited) parent, push into queue
                if (visited.insert(parent).second) {
                    q.push(parent);
                }
            }
        }
    }

    // the size of the hash set is Part 1's solution
    return visited.size();
}

```

### Complexity

Assuming $n$ rules and a maximum of $m$ child bags per rule, parsing takes $\mathcal{O}(n \times m)$ time.
Let $v$ be the number of unique bag colors (vertices) and $r$ be the total containing relationships (edges). Traversing the graph via **BFS** takes $\mathcal{O}(v + r)$ time, as each path is traversed at most once.

The reverse graph takes $\mathcal{O}(v + r)$ space, and the hash set requires $\mathcal{O}(v)$ space. The total space complexity is therefore $\mathcal{O}(v + r)$.

## Part 2

Part 2 flips the problem: we now need to count the *total number of individual bags required inside* the **shiny gold bag**.

### Idea

Since I already understood the **DAG** structure from Part 1, I built a **forward graph** to map parents to their children. This time, quantities matter. I created a `ColorCodedBag` struct to store both the child's color and its required quantity:

```cpp
struct ColorCodedBag {
    std::string color;
    int quantity;
};

```

I mapped this out using `std::unordered_map<std::string, std::vector<ColorCodedBag>> parentToChildren`. During the parsing phase, I updated the logic to capture the numerical quantities instead of skipping them, mapping the parent string to a vector of its child structs.

To solve Part 2, I wrote a recursive top-down traversal helper, `countNestedBags(currentColor)`. For each child bag, the total nested bags are calculated as:

$$\text{Total} = \text{quantity} + (\text{quantity} \times \text{nested bags inside child})$$

The function calls itself recursively to dig into the deepest layers, returning 0 if a bag contains no children. Calling `countNestedBags("shiny gold")` yields the final answer.

### Pseudocode

```cpp
// recursive helper
int countNestedBags(const string& currentColor) const {

    int total = 0;

    // lookup children of current color
    auto it = parentToChildren.find(currentColor);

    // if no children, return 0
    if (it == parentToChildren.end()) {
        return 0;
    }

    // otherwise, we look at each child associated to the current color
    for (const ColorCodedBag& child : it->second) {
        // count the child bags themselves and recursively count their contents
        total += child.quantity + (child.quantity * countNestedBags(child.color));
    }

    // return total sum of nested bags found
    return total;
}

int solvePart2() const {

    // guard
    if (parentToChildren.empty()) {
        throw runtime_error("Parent -> Children map is empty.");
    }

    // use recursive helper directly on shiny gold bag
    return countNestedBags("shiny gold");
}

```

### Complexity

Constructing the forward graph takes $\mathcal{O}(v + r)$ space and time. Because this recursive implementation does not use memoization, the time complexity scales directly with the total number of nested bags inside the target bag. While this tree traversal could theoretically take exponential time $\mathcal{O}(2^v)$ in a heavily interconnected worst-case **DAG**, it runs quite efficiently for the provided puzzle constraints.

### Build

Tested using:

```text
g++ -std=c++17 main.cpp HandyHaversacks.cpp -o main.exe
./main.exe

```
