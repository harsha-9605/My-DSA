# Recursion — Complete Notes

## 1. What is Recursion?

Recursion is when a function calls itself to solve a smaller version of the same problem.

Every recursive solution mainly needs:

1. **Base Case** — when recursion stops.
2. **Recursive Case** — call the function with a smaller problem.

```cpp
void solve(int n) {
    if (n == 0) {
        return;
    }

    solve(n - 1);
}
```

Basic flow:

```text
solve(3)
↓
solve(2)
↓
solve(1)
↓
solve(0) → base case
↑
return
↑
return
↑
return
```

---

# 2. Recursion Call Stack

Every recursive call gets its own stack frame.

Example:

```cpp
void fun(int n) {
    if (n == 0)
        return;

    fun(n - 1);
}
```

For:

```cpp
fun(3);
```

Call stack grows:

```text
fun(3)
fun(2)
fun(1)
fun(0)
```

After base case, calls return in reverse order:

```text
fun(0) returns
fun(1) returns
fun(2) returns
fun(3) returns
```

Important:

> Code before the recursive call executes while going DOWN.

> Code after the recursive call executes while coming BACK / unwinding.

Example:

```cpp
void fun(int n) {
    if (n == 0)
        return;

    cout << n << " ";

    fun(n - 1);

    cout << n << " ";
}
```

First `cout` executes while going down.

Second `cout` executes while coming back.

---

# 3. Base Case

The base case prevents infinite recursion.

Example:

```cpp
if (n == 0)
    return;
```

Without a proper base case:

```text
solve(3)
solve(2)
solve(1)
solve(0)
solve(-1)
solve(-2)
...
```

Eventually:

```text
Stack Overflow
```

The base-case return value depends on the meaning of the problem.

Examples:

### Sum

```cpp
if (n == 0)
    return 0;
```

Because `0` is the identity for addition.

### Power

```cpp
if (n == 0)
    return 1;
```

Because:

```text
x^0 = 1
```

### Maximum

Possible base:

```cpp
if (i == arr.size())
    return INT_MIN;
```

### Minimum

Possible base:

```cpp
if (i == arr.size())
    return INT_MAX;
```

### Check Sorted

```cpp
if (i == arr.size() - 1)
    return true;
```

Because reaching the last element means no invalid pair was found.

Important:

> Never automatically return `0`, `true`, or `false`.

Ask:

> What does reaching the base case mean for this problem?

---

# 4. Parameterized Recursion

Parameterized recursion carries the answer/state as a parameter.

Example: Sum from `1` to `n`.

```cpp
void sum(int n, int total) {
    if (n == 0) {
        cout << total;
        return;
    }

    sum(n - 1, total + n);
}
```

For:

```cpp
sum(5, 0);
```

Flow:

```text
(5,0)
↓
(4,5)
↓
(3,9)
↓
(2,12)
↓
(1,14)
↓
(0,15)
```

Answer:

```text
15
```

Parameterized recursion is useful when carrying:

```text
sum
count
index
path
answer
visited state
```

It appears heavily in:

* Arrays
* Backtracking
* Graph DFS
* Trees
* DP states

---

# 5. Important: `count++` vs `count + 1`

Suppose:

```cpp
solve(n / 10, count++);
```

This is usually wrong for passing the incremented value.

`count++` is post-increment.

It passes the OLD value first, then increments the local variable.

Instead use:

```cpp
count++;
solve(n / 10, count);
```

or simply:

```cpp
solve(n / 10, count + 1);
```

Example:

```cpp
void countDigits(int n, int count) {
    if (n == 0) {
        cout << count;
        return;
    }

    solve(n / 10, count + 1);
}
```

---

# 6. Functional Recursion

Functional recursion returns the answer.

Example: Sum of digits.

```cpp
int sumDigits(int n) {
    if (n == 0)
        return 0;

    return n % 10 + sumDigits(n / 10);
}
```

Example:

```text
1234

4 + sumDigits(123)
4 + 3 + sumDigits(12)
4 + 3 + 2 + sumDigits(1)
4 + 3 + 2 + 1
= 10
```

---

## Count Digits — Functional

```cpp
int countDigits(int n) {
    if (n == 0)
        return 0;

    return 1 + countDigits(n / 10);
}
```

Pattern:

