# 📘 Binary Search – Module 3: Binary Search on Answer

---

# 🎯 Goal

In this module, we are **not searching inside an array**.

Instead, we are **searching for the answer itself**.

Examples:

* Minimum speed
* Maximum distance
* Minimum capacity
* Minimum time
* Maximum length
* Minimum largest sum

The answer is usually a **number**, not an index.

---

# 1. How to Recognize Binary Search on Answer ⭐⭐⭐⭐⭐

Whenever you read a problem, ask these questions **in order**.

## Step 1: Is the answer numeric?

Examples:

* Speed
* Time
* Capacity
* Distance
* Days
* Length
* Size
* Sum

If **NO**, Binary Search on Answer is probably not applicable.

If **YES**, continue.

---

## Step 2: Can I verify one answer?

Suppose someone gives me

```text
mid = 25
```

Can I check whether **25 works or not**?

Notice:

I am **not** finding the answer.

I am only verifying one candidate answer.

If you can write a function like

```cpp
bool check(mid)
```

then continue.

---

## Step 3: Is there a Monotonic Property?

A Binary Search on Answer problem **must** have a monotonic property.

Typical patterns are:

### Pattern 1 (Minimum Answer)

```text
Answer

1 2 3 4 5 6

❌ ❌ ❌ ✅ ✅ ✅
```

Once an answer becomes valid,

every larger answer is also valid.

---

### Pattern 2 (Maximum Answer)

```text
Answer

1 2 3 4 5 6

✅ ✅ ✅ ❌ ❌ ❌
```

Once an answer becomes invalid,

every larger answer is also invalid.

---

## Recognition Formula

```text
Numeric Answer
        +
Can Verify One Answer
        +
Monotonic Property
        =
Binary Search on Answer
```

---

# 2. What Does `mid` Represent? ⭐⭐⭐⭐⭐

This is the **most important question**.

Before writing any code, complete this sentence:

```text
mid represents ______________________
```

Examples:

* Eating speed
* Ship capacity
* Maximum allowed subarray sum
* Number of days
* Minimum distance

Every line inside `check(mid)` comes from this sentence.

Never memorize the check function.

Always derive it.

---

# 3. How to Find the Search Space ⭐⭐⭐⭐⭐

This is the hardest part for beginners.

Never memorize.

Always reason.

---

## Finding LEFT

Ask yourself:

> What is the smallest possible answer?

Not the correct answer.

The smallest answer that could ever make sense.

Examples:

* Sometimes it is `1`
* Sometimes it is the minimum element
* Sometimes it is the maximum element

Ask:

> Can the answer ever be smaller than this?

If the answer is **No**, then this is your LEFT boundary.

---

## Finding RIGHT

Ask yourself:

> What is the largest possible answer?

Examples:

* Maximum element
* Sum of all elements
* Maximum distance

Ask:

> Can the answer ever become larger than this?

If the answer is **No**, then this is your RIGHT boundary.

---

## Golden Rule

```text
LEFT

↓

Smallest possible answer

RIGHT

↓

Largest possible answer
```

---

# 4. How to Build `check(mid)` ⭐⭐⭐⭐⭐

Never start by writing code.

Instead follow these steps.

---

## Step 1

Fix one answer.

Example

```text
mid = 20
```

---

## Step 2

Forget programming.

Pretend you are solving the problem manually.

Ask yourself:

> What would I physically do?

Write the process in English.

Example:

```text
Take package.

Still fits.

Continue.

Doesn't fit.

Start another ship.
```

---

## Step 3

Convert each English sentence into one line of code.

Example

```text
Take package
```

↓

```cpp
load += weight;
```

---

```text
Doesn't fit
```

↓

```cpp
days++;
load = weight;
```

---

## Rule

Never memorize code.

Always derive code from the manual process.

---

# 5. What Am I Counting?

Almost every Binary Search on Answer problem counts something.

Examples:

* Hours
* Days
* Students
* Subarrays
* Bouquets
* Painters
* Machines
* Cows
* Operations

Ask:

> What exactly am I counting inside `check(mid)`?

