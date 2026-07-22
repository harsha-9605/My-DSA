# 🌳 Trees — Module 1: Complete Fundamentals

# 1. What is a Tree?

A **Tree** is a non-linear hierarchical data structure consisting of:

```text
Nodes + Edges
```

Unlike linear data structures:

```text
Array:
1 → 2 → 3 → 4

Linked List:
1 → 2 → 3 → 4
```

A tree branches:

```text
        1
       / \
      2   3
     / \
    4   5
```

A tree does **not contain cycles**.

There is exactly one path between any two nodes in a tree.

---

# 2. Example Tree Used in These Notes

```text
            1
          /   \
         2     3
        / \     \
       4   5     6
          / \
         7   8
```

We will use this tree to understand all terminology.

---

# 3. Node

Each individual element in a tree is called a **Node**.

For our tree:

```text
Nodes:

1, 2, 3, 4, 5, 6, 7, 8
```

Total:

```text
N = 8 nodes
```

A node usually stores:

```text
Data / Value

Connection to children
```

In a binary tree, a node can have:

```text
Left Child
Right Child
```

We will implement this using pointers in the next module.

---

# 4. Edge

An **edge** is the connection between two nodes.

Our tree:

```text
            1
          /   \
         2     3
        / \     \
       4   5     6
          / \
         7   8
```

Edges:

```text
1 — 2
1 — 3

2 — 4
2 — 5

3 — 6

5 — 7
5 — 8
```

Total:

```text
7 edges
```

## Important Tree Property

For a tree containing:

```text
N nodes
```

the number of edges is always:

```text
Edges = N - 1
```

Example:

```text
N = 8

Edges = 8 - 1

      = 7
```

Remember:

```text
TREE:

N nodes
↓
N - 1 edges
```

---

# 5. Root Node

The topmost node of a rooted tree is called the **Root**.

```text
            1 ← ROOT
          /   \
         2     3
```

Here:

```text
Root = 1
```

Important:

```text
Root has no parent.
```

A rooted tree has exactly one root.

---

# 6. Parent and Child

Consider:

```text
        1
       / \
      2   3
```

`1` is the:

```text
Parent
```

of:

```text
2 and 3
```

And:

```text
2 and 3
```

are the children of `1`.

Another example:

```text
        2
       / \
      4   5
```

```text
Parent = 2

Children = 4, 5
```

Another:

```text
        5
       / \
      7   8
```

```text
Parent = 5

Children = 7, 8
```

Parent-child describes an **immediate relationship**.

---

# 7. Siblings

Nodes that have the **same parent** are called siblings.

Example:

```text
        1
       / \
      2   3
```

```text
2 and 3
```

are siblings.

Similarly:

```text
4 and 5
```

are siblings because their parent is `2`.

And:

```text
7 and 8
```

are siblings because their parent is `5`.

But:

```text
4 and 6
```

are NOT siblings because they have different parents.

Remember:

```text
Same Parent
    ↓
 Siblings
```

---

# 8. Leaf Node

A node with **no children** is called a:

```text
Leaf Node
```

or sometimes:

```text
Terminal Node
```

Our tree:

```text
            1
          /   \
         2     3
        / \     \
       4   5     6
          / \
         7   8
```

Leaf nodes:

```text
4
6
7
8
```

They have:

```text
0 children
```

In binary-tree pointer terms, a leaf eventually has:

```text
left  = NULL
right = NULL
```

---

# 9. Internal / Non-Leaf Node

A node that has at least one child is called an:

```text
Internal Node
```

or:

```text
Non-Leaf Node
```

In our tree:

```text
1
2
3
5
```

are internal nodes.

Important:

A node does NOT need two children to be internal.

Example:

```text
3
 \
  6
```

Node `3` has only one child.

It is still an internal node.

---

# 10. Ancestor

An **ancestor** of a node is any node above it on the path toward the root.

Example:

