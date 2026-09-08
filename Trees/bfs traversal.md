# 🌳 Trees — Module 4: BFS / Level Order Traversal

# 1. What is BFS in Trees?

BFS means:

```text
Breadth First Search
```

In a tree, BFS visits nodes:

```text
LEVEL BY LEVEL
```

Therefore BFS on trees is commonly called:

```text
LEVEL ORDER TRAVERSAL
```

Example:

```text
            1
          /   \
         2     3
        / \   / \
       4   5 6   7
```

BFS traversal:

```text
1

2 3

4 5 6 7
```

Flattened:

```text
1 2 3 4 5 6 7
```

So BFS processes:

```text
Level 0
↓
1

Level 1
↓
2 3

Level 2
↓
4 5 6 7
```

---

# 2. DFS vs BFS

We already learned DFS:

```text
DFS
=
Depth First Search
```

DFS goes:

```text
Deep into one branch

↓

Comes back

↓

Explores another branch
```

Example:

```text
            1
          /   \
         2     3
        / \   / \
       4   5 6   7
```

Preorder DFS:

```text
1 2 4 5 3 6 7
```

It goes deep:

```text
1
↓
2
↓
4
```

before exploring other branches.

---

BFS:

```text
BFS
=
Breadth First Search
```

goes level-by-level:

```text
1

↓

2 3

↓

4 5 6 7
```

Traversal:

```text
1 2 3 4 5 6 7
```

Main difference:

```text
DFS
→ Depth first
→ Recursion / Stack

BFS
→ Level by level
→ Queue
```

---

# 3. Why BFS Uses a Queue

A Queue follows:

```text
FIFO
```

which means:

```text
First In
First Out
```

Suppose:

```text
        1
       / \
      2   3
```

Start with:

```text
1
```

When processing `1`, we discover:

```text
2
3
```

We need to remember both nodes for later.

So we put them into a queue:

```text
Queue:

front → [2, 3] ← back
```

Since `2` entered first:

```text
2
```

gets processed before:

```text
3
```

This preserves the level order.

---

# 4. Basic BFS Idea

The basic BFS algorithm is:

```text
1. Push root into queue

2. While queue is not empty:

      Take front node

      Remove it

      Process it

      Push its left child if it exists

      Push its right child if it exists
```

Core pattern:

```text
Push ROOT

↓

Pop current node

↓

Process current node

↓

Push LEFT child

↓

Push RIGHT child

↓

Repeat
```

---

# 5. Basic BFS Code

```cpp
void levelOrder(TreeNode* root) {

    if (root == nullptr)
        return;

    queue<TreeNode*> q;

    q.push(root);

    while (!q.empty()) {

        TreeNode* node = q.front();

        q.pop();

        cout << node->val << " ";

        if (node->left != nullptr)
            q.push(node->left);

        if (node->right != nullptr)
            q.push(node->right);
    }
}
```

This prints the entire BFS traversal in one line.

Example:

```text
1 2 3 4 5 6 7
```

---

# 6. Why `queue<TreeNode*>`?

We write:

```cpp
queue<TreeNode*> q;
```

because the queue stores:

```text
POINTERS TO TREE NODES
```

It does not need to copy entire nodes.

Example:

```text
Queue:

[address of node 1]

[address of node 2]

[address of node 3]
```

So:

```cpp
TreeNode* node = q.front();
```

means:

```text
Get the pointer to the node
at the front of the queue.
```

Then we can access:

```cpp
node->val

node->left

node->right
```

This is the same pointer concept learned in Module 2.

---

# 7. Starting BFS

First handle empty tree:

```cpp
if (root == nullptr)
    return;
```

Then create queue:

```cpp
queue<TreeNode*> q;
```

Push root:

```cpp
q.push(root);
```

Suppose:

```text
        1
       / \
      2   3
```

Initially:

```text
Queue:

[1]
```

The root is the first node to process.

---

# 8. Processing the Front Node

Inside:

```cpp
while (!q.empty())
```

we write:

```cpp
TreeNode* node = q.front();

q.pop();
```

Suppose:

```text
Queue:

[2, 3, 4, 5]
 ↑
front
```

Then:

```cpp
TreeNode* node = q.front();
```

means:

```text
node → 2
```

Then:

```cpp
q.pop();
```

removes `2`.

Queue becomes:

```text
[3, 4, 5]
```

Now:

```cpp
node->val
```

is:

```text
2
```

---

# 9. Adding Children to Queue

After processing the current node:

