# Advent of Code 2020 - Day 7: Handy Haversacks

[Day 7: Handy Haversacks](https://adventofcode.com/2020/day/7)

You land at the regional airport in time for your next flight. In fact, it looks like you'll even have time to grab some food: all flights are currently delayed due to issues in luggage processing.

Due to recent aviation regulations, many rules (your puzzle input) are being enforced about bags and their contents; bags must be color-coded and must contain specific quantities of other color-coded bags. Apparently, nobody responsible for these regulations considered how long they would take to enforce!

## Part 1
In Part 1, we are given as input many *aviation regulations* (or *rules*) regarding bags and their contents. Each bag is *color-coded* and must contain specific *quantities* of other color-coded bags.

We are given an example:

```text
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
```

These rules specify the required contents for 9 bag types. In this example, every faded blue bag is empty, every vibrant plum bag contains 11 bags (5 faded blue and 6 dotted black), and so on.

We have a **shiny gold bag** that we want to carry in *at least one other bag* and want to find out how many different bag colors would be valid for the *outermost* bag. In the example above, the number of bag colors that can eventually contain at least one shiny gold bag is 4.

We are asked to read the list of *rules* given to us as input, and figure out how many *bag colors* can, eventually, *contain at least one* **shiny gold bag**. 

### Idea
In Day 7, I noticed a significant increase in difficulty compared to the previous 6 days, mostly because I was not quite familiar with the data structure I eventually ended up implementing for Day 7.

The *rules* given as input form a structural hierarchy of sorts, where the *parent* bag (*color-coded* using an "adjective" + "color") may contain a *child* (also *color-coded* and with a given *quantity*). Since we want to find the *total number of bags that* can hold our **shiny gold bag**, it made sense in my head to have this hierarchy of color-coded bags stored in some sort of structure that could be traversed **backwards** (from **children to parents**) in order to find all the valid *candidate* bags.

I initially thought about a **doubly linked list**, but soon realized that the relationships between each *child* bag and the *parent* bag acting as its container are not linear, meaning a *child* bag may be contained by multiple *parent* bags. This is when I realized that a doubly linked list would not work. So, after some online research, I found out about **Directed Acyclic Graphs (or DAGs)**, which I had only previously seen briefly in my *Data Structures & Algorithms* and *Database* courses.

Since Part 1 only asks about the *child-to-parent* relationships, using only the *color-coded names*, the *quantity* of each *child* bag is not needed. However, I suspect it might be for Part 2. 

For Part 1, I decided to model these *child-to-parent* relationships by mapping every *child* bag to each *parent* bag using a `std::unordered_map<std::string, std::vector<std::string>> childToParents` object, as a private member of the class `Haversacks`. This represents the **reversed graph**, which allows mapping the *child-to-parent* relationships in the form:

$$
\text{"shiny gold"} \rightarrow \text{\{"bright white", "muted yellow"\}}
$$ 

Parsing the input meant reading it line by line, since the rules are each given on a single line in the format:

$\text{parentAdjective parentColor}$ bags contain $\text{childQuantity childAdjective childColor}$ bag(s), ...

 - Each *parent* bag may contain more than one *child* bag or, if the $\text{childQuantity}$ field is "no", then it contains *no child bags*.
 - For each rule, I extract and create the *parent* bag. Then, if it contains any *child* bags, I extract their color-coded name and **push** it into the map `childToParents` by using the **child name** as the **key** and the **parent name** as the **value**.
 - Extra tokens in the string, such as the words "bags", "contain", or the numerical quantities of the child bags, are skipped as they are not needed for Part 1.
 - This parsing process is done for every *child* bag found in the rule, unless no child bag is present, in which case I simply *break* and move on to the next one.

With the graph built, I decided to use a **BFS** (*Breadth First Search*) algorithm for Part 1's solution. To do this, I implemented the **BFS** algorithm using a **queue** structure `std::queue<std::string> q` and initially **only inserting our shiny gold bag**. 

 - At each step of the algorithm, I take the *front* of the queue as the **current bag color** and then *pop* a **bag color** from the queue.
 - The current bag color uses the **reverse graph** structure to check its *direct parents*.
 - The *direct parents* are checked by performing **insert** operations on a **hash set** `std::unordered_set<std::string> visited`.
 - If an **insert** operation is successful, this means I found a *unique parent*, meaning a *valid candidate* to act as an outerbag for the **shiny gold bag**.

#### Note
I did not know this, but *inserting* into a hash set returns a *pair object*, with the *second value* indicating whether the insertion was successful or not, meaning if `visited.insert(parentName).second` evaluates to `true`.

 - Each time an **insert** operation is successful, I **push** it into the queue to inspect its *direct parents* next.
 - This process continues *until the queue runs empty*, at which point the **size** of the **hash set** `visited` is the number of *valid candidate outerbags* that may contain the **shiny gold bag**, which is Part 1's solution.

#### Pseudocode

Since parsing the input was also a *substantial* part of Day 7, I decided to show the related pseudocode before the main Part 1 solution:

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

        //
        string current = q.front();
        q.pop();

        // check the direct parents of current
        auto it = childToParents.find(current);
        // if we find one
        if (it != childToParents.end()) {

            // try inserting into hash set
            for (const string& parent : it->second) {
                // if we find a unique (unvisited) parent, we push into queue
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

#### Complexity
Assuming there are $n$ rules (lines of input) and that $m$ is the maximum number of *child bags* within a single rule. Parsing a single line's tokens takes constant time, and the cost of insertions into our map `childToParents` has a cost of $\mathcal{O}(1)$ on average. Assuming our graph contains $v$ unique bag colors (*vertices*) and $r$ is the total number of containing relationships (*edges*), traversing the graph (**BFS**) has a cost of $\mathcal{O}(v + r)$ since we never traverse the same path more than once. If we disregard the initial read phase, the total **time complexity** is therefore $\mathcal{O}(v+r)$. If we do count the initial read/parsing phase, then it becomes $\mathcal{O}(n \times m)$.

The **reverse graph** takes up $\mathcal{O}(v+r)$ space, and the **hash set** used takes up an additional $\mathcal{O}(v)$ space. Therefore, the total **space complexity** can be simplified to $\mathcal{O}(v+r)$.


## Part 2
It turns out that Part 2 asks to count *how many individual bags are required inside* the **shiny gold bag**. Since I already have a **reverse graph** that maps each *child* bag back up to its *parent* bag, I decided to implement a similar logic, using another **DAG** structure to act as a **forward graph**.

### Idea
For Part 2, instead of mapping each child bag to its parent, I can map each *parent* bag to the *child* bags contained (if any). Since the *numerical quantity* of each *child* bag is also needed to correctly count, I implemented a struct `ColorCodedBag` to represent a single *color-coded* bag with its corresponding *numerical quantity*:

```cpp
struct ColorCodedBag {
    std::string color;
    int quantity;
};
```

This helps with implementing the **forward graph** of *parent-to-child* relationships while parsing the input. This is implemented through the new private member `parentToChildren` I added to the class `Haversacks`. The map is represented as an object `std::unordered_map<std::string, std::vector<ColorCodedBag>> parentToChildren` to correctly represent the **forward graph** of  *parent-to-child* relationships read from input. 

The changes needed during the initial read phase were minimal. Now, instead of skipping the *numerical quantity* of each *child* bag of a rule, I convert it into its corresponding value. I then also update the new `parentToChildren` map for every rule with a *parent* that contains *child* bags. This is done by **pushing** the **parent name** as the **key** and the `ColorCodedBag` representing the *child* bag (with name and quantity) as the **value**.

After applying those changes, to solve Part 2, I decided to use a *recursive top-down traversal* helper:  
`countNestedBags(const std::string& currentColor) const`. 

This helper returns the total number of *nested child bags* assigned to `currentColor`. For each *child*, the returned result is given by:

$$
\text{Total for this child} = \text{quantity } + (\text{quantity } \times \text{ everything inside that child})
$$ 

The helper calls itself *recursively* in order to reach the *deepest nested layer* and return the total number of bags associated (directly or indirectly) with the `currentColor`. If the `currentColor` does not hold any *child* bags, then I return 0, so as not to influence the total sum. 

I can then solve Part 2 by using the helper and calling `countNestedBags("shiny gold")` to return the total number of bags required inside the **shiny gold bag**.

#### Pseudocode

```cpp
// recursive helper
int countNestedBags(const string& currentColor) const {

    int total = 0;

    // lookup children of current color
    auto it = parentToChildren.find(currentColor);

    // if no children, return 0 
    if (it == parentToChildren.end()) {
        
        // no nested bags
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

#### Complexity
Assuming the **forward graph** contains $v$ unique bag colors (*vertices*) and $r$ is the total number of contained relationships (*edges*), the recursive helper traverses the graph starting from the "shiny gold" bag. Since it is a **DAG**, there are no infinite cycles, but bags can be nested inside multiple different parents. In the worst case, this leads to a total **time complexity** of $\mathcal{O}(v + r)$.

The depth of the recursion stack is bounded by the maximum nesting depth of the bags, which evaluates to $\mathcal{O}(v)$ in the worst case. Since the **forward graph** takes up $\mathcal{O}(v+r)$ space, the total **space complexity** is $\mathcal{O}(v+r)$.

### Build
Tested using 
 
```text
g++ -std=c++17 main.cpp HandyHaversacks.cpp -o main.exe
./main.exe
```
