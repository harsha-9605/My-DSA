# 🌳 Trees — Module 2: TreeNode, Pointers & Tree Construction

# 1. Main Idea

A Binary Tree node is very similar to a Linked List node.

Linked List:

```cpp id="q09yzv"
struct ListNode {
    int val;
    ListNode* next;
};
```

Binary Tree:

```cpp id="u05cb8"
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};
```

Main structural difference:

```text id="f7afl9"
LINKED LIST

Node
 |
 next
 ↓
Node
 |
 next
 ↓
Node
```

Binary Tree:

```text id="29uy2e"
             Node
            /    \
         left    right
          ↓        ↓
        Node      Node
```

So:

```text id="qqz1ae"
Linked List Node
→ usually 1 next pointer

Binary Tree Node
→ 2 child pointers
   left
   right
```

The pointer concepts are the SAME.

---

# 2. Linked List vs Binary Tree Pointer Syntax

Linked List:

```cpp id="ky47yz"
head->val

head->next

head->next->val
```

Binary Tree:

```cpp id="t3nblf"
root->val

root->left

root->right

root->left->val
```

The `->` operator has exactly the same meaning:

```text id="tsbnyh"
Follow the pointer
↓
Access something inside that node
```

So knowledge of Linked List pointers transfers directly to Trees.

---

# 3. Binary Tree Node Structure

Basic structure:

```cpp id="2ujnxs"
struct TreeNode {
    int val;

    TreeNode* left;
    TreeNode* right;
};
```

Every node stores:

```text id="scvbqa"
┌─────────────────┐
│      val        │
│                 │
│ left pointer    │
│ right pointer   │
└─────────────────┘
```

Example:

```text id="oh4ybv"
        10
       /  \
      20   30
```

Conceptually:

```text id="96mb8d"
Node 10

val   = 10

left  → Node 20

right → Node 30
```

Important:

> A node does not physically contain its children.

It stores the **addresses/pointers** of its child nodes.

---

# 4. TreeNode Constructor

A common C++ structure:

```cpp id="lhws63"
struct TreeNode {

    int val;

    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {

        val = x;

        left = nullptr;

        right = nullptr;
    }
};
```

When we write:

```cpp id="yebpgd"
TreeNode* node = new TreeNode(5);
```

A new node is created:

```text id="e4iw9u"
node
 ↓

┌───────────────┐
│ val = 5       │
│               │
│ left = NULL   │
│ right = NULL  │
└───────────────┘
```

Initially:

```cpp id="dx3owk"
node->left == nullptr;

node->right == nullptr;
```

Therefore the node currently has:

```text id="tcm8g2"
0 children
```

So it is a:

```text id="jkg0fi"
Leaf Node
```

---

# 5. What is `TreeNode* root`?

Example:

```cpp id="8z3t79"
TreeNode* root = new TreeNode(10);
```

`root` is a:

```text id="x4vbg1"
POINTER
```

It stores the address of the node containing `10`.

Conceptually:

```text id="fwviyu"
root
 │
 │ address
 ↓

┌──────────────┐
│ val = 10     │
│ left = NULL  │
│ right = NULL │
└──────────────┘
```

Important:

```text id="1vwfzw"
root is NOT the entire tree.
```

`root` only points to the first/top node.

But through that node's pointers:

```text id="6x0j88"
root
 ↓
children
 ↓
their children
 ↓
...
```

we can access the entire tree.

---

# 6. Same Idea as Linked List Head

Linked List:

```cpp id="aqfgn8"
ListNode* head;
```

`head` points to the first node.

It does NOT physically contain the whole list.

```text id="udfokm"
head
 ↓

[10] → [20] → [30]
```

Similarly:

```cpp id="pnt0ps"
TreeNode* root;
```

```text id="ftvl7f"
root
 ↓

        10
       /  \
      20   30
```

`root` points only to node `10`.

But from node `10` we can reach:

```text id="vvpxmb"
20
30
and all nodes below them
```

---

# 7. `root->val`

Suppose:

```cpp id="z3crzv"
TreeNode* root = new TreeNode(10);
```

Then:

```cpp id="og6q81"
root->val
```

means:

```text id="a0r0cg"
Go to the node pointed to by root

↓

Access its val
```

Result:

```text id="7mccuy"
10
```

Therefore:

```cpp id="th0o2w"
cout << root->val;
```

prints:

```text id="6sj4bc"
10
```

Technically:

```cpp id="a45e8k"
root->val
```

is equivalent to:

```cpp id="2dfr8c"
(*root).val
```

But normally we use:

```cpp id="8hd2op"
root->val
```

---

# 8. `root->left`

```cpp id="jnx46s"
root->left
```

means:

```text id="60z4kk"
Access the LEFT CHILD POINTER
stored inside the root node.
```

Initially:

```text id="2rclrr"
root
 ↓

┌──────────────┐
│ val = 10     │
│ left = NULL  │
│ right = NULL │
└──────────────┘
```

Therefore:

```cpp id="wbm4me"
root->left == nullptr;
```

because no left child exists yet.

---

# 9. Adding a Left Child

```cpp id="nz6yd1"
root->left = new TreeNode(20);
```

First:

```cpp id="wzdb69"
new TreeNode(20)
```

creates a node.

Then its address is stored in:

```cpp id="kmlm7i"
root->left
```

Now:

```text id="om3efx"
        10
       /
      20
```

Conceptually:

```text id="fqyz69"
Node 10

left pointer
     |
     ↓

Node 20
```

So:

```cpp id="j3xw4g"
root->left->val
```

returns:

```text id="pm7ez7"
20
```

---

# 10. Adding a Right Child

```cpp id="1n2a4w"
root->right = new TreeNode(30);
```

Now:

```text id="36o65f"
        10
       /  \
      20   30
```

So:

```cpp id="vdf9qi"
root->left->val
```

gives:

```text id="kzxfg7"
20
```

and:

```cpp id="hm4f44"
root->right->val
```

gives:

```text id="0pdqvi"
30
```

---

# 11. Understanding Chained `->`

Suppose:

```text id="mm4a3b"
        10
       /  \
      20   30
     /
    40
```

Construction:

```cpp id="8r5qsm"
TreeNode* root = new TreeNode(10);

root->left = new TreeNode(20);

root->right = new TreeNode(30);

root->left->left = new TreeNode(40);
```

Now consider:

```cpp id="l9mjds"
root->left->left
```

Read from left to right.

```text id="x2fvq8"
root
 ↓
10

root->left
 ↓
20

root->left->left
 ↓
40
```

Therefore:

```cpp id="ymt42s"
root->left->left->val
```

returns:

```text id="iwf4t7"
40
```

Think of chained `->` as following a path through the tree.

---

# 12. Manual Tree Construction

Suppose we want:

```text id="0cpsfa"
            1
          /   \
         2     3
        / \     \
       4   5     6
          / \
         7   8
```

Create root:

```cpp id="v5zwbd"
TreeNode* root = new TreeNode(1);
```

Add children of `1`:

```cpp id="79b2n7"
root->left = new TreeNode(2);

root->right = new TreeNode(3);
```

Add children of `2`:

```cpp id="uqkn49"
root->left->left = new TreeNode(4);

root->left->right = new TreeNode(5);
```

Add child of `3`:

```cpp id="9kgk49"
root->right->right = new TreeNode(6);
```

Add children of `5`:

```cpp id="92xka4"
root->left->right->left =
    new TreeNode(7);

root->left->right->right =
    new TreeNode(8);
```

Complete code:

```cpp id="56ig03"
#include <iostream>
using namespace std;

struct TreeNode {

    int val;

    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {

        val = x;

        left = nullptr;
        right = nullptr;
    }
};

int main() {

    TreeNode* root = new TreeNode(1);

    root->left = new TreeNode(2);

    root->right = new TreeNode(3);

    root->left->left =
        new TreeNode(4);

    root->left->right =
        new TreeNode(5);

    root->right->right =
        new TreeNode(6);

    root->left->right->left =
        new TreeNode(7);

    root->left->right->right =
        new TreeNode(8);

    return 0;
}
```

This creates:

```text id="o6nq2q"
            1
          /   \
         2     3
        / \     \
       4   5     6
          / \
         7   8
```

---

# 13. Pointer Path Example

Consider:

```cpp id="7ayk8x"
root->left->right->left->val
```

Follow it:

```text id="99vwvg"
root
 ↓
1

left
 ↓
2

right
 ↓
5

left
 ↓
7
```

Therefore:

```text id="c7u20v"
Answer = 7
```

Another:

```cpp id="vkk0ms"
root->right->right->val
```

Path:

```text id="pt7s5j"
root
 ↓
1

right
 ↓
3

right
 ↓
6
```

Answer:

```text id="n51h61"
6
```

---

# 14. `nullptr` in Trees

Suppose:

```text id="iukr09"
        1
       / \
      2   3
```

Node `2` has no children.

Internally:

```text id="h4ve98"
Node 2

left  = nullptr

right = nullptr
```

The actual pointer structure can be imagined as:

```text id="bb76cp"
            1
          /   \
         2     3
        / \   / \
     NULL NULL NULL NULL
```

We normally don't draw these NULL pointers.

But recursion reaches them.

This is why the most common tree recursion base case is:

```cpp id="39jjz4"
if (root == nullptr)
    return;
```

---

# 15. How Recursion Stops at NULL

Suppose:

```text id="5f5v43"
        1
       /
      2
```

At node `2`:

```cpp id="1d5lr9"
solve(root->left);
```

But:

```text id="xtgqkq"
2's left = NULL
```

So:

```text id="c24zpf"
solve(NULL)
```

Base case:

```cpp id="t1s6k3"
if (root == nullptr)
    return;
```

hits.

Then recursion stops for that branch.

Same for the right pointer.

---

# 16. Why Tree Functions Receive `TreeNode* root`

Most tree functions look like:

```cpp id="lxifsv"
void solve(TreeNode* root) {

}
```

Why?

Because every function call needs to know:

```text id="otdt1p"
Which node/subtree
am I currently processing?
```

Example:

```text id="2r40bk"
          10
         /  \
       20    30
      / \
    40   50
```

Initial call:

```cpp id="dqaw0i"
solve(root);
```

Current:

```text id="asv6xi"
root → 10
```

Then:

```cpp id="j4m0cb"
solve(root->left);
```

`root->left` contains the address of node `20`.

A new recursive call is created.

Inside that call:

```text id="2m2lpd"
root → 20
```

So the subtree becomes:

```text id="ymt0zx"
        20
       /  \
      40   50
```

From this function call's perspective:

```text id="kqjlgq"
20 is now the root.
```

More precisely:

```text id="4zyazn"
20 is the root
of the CURRENT SUBTREE.
```

---

# 17. `root` Does NOT Change Globally

This is extremely important.

Suppose:

```cpp id="d54njl"
solve(root->left);
```

Original function call:

```text id="bzf21l"
Call 1

root → 10
```

New recursive call:

```text id="t6wum7"
Call 2

root → 20
```

They are separate function calls.

Conceptually:

```text id="cs5d2y"
CALL 1

root → 10

          10
         /  \
       20    30


CALL 2

root → 20

        20
       /  \
      40   50
```

The original call still has:

```text id="4xmh6y"
root → 10
```

The recursive call has:

```text id="d77b0c"
root → 20
```

This happens because the pointer is passed as a function argument.

Each function call gets its own local parameter.

---

# 18. Most Important Meaning of `root`

Inside a recursive tree function:

```cpp id="xjmwnv"
solve(TreeNode* root)
```

`root` means:

```text id="73pt6c"
Root of the CURRENT SUBTREE
that this function call is processing.
```

Example:

```text id="6t2a3p"
            10
           /  \
          20   30
         / \
        40 50
```

Call:

```text id="96xb0p"
solve(10)
```

Current subtree:

```text id="kvvufx"
            10
           /  \
          20   30
         / \
        40 50
```

Then:

```text id="yd3b66"
solve(20)
```

Current subtree:

```text id="swwot3"
        20
       /  \
      40   50
```

Then:

```text id="bnaxdl"
solve(40)
```

Current subtree:

```text id="n96b5u"
40
```

Then eventually:

```text id="x8r8xa"
solve(NULL)
```

Base case.

---

# 19. Tree Recursion vs Linked List Recursion

Linked List recursion:

```cpp id="z8eyp8"
solve(head->next);
```

Mental model:

```text id="8vs9ak"
Current Node
+
Remaining Linked List
```

Tree recursion:

```cpp id="knksjd"
solve(root->left);

solve(root->right);
```

Mental model:

```text id="7xg67v"
Current Node

+

Left Subtree

+

Right Subtree
```

Diagram:

```text id="7i0gwl"
              ROOT
             /    \
            /      \
      LEFT           RIGHT
     SUBTREE        SUBTREE
        ↓              ↓
    recursion       recursion
```

This is why recursion is extremely natural for trees.

---

# 20. Trees Are Not Only Solved With Recursion

A useful clarification:

Trees can be solved using:

```text id="6pxi8x"
1. Recursion

2. Stack

3. Queue
```

Recursive DFS is extremely common because trees are naturally recursive structures.

But we also use:

```text id="igzdu1"
Stack
↓
Iterative DFS
```

and:

```text id="k0jupq"
Queue
↓
BFS / Level Order Traversal
```

So:

```text id="mvz6vq"
Trees ≠ only recursion
```

But recursion is one of the most natural and important approaches.

---

# 21. LeetCode TreeNode Structure

LeetCode commonly gives:

```cpp id="q8l8as"
struct TreeNode {

    int val;

    TreeNode* left;

    TreeNode* right;

    TreeNode()
        : val(0),
          left(nullptr),
          right(nullptr) {}

    TreeNode(int x)
        : val(x),
          left(nullptr),
          right(nullptr) {}

    TreeNode(
        int x,
        TreeNode* left,
        TreeNode* right
    )
        : val(x),
          left(left),
          right(right) {}
};
```

Don't get confused by the constructors.

The important part is still:

```cpp id="cyb9do"
int val;

TreeNode* left;

TreeNode* right;
```

---

# 22. Trees Are Usually Already Created on LeetCode

For most LeetCode tree problems, you receive:

```cpp id="o85ecp"
TreeNode* root
```

Example:

```cpp id="49o9md"
class Solution {
public:

    int maxDepth(TreeNode* root) {

    }
};
```

You normally do NOT need to manually write:

```cpp id="vdb2x8"
new TreeNode(...)
```

LeetCode already constructs the tree.

Your job is to:

```text id="49op9k"
Traverse it

Process it

Return the answer
```

Manual construction is mainly useful for:

```text id="4w57i5"
Learning

Testing locally

Understanding pointers
```

---

# 23. Copying a Tree Pointer Does NOT Copy the Node

Suppose:

```cpp id="t9by1h"
TreeNode* temp = root->left;
```

If:

```text id="yqs42m"
        10
       /
      20
```

then:

```text id="scjj7u"
root->left
```

and:

```text id="18shkw"
temp
```

both point to the SAME node.

```text id="q1h47v"
root->left ──────┐
                 ↓

              Node 20

                 ↑
temp ────────────┘
```

We copied:

```text id="tlr9e7"
the ADDRESS
```

not:

```text id="skk7hk"
the entire Node
```

This is the same pointer behavior as Linked Lists.

---

# 24. Quick Pointer Rules

```cpp id="5tt90n"
root->val
```

means:

```text id="e28ajm"
Value of current node
```

---

```cpp id="k59hxk"
root->left
```

means:

```text id="cn90kk"
Pointer/address of left child
```

---

```cpp id="yj5cc4"
root->right
```

means:

```text id="t2k5q6"
Pointer/address of right child
```

---

```cpp id="w2esza"
root->left->val
```

means:

```text id="iqlqzj"
Value of left child
```

---

```cpp id="w61nsr"
root->left->right
```

means:

```text id="i4ihfj"
Pointer to the right child
of the left child
```

---

# 25. Creating a Tree Using User Input

Manual construction:

```cpp id="fys0ge"
root->left = new TreeNode(2);
```

works when we already know the exact tree.

But suppose the user wants to enter the tree using:

```cpp id="b9bgye"
cin >> data;
```

We need some way to tell the program:

```text id="s7ih2q"
Which node is left child?

Which node is right child?

Where are NULL children?
```

Unlike an array, simply entering:

```text id="3eybna"
1 2 3 4 5
```

does not uniquely describe every possible normal binary tree.

Therefore we need an **input convention**.

Two common ways are:

```text id="97ztt1"
1. Recursive Preorder Input

2. Level Order Input
```

---

# 26. Method 1 — Recursive Tree Construction Using `cin`

We can use:

```text id="wbj05p"
-1 = NULL
```

Suppose we want:

```text id="tpc1rv"
        1
       / \
      2   3
```

We can enter nodes in preorder:

```text id="1ol6w3"
1 2 -1 -1 3 -1 -1
```

Meaning:

```text id="ldf0xn"
1
↓
create node 1

2
↓
create left child 2

-1
↓
2's left = NULL

-1
↓
2's right = NULL

3
↓
create right child 3

-1
↓
3's left = NULL

-1
↓
3's right = NULL
```

---

# 27. Recursive Build Function

```cpp id="4wbmcq"
TreeNode* buildTree() {

    int data;

    cin >> data;

    if (data == -1) {
        return nullptr;
    }

    TreeNode* root =
        new TreeNode(data);

    root->left =
        buildTree();

    root->right =
        buildTree();

    return root;
}
```

Main:

```cpp id="4c04uq"
int main() {

    TreeNode* root =
        buildTree();

    return 0;
}
```

---

# 28. Understanding Recursive Construction

Code:

```cpp id="nqz9em"
TreeNode* buildTree() {

    int data;

    cin >> data;

    if (data == -1)
        return nullptr;

    TreeNode* root =
        new TreeNode(data);

    root->left =
        buildTree();

    root->right =
        buildTree();

    return root;
}
```

This follows:

```text id="57gvmk"
ROOT

↓

Build entire LEFT subtree

↓

Build entire RIGHT subtree
```

This is preorder-style construction:

```text id="sngppf"
ROOT
LEFT
RIGHT
```

---

# 29. Dry Run of Recursive Input

Input:

```text id="k62o9r"
1 2 -1 -1 3 -1 -1
```

First:

```text id="nxf22m"
data = 1

Create Node 1
```

Then:

```cpp id="m5ch67"
root->left = buildTree();
```

Next input:

```text id="9t5i5s"
2
```

Create:

```text id="9ewt3a"
Node 2
```

Then build `2`'s left.

Input:

```text id="m0fn6p"
-1
```

Return:

```text id="9b0pq7"
NULL
```

Build `2`'s right.

Input:

```text id="7w5f4z"
-1
```

Return:

```text id="o51b2p"
NULL
```

Node `2` complete:

```text id="yemdhw"
    2
   / \
NULL NULL
```

Return node `2` to the previous call.

Now:

```text id="kxnb23"
1
/
2
```

Then build `1`'s right.

Input:

```text id="lhjnpc"
3
```

Create node `3`.

Then:

```text id="vh0d1r"
-1 → left NULL

-1 → right NULL
```

Final:

```text id="v7sl9d"
        1
       / \
      2   3
```

---

# 30. Full Recursive User-Input Program

```cpp id="3q22y4"
#include <iostream>
using namespace std;

struct TreeNode {

    int val;

    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {

        val = x;

        left = nullptr;

        right = nullptr;
    }
};

TreeNode* buildTree() {

    int data;

    cin >> data;

    if (data == -1) {

        return nullptr;
    }

    TreeNode* root =
        new TreeNode(data);

    root->left =
        buildTree();

    root->right =
        buildTree();

    return root;
}

int main() {

    cout << "Enter tree: ";

    TreeNode* root =
        buildTree();

    return 0;
}
```

Example input:

```text id="90ukgs"
1 2 -1 -1 3 -1 -1
```

Creates:

```text id="a7ddpv"
        1
       / \
      2   3
```

---