```text
        1
       /
      2
       \
        5
       /
      7
```

For node `7`:

```text
Ancestors:

5
2
1
```

For node `5`:

```text
Ancestors:

2
1
```

Think:

```text
Node
↑
Parent
↑
Parent's parent
↑
...
Root
```

These are ancestors.

Usually, a node is not considered its own ancestor unless a problem explicitly uses an "ancestor-or-self" definition.

---

# 11. Descendant

A **descendant** is the opposite of an ancestor.

It means any node below another node.

Example:

```text
        2
       / \
      4   5
         / \
        7   8
```

Descendants of `2`:

```text
4
5
7
8
```

A child is an:

```text
Immediate Descendant
```

But descendants can exist many levels below.

Relationship:

```text
Ancestor
   ↓
 Parent
   ↓
 Child
   ↓
Descendant
```

---

# 12. Subtree

A **subtree** consists of:

```text
A node
+
All nodes below it
```

This is one of the most important concepts for recursion.

Example:

Subtree rooted at `5`:

```text
        5
       / \
      7   8
```

Subtree rooted at `2`:

```text
        2
       / \
      4   5
         / \
        7   8
```

The entire tree itself is also the subtree rooted at `1`.

---

## Why Subtrees Matter in Recursion

When we write:

```cpp
solve(root->left);
```

we are saying:

```text
Solve the same problem
for the entire LEFT SUBTREE.
```

When we write:

```cpp
solve(root->right);
```

we are saying:

```text
Solve the same problem
for the entire RIGHT SUBTREE.
```

This is the central recursive idea behind trees.

Instead of:

```text
solve(n - 1)
```

we now often have:

```text
solve(left subtree)

solve(right subtree)
```

---

# 13. Path

A **path** is a sequence of connected nodes.

Example:

```text
1 → 2 → 5 → 7
```

This is a path.

Another example:

```text
4 → 2 → 5 → 8
```

This is also a path when considering tree edges as connections in either direction.

For:

```text
1 → 2 → 5 → 7
```

Nodes:

```text
4 nodes
```

Edges:

```text
3 edges
```

Path length is commonly measured using:

```text
Number of edges
```

So:

```text
Path length = 3
```

However, some problems count nodes instead.

Always check the problem definition.

---

# 14. Depth of a Node

**Depth** means:

> Number of edges from the ROOT to that node.

Example:

```text
            1             Depth 0
          /   \
         2     3           Depth 1
        / \     \
       4   5     6         Depth 2
          / \
         7   8             Depth 3
```

Therefore:

```text
depth(1) = 0

depth(2) = 1
depth(3) = 1

depth(4) = 2
depth(5) = 2
depth(6) = 2

depth(7) = 3
depth(8) = 3
```

Mental model:

```text
DEPTH

Root
 ↓
 ↓
Node
```

Ask:

```text
How far is this node FROM the root?
```

---

# 15. Height of a Node

**Height** means:

> Number of edges on the longest downward path from that node to a leaf.

Example:

```text
        2
       / \
      4   5
         / \
        7   8
```

For node `2`, longest downward path:

```text
2 → 5 → 7
```

Number of edges:

```text
2
```

Therefore:

```text
height(2) = 2
```

For node `5`:

```text
5 → 7
```

Number of edges:

```text
1
```

Therefore:

```text
height(5) = 1
```

For leaf `7`:

```text
7
```

No downward edges.

Therefore:

```text
height(7) = 0
```

---

# 16. Depth vs Height

This is extremely important.

## Depth

```text
ROOT → NODE
```

Ask:

```text
How far is the node FROM the root?
```

## Height

```text
NODE → DEEPEST LEAF
```

Ask:

```text
How far can I go DOWN from this node?
```

Example for node `5`:

```text
            1
           /
          2
           \
            5
           / \
          7   8
```

Depth of `5`:

```text
1 → 2 → 5

2 edges

depth(5) = 2
```

Height of `5`:

```text
5 → 7

1 edge

height(5) = 1
```

Memory trick:

```text
DEPTH
↓
Root → Node

HEIGHT
↓
Node → Deepest Leaf
```

Or:

```text
Depth  → look UP toward root

Height → look DOWN toward leaves
```

---

# 17. Height of the Entire Tree

The height of a tree is usually defined as:

```text
Height of the Root
```

Our tree:

```text
            1
          /   \
         2     3
        / \     \
       4   5     6
          / \
         7   8
```

Longest root-to-leaf path:

```text
1 → 2 → 5 → 7
```

Number of edges:

```text
3
```

Therefore, using the edge-based definition:

```text
Tree Height = 3
```

---

# 18. Important Height Convention

Some problems define height using:

```text
Number of EDGES
```

Others use:

```text
Number of NODES
```

For:

```text
1 → 2 → 5 → 7
```

Edges:

```text
3
```

Nodes:

```text
4
```

So depending on the definition:

```text
Height = 3
```

or:

```text
Maximum Depth = 4
```

This is why coding problems such as maximum depth may return `4` even though edge-based tree height is `3`.

Always check whether the problem counts:

```text
EDGES

or

NODES
```

---

# 19. Level of a Node

Level is closely related to depth.

A common convention:

```text
Root = Level 0
```

Then:

```text
Level 0:

1


Level 1:

2, 3


Level 2:

4, 5, 6


Level 3:

7, 8
```

Some textbooks use:

```text
Root = Level 1
```

So level numbering may differ.

In coding problems, depth is usually less ambiguous.

---

# 20. Degree of a Node

The **degree of a node** means:

```text
Number of children
```

Example:

Node `1`:

```text
Children = 2, 3

degree(1) = 2
```

Node `3`:

```text
Child = 6

degree(3) = 1
```

Node `7`:

```text
No children

degree(7) = 0
```

In a Binary Tree:

```text
Maximum Degree = 2
```

because each node can have at most two children.

---

# 21. Binary Tree

A **Binary Tree** is a tree where every node has at most:

```text
2 children
```

These are called:

```text
Left Child

Right Child
```

Valid:

```text
       1
      / \
     2   3
```

Also valid:

```text
       1
      /
     2
```

Also valid:

```text
       1
        \
         3
```

A node may have:

```text
0 children

1 child

2 children
```

But never more than `2`.

---

# 22. Binary Tree ≠ Binary Search Tree

Very important distinction.

A normal Binary Tree:

```text
       10
      /  \
     50   2
```

is completely valid.

Binary Trees have:

```text
NO ordering rule
```

A **Binary Search Tree (BST)** adds an ordering property:

```text
Left Subtree Values
        <
       Root
        <
Right Subtree Values
```

Simplified:

```text
Left < Root < Right
```

Example BST:

```text
        10
       /  \
      5    15
```

We should learn these separately:

```text
Binary Trees
     ↓
Complete Binary Trees
     ↓
Binary Search Trees later
```

Do not mix normal Binary Tree rules with BST rules.

---

# 23. Types of Binary Trees

Important interview terminology:

```text
Full Binary Tree

Complete Binary Tree

Perfect Binary Tree

Balanced Binary Tree

Skewed Binary Tree
```

---

# 24. Full Binary Tree

A **Full Binary Tree** means:

Every node has either:

```text
0 children
```

or:

```text
2 children
```

Never exactly one child.

Example:

```text
        1
       / \
      2   3
     / \
    4   5
```

Node `1`:

```text
2 children
```

Node `2`:

```text
2 children
```

Nodes `3,4,5`:

```text
0 children
```

Therefore:

```text
FULL Binary Tree
```

Invalid full tree:

```text
        1
       /
      2
```

Node `1` has exactly:

```text
1 child
```

Therefore it is not full.

Memory:

```text
FULL

0 OR 2 children
```

---

# 25. Complete Binary Tree

