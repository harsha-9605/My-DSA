# 🌳 Binary Trees & BST — Complete Syllabus

## Progress

* [x] Module 1 — Tree Fundamentals
* [x] Module 2 — Tree Representation & Construction
* [x] Module 3 — DFS Traversals
* [x] Module 4 — BFS / Level Order Traversal
* [ ] Module 5 — Basic Recursive Tree Problems
* [ ] Module 6 — Diameter & Path-Based Recursion
* [ ] Module 7 — Root-to-Leaf Path Problems
* [ ] Module 8 — Tree Views & Level Patterns
* [ ] Module 9 — Lowest Common Ancestor
* [ ] Module 10 — Construct Trees from Traversals
* [ ] Module 11 — Serialization & Deserialization
* [ ] Module 12 — Advanced Binary Tree Problems
* [ ] Module 13 — BST Fundamentals
* [ ] Module 14 — BST Search, Insert & Delete
* [ ] Module 15 — BST Validation
* [ ] Module 16 — BST Order-Based Problems
* [ ] Module 17 — Advanced BST Problems

---

# Module 1 — Tree Fundamentals ✅

## Learn

* Tree terminology
* Root
* Node
* Edge
* Parent
* Child
* Siblings
* Leaf node
* Internal node
* Ancestors
* Descendants
* Subtree
* Level
* Depth
* Height
* Binary Tree
* Full Binary Tree
* Complete Binary Tree
* Perfect Binary Tree
* Balanced Binary Tree
* Skewed Binary Tree
* Tree height using edges vs nodes

## Questions

* Theory and tree-identification questions

---

# Module 2 — Tree Representation & Construction ✅

## Learn

* `TreeNode` structure
* `root->val`
* `root->left`
* `root->right`
* Tree pointers
* `nullptr`
* Creating nodes
* Connecting nodes
* Manual tree construction
* Tree construction using input
* Moving through tree pointers
* Local behavior of `root` in recursive calls

## Questions

* Create a binary tree manually
* Create a tree using input
* Access left/right nodes
* Navigate through tree pointers

---

# Module 3 — DFS Tree Traversals ✅

## Learn

### Preorder

```text
Root → Left → Right
```

### Inorder

```text
Left → Root → Right
```

### Postorder

```text
Left → Right → Root
```

* Recursive traversal
* Recursion stack
* Traversal dry runs
* Time complexity `O(n)`
* Space complexity `O(h)`

## Questions

* [x] LC 144 — Binary Tree Preorder Traversal
* [x] LC 94 — Binary Tree Inorder Traversal
* [x] LC 145 — Binary Tree Postorder Traversal

---

# Module 4 — BFS / Level Order Traversal ✅

## Learn

* BFS in trees
* Queue-based traversal
* FIFO
* `queue<TreeNode*>`
* Flat level-order traversal
* Level-by-level traversal
* `q.size()` snapshot
* Separating levels
* `vector<vector<int>>`
* BFS dry run
* BFS vs DFS
* Time complexity `O(n)`
* Space complexity `O(w)`, worst case `O(n)`

## Questions

* [x] LC 102 — Binary Tree Level Order Traversal

Later variations:

* [ ] LC 107 — Binary Tree Level Order Traversal II
* [ ] LC 103 — Binary Tree Zigzag Level Order Traversal
* [ ] LC 199 — Binary Tree Right Side View

---

# Module 5 — Basic Recursive Tree Problems 🔄

## Learn

### Basic subtree recursion

```text
Solve left subtree
Solve right subtree
Combine answers
Return answer
```

### Important patterns

```cpp
// Count
return 1 + left + right;

// Sum
return root->val + left + right;

// Height / Maximum Depth
return 1 + max(left, right);
```

* Count nodes
* Sum of nodes
* Count leaf nodes
* Depth of a specific node
* Height of a specific node
* Maximum depth
* Edge-based vs node-based height/depth
* Functional recursion on trees
* Two-tree recursion
* Modifying trees recursively
* Structural comparison
* Balanced-tree checking

## Questions

* [x] Custom — Count Total Nodes
* [x] Custom — Sum of All Nodes
* [x] Custom — Count Leaf Nodes
* [x] Custom — Depth of a Specific Node
* [x] Custom — Height of a Specific Node
* [x] LC 104 — Maximum Depth of Binary Tree
* [x] LC 100 — Same Tree
* [ ] LC 404 — Sum of Left Leaves
* [ ] LC 226 — Invert Binary Tree
* [ ] LC 101 — Symmetric Tree
* [ ] LC 110 — Balanced Binary Tree

