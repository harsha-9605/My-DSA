# 🌳 Trees — Module 3: DFS Traversals

# 1. What is Tree Traversal?

**Traversal** means:

> Visiting every node of a tree in a particular order.

In a Linked List, there is usually one natural direction:

```text
1 → 2 → 3 → 4
```

We can simply do:

```cpp
while (temp != nullptr) {

    cout << temp->val << " ";

    temp = temp->next;
}
```

But a Binary Tree branches:

```text
        1
       / \
      2   3
```

At every node we have three things:

```text
ROOT

LEFT SUBTREE

RIGHT SUBTREE
```

Changing the order in which we process these gives different tree traversals.

---

# 2. DFS — Depth First Search

DFS means:

```text
Depth First Search
```

The idea is:

```text
Go deep into one branch

↓

Finish that branch

↓

Come back

↓

Explore another branch
```

Example:

```text
        1
       / \
      2   3
     /
    4
```

DFS may go:

```text
1
↓
2
↓
4
```

before coming back to explore other branches.

The three main recursive DFS traversals are:

```text
1. Preorder

2. Inorder

3. Postorder
```

---

# 3. Three DFS Traversals

The three traversals are:

## Preorder

```text
ROOT
LEFT
RIGHT
```

Short form:

```text
NLR
```

where:

```text
N = Node / Root
L = Left
R = Right
```

---

## Inorder

```text
LEFT
ROOT
RIGHT
```

Short form:

```text
LNR
```

---

## Postorder

```text
LEFT
RIGHT
ROOT
```

Short form:

```text
LRN
```

---

# 4. Easiest Way to Remember

Notice:

```text
LEFT always comes before RIGHT
```

in these standard recursive traversals.

Only the position of:

```text
ROOT
```

changes.

```text
PREORDER

ROOT LEFT RIGHT
↑
Root comes before
```

```text
INORDER

LEFT ROOT RIGHT
     ↑
Root comes in-between
```

```text
POSTORDER

LEFT RIGHT ROOT
           ↑
Root comes after
```

Therefore:

```text
PRE  → Root before subtrees

IN   → Root in between subtrees

POST → Root after subtrees
```

---

# 5. The One Recursive Template

Do NOT memorize three completely different algorithms.

Remember this one structure:

```cpp
void traversal(TreeNode* root) {

    if (root == nullptr)
        return;

    // POSITION A

    traversal(root->left);

    // POSITION B

    traversal(root->right);

    // POSITION C
}
```

The position where we process:

```cpp
root->val
```

determines the traversal.

```text
POSITION A
↓
PREORDER

POSITION B
↓
INORDER

POSITION C
↓
POSTORDER
```

This is the most important pattern.

---

# 6. Preorder Traversal

Order:

```text
ROOT → LEFT → RIGHT
```

Code:

```cpp
void preorder(TreeNode* root) {

    if (root == nullptr)
        return;

    cout << root->val << " ";

    preorder(root->left);

    preorder(root->right);
}
```

Breakdown:

```cpp
cout << root->val;
```

means:

```text
ROOT
```

Then:

```cpp
preorder(root->left);
```

means:

```text
LEFT SUBTREE
```

Then:

```cpp
preorder(root->right);
```

means:

```text
RIGHT SUBTREE
```

Therefore:

```text
ROOT
LEFT
RIGHT
```

---

# 7. Preorder Example

Tree:

```text
        1
       / \
      2   3
     / \
    4   5
```

Preorder:

```text
ROOT → LEFT → RIGHT
```

Start at:

```text
1
```

Then entire left subtree:

```text
        2
       / \
      4   5
```

gives:

```text
2 4 5
```

Then right subtree:

```text
3
```

Final:

```text
1 2 4 5 3
```

---

# 8. Recursive Thinking for Preorder

Do NOT think only node-by-node:

```text
1
then 2
then 4
then 5...
```

Think in terms of subtrees.

For:

```text
        1
       / \
      2   3
     / \
    4   5
```

Think:

```text
preorder(1)

=

Process 1

+

Completely solve LEFT subtree

+

Completely solve RIGHT subtree
```

Therefore:

```text
1

+

2 4 5

+

3
```

Result:

```text
1 2 4 5 3
```

This subtree thinking is extremely important for harder tree problems.

---

# 9. Inorder Traversal

Order:

```text
LEFT → ROOT → RIGHT
```

Code:

```cpp
void inorder(TreeNode* root) {

    if (root == nullptr)
        return;

    inorder(root->left);

    cout << root->val << " ";

    inorder(root->right);
}
```

Notice the print line is now between the recursive calls.

```cpp
inorder(root->left);     // LEFT

cout << root->val;       // ROOT

inorder(root->right);    // RIGHT
```

Therefore:

```text
LEFT
ROOT
RIGHT
```

---

# 10. Inorder Example

Tree:

```text
        1
       / \
      2   3
     / \
    4   5
```

Start at `1`.

But inorder says:

```text
LEFT first
```

So go to `2`.

Again:

```text
LEFT first
```

Go to `4`.

At `4`:

```text
left = NULL
```

Base case returns.

Now process:

```text
4
```

Then `4`'s right is NULL.

Return to `2`.

Process:

```text
2
```

Then process right subtree:

```text
5
```

Left subtree of `1` gives:

```text
4 2 5
```

Now process root:

```text
1
```

Then right subtree:

```text
3
```

Final:

```text
4 2 5 1 3
```

---

# 11. Inorder and Going Down / Coming Back

This directly connects with recursion.

Remember:

```text
Code BEFORE recursive call

→ executes while going DOWN
```

```text
Code AFTER recursive call

→ executes while coming BACK
```

Consider:

```cpp
inorder(root->left);

cout << root->val;

inorder(root->right);
```

First we keep going:

```text
LEFT
LEFT
LEFT
...
```

until:

```text
root == NULL
```

Then recursion starts returning.

Example:

```text
        1
       /
      2
     /
    4
```

Calls:

```text
inorder(1)

↓

inorder(2)

↓

inorder(4)

↓

inorder(NULL)
```

Base case:

```text
NULL → return
```

Now we come back to `4`.

Print:

```text
4
```

Then right is NULL.

Return to `2`.

Print:

```text
2
```

Return toward `1`.

Print:

```text
1
```

Output:

```text
4 2 1
```

This is the recursion call stack working automatically.

---

# 12. Postorder Traversal

Order:

```text
LEFT → RIGHT → ROOT
```

Code:

```cpp
void postorder(TreeNode* root) {

    if (root == nullptr)
        return;

    postorder(root->left);

    postorder(root->right);

    cout << root->val << " ";
}
```

Breakdown:

```cpp
postorder(root->left);
```

```text
LEFT
```

Then:

```cpp
postorder(root->right);
```

```text
RIGHT
```

Finally:

```cpp
cout << root->val;
```

```text
ROOT
```

Therefore:

```text
LEFT
RIGHT
ROOT
```

---

# 13. Postorder Example

Tree:

```text
        1
       / \
      2   3
     / \
    4   5
```

For root `1`:

First solve entire left subtree:

```text
        2
       / \
      4   5
```

At `2`:

First:

```text
4
```

Then:

```text
5
```

Only after both children are finished:

```text
2
```

So left subtree gives:

```text
4 5 2
```

Then right subtree:

```text
3
```

Finally root:

```text
1
```

Final:

```text
4 5 2 3 1
```

---

# 14. Compare All Three

Tree:

```text
        1
       / \
      2   3
     / \
    4   5
```

## Preorder

```text
ROOT LEFT RIGHT

1 2 4 5 3
```

## Inorder

```text
LEFT ROOT RIGHT

4 2 5 1 3
```

## Postorder

```text
LEFT RIGHT ROOT

4 5 2 3 1
```

---

# 15. Only One Line Changes Position