```cpp
if (node->left != nullptr)
    q.push(node->left);

if (node->right != nullptr)
    q.push(node->right);
```

Suppose current node is:

```text
        2
       / \
      4   5
```

Then:

```cpp
q.push(node->left);
```

pushes:

```text
4
```

and:

```cpp
q.push(node->right);
```

pushes:

```text
5
```

If queue previously contained:

```text
[3]
```

it now becomes:

```text
[3, 4, 5]
```

Important:

```text
3 stays in front
```

because it entered the queue before `4` and `5`.

This is why BFS naturally stays level-by-level.

---

# 10. Full BFS Dry Run

Tree:

```text
            1
          /   \
         2     3
        / \   / \
       4   5 6   7
```

Initially:

```text
Queue:

[1]

Output:

[]
```

---

Process `1`:

```text
Pop 1

Output:

[1]
```

Push:

```text
2
3
```

Queue:

```text
[2, 3]
```

---

Process `2`:

```text
Pop 2

Output:

[1, 2]
```

Push:

```text
4
5
```

Queue:

```text
[3, 4, 5]
```

Notice:

```text
3
```

is still first.

So nodes from the current level are processed before newly discovered nodes from the next level.

---

Process `3`:

```text
Pop 3

Output:

[1, 2, 3]
```

Push:

```text
6
7
```

Queue:

```text
[4, 5, 6, 7]
```

---

Then process:

```text
4
5
6
7
```

Final output:

```text
1 2 3 4 5 6 7
```

---

# 11. Why Queue Maintains Level Order

Consider:

```text
        1
       / \
      2   3
     / \
    4   5
```

After processing `1`:

```text
Queue:

[2, 3]
```

Now process `2`.

Its children:

```text
4
5
```

are added to the BACK:

```text
Queue:

[3, 4, 5]
```

So `3` must be processed before `4` and `5`.

Therefore:

```text
Nodes already waiting
from the current level

are processed before

new nodes from the next level.
```

This is exactly why:

```text
QUEUE + FIFO
```

works perfectly for BFS.

---

# 12. Two Common Types of Level Order Output

There are two common requirements.

## Type 1 — Flat BFS

Output:

```text
[1, 2, 3, 4, 5, 6, 7]
```

We only need:

```cpp
while (!q.empty())
```

and process nodes one by one.

---

## Type 2 — Separate Each Level

Output:

```text
[
    [1],
    [2, 3],
    [4, 5, 6, 7]
]
```

Now we must know:

```text
Which nodes belong
to the SAME LEVEL?
```

For this we use:

```cpp
int size = q.size();
```

This is one of the most important BFS patterns.

---

# 13. The `q.size()` Level Trick

Suppose before processing a level:

```text
Queue:

[2, 3]
```

Both currently stored nodes belong to the same level.

So:

```cpp
int size = q.size();
```

gives:

```text
size = 2
```

This means:

```text
There are exactly 2 nodes
in the CURRENT LEVEL.
```

Now process exactly:

```text
2 nodes
```

using:

```cpp
for (int i = 0; i < size; i++)
```

---

# 14. Dry Run of `q.size()` Trick

Tree:

```text
            1
          /   \
         2     3
        / \   / \
       4   5 6   7
```

After processing root:

```text
Queue:

[2, 3]
```

Now:

```cpp
int size = q.size();
```

So:

```text
size = 2
```

Create:

```cpp
vector<int> level;
```

Process exactly two nodes.

---

First:

```text
Pop 2
```

Add:

```text
level = [2]
```

Push its children:

```text
4
5
```

Queue becomes:

```text
[3, 4, 5]
```

---

Second:

```text
Pop 3
```

Add:

```text
level = [2, 3]
```

Push:

```text
6
7
```

Queue becomes:

```text
[4, 5, 6, 7]
```

Now we have processed exactly:

```text
size = 2
```

nodes.

Therefore current level is:

```text
[2, 3]
```

The queue now contains:

```text
[4, 5, 6, 7]
```

which is the NEXT level.

---

# 15. Why We Store `size` BEFORE Processing

This is extremely important.

Correct:

```cpp
int size = q.size();

for (int i = 0; i < size; i++) {

}
```

Why?

Because:

```text
q.size()
```

changes while we process nodes.

Example:

Initially:

```text
Queue:

[2, 3]

q.size() = 2
```

Process `2`.

Push:

```text
4
5
```

Queue:

```text
[3, 4, 5]

q.size() = 3
```

