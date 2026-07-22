# 📚 Linked List Roadmap (Placement Focus)

---

# Module 1 — Basics (Must Know)

## 🎯 Goal
Understand how a linked list works internally.

### Concepts
- [ ] What is a Linked List?
- [ ] Why use Linked Lists over Arrays?
- [ ] Node Structure
- [ ] Head Pointer
- [ ] Tail Pointer
- [ ] NULL Pointer
- [ ] Traversal
- [ ] Counting Nodes

### Visualization

#### Array

```text
10   20   30   40
|    |    |    |

Memory is contiguous.
```

#### Linked List

```text
10 -> 20 -> 30 -> 40 -> NULL

Each node stores:
• Value
• Next Pointer
```

### Problems

- [ ] Traverse Linked List
- [ ] Count Nodes
- [ ] Search Element
- [ ] Print Reverse (Recursion)

---

# Module 2 — Basic Operations

## Operations

### Insert

- [ ] Beginning
- [ ] End
- [ ] At Position

### Delete

- [ ] Beginning
- [ ] End
- [ ] At Position

### Other Operations

- [ ] Update
- [ ] Search
- [ ] Length
- [ ] Reverse Printing

### Problems

- [ ] Design Your Own Linked List

---

# Module 3 — Fast & Slow Pointer ⭐⭐⭐⭐⭐

## Pattern

```text
slow += 1

fast += 2
```

## Applications

- [ ] Middle Node
- [ ] Detect Cycle
- [ ] Find Cycle Start
- [ ] Happy Number
- [ ] Palindrome Linked List
- [ ] Remove Nth Node From End
- [ ] Split List

## Problems

- [ ] LC 876 — Middle of Linked List
- [ ] LC 141 — Linked List Cycle
- [ ] LC 142 — Linked List Cycle II
- [ ] LC 19 — Remove Nth Node From End
- [ ] LC 234 — Palindrome Linked List

---

# Module 4 — Reverse Linked List ⭐⭐⭐⭐⭐

## Master This Pattern

```text
prev

curr

next
```

Practice until it becomes muscle memory.

## Learn

- [ ] Reverse Entire List
- [ ] Reverse First K Nodes
- [ ] Reverse Between Positions
- [ ] Reverse Recursively
- [ ] Reverse in Groups

## Problems

- [ ] LC 206 — Reverse Linked List
- [ ] LC 92 — Reverse Linked List II
- [ ] LC 25 — Reverse Nodes in K Group

---

# Module 5 — Merge Pattern

## Understand

- [ ] Dummy Node
- [ ] Tail Pointer
- [ ] Merge Logic

## Problems

- [ ] LC 21 — Merge Two Sorted Lists
- [ ] LC 23 — Merge K Sorted Lists
- [ ] LC 148 — Sort List

---

# Module 6 — Dummy Node Pattern ⭐⭐⭐⭐⭐

## Learn

```text
dummy

tail

curr
```

## Problems

- [ ] LC 203 — Remove Linked List Elements
- [ ] LC 83 — Remove Duplicates
- [ ] LC 82 — Remove Duplicates II
- [ ] LC 86 — Partition List
- [ ] LC 24 — Swap Nodes in Pairs

---

# Module 7 — Two Pointer Pattern

## Learn

```text
prev

curr

next

left

right
```

## Problems

- [ ] Pairwise Swap
- [ ] Delete Node
- [ ] Reorder List
- [ ] Partition List
- [ ] LC 328 — Odd Even Linked List
- [ ] LC 143 — Reorder List

---

# Module 8 — Cycle Pattern

## Floyd's Cycle Detection

### Understand

- [ ] Why Fast Meets Slow
- [ ] Distance Proof
- [ ] Finding Cycle Entry

## Problems

- [ ] LC 141 — Linked List Cycle
- [ ] LC 142 — Linked List Cycle II
- [ ] Happy Number
- [ ] Circular Array Loop (Optional)

---

# Module 9 — Intersection Pattern

## Understand

- [ ] Length Method
- [ ] Pointer Switching Trick

## Problems

- [ ] LC 160 — Intersection of Two Linked Lists

---

# Module 10 — Random Pointer

## Learn

- [ ] HashMap Method
- [ ] O(1) Space Interleaving Method

## Problems

- [ ] LC 138 — Copy List with Random Pointer

---