```text
current contribution
+
answer from smaller problem
```

---

# 7. Parameterized vs Functional Recursion

### Parameterized

Carry the answer downward:

```cpp
solve(n - 1, answer + something);
```

Mental model:

```text
Carry answer DOWN
```

### Functional

Get the answer from recursion and combine it:

```cpp
return something + solve(smallerProblem);
```

Mental model:

```text
Get answer from BELOW
↓
Use it while coming BACK
```

Example:

```cpp
int sum(int n) {
    if (n == 0)
        return 0;

    return n + sum(n - 1);
}
```

---

# 8. Head and Tail Recursion

## Tail Recursion

Recursive call is the last meaningful operation.

```cpp
void solve(int n) {
    if (n == 0)
        return;

    cout << n;

    solve(n - 1);
}
```

Nothing remains after recursion.

---

## Head Recursion

Work happens after the recursive call.

```cpp
void solve(int n) {
    if (n == 0)
        return;

    solve(n - 1);

    cout << n;
}
```

Recursion first goes to the base case.

Then work happens while returning.

---

# 9. Linear Recursion

One recursive call per function invocation.

```cpp
solve(n - 1);
```

Structure:

```text
solve(n)
↓
solve(n-1)
↓
solve(n-2)
↓
...
```

Usually:

```text
Time  = O(n)
Stack = O(n)
```

if each call performs `O(1)` work.

---

# 10. Multiple / Binary Recursion

A function makes multiple recursive calls.

Example:

```cpp
int fun(int n) {
    if (n <= 1)
        return 1;

    return fun(n - 1) + fun(n - 2);
}
```

Example:

```text
fun(3)

        fun(3)
       /      \
   fun(2)    fun(1)
   /   \
fun(1) fun(0)
```

Important distinction:

```text
Total number of calls
→ TIME COMPLEXITY

Maximum active recursion depth
→ STACK SPACE
```

For naive Fibonacci-like recursion:

```text
Time  ≈ O(2^n) upper bound
Stack = O(n)
```

Repeated subproblems are why memoization/DP helps.

---

# 11. Recursion on Arrays

Main pattern:

```cpp
solve(arr, index);
```

Instead of reducing `n`, move an index:

```text
0 → 1 → 2 → ... → n
```

Mental model:

> Handle current element.

> Recursion handles remaining elements.

---

# 12. Sum of Array

```cpp
int sum(vector<int>& arr, int i) {
    if (i == arr.size())
        return 0;

    return arr[i] + sum(arr, i + 1);
}
```

Complexity:

```text
T(n) = T(n-1) + O(1)

Time  = O(n)
Stack = O(n)
```

---

# 13. Maximum Element

Approach 1:

```cpp
int findMax(vector<int>& arr, int i) {
    if (i == arr.size())
        return INT_MIN;

    return max(arr[i], findMax(arr, i + 1));
}
```

Why `INT_MIN`?

If we returned `0`, negative-only arrays would fail.

Example:

```text
[-8, -3, -10]
```

`0` would incorrectly become the maximum.

---

## Cleaner Base Case

```cpp
int findMax(vector<int>& arr, int i) {
    if (i == arr.size() - 1)
        return arr[i];

    return max(arr[i], findMax(arr, i + 1));
}
```

Mental model:

```text
Maximum =
max(
    current element,
    maximum of remaining array
)
```

Complexity:

```text
Time  = O(n)
Stack = O(n)
```

---

# 14. Minimum Element

```cpp
int findMin(vector<int>& arr, int i) {
    if (i == arr.size() - 1)
        return arr[i];

    return min(arr[i], findMin(arr, i + 1));
}
```

Alternative base:

```cpp
if (i == arr.size())
    return INT_MAX;
```

---

# 15. Recursive Linear Search

```cpp
bool search(vector<int>& arr, int i, int target) {
    if (i == arr.size())
        return false;

    if (arr[i] == target)
        return true;

    return search(arr, i + 1, target);
}
```

Worst case:

```text
Time  = O(n)
Stack = O(n)
```

Best case:

```text
O(1)
```

if the first element matches.

---

# 16. First Occurrence

```cpp
int firstOccurrence(vector<int>& arr, int i, int target) {
    if (i == arr.size())
        return -1;

    if (arr[i] == target)
        return i;

    return firstOccurrence(arr, i + 1, target);
}
```