This is extremely important.

## Preorder

```cpp
cout << root->val;

solve(root->left);

solve(root->right);
```

---

## Inorder

```cpp
solve(root->left);

cout << root->val;

solve(root->right);
```

---

## Postorder

```cpp
solve(root->left);

solve(root->right);

cout << root->val;
```

The recursive structure remains:

```text
LEFT

RIGHT
```

Only:

```text
ROOT PROCESSING
```

moves.

---

# 16. Why Recursion Works Naturally for Trees

Suppose:

```text
            1
          /   \
         2     3
        / \     \
       4   5     6
```

At node `1`:

```text
Current Node = 1

Left Subtree = tree rooted at 2

Right Subtree = tree rooted at 3
```

When we call:

```cpp
solve(root->left);
```

we are saying:

```text
Recursion:

Solve the entire tree
rooted at node 2.
```

When that finishes:

```cpp
solve(root->right);
```

means:

```text
Solve the entire tree
rooted at node 3.
```

So recursion naturally breaks:

```text
BIG TREE

↓

CURRENT NODE

+

LEFT SMALLER TREE

+

RIGHT SMALLER TREE
```

---

# 17. Why We Don't Need `temp = temp->left`

In Module 2 we learned:

```cpp
temp = temp->left;
```

moves a pointer to the left child.

But if we only keep doing:

```cpp
temp = temp->left;
```

we lose the easy path back to other branches.

Example:

```text
        1
       / \
      2   3
     / \
    4   5
```

If we manually move:

```text
1 → 2 → 4
```

we still need to remember:

```text
Go back to 2

↓

Visit 5

↓

Go back to 1

↓

Visit 3
```

Recursion solves this using the:

```text
CALL STACK
```

So:

```cpp
solve(root->left);
```

does not permanently move the original `root`.

It creates another function call with its own local `root`.

---

# 18. Recursive Call Stack

Example:

```text
        1
       /
      2
     /
    4
```

Call:

```text
solve(1)
```

Then:

```text
solve(2)
```

Then:

```text
solve(4)
```

Then:

```text
solve(NULL)
```

Call stack conceptually:

```text
solve(1)

    solve(2)

        solve(4)

            solve(NULL)
```

When NULL returns:

```text
Return to solve(4)
```

When `4` finishes:

```text
Return to solve(2)
```

When `2` finishes:

```text
Return to solve(1)
```

Therefore recursion remembers where to return.

We don't manually maintain parent pointers for basic recursive traversal.

---

# 19. Each Recursive Call Has Its Own `root`

Suppose:

```text
        10
       /  \
      20   30
     / \
    40 50
```

Initial:

```cpp
solve(root);
```

Call 1:

```text
root → 10
```

Then:

```cpp
solve(root->left);
```

Call 2:

```text
root → 20
```

Then:

```cpp
solve(root->left);
```

Call 3:

```text
root → 40
```

Each call has its own local `root`.

```text
Call 1:

root → 10


Call 2:

root → 20


Call 3:

root → 40
```

The original root is NOT globally changed.

---

# 20. Base Case

All three recursive traversals use:

```cpp
if (root == nullptr)
    return;
```

Why?

Every leaf eventually has:

```text
left = NULL

right = NULL
```

Example:

```text
      4
     / \
  NULL NULL
```

When recursion calls:

```cpp
solve(root->left);
```

it becomes:

```text
solve(NULL)
```

Base case hits:

```cpp
if (root == nullptr)
    return;
```

and that branch stops.

---

# 21. Full Preorder Code

```cpp
void preorder(TreeNode* root) {

    if (root == nullptr)
        return;

    cout << root->val << " ";

    preorder(root->left);

    preorder(root->right);
}
```

Pattern:

```text
ROOT
LEFT
RIGHT
```

---

# 22. Full Inorder Code

```cpp
void inorder(TreeNode* root) {

    if (root == nullptr)
        return;

    inorder(root->left);

    cout << root->val << " ";

    inorder(root->right);
}
```