# Module 11 — LRU Cache ⭐⭐⭐⭐⭐

## Need

- [ ] Doubly Linked List
- [ ] HashMap

## Problems

- [ ] LC 146 — LRU Cache

---

# Module 12 — Doubly Linked List

## Concepts

```text
prev <-> node <-> next
```

### Learn

- [ ] Traversal
- [ ] Insertion
- [ ] Deletion
- [ ] Reverse
- [ ] Implement DLL

---

# Module 13 — Circular Linked List

## Learn

- [ ] Traversal
- [ ] Insertion
- [ ] Deletion

## Applications

- [ ] Josephus Problem
- [ ] Round Robin Scheduling

---

# Module 14 — Advanced Interview Questions

## Problems

- [ ] LC 430 — Flatten Multilevel Doubly Linked List
- [ ] LC 147 — Insertion Sort List
- [ ] LC 725 — Split Linked List in Parts
- [ ] LC 1669 — Merge In Between Linked Lists
- [ ] LC 61 — Rotate List
- [ ] LC 2 — Add Two Numbers
- [ ] Swap Kth Node
- [ ] Remove Zero Sum Consecutive Nodes

---

# Module 15 — Design Problems

Implement

- [ ] Linked List
- [ ] Doubly Linked List
- [ ] Browser History
- [ ] Deque
- [ ] LRU Cache
- [ ] LFU Cache (Optional)

---

# 🎯 Must Solve Problems

## 🟢 Easy

- [ ] LC 206 — Reverse Linked List
- [ ] LC 21 — Merge Two Sorted Lists
- [ ] LC 83 — Remove Duplicates
- [ ] LC 876 — Middle of Linked List
- [ ] LC 141 — Linked List Cycle
- [ ] LC 160 — Intersection of Two Linked Lists
- [ ] LC 203 — Remove Linked List Elements
- [ ] LC 234 — Palindrome Linked List

---

## 🟡 Medium

- [ ] LC 19 — Remove Nth Node From End
- [ ] LC 24 — Swap Nodes in Pairs
- [ ] LC 92 — Reverse Linked List II
- [ ] LC 143 — Reorder List
- [ ] LC 328 — Odd Even Linked List
- [ ] LC 61 — Rotate List
- [ ] LC 82 — Remove Duplicates II
- [ ] LC 86 — Partition List
- [ ] LC 138 — Copy List with Random Pointer
- [ ] LC 146 — LRU Cache
- [ ] LC 142 — Linked List Cycle II
- [ ] LC 2 — Add Two Numbers

---

## 🔴 Hard

- [ ] LC 25 — Reverse Nodes in K Group
- [ ] LC 23 — Merge K Sorted Lists
- [ ] LC 430 — Flatten a Multilevel Doubly Linked List

---

# 🧠 Interview Patterns

| Pattern | Used In |
|----------|----------|
| Traversal | Search, Count, Print |
| Fast & Slow Pointer | Middle, Cycle, Palindrome, Nth Node |
| Reverse | Reverse List, K-Group, Reorder |
| Dummy Node | Merge, Delete, Partition, Swap |
| Two Pointers | Reorder, Odd-Even, Intersection |
| Merge | Merge Lists, Sort List |
| HashMap | Random Pointer, LRU Cache |
| Doubly Linked List | LRU Cache, Browser History |
| Circular Linked List | Josephus, Round Robin |

---

# 📅 Recommended Study Order

1. ✅ Basics
2. ✅ Basic Operations
3. ✅ Reverse Linked List
4. ✅ Fast & Slow Pointer
5. ✅ Merge Pattern
6. ✅ Dummy Node Pattern
7. ✅ Two Pointer Pattern
8. ✅ Cycle Pattern
9. ✅ Intersection Pattern
10. ✅ Doubly Linked List
11. ✅ Random Pointer
12. ✅ LRU Cache
13. ✅ Circular Linked List
14. ✅ Advanced Problems

---

# 🏁 Placement Checklist

- [ ] Understand every pointer movement
- [ ] Reverse a Linked List without help
- [ ] Solve all Easy problems
- [ ] Solve all Medium problems
- [ ] Understand Dummy Node pattern
- [ ] Master Fast & Slow Pointer
- [ ] Implement Doubly Linked List
- [ ] Implement LRU Cache
- [ ] Solve at least 25–30 Linked List questions
- [ ] Revise all patterns before interviews