Example:

```text
[2,5,7,5,9]
target = 5

answer = 1
```

---

# 17. Last Occurrence

Search backward:

```cpp
int lastOccurrence(vector<int>& arr, int i, int target) {
    if (i < 0)
        return -1;

    if (arr[i] == target)
        return i;

    return lastOccurrence(arr, i - 1, target);
}
```

Initial call:

```cpp
lastOccurrence(arr, arr.size() - 1, target);
```

Example:

```text
[2,5,7,5,9]

answer = 3
```

---

# 18. Find All Occurrences

```cpp
void findAll(
    vector<int>& arr,
    int i,
    int target,
    vector<int>& ans
) {
    if (i == arr.size())
        return;

    if (arr[i] == target)
        ans.push_back(i);

    findAll(arr, i + 1, target, ans);
}
```

Example:

```text
arr = [2,5,3,5,8,5]
target = 5

ans = [1,3,5]
```

Complexity:

```text
Time             = O(n)
Recursion Stack  = O(n)
Output Space     = O(n) worst case
```

---

# 19. Check if Array is Sorted

```cpp
bool isSorted(vector<int>& arr, int i) {
    if (i == arr.size() - 1)
        return true;

    if (arr[i] > arr[i + 1])
        return false;

    return isSorted(arr, i + 1);
}
```

Important mistake:

```cpp
if (i == arr.size() - 1)
    return false;
```

is wrong.

If we reach the last element without finding an invalid pair, the array is sorted.

So:

```cpp
return true;
```

Complexity:

```text
Worst Time = O(n)
Stack      = O(n)

Best Time  = O(1)
```

---

# 20. Reverse Array Recursively

Two-pointer recursion:

```cpp
void reverseArray(
    vector<int>& arr,
    int left,
    int right
) {
    if (left >= right)
        return;

    swap(arr[left], arr[right]);

    reverseArray(arr, left + 1, right - 1);
}
```

Initial call:

```cpp
reverseArray(arr, 0, arr.size() - 1);
```

Example:

```text
[1,2,3,4,5]
↓
[5,2,3,4,1]
↓
[5,4,3,2,1]
```

Complexity:

```text
T(n) = T(n-2) + O(1)
```

Number of calls:

```text
n/2
```

But:

```text
O(n/2) = O(n)
```

Therefore:

```text
Time  = O(n)
Stack = O(n)
```

Important:

```text
n → n-2 → n-4
```

is still `O(n)`.

It is NOT `O(log n)`.

---

# 21. Palindrome Recursively

```cpp
bool palindrome(string& s, int left, int right) {
    if (left >= right)
        return true;

    if (s[left] != s[right])
        return false;

    return palindrome(s, left + 1, right - 1);
}
```

Example:

```text
racecar

r == r
a == a
c == c
middle reached

true
```

Complexity:

```text
T(n) = T(n-2) + O(1)

Time  = O(n)
Stack = O(n)
```

Best case:

```text
O(1)
```

if first and last characters mismatch immediately.

---

# 22. Recursive Binary Search

```cpp
int binarySearch(
    vector<int>& arr,
    int left,
    int right,
    int target
) {
    if (left > right)
        return -1;

    int mid = left + (right - left) / 2;

    if (arr[mid] == target)
        return mid;

    if (target < arr[mid])
        return binarySearch(
            arr,
            left,
            mid - 1,
            target
        );

    return binarySearch(
        arr,
        mid + 1,
        right,
        target
    );
}
```

Initial call:

```cpp
binarySearch(
    arr,
    0,
    arr.size() - 1,
    target
);
```

Important:

Only ONE recursive branch executes.

Therefore:

```text
T(n) = T(n/2) + O(1)
```

NOT:

```text
2T(n/2)
```

Complexity:

```text
Time  = O(log n)
Stack = O(log n)
```

Comparison:

```text
Iterative Binary Search
Time  = O(log n)
Space = O(1)

Recursive Binary Search
Time  = O(log n)
Space = O(log n)
```

---

# 23. Recursion on Strings

Main pattern:

```cpp
solve(string, index);
```

Important problems covered:

* Palindrome
* Remove character
* Remove consecutive duplicates
* Replace character

---