Pattern:

```text
LEFT
ROOT
RIGHT
```

---

# 23. Full Postorder Code

```cpp
void postorder(TreeNode* root) {

    if (root == nullptr)
        return;

    postorder(root->left);

    postorder(root->right);

    cout << root->val << " ";
}
```

Pattern:

```text
LEFT
RIGHT
ROOT
```

---

# 24. Returning a Vector Instead of Printing

On LeetCode, we often need to return:

```cpp
vector<int>
```

instead of printing.

Instead of:

```cpp
cout << root->val;
```

we use:

```cpp
ans.push_back(root->val);
```

---

# 25. Preorder Vector Version

```cpp
class Solution {
public:

    void solve(
        TreeNode* root,
        vector<int>& ans
    ) {

        if (root == nullptr)
            return;

        ans.push_back(root->val);

        solve(root->left, ans);

        solve(root->right, ans);
    }

    vector<int> preorderTraversal(
        TreeNode* root
    ) {

        vector<int> ans;

        solve(root, ans);

        return ans;
    }
};
```

Pattern:

```text
ROOT
LEFT
RIGHT
```

---

# 26. Inorder Vector Version

```cpp
void inorder(
    TreeNode* root,
    vector<int>& ans
) {

    if (root == nullptr)
        return;

    inorder(root->left, ans);

    ans.push_back(root->val);

    inorder(root->right, ans);
}
```

Pattern:

```text
LEFT
ROOT
RIGHT
```

---

# 27. Postorder Vector Version

```cpp
void postorder(
    TreeNode* root,
    vector<int>& ans
) {

    if (root == nullptr)
        return;

    postorder(root->left, ans);

    postorder(root->right, ans);

    ans.push_back(root->val);
}
```

Pattern:

```text
LEFT
RIGHT
ROOT
```

---

# 28. Bigger Example

Tree:

```text
            1
          /   \
         2     3
        / \     \
       4   5     6
          / \
         7   8
```

## Preorder

```text
ROOT LEFT RIGHT
```

Result:

```text
1 2 4 5 7 8 3 6
```

---

## Inorder

```text
LEFT ROOT RIGHT
```

Result:

```text
4 2 7 5 8 1 3 6
```

---

## Postorder

```text
LEFT RIGHT ROOT
```

Result:

```text
4 7 8 5 2 6 3 1
```

---

# 29. Another Example

Tree:

```text
             10
           /    \
          5      20
         / \    /  \
        3   7  15   25
             \
              8
```

## Preorder

```text
ROOT LEFT RIGHT
```

```text
10 5 3 7 8 20 15 25
```

Important:

Preorder always starts with the root.

So:

```text
10
```

must be first.

---

## Inorder

```text
LEFT ROOT RIGHT
```

```text
3 5 7 8 10 15 20 25
```

---

## Postorder

```text
LEFT RIGHT ROOT
```

```text
3 8 7 5 15 25 20 10
```

Postorder always processes the root after both subtrees.

Therefore:

```text
10
```

comes last.

---

# 30. Important BST Connection

For a normal Binary Tree:

```text
Inorder traversal
does NOT necessarily give sorted order.
```

But for a:

```text
Binary Search Tree (BST)
```

Inorder traversal gives:

```text
SORTED ASCENDING ORDER
```

Example BST:

```text
        4
       / \
      2   6
     / \ / \
    1  3 5  7
```

Inorder:

```text
1 2 3 4 5 6 7
```

Remember this for the BST module later.

---

# 31. Time Complexity

For all three traversals:

```text
Preorder

Inorder

Postorder
```

every node is visited exactly once.

If there are:

```text
n nodes
```

then:

```text
Time Complexity = O(n)
```

Why?

```text
Each node
↓
Visited once
↓
Constant work per node
```

Therefore:

```text
O(n)
```

---

# 32. Recurrence Intuition

For a tree:

```text
          ROOT
         /    \
      LEFT    RIGHT
```

Traversal performs:

```text
Work at root

+

Traverse left subtree

+

Traverse right subtree
```

So:

```text
T(n)

=

T(left subtree)

+

T(right subtree)

+

O(1)
```

Across the entire tree, every node is processed once.

Therefore:

```text
T(n) = O(n)
```

---

# 33. Why Two Recursive Calls Does NOT Mean O(2^n)

We write:

```cpp
solve(root->left);

solve(root->right);
```

There are two recursive calls.

But this does NOT automatically mean:

```text
O(2^n)
```

because the calls process:

```text
Different subtrees
```

Each node belongs to one subtree path and is visited once.

So total work is:

```text
O(n)
```

This is different from something like naive Fibonacci recursion where the same subproblems are repeatedly recomputed.

---

# 34. Space Complexity

Recursive space depends on:

```text
Maximum number of active
recursive calls at one time
```

That equals the depth of the deepest recursive path.

Therefore:

```text
Space = O(h)
```

where:

```text
h = height of tree
```

---

# 35. Balanced Tree Space

Balanced tree:

```text
            1
         /     \
        2       3
       / \     / \
      4   5   6   7
```

Height:

```text
h ≈ log n
```

Therefore recursive stack:

```text
O(log n)
```

---

# 36. Skewed Tree Space

Skewed tree:

```text
1
 \
  2
   \
    3
     \
      4
       \
        5
```

Height:

```text
h ≈ n
```

Therefore:

```text
Recursive Stack = O(n)
```

---

# 37. Final Complexity

For recursive DFS traversals:

```text
TIME

O(n)
```

because every node is visited once.

Space:

```text
O(h)
```

where `h` is tree height.

Therefore:

```text
Balanced Tree

Time  = O(n)

Space = O(log n)
```

Worst-case skewed tree:

```text
Time  = O(n)

Space = O(n)
```

---

# 38. Traversal Mental Model

Whenever you see:

```cpp
void solve(TreeNode* root) {

    if (root == nullptr)
        return;

    // ?

    solve(root->left);

    // ?

    solve(root->right);

    // ?
}
```

Immediately think:

```text
Before LEFT
↓
PREORDER position


Between LEFT and RIGHT
↓
INORDER position


After RIGHT
↓
POSTORDER position
```

Visual:

```text
             solve(root)
                 |
        ┌────────┼────────┐
        │        │        │
       PRE      LEFT      IN
                 |
               RIGHT
                 |
                POST
```

Simpler:

```text
PROCESS ROOT
solve(left)
solve(right)

= PREORDER
```

```text
solve(left)
PROCESS ROOT
solve(right)

= INORDER
```

```text
solve(left)
solve(right)
PROCESS ROOT

= POSTORDER
```

---

# 39. Most Important Recursive Thinking

Do NOT think:

```text
How do I manually visit
every individual node?
```

Think:

```text
At current ROOT:

1. Handle current node
   at the correct position

2. Trust recursion to handle
   the ENTIRE left subtree

3. Trust recursion to handle
   the ENTIRE right subtree
```

For example:

```cpp
preorder(root->left);
```

does NOT mean:

```text
Visit only the left child.
```

It means:

```text
Perform preorder traversal
on the ENTIRE tree rooted
at the left child.
```

This distinction is extremely important.

---

# 40. Preorder / Inorder / Postorder in One View

```text
PREORDER
────────

ROOT
 ↓
LEFT
 ↓
RIGHT

Code:

process(root)

solve(left)

solve(right)
```

```text
INORDER
───────

LEFT
 ↓
ROOT
 ↓
RIGHT

Code:

solve(left)

process(root)

solve(right)
```

```text
POSTORDER
─────────

LEFT
 ↓
RIGHT
 ↓
ROOT

Code:

solve(left)

solve(right)

process(root)
```

---

# 41. Common Mistakes

## Mistake 1 — Starting Preorder From Leftmost Node