Then process `3`.

Push:

```text
6
7
```

Queue:

```text
[4, 5, 6, 7]

q.size() = 4
```

The queue size keeps changing.

Therefore we take a snapshot:

```cpp
int size = q.size();
```

before processing the level.

This stores:

```text
Number of nodes belonging
to the CURRENT LEVEL.
```

---

# 16. Why Not Use Changing `q.size()` Directly?

Avoid patterns where the loop condition depends directly on a queue size that changes as children are pushed.

For example:

```cpp
for (int i = 0; i < q.size(); i++) {

}
```

The problem is:

```text
We pop current-level nodes

BUT

we also push next-level nodes
```

So:

```text
q.size()
```

is changing during the loop.

That can cause:

```text
Current level

and

Next level
```

to get mixed or processed incorrectly.

Correct pattern:

```cpp
int size = q.size();

for (int i = 0; i < size; i++) {

}
```

Now:

```text
size
```

does NOT change.

It represents exactly one level.

---

# 17. Level-by-Level BFS Code

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {

    vector<vector<int>> ans;

    if (root == nullptr)
        return ans;

    queue<TreeNode*> q;

    q.push(root);

    while (!q.empty()) {

        int size = q.size();

        vector<int> level;

        for (int i = 0; i < size; i++) {

            TreeNode* node = q.front();

            q.pop();

            level.push_back(node->val);

            if (node->left != nullptr)
                q.push(node->left);

            if (node->right != nullptr)
                q.push(node->right);
        }

        ans.push_back(level);
    }

    return ans;
}
```

---

# 18. Understanding the Outer `while`

```cpp
while (!q.empty())
```

The outer loop basically represents:

```text
PROCESS LEVELS
```

Conceptually:

```text
Iteration 1

Level 0
```

```text
Iteration 2

Level 1
```

```text
Iteration 3

Level 2
```

and so on.

---

# 19. Understanding the Inner `for`

```cpp
int size = q.size();

for (int i = 0; i < size; i++)
```

The inner loop means:

```text
PROCESS ALL NODES
OF THIS CURRENT LEVEL
```

So mental model:

```text
while loop

→ moves LEVEL BY LEVEL


for loop

→ processes every NODE
   inside one level
```

This is a very useful BFS pattern.

---

# 20. `vector<vector<int>>`

For level order:

```text
[
    [1],
    [2,3],
    [4,5,6,7]
]
```

we use:

```cpp
vector<vector<int>> ans;
```

Each:

```cpp
vector<int> level;
```

stores one level.

Example:

```text
level 0:

[1]
```

Push:

```cpp
ans.push_back(level);
```

Now:

```text
ans:

[
    [1]
]
```

Next:

```text
level:

[2,3]
```

Push:

```text
ans:

[
    [1],
    [2,3]
]
```

Next:

```text
level:

[4,5,6,7]
```

Final:

```text
[
    [1],
    [2,3],
    [4,5,6,7]
]
```

---

# 21. LeetCode 102 — Binary Tree Level Order Traversal

This is the main direct BFS problem.

Example:

```text
        3
       / \
      9   20
         /  \
        15   7
```

Expected:

```text
[
    [3],
    [9,20],
    [15,7]
]
```

Pattern:

```text
Create answer

↓

Handle NULL root

↓

Create queue

↓

Push root

↓

While queue not empty

↓

Store current queue size

↓

Create current level vector

↓

Process exactly size nodes

↓

Push children

↓

Add completed level to answer

↓

Repeat
```

---

# 22. LeetCode 102 Code

```cpp
class Solution {
public:

    vector<vector<int>> levelOrder(TreeNode* root) {

        vector<vector<int>> ans;

        if (root == nullptr)
            return ans;

        queue<TreeNode*> q;

        q.push(root);

        while (!q.empty()) {

            int size = q.size();

            vector<int> level;

            for (int i = 0; i < size; i++) {

                TreeNode* node = q.front();

                q.pop();

                level.push_back(node->val);

                if (node->left != nullptr)
                    q.push(node->left);

                if (node->right != nullptr)
                    q.push(node->right);
            }

            ans.push_back(level);
        }

        return ans;
    }
};
```

---

# 23. LeetCode 102 Dry Run

Tree:

```text
        3
       / \
      9   20
         /  \
        15   7
```

Initially:

```text
Queue:

[3]

ans:

[]
```

---

## Level 0

```text
size = 1
```

Process:

```text
3
```

Level:

```text
[3]
```

Push:

```text
9
20
```

Queue:

```text
[9,20]
```

Answer:

```text
[
    [3]
]
```

---

## Level 1

Queue:

```text
[9,20]
```

So:

```text
size = 2
```

Process `9`.

No children.

Process `20`.

Push:

```text
15
7
```

Current level:

```text
[9,20]
```

Queue:

```text
[15,7]
```

Answer:

```text
[
    [3],
    [9,20]
]
```

---

## Level 2

```text
size = 2
```

Process:

```text
15
7
```

Current level:

```text
[15,7]
```

No children.

Queue becomes empty.

Final:

```text
[
    [3],
    [9,20],
    [15,7]
]
```

---

# 24. BFS Time Complexity

Suppose tree contains:

```text
n nodes
```

Every node is:

```text
Pushed into queue once

and

Popped from queue once
```

Each node requires constant work.

Therefore:

```text
Time Complexity = O(n)
```

---

# 25. BFS Space Complexity

The queue may contain many nodes at the same time.

For example, in a balanced tree:

```text
                1
           /         \
          2           3
        /   \       /   \
       4     5     6     7
      / \   / \   / \   / \
     ........many nodes........
```

The widest level can contain many nodes.

In a complete/balanced tree, the last level can contain approximately:

```text
n / 2
```

nodes.

Big-O ignores constants:

```text
O(n / 2)

=

O(n)
```

Therefore worst-case BFS queue space:

```text
O(n)
```

---

# 26. BFS Final Complexity

```text
Time:

O(n)
```

because every node is processed once.

```text
Space:

O(n)
```

in the worst case because the queue may hold many nodes from a wide level.

More precisely, queue space is related to:

```text
Maximum width of the tree
```

So we can say:

```text
Space = O(w)
```

where:

```text
w = maximum width
```

Worst case:

```text
w = O(n)
```

therefore:

```text
Worst-case Space = O(n)
```

---

# 27. DFS vs BFS Complexity

## Recursive DFS

```text
Time:

O(n)

Space:

O(h)
```

where:

```text
h = tree height
```

Balanced:

```text
O(log n)
```

Skewed:

```text
O(n)
```

---

## BFS

```text
Time:

O(n)

Space:

O(w)
```

where:

```text
w = maximum tree width
```

Worst case:

```text
O(n)
```

---

# 28. DFS vs BFS — Main Mental Model

```text
DFS

GO DEEP
```

Tool:

```text
Recursion

or

Stack
```

Example:

```text
1
↓
2
↓
4
```

---

```text
BFS

GO LEVEL BY LEVEL
```

Tool:

```text
Queue
```

Example:

```text
1

↓

2 3

↓

4 5 6 7
```

---

# 29. Basic BFS vs Level-Separated BFS

## Basic BFS

If question asks:

```text
Return all nodes in BFS order
```

Example:

```text
[1,2,3,4,5,6,7]
```

Use:

```cpp
while (!q.empty()) {

    TreeNode* node = q.front();

    q.pop();

    // process node

    // push children
}
```

---

## Level-Separated BFS

If question asks:

```text
Return nodes level by level
```

Example:

```text
[
    [1],
    [2,3],
    [4,5,6,7]
]
```

Use:

```cpp
while (!q.empty()) {

    int size = q.size();

    for (int i = 0; i < size; i++) {

        // process current level
    }
}
```

The key difference is:

```text
q.size() snapshot
```

---

# 30. Important BFS Pattern

This pattern will appear in many future tree and graph questions:

```cpp
queue<TreeNode*> q;

q.push(root);

while (!q.empty()) {

    int size = q.size();

    for (int i = 0; i < size; i++) {

        TreeNode* node = q.front();

        q.pop();

        // PROCESS CURRENT NODE

        if (node->left)
            q.push(node->left);

        if (node->right)
            q.push(node->right);
    }
}
```

This is the core:

```text
LEVEL-BY-LEVEL BFS TEMPLATE
```

---

# 31. Why Left Is Usually Pushed Before Right

We normally write:

```cpp
if (node->left)
    q.push(node->left);

if (node->right)
    q.push(node->right);
```

This produces:

```text
LEFT TO RIGHT
```

level order.

Example:

```text
        1
       / \
      2   3
```

Queue becomes:

```text
[2,3]
```

So output:

```text
2 before 3
```

If we intentionally pushed right first:

```cpp
q.push(node->right);