# 24. Remove a Character — Parameterized

Example:

```text
banana
remove 'a'

answer = bnn
```

```cpp
void removeChar(
    string& s,
    int i,
    char target,
    string& ans
) {
    if (i == s.size())
        return;

    if (s[i] != target)
        ans += s[i];

    removeChar(
        s,
        i + 1,
        target,
        ans
    );
}
```

Complexity:

```text
Time  = O(n)
Stack = O(n)
Output = O(n)
```

---

# 25. Remove Character — Functional Recursion

```cpp
string removeChar(
    string& s,
    int i,
    char target
) {
    if (i == s.size())
        return "";

    string remaining =
        removeChar(s, i + 1, target);

    if (s[i] == target)
        return remaining;

    return s[i] + remaining;
}
```

Important structure:

```text
Go DOWN
↓
Get processed remaining answer
↓
Use current character
↓
Return while coming BACK
```

The recursive call does NOT have to be the final statement.

The current function waits for the deeper call to return.

---

# 26. Remove Consecutive Duplicates

Example:

```text
aaabbccdaa
↓
abcda
```

Functional approach:

```cpp
string removeDuplicates(string& s, int i) {
    if (i == s.size() - 1)
        return string(1, s[i]);

    string remaining =
        removeDuplicates(s, i + 1);

    if (s[i] == remaining[0])
        return remaining;

    return s[i] + remaining;
}
```

Important base case:

```cpp
return string(1, s[i]);
```

Do NOT return:

```cpp
return "";
```

because that would lose the final character.

Note:

Repeated string creation/copying may make this straightforward functional implementation:

```text
Time = up to O(n²)
```

Recursion depth:

```text
O(n)
```

A parameterized/output-reference approach can avoid repeated string copying and give linear traversal.

---

# 27. Replace Character

Example:

```text
banana

'a' → 'x'

bxnxnx
```

```cpp
void replaceChar(
    string& s,
    int i,
    char oldChar,
    char newChar
) {
    if (i == s.size())
        return;

    if (s[i] == oldChar)
        s[i] = newChar;

    replaceChar(
        s,
        i + 1,
        oldChar,
        newChar
    );
}
```

Complexity:

```text
Time  = O(n)
Stack = O(n)
```

---

# 28. Normal Recursive Power

```cpp
long long power(long long x, int n) {
    if (n == 0)
        return 1;

    return x * power(x, n - 1);
}
```

Example:

```text
2^5

= 2 × 2^4
= 2 × 2 × 2^3
...
= 32
```

Recurrence:

```text
T(n) = T(n-1) + O(1)
```

Complexity:

```text
Time  = O(n)
Stack = O(n)
```

---

# 29. Fast Exponentiation

Main idea:

For even `n`:

```text
x^n =
x^(n/2) × x^(n/2)
```

For odd `n`:

```text
x^n =
x × x^(n/2) × x^(n/2)
```

Optimized:

```cpp
long long power(long long x, int n) {
    if (n == 0)
        return 1;

    long long half =
        power(x, n / 2);

    if (n % 2 == 0)
        return half * half;

    return x * half * half;
}
```

Input shrinks:

```text
n
↓
n/2
↓
n/4
↓
n/8
...
1
```

Recurrence:

```text
T(n) = T(n/2) + O(1)
```

Complexity:

```text
Time  = O(log n)
Stack = O(log n)
```

---

# 30. Important Fast-Power Optimization

Bad:

```cpp
return power(x, n / 2)
     * power(x, n / 2);
```

This calculates the same recursive result twice.

Recurrence:

```text
T(n) = 2T(n/2) + O(1)
```

which becomes:

```text
O(n)
```

Better:

```cpp
long long half =
    power(x, n / 2);

return half * half;
```

Only one recursive call:

```text
T(n) = T(n/2) + O(1)

→ O(log n)
```

Important lesson:

> Reusing a recursive result can completely change the complexity.

---

# 31. Recursion Time Complexity

For every recursive function ask 3 questions:

```text
1. How many recursive calls execute?

2. What is the input size of each call?

3. How much work happens outside recursion?
```

Then write the recurrence.

---

# 32. What Does T(n) Mean?

`T(n)` means:

> Total time needed to solve a problem of size `n`.

Example:

```cpp
solve(n - 1);
```

