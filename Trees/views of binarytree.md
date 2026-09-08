# 🌳 Module 8 — Tree Views & Level Patterns

# Goal

This module is all about solving tree problems using **Breadth First Search (BFS)**.

Unlike previous modules that focused on recursion (DFS), this module focuses on processing the tree **level by level**.

Examples:

- Right View
- Left View
- Zigzag Traversal
- Largest Value in Each Level
- Top View
- Bottom View

---

# DFS vs BFS

## DFS (Previous Modules)

Think vertically.

```

Root

↓

Left

↓

Right

↓

Return to Parent

```

Used for

- Height
- Diameter
- Path Sum
- LCA
- Balanced Tree

---

## BFS (Module 8)

Think horizontally.

```

Level 0

↓

Level 1

↓

Level 2

↓

Level 3

```

Used for

- Views
- Zigzag
- Largest Value
- Top View
- Bottom View

---

# Master BFS Template

Every question in this module starts with this template.

```cpp
queue<TreeNode*> q;

if(root==nullptr)
    return {};

q.push(root);

while(!q.empty())
{
    int size=q.size();

    for(int i=0;i<size;i++)
    {
        TreeNode* node=q.front();
        q.pop();

        // Process Current Node

        if(node->left)
            q.push(node->left);

        if(node->right)
            q.push(node->right);
    }
}
```

## Time Complexity

```
O(n)
```

Every node is visited exactly once.

## Space

```
O(n)
```

Queue may contain an entire level.

---

# Pattern 1 — One Answer Per Level

Many questions ask

> "For every level..."

Examples

- First node
- Last node
- Maximum value

BFS naturally processes one complete level.

---

# LC 199 — Right Side View

## Observation

Store the **last node** of every level.

Tree

```
        1
      /   \
     2     3
      \     \
       5     4
```

Levels

```
1

2 3

5 4
```

Right View

```
1

3

4
```

### Code

```cpp
if(i==size-1)
{
    ans.push_back(node->val);
}
```

Only the last node is stored.

---

# Left View

Exactly opposite.

Store the **first node**.

```cpp
if(i==0)
{
    ans.push_back(node->val);
}
```

Nothing else changes.

---

# LC 515 — Largest Value in Each Row

Instead of first or last node,

store the maximum value.

```cpp
int maxi=INT_MIN;

for(...)
{
    maxi=max(maxi,node->val);
}

ans.push_back(maxi);
```

---

# LC 103 — Zigzag Traversal

Normal BFS

```
1

2 3

4 5 6 7
```

Zigzag

```
1

3 2

4 5 6 7

7 6 5 4
```

Idea

Store each level inside

```cpp
vector<int> level;
```

Then

- keep as it is
- or reverse it

depending on the current direction.

Usually

```cpp
bool leftToRight=true;
```

Flip every level.

```cpp
leftToRight=!leftToRight;
```

---

# New Concept — Horizontal Distance (HD)

Used in

- Top View
- Bottom View

Every node gets one Horizontal Distance.

```
            1(0)

      2(-1)      3(+1)

   4(-2) 5(0) 6(0) 7(+2)
```

Rules

Left Child

```
HD-1
```

Right Child

```
HD+1
```

---

# BFS + Metadata

Earlier

```cpp
queue<TreeNode*>
```

Now

```cpp
queue<pair<TreeNode*,int>>
```

Extra information

```
Horizontal Distance
```

Queue stores

```
(Node*, HD)
```

Example

```cpp
q.push({root,0});
```

---

# Why map?

Question

Why not

```cpp
unordered_map
```

Answer

Top View must be printed

```
Left

↓

Root

↓

Right
```

That means

```
HD

-2

-1

0

1

2
```

Only

```cpp
map
```

keeps keys sorted.

---

# Top View

## Definition

Store the **first node** seen for every Horizontal Distance.

Example

```
        1
       / \
      2   3
       \
        4
```

HD

```
1 -> 0

2 -> -1

3 -> +1

4 -> 0
```

For

HD=0

keep

```
1
```

Ignore

```
4
```

---

## Logic

```cpp
if(!mp.count(hd))
{
    mp[hd]=node->data;
}
```

Meaning

Only store the first node.

---

## Code

```cpp
map<int,int> mp;

queue<pair<Node*,int>> q;

q.push({root,0});

while(!q.empty())
{
    Node* node=q.front().first;
    int hd=q.front().second;
    q.pop();

    if(!mp.count(hd))
        mp[hd]=node->data;

    if(node->left)
        q.push({node->left,hd-1});

    if(node->right)
        q.push({node->right,hd+1});
}

for(auto [hd,val]:mp)
    ans.push_back(val);
```

---

# Bottom View

Definition

Store the **last node** seen for every HD.

Instead of

```cpp
if(!mp.count(hd))
```

Simply write

```cpp
mp[hd]=node->data;
```

Every new node overwrites the old one.

---

Example

HD = 0

Visit

```
1
```

Map

```
0 → 1
```

Visit

```
5
```

Map

```
0 → 5
```

Visit

```
8
```

Map

```
0 → 8
```

Final answer

```
8
```

because it is the bottom-most node.

---

## Code

```cpp
map<int,int> mp;

queue<pair<Node*,int>> q;

q.push({root,0});

while(!q.empty())
{
    Node* node=q.front().first;
    int hd=q.front().second;
    q.pop();

    mp[hd]=node->data;

    if(node->left)
        q.push({node->left,hd-1});

    if(node->right)
        q.push({node->right,hd+1});
}

for(auto [hd,val]:mp)
    ans.push_back(val);
```

---

# map vs unordered_map

## unordered_map

Use when

- Order doesn't matter
- Fast lookup
- Frequency
- Prefix Sum
- Hashing

Example

```cpp
unordered_map<int,int> mp;
```

---

## map

Use when

Keys must be sorted.

Examples

- Top View
- Bottom View
- Vertical Traversal

Example

```cpp
map<int,int> mp;
```

---

# map Overwrite

```cpp
map<int,int> mp;

mp[0]=2;
```

Map

```
0 → 2
```

Now

```cpp
mp[0]=5;
```

Map becomes

```
0 → 5
```

Old value is overwritten.

This is exactly why Bottom View works.

---

# Module 8 Patterns

## Pattern 1

One answer per level

Questions

- Right View
- Left View
- Largest Value

---

## Pattern 2

Alternate direction

Question

- Zigzag

---

## Pattern 3

BFS + Metadata

Queue stores

```
(Node*, HD)
```

Questions

- Top View
- Bottom View

---

## Pattern 4

Sorted Output

Whenever output must be ordered by key,

use

```cpp
map
```

instead of

```cpp
unordered_map
```

---

# Problems Completed

✅ LC 199 — Binary Tree Right Side View

✅ LC 103 — Binary Tree Zigzag Level Order Traversal

✅ LC 515 — Find Largest Value in Each Tree Row

✅ Left View of Binary Tree

✅ Top View of Binary Tree

✅ Bottom View of Binary Tree

---

# Key Takeaways

- Think **BFS** whenever a tree problem says **"each level"**.
- The BFS template remains the same; only the processing inside the loop changes.
- Use **`queue<pair<Node*, HD>>`** when extra information (metadata) is needed.
- Use **`map`** when the final output must be sorted by keys.
- **Top View = first node for each HD.**
- **Bottom View = last node for each HD (overwrite previous values).**