q.push(node->left);
```

the order would become:

```text
1 3 2 ...
```

So child insertion order affects traversal order.

---

# 32. Common Mistakes

## Mistake 1 — Forgetting Empty Tree

Always consider:

```cpp
if (root == nullptr)
```

For a return type like:

```cpp
vector<vector<int>>
```

we return:

```cpp
return {};
```

or:

```cpp
vector<vector<int>> ans;

if (root == nullptr)
    return ans;
```

---

## Mistake 2 — Pushing NULL Children

Instead of blindly pushing:

```cpp
q.push(node->left);

q.push(node->right);
```

normally check:

```cpp
if (node->left != nullptr)
    q.push(node->left);

if (node->right != nullptr)
    q.push(node->right);
```

This keeps the queue containing only real nodes for standard BFS.

---

## Mistake 3 — Forgetting `q.pop()`

If we only do:

```cpp
TreeNode* node = q.front();
```

but never:

```cpp
q.pop();
```

the same front node remains in the queue.

The loop will not progress correctly.

Correct:

```cpp
TreeNode* node = q.front();

q.pop();
```

---

## Mistake 4 — Using Changing Queue Size for a Level

Do not rely on a queue size that changes as children are added.

Correct:

```cpp
int size = q.size();

for (int i = 0; i < size; i++) {

}
```

`size` is a snapshot of:

```text
CURRENT LEVEL NODE COUNT
```

---

## Mistake 5 — Mixing DFS and BFS Tools

Remember:

```text
DFS

→ Recursion / Stack
```

```text
BFS

→ Queue
```

A queue naturally processes nodes in discovery order.

---

# 33. Queue Dry-Run Pattern

Whenever confused, draw:

```text
Queue
Output
```

Example:

```text
Tree:

        1
       / \
      2   3
```

Start:

```text
Queue = [1]

Output = []
```

Process `1`:

```text
Queue = [2,3]

Output = [1]
```

Process `2`:

```text
Queue = [3]

Output = [1,2]
```

Process `3`:

```text
Queue = []

Output = [1,2,3]
```

This makes BFS easy to debug.

---

# 34. Questions / Problems Done in Module 4

## Problem 1 — Basic Level Order Traversal

Goal:

```text
Print / return:

1 2 3 4 5 6 7
```

Concept learned:

```text
Queue

Push root

Pop front

Push children
```

---

## Problem 2 — LeetCode 102: Binary Tree Level Order Traversal

Goal:

```text
Return:

[
    [1],
    [2,3],
    [4,5,6,7]
]
```

Concept learned:

```text
Level-by-level BFS

+

q.size() snapshot

+

vector<vector<int>>
```

Main pattern:

```cpp
while (!q.empty()) {

    int size = q.size();

    vector<int> level;

    for (int i = 0; i < size; i++) {

        // process nodes of current level
    }

    ans.push_back(level);
}
```

---

# 35. Future Problems Using the Same BFS Pattern

We do not need to solve all of these right now, but this same pattern will appear in:

```text
Binary Tree Level Order Traversal

Right Side View

Left Side View

Average of Levels

Largest Value in Each Row

Zigzag Level Order Traversal

Minimum Depth

Maximum Width

Cousins in Binary Tree

Connect Nodes at Same Level
```

The core remains:

```text
QUEUE

+

LEVEL SIZE
```

Then the question changes what we do with each level.

---

# 36. Ultra-Short Revision

## BFS

```text
Breadth First Search

=

Level Order Traversal
```

Tool:

```text
QUEUE
```

Basic template:

```cpp
queue<TreeNode*> q;

q.push(root);

while (!q.empty()) {

    TreeNode* node = q.front();

    q.pop();

    // process node

    if (node->left)
        q.push(node->left);

    if (node->right)
        q.push(node->right);
}
```

---

For separate levels:

```cpp
while (!q.empty()) {

    int size = q.size();

    for (int i = 0; i < size; i++) {

        // process exactly
        // one level
    }
}
```

Remember:

```text
while loop
→ levels

for loop
→ nodes inside current level
```

Complexity:

```text
Time:

O(n)

Space:

O(w)

Worst case:

O(n)
```

---

# 37. Core Mental Model

```text
DFS

I need to explore DEPTH

→ Recursion / Stack
```

```text
BFS

I need to explore LEVELS

→ Queue
```

For level-specific questions:

```text
Take q.size()
BEFORE processing

↓

That tells us how many nodes
belong to CURRENT LEVEL

↓

Process exactly those nodes

↓

Children added during processing
belong to NEXT LEVEL
```