---

# Module 6 — Diameter & Path-Based Recursion

## Learn

* Subtree height reuse
* Diameter of a tree
* Path through current node
* Global answer vs returned answer
* Returning one path to parent
* Combining left and right paths
* Postorder-style recursion
* Efficient `O(n)` tree recursion

## Questions

* [ ] LC 543 — Diameter of Binary Tree ⭐
* [ ] LC 124 — Binary Tree Maximum Path Sum ⭐
* [ ] LC 687 — Longest Univalue Path — Optional

---

# Module 7 — Root-to-Leaf Path Problems

## Learn

* Root-to-leaf recursion
* Path sum
* Carrying remaining sum
* Building paths recursively
* Backtracking inside trees
* Returning paths
* Leaf-node conditions

## Questions

* [ ] LC 112 — Path Sum ⭐
* [ ] LC 113 — Path Sum II ⭐
* [ ] LC 257 — Binary Tree Paths ⭐
* [ ] LC 129 — Sum Root to Leaf Numbers

---

# Module 8 — Tree Views & Level Patterns

## Learn

* Right view
* Left view
* Zigzag traversal
* Level-based processing
* First node of each level
* Last node of each level
* Horizontal distance
* Top view
* Bottom view
* BFS with extra information

## Questions

* [ ] LC 199 — Binary Tree Right Side View ⭐
* [ ] LC 103 — Binary Tree Zigzag Level Order Traversal ⭐
* [ ] Left View of Binary Tree — GFG
* [ ] Top View of Binary Tree — GFG ⭐
* [ ] Bottom View of Binary Tree — GFG ⭐
* [ ] LC 515 — Find Largest Value in Each Tree Row

---

# Module 9 — Lowest Common Ancestor

## Learn

* Lowest Common Ancestor concept
* Searching for two target nodes
* Returning target nodes through recursion
* Left subtree result
* Right subtree result
* Combining recursive results
* Ancestor relationships

## Questions

* [ ] LC 236 — Lowest Common Ancestor of a Binary Tree ⭐⭐⭐

BST version later:

* [ ] LC 235 — Lowest Common Ancestor of a BST

---

# Module 10 — Construct Trees from Traversals

## Learn

* Building trees recursively
* Preorder + Inorder
* Inorder + Postorder
* Finding root from traversal
* Splitting left/right subtrees
* Inorder index mapping
* Hash map optimization
* Recursive range boundaries

## Questions

* [ ] LC 105 — Construct Binary Tree from Preorder and Inorder ⭐⭐⭐
* [ ] LC 106 — Construct Binary Tree from Inorder and Postorder ⭐⭐

---

# Module 11 — Serialization & Deserialization

## Learn

* Tree → serialized representation
* Serialized representation → tree
* Handling `nullptr`
* Preorder serialization
* BFS serialization
* Reconstructing tree structure

## Questions

* [ ] LC 297 — Serialize and Deserialize Binary Tree ⭐

Optional BST version:

* [ ] LC 449 — Serialize and Deserialize BST

---

# Module 12 — Advanced Binary Tree Problems

## Learn

* Maximum width
* Positional indexing
* Overflow-safe indexing
* Parent mapping
* Treating tree as an undirected graph
* Nodes at distance `K`
* Vertical traversal
* Row and column coordinates
* Sorting tree nodes by position
* Complete-tree checking

## Questions

* [ ] LC 662 — Maximum Width of Binary Tree ⭐
* [ ] LC 863 — All Nodes Distance K in Binary Tree ⭐
* [ ] LC 987 — Vertical Order Traversal ⭐
* [ ] LC 958 — Check Completeness of a Binary Tree

---

# 🌲 Binary Search Trees

---

# Module 13 — BST Fundamentals

## Learn

BST property:

```text
Left < Root < Right
```

* Binary Tree vs BST
* BST ordering property
* Recursive BST structure
* Searching using ordering
* Minimum value
* Maximum value
* Inorder traversal of BST
* Why inorder of BST is sorted
* Time complexity based on tree height

## Questions

* [ ] Basic BST search
* [ ] Find minimum in BST
* [ ] Find maximum in BST
* [ ] Verify sorted inorder manually

