# 🌳 Module 5 — Basic Recursive Tree Problems

## Status

* [x] Module 5 Complete

---

# 1. Core Tree Recursion Structure

Most recursive tree problems follow:

```cpp
solve(TreeNode* root) {

    if (root == nullptr)
        return baseValue;

    auto left = solve(root->left);
    auto right = solve(root->right);

    return combine(left, right);
}
```

Each recursive call gets its own:

* `root`
* Local variables
* Stack frame

Changing a local variable inside one recursive call does not overwrite the local variable of another call.

---

# 2. Important Return Patterns

## Count Nodes

```cpp
int countNodes(TreeNode* root) {

    if (root == nullptr)
        return 0;

    return 1
         + countNodes(root->left)
         + countNodes(root->right);
}
```

Pattern:

```text
1 + left + right
```

`1` represents the current node.

### Complexity

```text
Time  = O(n)
Space = O(h)
```

---

# 3. Sum of All Nodes

```cpp
int sumNodes(TreeNode* root) {

    if (root == nullptr)
        return 0;

    return root->val
         + sumNodes(root->left)
         + sumNodes(root->right);
}
```

Pattern:

```text
current value + left sum + right sum
```

### Complexity

```text
Time  = O(n)
Space = O(h)
```

---

# 4. Maximum Depth / Height

## Node-Based Height

```cpp
int maxDepth(TreeNode* root) {

    if (root == nullptr)
        return 0;

    return 1 + max(
        maxDepth(root->left),
        maxDepth(root->right)
    );
}
```

Pattern:

```text
1 + max(left, right)
```

Use `max()` because height follows the longest path.

## Edge-Based Height

```cpp
int height(TreeNode* root) {

    if (root == nullptr)
        return -1;

    return 1 + max(
        height(root->left),
        height(root->right)
    );
}
```

Difference:

```text
Node-based:
NULL = 0
Leaf = 1

Edge-based:
NULL = -1
Leaf = 0
```

### Question

* [x] LC 104 — Maximum Depth of Binary Tree

### Complexity

```text
Time  = O(n)
Space = O(h)
```

---

# 5. Depth of a Specific Node

Depth:

```text
Number of edges:

ROOT → TARGET
```

Example:

```text
        8
       /
      4
     /
    2
   /
  1
```

```text
Depth(8) = 0
Depth(4) = 1
Depth(2) = 2
Depth(1) = 3
```

## Functional Recursion

```cpp
int depth(TreeNode* root, int target) {

    if (root == nullptr)
        return -1;

    if (root->val == target)
        return 0;

    int left = depth(root->left, target);

    if (left != -1)
        return 1 + left;

    int right = depth(root->right, target);

    if (right != -1)
        return 1 + right;

    return -1;
}
```

When target is found:

```text
return 0
```

Then while recursion unwinds:

```text
Target → 0
Parent → 1
Parent → 2
Parent → 3
```

The edges are counted while **coming back up**.

`-1` means:

```text
Target not found in this branch
```

---

# 6. Height of a Specific Node

Height:

```text
TARGET → DEEPEST LEAF
```

Once the target is found, treat that target as the root of its own subtree.

Helper:

```cpp
int height(TreeNode* root) {

    if (root == nullptr)
        return -1;

    return 1 + max(
        height(root->left),
        height(root->right)
    );
}
```

Search target:

```cpp
int heightOfTarget(TreeNode* root, int target) {

    if (root == nullptr)
        return -1;

    if (root->val == target)
        return height(root);

    int left = heightOfTarget(root->left, target);

    if (left != -1)
        return left;

    return heightOfTarget(root->right, target);
}
```

Difference:

```text
DEPTH

Root
 ↓
Target


HEIGHT

Target
 ↓
Deepest Leaf
```

---

# 7. Count Leaf Nodes

A leaf node must have:

```cpp
root->left == nullptr &&
root->right == nullptr
```

Code:

```cpp
int countLeaves(TreeNode* root) {

    if (root == nullptr)
        return 0;

    if (root->left == nullptr &&
        root->right == nullptr)
        return 1;

    return countLeaves(root->left)
         + countLeaves(root->right);
}
```

Important:

```cpp
&&
```

is required.

This is wrong:

```cpp
left == nullptr || right == nullptr
```

because a node with only one child is not a leaf.

### Why `root == nullptr` is needed

Consider:

```text
    5
     \
      8
```

From `5`:

```cpp
countLeaves(root->left)
```

calls:

```text
countLeaves(NULL)
```

Therefore:

```cpp
if (root == nullptr)
    return 0;
```

is required for general binary trees.

### Complexity

```text
Time  = O(n)
Space = O(h)
```