# 31. Larger Recursive Input Example

To create:

```text id="9cfhjg"
            1
          /   \
         2     3
        / \     \
       4   5     6
```

Preorder input with `-1` representing NULL:

```text id="crzswf"
1
2
4
-1
-1
5
-1
-1
3
-1
6
-1
-1
```

On one line:

```text id="4kk5sz"
1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
```

Pattern:

```text id="7fzmdx"
Node

↓

Entire Left Subtree

↓

Entire Right Subtree
```

---

# 32. Why `return root`?

In:

```cpp id="eg1qct"
TreeNode* buildTree()
```

the function returns:

```text id="c89pda"
Pointer to the root
of the tree/subtree it created.
```

Example:

```cpp id="r5is0r"
root->left = buildTree();
```

Suppose `buildTree()` creates:

```text id="t2fgxq"
        2
       / \
      4   5
```

It returns:

```text id="wfyngj"
Pointer to Node 2
```

That pointer is stored in:

```cpp id="byjdv6"
root->left
```

So the entire subtree becomes connected automatically:

```text id="61ws2u"
        1
       /
      2
     / \
    4   5
```

This is an extremely important recursion idea:

```text id="6hvgmo"
A recursive call can build
an entire subtree

and return only its ROOT POINTER.
```

Because that root pointer gives access to everything below it.

---

# 33. Method 2 — Level Order User Input

Another common method uses a:

```text id="2uvzo2"
QUEUE
```

This creates the tree:

```text id="bbd2zb"
Level by Level
```

For example:

```text id="99w5yw"
        1
       / \
      2   3
     / \
    4   5
```

We can ask:

```text id="kcdtwj"
Enter root

Enter left child of 1
Enter right child of 1

Enter left child of 2
Enter right child of 2

Enter left child of 3
Enter right child of 3

...
```

Again:

```text id="2yt7v4"
-1 = no child
```

---

# 34. Level Order Construction Code

```cpp id="uqnmuv"
#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {

    int val;

    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {

        val = x;

        left = nullptr;

        right = nullptr;
    }
};

TreeNode* buildLevelOrder() {

    int data;

    cout << "Enter root: ";

    cin >> data;

    if (data == -1)
        return nullptr;

    TreeNode* root =
        new TreeNode(data);

    queue<TreeNode*> q;

    q.push(root);

    while (!q.empty()) {

        TreeNode* current =
            q.front();

        q.pop();

        int leftData;

        cout
            << "Enter left child of "
            << current->val
            << ": ";

        cin >> leftData;

        if (leftData != -1) {

            current->left =
                new TreeNode(leftData);

            q.push(current->left);
        }

        int rightData;

        cout
            << "Enter right child of "
            << current->val
            << ": ";

        cin >> rightData;

        if (rightData != -1) {

            current->right =
                new TreeNode(rightData);

            q.push(current->right);
        }
    }

    return root;
}
```

---

# 35. How Level Order Construction Works

Suppose input creates:

```text id="11t11f"
        1
       / \
      2   3
```

First:

```text id="l9ykwy"
Create root = 1

Queue:

[1]
```

Pop `1`.

Ask:

```text id="ct0x2r"
left child of 1?
```

Input:

```text id="gn7gqq"
2
```

Create node `2`.

Push it:

```text id="f26ee3"
Queue:

[2]
```

Ask:

```text id="rkw7pu"
right child of 1?
```

Input:

```text id="d8s98z"
3
```

Create node `3`.

Push:

```text id="e2ltb5"
Queue:

[2,3]
```

Then process node `2`.

Then node `3`.

This is exactly the BFS idea:

```text id="a3eh5m"
Process nodes level-by-level
using a queue.
```

We will properly learn this in the BFS/Level Order module.

---

# 36. Which Tree Construction Method Matters More?

For interviews and LeetCode:

```text id="l7q9tk"
Manual construction
→ mainly for understanding/testing

Recursive cin construction
→ useful for understanding recursion

Level-order construction
→ useful for understanding queues/BFS

LeetCode
→ usually tree is already provided
```

You do NOT need to memorize complex tree input code for placements.