---

# Module 14 — BST Search, Insert & Delete

## Learn

* Search in BST
* Iterative search
* Recursive search
* Insert into BST
* Delete from BST

### Delete cases

```text
0 children
1 child
2 children
```

* Inorder successor
* Inorder predecessor

## Questions

* [ ] LC 700 — Search in a Binary Search Tree
* [ ] LC 701 — Insert into a Binary Search Tree
* [ ] LC 450 — Delete Node in a BST ⭐⭐⭐

---

# Module 15 — BST Validation

## Learn

* Valid BST rules
* Why checking only parent-child is insufficient
* Lower and upper bounds
* Range-based recursion
* Inorder validation
* Previous-node technique

## Questions

* [ ] LC 98 — Validate Binary Search Tree ⭐⭐⭐

---

# Module 16 — BST Order-Based Problems

## Learn

* Sorted inorder property
* Kth smallest
* Kth largest
* Rank/order concepts
* LCA using BST ordering
* Constructing balanced BST

## Questions

* [ ] LC 230 — Kth Smallest Element in a BST ⭐⭐⭐
* [ ] LC 235 — Lowest Common Ancestor of a BST ⭐
* [ ] LC 108 — Convert Sorted Array to Binary Search Tree ⭐

---

# Module 17 — Advanced BST Problems

## Learn

* BST iterator
* Controlled inorder traversal
* Stack-based lazy traversal
* Recovering swapped BST nodes
* BST serialization
* Advanced inorder applications

## Questions

* [ ] LC 173 — Binary Search Tree Iterator ⭐
* [ ] LC 99 — Recover Binary Search Tree ⭐
* [ ] LC 449 — Serialize and Deserialize BST — Optional

---

# ⭐ Core Must-Solve Questions

## Basic Recursion

* [ ] LC 104 — Maximum Depth of Binary Tree
* [x] LC 100 — Same Tree
* [ ] LC 404 — Sum of Left Leaves
* [ ] LC 226 — Invert Binary Tree
* [ ] LC 101 — Symmetric Tree
* [ ] LC 110 — Balanced Binary Tree

## BFS / Views

* [x] LC 102 — Level Order Traversal
* [ ] LC 103 — Zigzag Level Order
* [ ] LC 199 — Right Side View
* [ ] Top View — GFG
* [ ] Bottom View — GFG

## Paths

* [ ] LC 543 — Diameter of Binary Tree
* [ ] LC 112 — Path Sum
* [ ] LC 113 — Path Sum II
* [ ] LC 257 — Binary Tree Paths
* [ ] LC 124 — Binary Tree Maximum Path Sum

## LCA

* [ ] LC 236 — LCA of Binary Tree

## Tree Construction

* [ ] LC 105 — Preorder + Inorder
* [ ] LC 106 — Inorder + Postorder

## Advanced Binary Tree

* [ ] LC 297 — Serialize and Deserialize
* [ ] LC 662 — Maximum Width
* [ ] LC 863 — Distance K
* [ ] LC 987 — Vertical Traversal

## BST

* [ ] LC 700 — Search BST
* [ ] LC 701 — Insert BST
* [ ] LC 450 — Delete BST
* [ ] LC 98 — Validate BST
* [ ] LC 230 — Kth Smallest
* [ ] LC 235 — LCA BST
* [ ] LC 108 — Sorted Array to BST
* [ ] LC 173 — BST Iterator

---

# Final Learning Order

```text
Module 1
Tree Fundamentals
        ↓
Module 2
Representation & Construction
        ↓
Module 3
DFS Traversals
        ↓
Module 4
BFS / Level Order
        ↓
Module 5
Basic Recursive Problems
        ↓
Module 6
Diameter & Path-Based Recursion
        ↓
Module 7
Root-to-Leaf Paths
        ↓
Module 8
Views & Level Patterns
        ↓
Module 9
Lowest Common Ancestor
        ↓
Module 10
Construct Trees from Traversals
        ↓
Module 11
Serialization / Deserialization
        ↓
Module 12
Advanced Binary Tree Problems
        ↓
Module 13
BST Fundamentals
        ↓
Module 14
BST Search / Insert / Delete
        ↓
Module 15
BST Validation
        ↓
Module 16
BST Order-Based Problems
        ↓
Module 17
Advanced BST
```