with constant work:

```text
T(n) = T(n-1) + O(1)
```

Example:

```cpp
solve(n / 2);
```

```text
T(n) = T(n/2) + O(1)
```

Two calls:

```cpp
solve(n / 2);
solve(n / 2);
```

```text
T(n) = 2T(n/2) + O(1)
```

---

# 33. Expansion Method

## Case 1

```text
T(n) = T(n-1) + 1
```

Expand:

```text
T(n)
= T(n-1) + 1
= T(n-2) + 2
= T(n-3) + 3
...
= T(n-k) + k
```

Base:

```text
n-k = 0

k = n
```

Therefore:

```text
O(n)
```

---

# 34. Division Recurrence

```text
T(n) = T(n/2) + 1
```

Expand:

```text
T(n)
= T(n/2) + 1
= T(n/4) + 2
= T(n/8) + 3
```

After `k`:

```text
T(n / 2^k) + k
```

Base:

```text
n / 2^k = 1
```

Therefore:

```text
n = 2^k

k = log₂n
```

So:

```text
O(log n)
```

---

# 35. Subtracting vs Dividing

Very important shortcut:

```text
n → n-1
n → n-2
n → n-5
n → n-100
```

Subtracting a constant:

```text
O(n) levels
```

Example:

```text
T(n) = T(n-2) + 1
```

Number of calls:

```text
n/2
```

But:

```text
O(n/2) = O(n)
```

---

Dividing by a constant:

```text
n → n/2
n → n/4
n → n/8
```

gives:

```text
O(log n) levels
```

General:

```text
n → n/2 → O(log n)

n → n/3 → O(log n)

n → n/10 → O(log n)
```

Log bases are ignored in Big-O.

---

# 36. Work Inside Each Recursive Call Matters

Example:

```cpp
void solve(int n) {
    if (n == 0)
        return;

    for (int i = 0; i < n; i++)
        cout << i;

    solve(n - 1);
}
```

Recurrence:

```text
T(n) = T(n-1) + n
```

Expand:

```text
n + (n-1) + (n-2) + ... + 1
```

Formula:

```text
n(n+1)/2
```

Therefore:

```text
Time = O(n²)
```

Stack:

```text
O(n)
```

Important:

> Do not determine complexity only from the recursive call.

Also count the work done inside every call.

---

# 37. Important Geometric Series

Example:

```text
T(n) = T(n/2) + n
```

Expand:

```text
n + n/2 + n/4 + n/8 + ...
```

This sum is less than:

```text
2n
```

Therefore:

```text
O(n)
```

NOT:

```text
O(n log n)
```

Even though recursion depth is `log n`.

Why?

Because every level does less work.

---

# 38. Two Calls With n/2

```text
T(n) = 2T(n/2) + 1
```

Tree:

```text
              n
           /     \
         n/2     n/2
        /  \     /  \
      n/4 n/4  n/4 n/4
```

Number of nodes:

```text
1
2
4
8
...
n
```

Total:

```text
1 + 2 + 4 + ... + n

≈ 2n

= O(n)
```

Therefore:

```text
Time  = O(n)
Stack = O(log n)
```

Stack is based on one deepest path:

```text
n → n/2 → n/4 → ... → 1
```

---

# 39. Two Calls With n-1

```text
T(n) = 2T(n-1) + 1
```

Tree grows approximately:

```text
1
2
4
8
...
2^n
```

Therefore:

```text
Time = O(2^n)
```

Maximum depth:

```text
n
```

Therefore:

```text
Stack = O(n)
```

Important comparison:

```text
2T(n-1) → exponential

2T(n/2) → linear
```

The number of recursive calls alone does NOT determine complexity.

How fast the input shrinks matters.

---

# 40. Merge-Sort-Shaped Recurrence

```text
T(n) = 2T(n/2) + n
```

At each recursion-tree level:

```text
Level 0:

n
```

Next:

```text
n/2 + n/2 = n
```

Next:

```text
n/4 + n/4 + n/4 + n/4 = n
```

So:

```text
Work per level = O(n)
```

Number of levels:

```text
O(log n)
```

Therefore:

```text
O(n × log n)

= O(n log n)
```

This is the main recurrence behind Merge Sort.

---

# 41. Master Recurrence Form

Many divide-and-conquer algorithms follow:

```text
T(n) = aT(n/b) + f(n)
```

Where:

```text
a
= number of recursive calls

n/b
= size of each recursive problem

f(n)
= work outside recursion
```

Example:

```text
T(n) = 2T(n/2) + n
```

Means:

```text
2 recursive calls

each problem size = n/2

extra work = O(n)
```

---

# 42. Basic Master Theorem Idea

For:

```text
T(n) = aT(n/b) + f(n)
```

Calculate:

```text
n^(log_b a)
```

Then compare it with:

```text
f(n)
```

Example:

```text
T(n) = 2T(n/2) + n
```

Here:

```text
a = 2
b = 2

n^(log₂2)
= n
```

And:

```text
f(n) = n
```

Both have the same growth.

Therefore:

```text
O(n log n)
```

For placement-level DSA, first understand:

* Expansion
* Recursion trees

Then use Master Theorem as a shortcut.

---

# 43. Complexity Cheat Sheet

| Recurrence       | Time         |
| ---------------- | ------------ |
| `T(n)=T(n-1)+1`  | `O(n)`       |
| `T(n)=T(n-2)+1`  | `O(n)`       |
| `T(n)=T(n/2)+1`  | `O(log n)`   |
| `T(n)=T(n-1)+n`  | `O(n²)`      |
| `T(n)=T(n/2)+n`  | `O(n)`       |
| `T(n)=2T(n/2)+1` | `O(n)`       |
| `T(n)=2T(n/2)+n` | `O(n log n)` |
| `T(n)=2T(n-1)+1` | `O(2^n)`     |

Do not blindly memorize.

Always ask:

```text
How many calls?

How much does input shrink?

How much work per call?
```

---

# 44. Time vs Stack Space

Never confuse:

```text
TOTAL recursive calls
```

with:

```text
MAXIMUM active recursive calls
```

Time complexity depends mainly on:

```text
Total work across all calls
```

Stack space depends on:

```text
Maximum recursion depth
```

Example Fibonacci:

```text
Time  = O(2^n) upper bound
Stack = O(n)
```

Example recursive binary search:

```text
Time  = O(log n)
Stack = O(log n)
```

Example:

```text
T(n) = 2T(n/2) + 1
```

```text
Time  = O(n)
Stack = O(log n)
```

---

# 45. Recursion Complexity Mental Checklist

Whenever I see recursion:

```text
STEP 1
How many recursive calls actually execute?

↓

STEP 2
What is the size of each recursive call?

n-1?
n-2?
n/2?

↓

STEP 3
How much non-recursive work happens?

O(1)?
O(n)?
O(n²)?

↓

STEP 4
Write recurrence

↓

STEP 5
Expand or draw recursion tree

↓

STEP 6
Total work
= TIME COMPLEXITY

↓

STEP 7
Maximum recursion depth
= STACK SPACE
```

---

# 46. Problems / Patterns Practiced

## Basic Recursion

* Print numbers recursively
* Understand going down vs coming back
* Sum `1` to `n` using parameterized recursion
* Sum digits
* Count digits
* Functional recursion
* Parameterized recursion

## Array Recursion

* Sum of array
* Maximum element
* Minimum element
* Recursive linear search
* First occurrence
* Last occurrence
* Find all occurrences
* Check if array is sorted
* Reverse array recursively

## String Recursion

* Palindrome check
* Remove a character
* Remove character using functional recursion
* Remove consecutive duplicates
* Replace characters

## Divide / Shrink Recursion

* Recursive binary search
* Normal recursive power
* Fast exponentiation

## Multiple Recursion

* Fibonacci recursion tree
* Multiple recursive calls
* Repeated subproblems
* Relation to memoization/DP

## Complexity

* `T(n-1)`
* `T(n-2)`
* `T(n/2)`
* Multiple recursive calls
* Recursion tree
* Expansion method
* Basic Master Theorem idea
* Time vs recursion-stack space

---

# 47. Common Mistakes I Made / Important Corrections

### Mistake 1 — Using `count++` as argument

```cpp
solve(n / 10, count++);
```

Better:

```cpp
solve(n / 10, count + 1);
```

---

### Mistake 2 — Maximum base case returning 0

```cpp
if (i == arr.size())
    return 0;
```

Fails for negative arrays.