The important thing is understanding how it works.

The recursive version is especially useful because it reinforces:

```text id="5iq5bd"
root
+
left subtree
+
right subtree
```

---

# 37. Important User-Input Limitation

If we simply input:

```text id="p51nqj"
1 2 3 4 5
```

we do NOT necessarily know the exact shape of a general binary tree.

For example, `2` could be:

```text id="k0t42a"
left child
```

or another node could be missing.

Therefore we need some representation for:

```text id="m5m1pc"
NULL children
```

Common choices:

```text id="m0zdv7"
-1

null

#
```

For learning C++ input, we commonly use:

```text id="jyzm55"
-1
```

Note:

If `-1` itself must be a valid node value, then choose a different input convention instead of using `-1` as the null marker.

---

# 38. Module 2 Core Mental Model

A tree node:

```text id="tyeqe2"
┌─────────────┐
│ value       │
│             │
│ left  ──────┼──→ Left Child
│ right ──────┼──→ Right Child
└─────────────┘
```

Tree:

```text id="j8ve40"
             root
              ↓

             Node
            /    \
         left    right
          ↓        ↓
        Node      Node
```

Pointers work exactly like Linked Lists.

The important new recursive idea is:

```text id="74am71"
Each node can be treated
as the root of its own subtree.
```

Therefore:

```cpp id="spjjsi"
solve(root->left);
```

means:

```text id="e7f3sz"
Give recursion the entire
LEFT SUBTREE.
```

And inside that recursive call:

```text id="f26y7c"
root
```

now locally points to:

```text id="km5s63"
the root of that subtree.
```

It does NOT globally change the original root.

---

# 39. Module 2 Quick Revision

## Node Structure

```cpp id="eh7jxk"
struct TreeNode {

    int val;

    TreeNode* left;

    TreeNode* right;
};
```

---

## Create Node

```cpp id="0jbp69"
TreeNode* root =
    new TreeNode(10);
```

---

## Create Left Child

```cpp id="zbr4gc"
root->left =
    new TreeNode(20);
```

---

## Create Right Child

```cpp id="oq62qh"
root->right =
    new TreeNode(30);
```

---

## Access Current Value

```cpp id="b19p1b"
root->val
```

---

## Access Left Child

```cpp id="8mybsr"
root->left
```

---

## Access Right Child

```cpp id="k05h4m"
root->right
```

---

## Common Recursive Base Case

```cpp id="8f1gx3"
if (root == nullptr)
    return;
```

---

## Recursive Subtrees

```cpp id="u8dr04"
solve(root->left);

solve(root->right);
```

---

# 40. Final Module 2 Checklist

I should now understand:

* [x] Binary Tree node structure
* [x] Similarity with Linked List nodes
* [x] `TreeNode*`
* [x] What `root` stores
* [x] `root->val`
* [x] `root->left`
* [x] `root->right`
* [x] Chained `->`
* [x] `nullptr` children
* [x] Creating nodes using `new`
* [x] Connecting left/right children
* [x] Manual tree construction
* [x] Pointer copying does not copy nodes
* [x] Each recursive call has its own local `root`
* [x] `root` means root of the current subtree
* [x] Original root is not globally changed by `solve(root->left)`
* [x] Linked List recursion vs Tree recursion
* [x] Trees can use recursion, stacks, and queues
* [x] LeetCode usually provides the tree already
* [x] Recursive tree construction using `cin`
* [x] Using `-1` to represent NULL
* [x] Why recursive `buildTree()` returns a root pointer
* [x] Basic level-order construction using a queue
* [x] Why plain values alone may not describe a general tree's shape

# Module 2 — COMPLETE ✅

Next:

```text id="s54chv"
MODULE 3

DFS TREE TRAVERSALS

1. Preorder
   ROOT → LEFT → RIGHT

2. Inorder
   LEFT → ROOT → RIGHT

3. Postorder
   LEFT → RIGHT → ROOT

+
Recursive call-stack dry runs

+
Going DOWN vs Coming BACK

+
Why moving ONE line changes traversal

+
Time = O(n)

+
Stack = O(h)
```