Wrong thinking:

```text
Go left first
```

for preorder.

Correct:

```text
PREORDER

ROOT FIRST
```

So preorder always starts with the root of the current tree/subtree.

---

## Mistake 2 — Thinking Two Recursive Calls Means O(2^n)

Wrong:

```text
Two calls
→ O(2^n)
```

Correct:

```text
Each call handles different subtrees.

Every node visited once.

→ O(n)
```

---

## Mistake 3 — Saying Recursive Space Is Always O(n)

More precise:

```text
Space = O(h)
```

Then:

```text
Balanced:

O(log n)
```

```text
Worst-case skewed:

O(n)
```

---

## Mistake 4 — Thinking `root` Changes Globally

When:

```cpp
solve(root->left);
```

the new recursive call gets:

```text
root = left child
```

locally.

The previous call still has its own original `root`.

---

## Mistake 5 — Thinking `solve(root->left)` Handles Only One Node

It handles:

```text
ENTIRE LEFT SUBTREE
```

because that recursive call again processes:

```text
its root

its left subtree

its right subtree
```

---

# 42. Quick Revision Table

| Traversal | Order               | Root Position           |
| --------- | ------------------- | ----------------------- |
| Preorder  | Root → Left → Right | Before recursive calls  |
| Inorder   | Left → Root → Right | Between recursive calls |
| Postorder | Left → Right → Root | After recursive calls   |

Complexity for all:

```text
Time = O(n)

Recursive Stack = O(h)
```

Balanced:

```text
O(log n) stack
```

Skewed:

```text
O(n) stack
```

---

# 43. Ultra-Short Revision

```text
PREORDER

NLR

Root Left Right
```

```text
INORDER

LNR

Left Root Right
```

```text
POSTORDER

LRN

Left Right Root
```

One template:

```cpp
if (root == nullptr)
    return;

// PRE

solve(root->left);

// IN

solve(root->right);

// POST
```

Complexity:

```text
Time  = O(n)

Space = O(h)
```

Core recursion idea:

```text
Current Node

+

Entire Left Subtree

+

Entire Right Subtree
```

---

# 44. Module 3 Checklist

I should now understand:

* [x] What traversal means
* [x] DFS meaning
* [x] Preorder traversal
* [x] `ROOT → LEFT → RIGHT`
* [x] Inorder traversal
* [x] `LEFT → ROOT → RIGHT`
* [x] Postorder traversal
* [x] `LEFT → RIGHT → ROOT`
* [x] Why only root-processing position changes
* [x] One generic recursive traversal template
* [x] Recursive preorder code
* [x] Recursive inorder code
* [x] Recursive postorder code
* [x] Printing traversal values
* [x] Storing traversal in `vector<int>`
* [x] Base case `root == nullptr`
* [x] Going down vs coming back
* [x] Recursive call stack behavior
* [x] Each call has its own local `root`
* [x] `solve(root->left)` means entire left subtree
* [x] `solve(root->right)` means entire right subtree
* [x] Why recursion remembers where to return
* [x] Why two recursive calls do not mean `O(2^n)`
* [x] Time complexity `O(n)`
* [x] Space complexity `O(h)`
* [x] Balanced tree stack `O(log n)`
* [x] Skewed tree stack `O(n)`
* [x] BST inorder gives sorted order

# Module 3 — COMPLETE ✅

Next:

```text
MODULE 4

BFS / LEVEL ORDER TRAVERSAL

        1
       / \
      2   3
     / \ / \
    4  5 6  7

Traversal:

1
2 3
4 5 6 7

Core Tool:

QUEUE

Main Pattern:

push root
↓
while queue not empty
↓
pop front
↓
process node
↓
push left
↓
push right

We will learn:

- Basic Level Order Traversal
- Why Queue is used
- Queue dry run
- Level-by-level processing
- `queue.size()` trick
- `vector<vector<int>>`
- Time and Space Complexity
```
