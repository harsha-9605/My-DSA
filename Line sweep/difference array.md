# Difference Array

> A Difference Array is used when we need to perform **multiple range updates efficiently**.

---

# Intuition

Suppose we have:

```text
0 0 0 0 0 0
```

Operation:

```text
+3 on [2...4]
```

Normal approach:

```text
0 0 3 3 3 0
```

We update every element.

Time Complexity:

```
O(length of range)
```

Instead, think differently.

At index 2:

> "Start adding +3"

At index 5:

> "Stop adding +3"

Difference array:

```text
0 0 3 0 0 -3
```

Taking the prefix sum gives

```text
0 0 3 3 3 0
```

Exactly the same answer.

---

# Why does it work?

Difference Array stores **changes**, not actual values.

Positive value

```text
Start adding.
```

Negative value

```text
Stop adding.
```

Taking the prefix sum accumulates all active changes.

---

# Range Update

To add `val` to every index in `[l...r]`

```cpp
diff[l] += val;

if (r + 1 < n)
    diff[r + 1] -= val;
```

Notice the boundary check.

If `r` is the last index, there is no `r+1`.

---

# Recover Original Array

Take the prefix sum.

```cpp
vector<int> ans(n);

ans[0] = diff[0];

for(int i=1;i<n;i++)
    ans[i] = ans[i-1] + diff[i];
```

---

# Building Difference Array

Given

```text
nums

4 7 7 10 6
```

Difference Array

```text
4 3 0 3 -4
```

Formula

```cpp
diff[0] = nums[0];

for(int i=1;i<n;i++)
    diff[i] = nums[i] - nums[i-1];
```

---

# Recovering Original Array

Given

```text
diff

4 3 0 3 -4
```

Recover

```cpp
nums[0] = diff[0];

for(int i=1;i<n;i++)
    nums[i] = nums[i-1] + diff[i];
```

---

# Time Complexity

Without Difference Array

Range Update

```
O(q × n)
```

where

- q = number of queries

With Difference Array

Each update

```
O(1)
```

After all updates

One Prefix Sum

```
O(n)
```

Total

```
O(q + n)
```

---

# Example

Original

```text
1 2 3 4 5
```

Difference Array

```text
1 1 1 1 1
```

Update

```text
+2 on [1...3]
```

Difference Array

```text
1 3 1 1 -1
```

Prefix Sum

```text
1
1+3=4
4+1=5
5+1=6
6-1=5
```

Result

```text
1 4 5 6 5
```

---

# Important Edge Case

If

```text
r == n-1
```

Do NOT do

```cpp
diff[r+1] -= val;
```

Instead

```cpp
diff[l] += val;
```

only.

---

# When to Think of Difference Array

Whenever you hear

- Multiple range updates
- Add x to every element in [l...r]
- Hundreds of thousands of updates
- Range increment/decrement
- Offline updates

Think

> Difference Array

---

# Difference Array vs Prefix Sum

## Prefix Sum

Purpose

```
Fast Range Queries
```

Update

```
Slow
```

Query

```
O(1)
```

---

## Difference Array

Purpose

```
Fast Range Updates
```

Update

```
O(1)
```

Recover array

```
One Prefix Sum
```

---

# Difference Array vs Line Sweep

Difference Array

- Special case of Line Sweep
- Usually arrays
- Uses prefix sum

Line Sweep

- General technique
- Events
- Intervals
- Geometry
- Calendars
- Maps

Think

```
Difference Array ⊂ Line Sweep
```

---

# Common Interview Problems

## Easy

- 1109. Corporate Flight Bookings
- 1854. Maximum Population Year

---

## Medium

- 1094. Car Pooling
- 2381. Shifting Letters II

---

## Hard

- 3355. Zero Array Transformation I
- 3356. Zero Array Transformation II

---

# Template

```cpp
vector<int> diff(n,0);

for(auto &q : queries)
{
    int l = q[0];
    int r = q[1];
    int val = q[2];

    diff[l] += val;

    if(r+1<n)
        diff[r+1] -= val;
}

vector<int> ans(n);

ans[0] = diff[0];

for(int i=1;i<n;i++)
    ans[i] = ans[i-1] + diff[i];
```

---

# Key Takeaways

- Difference Array stores **changes**, not values.
- Update only two positions for every range.
- Prefix Sum reconstructs the final array.
- Best for **multiple range updates**.
- Time Complexity = **O(q + n)**.
- Difference Array is a **special case of Line Sweep**.