Use:

```cpp
return INT_MIN;
```

or stop at the last element:

```cpp
if (i == arr.size() - 1)
    return arr[i];
```

---

### Mistake 3 — Forgetting recursive function call

Wrong:

```cpp
return max(arr[i], i + 1);
```

Correct:

```cpp
return max(
    arr[i],
    findMax(arr, i + 1)
);
```

`i+1` is only an index.

Recursion must solve the remaining problem.

---

### Mistake 4 — Sorted-array base case

Wrong:

```cpp
if (i == arr.size() - 1)
    return false;
```

Correct:

```cpp
return true;
```

Reaching the end means no invalid pair was found.

---

### Mistake 5 — Thinking `n/2` calls means O(log n)

If recursion changes:

```text
n → n-2 → n-4
```

there are `n/2` calls.

But:

```text
O(n/2) = O(n)
```

`O(log n)` happens when the input itself is repeatedly divided:

```text
n → n/2 → n/4 → n/8
```

---

### Mistake 6 — Assuming recursion call must be last

It does NOT have to be.

Example:

```cpp
string remaining =
    solve(i + 1);

if (condition)
    return remaining;

return s[i] + remaining;
```

The current call waits for recursion to return, then continues execution.

---

### Mistake 7 — Thinking recursive space is always O(n)

No.

Look at maximum depth.

```text
n → n-1
= O(n) stack
```

But:

```text
n → n/2
= O(log n) stack
```

Example fast power:

```text
Time  = O(log n)
Space = O(log n)
```

---

### Mistake 8 — Calling the same recursion twice unnecessarily

Bad:

```cpp
return solve(n/2) + solve(n/2);
```

Two recursive calls.

Better when both results are identical:

```cpp
auto x = solve(n/2);

return x + x;
```

Only one recursive call.

This can change:

```text
O(n)
```

into:

```text
O(log n)
```

depending on the recurrence.

---

# 48. Final Recursion Mental Model

For every recursion problem, think:

```text
1. What is my STATE?

   n?
   index?
   left/right?
   sum?
   path?

2. What is my BASE CASE?

3. What is the SMALLER PROBLEM?

4. What should THIS CALL do?

5. Do I need:

   Parameterized recursion?

   OR

   Functional recursion?

6. Does work happen:

   while going DOWN?

   OR

   while coming BACK?

7. How many recursive calls execute?

8. What is the recurrence T(n)?

9. What is total TIME?

10. What is maximum STACK DEPTH?
```

---

# 49. Connection to Future Topics

The recursion foundation learned here is enough to start the major recursive DSA topics.

## Trees

```text
Node
├── recurse left
└── recurse right
```

Main new idea:

```text
Recursive structure of a tree
```

---

## Backtracking

Builds on parameterized recursion.

Main pattern:

```text
CHOOSE
↓
RECURSE
↓
UNDO
```

Example structure:

```cpp
path.push_back(choice);

solve(...);

path.pop_back();
```

New idea:

```text
State restoration
```

---

## Graph DFS

Parameterized recursion with:

```text
current node
visited array
adjacency list
```

Main new issue:

```text
Cycles
```

so we need:

```text
visited
```

---

## Dynamic Programming

Starts from recursion:

```text
state
↓
recurrence
↓
base case
```

Then identifies:

```text
Repeated subproblems
```

and optimizes them using:

```text
Memoization
```

---

# 50. Recursion Status

Core recursion foundation completed:

* Base cases ✅
* Call stack ✅
* Going down / coming back ✅
* Parameterized recursion ✅
* Functional recursion ✅
* Head / tail recursion ✅
* Linear recursion ✅
* Multiple recursion ✅
* Recursion trees ✅
* Arrays recursion ✅
* Strings recursion ✅
* Recursive binary search ✅
* Fast exponentiation ✅
* Time and space complexity basics ✅
* Recurrence relations ✅
* Expansion method ✅
* Basic recursion-tree analysis ✅
* Basic Master Theorem concept ✅

Next major topics should be learned separately:

```text
Trees
Backtracking
Graphs
Dynamic Programming
```

Do not mix all of their problems into the basic recursion module.

The most important thing to keep practicing alongside those topics:

```text
Recurrence equation
+
Time complexity
+
Maximum recursion-stack depth
```