---

# 8. Same Tree

### Question

* [x] LC 100 — Same Tree

Two trees are the same when:

```text
Same structure
AND
Same values
```

Code:

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {

    if (p == nullptr && q == nullptr)
        return true;

    if (p == nullptr || q == nullptr)
        return false;

    if (p->val != q->val)
        return false;

    return isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}
```

New pattern:

```text
Two-tree recursion
```

Compare:

```text
p left  ↔ q left
p right ↔ q right
```

### Complexity

```text
Time  = O(n)
Space = O(h)
```

---

# 9. Sum of Left Leaves

### Question

* [x] LC 404 — Sum of Left Leaves

A left leaf must satisfy:

```text
1. It is a LEFT child
2. It is also a LEAF
```

## Parent-Lookahead Approach

Check:

```cpp
root->left != nullptr &&
root->left->left == nullptr &&
root->left->right == nullptr
```

Example:

```cpp
int sumOfLeftLeaves(TreeNode* root) {

    if (root == nullptr)
        return 0;

    int current = 0;

    if (root->left &&
        root->left->left == nullptr &&
        root->left->right == nullptr) {

        current = root->left->val;
    }

    return current
         + sumOfLeftLeaves(root->left)
         + sumOfLeftLeaves(root->right);
}
```

Important:

Do not immediately:

```cpp
return root->left->val;
```

because returning from the current call stops that call completely and may prevent other subtrees from being searched.

---

## Flag Approach

Pass information about whether the current node is a left child.

```cpp
int solve(TreeNode* root, bool isLeft) {

    if (root == nullptr)
        return 0;

    if (root->left == nullptr &&
        root->right == nullptr) {

        if (isLeft)
            return root->val;

        return 0;
    }

    return solve(root->left, true)
         + solve(root->right, false);
}
```

Initial call:

```cpp
solve(root, false);
```

Meaning:

```text
Go left  → true
Go right → false
```

When a leaf is reached:

```text
isLeft == true
→ left leaf
→ add value
```

### Complexity

```text
Time  = O(n)
Space = O(h)
```

---

# 10. Local Variables in Recursion

Example:

```cpp
int current = 0;
```

Every recursive call gets its own separate `current`.

Example:

```text
Call root = 3
current = 9

    Call root = 9
    current = 0

    Call root = 20
    current = 15
```

These variables do not overwrite each other.

Each call has its own stack frame.

---

# 11. Invert Binary Tree

### Question

* [x] LC 226 — Invert Binary Tree

Goal:

```text
At every node:

LEFT ↔ RIGHT
```

Code:

```cpp
TreeNode* invertTree(TreeNode* root) {

    if (root == nullptr)
        return root;

    invertTree(root->left);
    invertTree(root->right);

    swap(root->left, root->right);

    return root;
}
```

This follows postorder-style processing:

```text
LEFT
RIGHT
CURRENT NODE
```

Alternative:

```cpp
TreeNode* invertTree(TreeNode* root) {

    if (root == nullptr)
        return nullptr;

    swap(root->left, root->right);

    invertTree(root->left);
    invertTree(root->right);

    return root;
}
```

Both approaches work.

---

## Important Return Concept

This:

```cpp
if (root == nullptr)
    return root;
```

only returns from calls where:

```text
root == NULL
```

It does not automatically return from previous recursive calls.

Every call needs its own return.

```text
invertTree(NULL)
→ returns NULL

invertTree(leaf)
→ returns leaf

invertTree(parent)
→ returns parent