A **Complete Binary Tree** means:

1. Every level is completely filled except possibly the last level.
2. The last level must be filled from:

```text
LEFT → RIGHT
```

Example:

```text
        1
       / \
      2   3
     / \  /
    4  5 6
```

This is complete.

Last level:

```text
4 5 6
```

is filled from the left.

---

Invalid:

```text
        1
       / \
      2   3
       \  /
        5 6
```

There is a gap before node `5`.

Therefore:

```text
NOT COMPLETE
```

Important:

```text
Complete Binary Trees
```

are used heavily in:

```text
Heaps

Priority Queues
```

---

# 26. Perfect Binary Tree

A **Perfect Binary Tree** has:

1. Every internal node has exactly `2` children.
2. All leaf nodes are at the same level.

Example:

```text
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

All internal nodes:

```text
1
2
3
```

have exactly two children.

All leaves:

```text
4
5
6
7
```

are at the same level.

Therefore:

```text
Perfect Binary Tree
```

---

# 27. Perfect Binary Tree Formula

If height `h` is measured using edges:

```text
Total Nodes = 2^(h+1) - 1
```

Example:

```text
Height = 2
```

Then:

```text
Nodes

= 2^(2+1) - 1

= 2³ - 1

= 8 - 1

= 7
```

Which matches:

```text
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

---

# 28. Balanced Binary Tree

A height-balanced binary tree satisfies:

```text
| height(left subtree)
-
height(right subtree) |

<= 1
```

at every node.

Example:

```text
       1
      / \
     2   3
    /
   4
```

The left side is only slightly deeper.

This can still be balanced.

Important:

The condition must hold:

```text
AT EVERY NODE
```

not only at the root.

We will later solve:

```text
Balanced Binary Tree
```

using recursion.

---

# 29. Skewed Binary Tree

A skewed tree behaves almost like a linked list.

## Left-Skewed

```text
       1
      /
     2
    /
   3
  /
 4
```

## Right-Skewed

```text
1
 \
  2
   \
    3
     \
      4
```

Most nodes have only one child.

This is very important for complexity.

For `n` nodes:

```text
Balanced Tree

Height ≈ O(log n)
```

But:

```text
Skewed Tree

Height = O(n)
```

This affects recursive stack space.

---

# 30. Quick Comparison of Binary Tree Types

## Full

```text
Every node:

0 OR 2 children
```

Memory:

```text
No node has exactly 1 child.
```

---

## Complete

```text
All levels filled

except possibly last

Last level filled:

LEFT → RIGHT
```

Memory:

```text
No gaps from the left.
```

---

## Perfect

```text
Every internal node:

2 children

AND

All leaves:

same level
```

Memory:

```text
Completely filled triangle.
```

---

## Balanced

```text
Left and right subtree
heights differ by at most 1

at every node.
```

Memory:

```text
Height stays small.
```

---

## Skewed

```text
Mostly one child per node.
```

Memory:

```text
Looks like Linked List.
```

---

# 31. Relationship Between These Types

A Perfect Binary Tree is also:

```text
Full
+
Complete
+
Balanced
```

But:

```text
Full
```

does NOT necessarily mean:

```text
Complete
```

And:

```text
Complete
```

does NOT necessarily mean:

```text
Perfect
```

Each term describes a different structural property.

---

# 32. Most Important Tree Recursion Idea

Suppose:

```text
            1
          /   \
         2     3
        / \     \
       4   5     6
```

Standing at:

```text
root = 1
```

Do NOT think:

```text
How do I manually process
1,2,3,4,5,6?
```

Instead think:

```text
I handle node 1.

Recursion handles:

LEFT SUBTREE

        2
       / \
      4   5


and

RIGHT SUBTREE

        3
         \
          6
```

The recursive structure becomes:

```cpp
solve(root) {

    solve(root->left);

    solve(root->right);

}
```

Mental model:

```text
CURRENT NODE

     root
     /  \
    /    \

LEFT      RIGHT
SUBTREE   SUBTREE
   ↓         ↓
recursion recursion
handles    handles
everything everything
```

This is exactly the recursion principle:

```text
Trust recursion to solve
the smaller problem.
```

The smaller problem is now:

```text
A SUBTREE
```

instead of:

```text
n - 1
```

---

# 33. Generic Recursive Tree Template

Many tree problems eventually look like:

```cpp
ReturnType solve(TreeNode* root) {

    if (root == nullptr)
        return baseValue;

    auto left =
        solve(root->left);

    auto right =
        solve(root->right);

    return combine(
        root,
        left,
        right
    );
}
```

Meaning:

```text
1. Handle base case

2. Ask left subtree for answer

3. Ask right subtree for answer

4. Combine both answers
   with current node
```

This is functional recursion applied to trees.

---

# 34. Tree Base Case

The most common tree recursion base case is:

```cpp
if (root == nullptr)
    return;
```

or:

```cpp
if (root == nullptr)
    return someBaseValue;
```

Why?

Eventually:

```text
Leaf
 / \
NULL NULL
```

Recursion reaches:

```text
root == NULL
```

and stops.

Example:

```text
       4
      / \
   NULL NULL
```

When recursion tries:

```cpp
solve(root->left);
```

it receives:

```text
NULL
```

and hits the base case.

---

# 35. Tree Traversal Time Complexity

Suppose:

```cpp
void solve(TreeNode* root) {

    if (root == nullptr)
        return;

    solve(root->left);

    solve(root->right);
}
```

If every node is visited once:

```text
N nodes
```

then:

```text
Time Complexity = O(N)
```

Because:

```text
Each node
↓
processed once
```

---

# 36. Tree Recursive Stack Space

This is extremely important.

Recursive stack depends on:

```text
Maximum recursion depth
```

which depends on:

```text
Tree Height = h
```

Therefore:

```text
Recursive Stack Space = O(h)
```

NOT automatically:

```text
O(n)
```

---

# 37. Balanced Tree Stack Space

Balanced tree:

```text
            *
         /     \
        *       *
       / \     / \
      *   *   *   *
```

Height:

```text
h ≈ log n
```

Therefore:

```text
Recursive Stack

= O(h)

= O(log n)
```

---

# 38. Skewed Tree Stack Space

Skewed tree:

```text
*
 \
  *
   \
    *
     \
      *
```

Height:

```text
h ≈ n
```

Therefore:

```text
Recursive Stack

= O(h)

= O(n)
```

---

# 39. Fundamental Tree Complexity Rule

For most recursive DFS tree traversals:

```text
TIME

O(n)
```

because every node is visited once.

Space:

```text
O(h)
```

where:

```text
h = tree height
```

Therefore:

```text
Balanced Tree:

Time  = O(n)
Stack = O(log n)
```

Worst-case skewed tree:

```text
Time  = O(n)
Stack = O(n)
```

This pattern will appear repeatedly in tree problems.

---

# 40. Depth vs Height and Complexity

Do not confuse:

```text
Depth
```

with:

```text
Height
```

Recursive stack for a full tree traversal depends on:

```text
Maximum Depth
```

which is equivalent to the tree's height up to the edge-vs-node convention.

So we usually write:

```text
Space = O(h)
```

---

# 41. Important Tree Facts

## Fact 1

For a tree:

```text
Edges = Nodes - 1
```

---

## Fact 2

A Binary Tree node can have:

```text
0
1
or
2 children
```

---

## Fact 3

Maximum degree of a Binary Tree:

```text
2
```

---

## Fact 4

Leaf node:

```text
0 children
```

---

## Fact 5

Root:

```text
No parent
```

---

## Fact 6

Depth:

```text
Root → Node
```

---

## Fact 7

Height:

```text
Node → Deepest Leaf
```

---

## Fact 8

Tree Height:

```text
Height of Root
```

---

## Fact 9

Perfect Binary Tree:

```text
Nodes = 2^(h+1) - 1
```

when `h` counts edges.

---

## Fact 10

Most recursive full-tree traversals:

```text
Time = O(n)

Stack = O(h)
```

---

# 42. Quick Revision Table

| Term          | Meaning                      |
| ------------- | ---------------------------- |
| Node          | Individual element           |
| Edge          | Connection between nodes     |
| Root          | Topmost node                 |
| Parent        | Immediate node above         |
| Child         | Immediate node below         |
| Sibling       | Nodes with same parent       |
| Leaf          | Node with no children        |
| Internal Node | Node with at least one child |
| Ancestor      | Node above another node      |
| Descendant    | Node below another node      |
| Subtree       | Node + everything below it   |
| Path          | Sequence of connected nodes  |
| Depth         | Root → Node distance         |
| Height        | Node → Deepest leaf distance |
| Tree Height   | Height of root               |
| Degree        | Number of children           |
| Binary Tree   | At most 2 children           |

---

# 43. Binary Tree Types Quick Revision

| Type     | Main Rule                                                    |
| -------- | ------------------------------------------------------------ |
| Full     | Every node has `0` or `2` children                           |
| Complete | Last level filled left → right                               |
| Perfect  | All internal nodes have 2 children + all leaves same level   |
| Balanced | Left/right subtree heights differ by at most 1 at every node |
| Skewed   | Mostly one child per node                                    |

---

# 44. Important Differences

## Depth vs Height

```text
Depth:

ROOT
 ↓
NODE
```

```text
Height:

NODE
 ↓
DEEPEST LEAF
```

---

## Binary Tree vs BST

```text
Binary Tree:

At most 2 children

NO ordering requirement
```

```text
BST:

Binary Tree
+
Ordering property

Left < Root < Right
```

---

## Full vs Complete

```text
FULL:

0 or 2 children
```

```text
COMPLETE:

Filled level-by-level
and last level left-to-right
```

---

## Complete vs Perfect

```text
COMPLETE:

Last level may be incomplete.
```

```text
PERFECT:

Every level completely filled.
```

---

# 45. Final Mental Model for Trees

When looking at:

```text
           ROOT
          /    \
         /      \
      LEFT      RIGHT
     SUBTREE   SUBTREE
```

Think:

```text
Current node
+
Two smaller tree problems
```

Recursion:

```text
solve(root)

        ↓

solve(left subtree)

        +

solve(right subtree)

        ↓

combine answers
```

This is the core idea that will power almost every recursive Binary Tree problem.

---

# 46. Module 1 Checklist

I should now understand:

* [x] What a Tree is
* [x] Node
* [x] Edge
* [x] Root
* [x] Parent
* [x] Child
* [x] Sibling
* [x] Leaf Node
* [x] Internal Node
* [x] Ancestor
* [x] Descendant
* [x] Subtree
* [x] Path
* [x] Depth
* [x] Height
* [x] Depth vs Height
* [x] Level
* [x] Degree
* [x] Binary Tree
* [x] Binary Tree vs BST
* [x] Full Binary Tree
* [x] Complete Binary Tree
* [x] Perfect Binary Tree
* [x] Balanced Binary Tree
* [x] Skewed Binary Tree
* [x] `N nodes → N-1 edges`
* [x] Perfect Tree formula
* [x] Basic recursive subtree mental model
* [x] `Time = O(n)` for full traversal
* [x] `Stack = O(h)`
* [x] Balanced stack = `O(log n)`
* [x] Skewed stack = `O(n)`

# Module 1 — COMPLETE ✅

Next:

```text
MODULE 2

Binary Tree Node Structure
+
Pointers
+
TreeNode class/struct
+
root->left / root->right
+
Creating nodes
+
Connecting nodes
+
How a tree exists in memory
+
Manual tree construction
```