That count decides whether `mid` is valid or invalid.

---

# 6. Choosing Binary Search Direction ⭐⭐⭐⭐⭐

This depends on what the problem asks.

---

## Case 1 — Find Minimum Answer

Typical monotonicity:

```text
❌ ❌ ❌ ✅ ✅ ✅
```

When `check(mid)` is true:

```cpp
ans = mid;
right = mid - 1;
```

Reason:

We already have a valid answer.

Try to find a smaller one.

---

## Case 2 — Find Maximum Answer

Typical monotonicity:

```text
✅ ✅ ✅ ❌ ❌ ❌
```

When `check(mid)` is true:

```cpp
ans = mid;
left = mid + 1;
```

Reason:

We already have a valid answer.

Try to find a larger one.

---

# 7. Universal Binary Search Template

```cpp
int left = minimumPossibleAnswer;
int right = maximumPossibleAnswer;
int ans = -1;

while(left <= right)
{
    int mid = left + (right - left) / 2;

    if(check(mid))
    {
        ans = mid;

        // Minimum Answer
        right = mid - 1;

        // Maximum Answer
        // left = mid + 1;
    }
    else
    {
        // Minimum Answer
        left = mid + 1;

        // Maximum Answer
        // right = mid - 1;
    }
}

return ans;
```

---

# 8. Time Complexity

General Formula

```text
O(Check Function × log(Search Space))
```

Examples

If

```text
check(mid) = O(n)
```

Then

```text
Total = O(n log(Search Space))
```

Never assume Binary Search on Answer is simply `O(log n)`.

---

# 9. Interview Thinking Process ⭐⭐⭐⭐⭐

Whenever you see a new problem, ask these questions in this exact order.

---

## Question 1

What exactly is the answer?

Examples:

* Speed?
* Capacity?
* Time?
* Distance?
* Length?
* Sum?

---

## Question 2

Can I verify one answer?

Suppose the answer is 25.

Can I tell whether 25 works?

---

## Question 3

Does the verification become monotonic?

Examples

```text
❌ ❌ ❌ ✅ ✅ ✅
```

or

```text
✅ ✅ ✅ ❌ ❌ ❌
```

---

## Question 4

What does `mid` represent?

Complete this sentence:

```text
mid represents ____________________
```

---

## Question 5

What is the smallest possible answer?

↓

LEFT

---

## Question 6

What is the largest possible answer?

↓

RIGHT

---

## Question 7

Pretend `mid` is fixed.

Solve the problem manually.

Do not think about code.

---

## Question 8

Convert the manual process into code.

English

↓

Code

---

## Question 9

If `check(mid)` is true,

Should I search LEFT or RIGHT?

* Minimum Answer → Search LEFT
* Maximum Answer → Search RIGHT

---

# 10. Common Mistakes

❌ Memorizing `check(mid)`.

✅ Derive it using the meaning of `mid`.

---

❌ Guessing LEFT and RIGHT.

✅ Reason about the smallest and largest possible answer.

---

❌ Writing code immediately.

✅ Simulate manually first.

---

❌ Forgetting to identify monotonicity.

✅ Always prove the monotonic property before using Binary Search.

---

❌ Thinking every Binary Search problem is on an array.

✅ Ask first:

```text
Am I searching an index?

OR

Am I searching an answer?
```

---

# ⭐ Golden Framework (Memorize This)

```text
Read the problem

↓

Is the answer numeric?

↓

Can I verify one answer?

↓

Is the verification monotonic?

↓

Find LEFT (smallest possible answer)

↓

Find RIGHT (largest possible answer)

↓

Define what mid represents

↓

Solve manually for one mid

↓

Convert manual process into check(mid)

↓

Choose Binary Search direction

↓

Implement
```

---

# 🔥 Final Rule

Do **not** memorize Binary Search problems.

Memorize **one thinking process**.

Every new Binary Search on Answer problem can be solved by following the same framework:

1. Recognize the pattern.
2. Find the search space.
3. Define what `mid` represents.
4. Build `check(mid)` by simulation.
5. Binary Search over the answer.