invertTree(original root)
→ returns original root
```

Therefore:

```cpp
return root;
```

at the end is necessary because the function returns:

```cpp
TreeNode*
```

### Complexity

```text
Time  = O(n)
Space = O(h)
```

---

# 12. Symmetric Tree

### Question

* [x] LC 101 — Symmetric Tree

Symmetry means comparing mirror positions.

Same Tree compares:

```text
left  ↔ left
right ↔ right
```

Symmetric Tree compares:

```text
left  ↔ right
right ↔ left
```

Core mirror pattern:

```cpp
bool mirror(TreeNode* p, TreeNode* q) {

    if (p == nullptr && q == nullptr)
        return true;

    if (p == nullptr || q == nullptr)
        return false;

    if (p->val != q->val)
        return false;

    return mirror(p->left, q->right) &&
           mirror(p->right, q->left);
}
```

### Complexity

```text
Time  = O(n)
Space = O(h)
```

---

# 13. Balanced Binary Tree

### Question

* [x] LC 110 — Balanced Binary Tree

A tree is balanced when for **every node**:

```text
|left height - right height| <= 1
```

Height helper:

```cpp
int height(TreeNode* root) {

    if (root == nullptr)
        return 0;

    return 1 + max(
        height(root->left),
        height(root->right)
    );
}
```

Basic solution:

```cpp
bool isBalanced(TreeNode* root) {

    if (root == nullptr)
        return true;

    int left = height(root->left);
    int right = height(root->right);

    if (abs(left - right) > 1)
        return false;

    return isBalanced(root->left) &&
           isBalanced(root->right);
}
```

---

## Important Mistake

This is wrong:

```cpp
int left = 1 + isBalanced(root->left);
int right = 1 + isBalanced(root->right);
```

Because:

```cpp
isBalanced()
```

returns:

```text
bool
```

C++ converts:

```text
true  → 1
false → 0
```

Therefore:

```text
1 + true  = 2
1 + false = 1
```

So `left` and `right` would only contain:

```text
1 or 2
```

They would not contain actual subtree heights.

Rule:

```text
Need height     → function returns int
Need count      → function returns int
Need sum        → function returns int
Need true/false → function returns bool
Need node       → function returns TreeNode*
```

---

## Why Check Subtrees Too?

Checking only:

```cpp
abs(left - right) <= 1
```

checks only the **current node**.

The root may be balanced while a node deeper inside is unbalanced.

Therefore:

```cpp
return isBalanced(root->left) &&
       isBalanced(root->right);
```

ensures the condition holds for every node.

Important distinction:

```text
height() recursion

→ visits nodes
→ calculates HEIGHT only


isBalanced() recursion

→ visits nodes
→ checks BALANCE
```

Calling `height()` does not automatically check whether every subtree is balanced.

### Basic Solution Complexity

```text
Worst-case Time = O(n²)
Space           = O(h)
```

Repeated `height()` calls recalculate subtree heights.

An optimized single-pass solution can reduce time to:

```text
O(n)
```

---

# 14. Main Patterns Learned

## Pattern 1 — Need Both Subtrees

```cpp
left + right
```

Examples:

```text
Count nodes
Sum nodes
Count leaves
```

---

## Pattern 2 — Need Longest Subtree

```cpp
1 + max(left, right)
```

Examples:

```text
Height
Maximum depth
```

---

## Pattern 3 — Need Both Conditions True

```cpp
leftCondition && rightCondition
```

Examples:

```text
Same Tree
Symmetric Tree
Balanced Tree
```

---

## Pattern 4 — Search for One Target

```cpp
int left = solve(root->left);

if (left != NOT_FOUND)
    return left;

return solve(root->right);
```

Examples:

```text
Depth of specific node
Height of specific node
```

---

## Pattern 5 — Carry Information Downward

```cpp
solve(child, extraInformation);
```

Example:

```text
Sum of Left Leaves using isLeft flag
```

---

## Pattern 6 — Modify the Tree

```cpp
solve(root->left);
solve(root->right);

modify(root);
```

Example:

```text
Invert Binary Tree
```

---

# 15. Complexity Rules

For most basic tree recursion:

```text
Time = O(n)
```

because every node is visited once.

Recursion stack:

```text
Space = O(h)
```

Where `h` is tree height.

Balanced tree:

```text
h = O(log n)
```

Therefore:

```text
Space = O(log n)
```

Skewed tree:

```text
h = O(n)
```

Therefore:

```text
Space = O(n)
```

Be careful with nested/repeated recursion such as basic Balanced Binary Tree:

```text
isBalanced()
    +
repeated height()
```

Worst case:

```text
O(n²)
```

---

# 16. Questions Completed

* [x] Custom — Count Total Nodes
* [x] Custom — Sum of All Nodes
* [x] Custom — Count Leaf Nodes
* [x] Custom — Depth of a Specific Node
* [x] Custom — Height of a Specific Node
* [x] LC 104 — Maximum Depth of Binary Tree
* [x] LC 100 — Same Tree
* [x] LC 404 — Sum of Left Leaves
* [x] LC 226 — Invert Binary Tree
* [x] LC 101 — Symmetric Tree
* [x] LC 110 — Balanced Binary Tree

---

# Module 5 Complete ✅

## Key Takeaway

For every tree recursion problem, ask:

```text
1. What is my base case?

2. What should each recursive call RETURN?

3. Do I need:
   - left + right?
   - max(left, right)?
   - left && right?
   - one target path?
   - extra information as a parameter?
   - modification of pointers?

4. What should the CURRENT node do with
   the answers returned by its children?

5. What does the current call return
   back to its parent?
```

## Next

```text
Module 6 — Diameter & Path-Based Recursion

Main Question:
LC 543 — Diameter of Binary Tree
```
