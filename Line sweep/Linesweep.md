# Line Sweep Algorithm

> Line Sweep is a technique where we process **events in sorted order** instead of checking every point individually.

---

# Intuition

Suppose we have intervals:

```text
Meeting A : [1,5]
Meeting B : [2,7]
Meeting C : [4,6]
```

Instead of checking every point one by one, record only **where something changes**.

```text
1 : +1
2 : +1
4 : +1
5 : -1
6 : -1
7 : -1
```

Now sweep from left to right.

Current meetings

```text
0
1
2
3
2
1
0
```

We only care about **events**, not every position.

---

# Core Idea

Every interval has

- Start Event
- End Event

Store only these events.

Then process them in sorted order.

---

# General Template

```cpp
map<int,int> events;

for(auto &interval : intervals)
{
    events[start] += value;
    events[end] -= value;
}

int current = 0;

for(auto &[position, change] : events)
{
    current += change;

    // process current state
}
```

---

# Why map?

Line Sweep requires processing events

```text
Left ---> Right
```

Therefore keys must be sorted.

`map`

```cpp
O(log n)
```

Automatically keeps keys sorted.

`unordered_map`

```cpp
Average O(1)
```

BUT

Keys are NOT sorted.

Example

```text
unordered_map iteration

10
2
7
1
```

Wrong order for Line Sweep.

---

# Can we use unordered_map?

Yes.

Store events

```cpp
unordered_map<int,int> events;
```

Then

```cpp
vector<int> keys;

for(auto &it : events)
    keys.push_back(it.first);

sort(keys.begin(), keys.end());
```

Now iterate in sorted order.

Usually

Using `map`

is simpler.

---

# Difference Array vs Line Sweep

Difference Array

- Special case of Line Sweep
- Works when coordinates are small
- Uses array
- Prefix Sum reconstructs answer

Example

```cpp
vector<int> diff(1001);
```

---

Line Sweep

- General technique
- Works for huge coordinates
- Uses events
- Usually implemented with map

Example

```cpp
map<int,int> events;
```

---

Relationship

```text
Line Sweep
│
├── Difference Array
├── Event Sweep
├── Coordinate Compression + Sweep
└── Geometry Sweep
```

Difference Array ⊂ Line Sweep

---

# When to use Difference Array

Coordinates are small.

Example

```text
0 <= x <= 1000
```

Use

```cpp
vector<int> diff(1001);
```

---

# When to use Line Sweep

Coordinates are huge.

Example

```text
5

100

500000

1000000000
```

Cannot create

```cpp
vector<int> diff(1000000001);
```

Instead

```cpp
map<int,int> events;
```

Store only changes.

---

# Time Complexity

Difference Array

Updates

```
O(1)
```

Prefix Sum

```
O(n)
```

Total

```
O(q+n)
```

---

Line Sweep

Insertion

```
O(log k)
```

where

k = number of events

Traversal

```
O(k)
```

Total

```
O(k log k)
```

---

# Interval Types (VERY IMPORTANT)

## Inclusive Interval

```text
[l,r]
```

Effect includes r.

Update

```cpp
diff[l] += val;

diff[r+1] -= val;
```

Examples

- Range Addition
- Corporate Flight Bookings

---

## Half-open Interval

```text
[l,r)
```

Effect ends before r.

Update

```cpp
diff[l] += val;

diff[r] -= val;
```

Examples

- Car Pooling

Passengers

```text
Pickup at from

Drop at to
```

Passengers are NOT inside the car at

```text
to
```

Therefore

```cpp
events[to] -= passengers;
```

NOT

```cpp
events[to+1]
```

---

# Difference Array Example

Range

```text
+5 on [2,4]
```

Updates

```cpp
diff[2]+=5;

diff[5]-=5;
```

---

# Car Pooling Example

Trip

```text
[2,1,5]
```

Meaning

Passengers travel

```text
1

2

3

4
```

Not

```text
5
```

Updates

```cpp
diff[1]+=2;

diff[5]-=2;
```

Correct.

---

# How to Identify Line Sweep

Look for

- Events
- Intervals
- Start / End
- Maximum overlap
- Active intervals
- People entering/leaving
- Meetings
- Buildings
- Flights
- Population
- Cars
- Huge coordinates

Think

```
Record only changes.
```

---

# Common Interview Problems

## Difference Array

- 1109 Corporate Flight Bookings ⭐⭐⭐⭐⭐
- 1094 Car Pooling ⭐⭐⭐⭐⭐
- 1854 Maximum Population Year
- 2381 Shifting Letters II
- 3355 Zero Array Transformation I
- 3356 Zero Array Transformation II

---

## Line Sweep

- 1094 Car Pooling
- 1854 Maximum Population Year
- 253 Meeting Rooms II
- 218 Skyline Problem
- 56 Merge Intervals
- 57 Insert Interval
- 759 Employee Free Time
- 732 My Calendar III
- 391 Perfect Rectangle

---

# Common Mistakes

❌ Using unordered_map directly

Need sorted traversal.

---

❌ Using r+1 for half-open intervals

Car Pooling

Wrong

```cpp
events[to+1]-=x;
```

Correct

```cpp
events[to]-=x;
```

---

❌ Confusing inclusive and half-open intervals

Always read the problem carefully.

---

❌ Creating huge arrays

Instead of

```cpp
vector<int>(1000000000);
```

Use

```cpp
map<int,int>
```

---

# Interview Trick

Ask yourself

### Can I afford an array?

YES

↓

Difference Array

---

NO

↓

Line Sweep (map)

---

# Key Takeaways

- Line Sweep processes **events**, not every position.
- Difference Array is an **array implementation of Line Sweep**.
- Use `map` because events must be processed in sorted order.
- Use Difference Array when coordinates are small.
- Use Line Sweep when coordinates are huge or sparse.
- Always identify whether intervals are **inclusive `[l,r]`** or **half-open `[l,r)`** before writing updates.