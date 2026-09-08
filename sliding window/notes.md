# 🔥 Sliding Window — Complete Placement Notes

# 1. What is Sliding Window?

Sliding Window is used mainly for problems involving a **contiguous**:

- Subarray
- Substring
- Window/range

Instead of recalculating every possible subarray from scratch, we maintain a window:

```text
[left ........ right]
```

Usually:

- `right` expands the window
- `left` shrinks the window

This often reduces:

```text
Brute Force: O(n²) / O(n³)

to

Sliding Window: O(n)
```

---

# 2. How to Recognize Sliding Window

Look for words such as:

```text
subarray
substring
contiguous
consecutive
window
longest
shortest / minimum
at most K
exactly K
contains characters
distinct characters
```

But these words alone do NOT guarantee sliding window.

The important question is:

> Can I maintain a contiguous range by moving `left` and `right` without needing to move them backward?

---

# 3. Main Sliding Window Patterns

```text
1. Fixed Size Window

2. Variable Size — Longest Valid Window

3. Variable Size — Minimum Valid Window

4. HashMap / Frequency Window

5. AtMost(K) Counting Trick

6. Anagram / Permutation Fixed Window

7. Word-Based Sliding Window

8. Sliding Window + Heap / Deque
```

---

# 🟢 MODULE 1 — FIXED SIZE SLIDING WINDOW

## Recognition

Use when the window size is already known.

Typical wording:

```text
subarray of size K
substring of length K
every window of size K
```

Window length always remains:

```text
K
```

---

## Basic Template

```cpp
int left = 0;
long long sum = 0;

for(int right = 0; right < nums.size(); right++)
{
    sum += nums[right];

    if(right - left + 1 == k)
    {
        // process current window

        sum -= nums[left];
        left++;
    }
}
```

Mental model:

```text
ADD new element

↓

PROCESS full window

↓

REMOVE old element

↓

MOVE left
```

---

## Alternative: Build First Window

```cpp
int sum = 0;

for(int i = 0; i < k; i++)
{
    sum += nums[i];
}

int answer = sum;

for(int i = k; i < nums.size(); i++)
{
    sum += nums[i];
    sum -= nums[i-k];

    answer = max(answer, sum);
}
```

---

## Problems

- Maximum Sum Subarray of Size K
- LC 643 — Maximum Average Subarray I
- LC 1343 — Number of Subarrays of Size K and Average ≥ Threshold
- LC 1456 — Maximum Number of Vowels in a Substring
- LC 2090 — K Radius Subarray Averages
- First Negative Integer in Every Window
- Count Distinct Elements in Every Window
- LC 438 — Find All Anagrams
- LC 567 — Permutation in String

---

# 🟡 MODULE 2 — VARIABLE SIZE WINDOW

Window size is NOT fixed.

General structure:

```text
EXPAND right

↓

Update window state

↓

Condition violated?

↓

SHRINK left

↓

Process answer
```

The most important question is:

> What makes my window invalid?

---

# Pattern A — Longest Valid Window

Examples:

```text
Longest subarray with at most K zeros

Longest substring without duplicates

Longest substring with at most K distinct characters
```

Template:

```cpp
int left = 0;
int ans = 0;

for(int right = 0; right < n; right++)
{
    // add nums[right]

    while(window is invalid)
    {
        // remove nums[left]
        left++;
    }

    ans = max(ans, right-left+1);
}
```

Key idea:

```text
EXPAND

↓

If invalid → SHRINK

↓

Once valid → UPDATE longest
```

---

## LC 1004 — Max Consecutive Ones III

Window is valid when:

```text
zeros <= k
```

Template:

```cpp
int left = 0;
int zeros = 0;
int ans = 0;

for(int right = 0; right < nums.size(); right++)
{
    if(nums[right] == 0)
        zeros++;

    while(zeros > k)
    {
        if(nums[left] == 0)
            zeros--;

        left++;
    }

    ans = max(ans, right-left+1);
}
```

---

## LC 1493 — Longest Subarray of 1's After Deleting One Element

Allow at most:

```text
1 zero
```

Since one element MUST be deleted:

```cpp
ans = max(ans, right-left);
```

instead of:

```cpp
right-left+1
```

---

# Pattern B — Minimum Valid Window

Examples:

```text
Minimum length with sum >= target

Smallest substring containing required characters
```

The direction is different.

For longest:

```text
Shrink while INVALID
```

For minimum:

```text
Shrink while VALID
```

because once the condition is satisfied, we want to make the window smaller.

Template:

```cpp
for(int right = 0; right < n; right++)
{
    // expand

    while(window is valid)
    {
        answer = min(answer, right-left+1);

        // shrink
        left++;
    }
}
```

---

## LC 209 — Minimum Size Subarray Sum

Condition:

```text
sum >= target
```

Template:

```cpp
int left = 0;
int sum = 0;
int minLen = INT_MAX;

for(int right = 0; right < nums.size(); right++)
{
    sum += nums[right];

    while(sum >= target)
    {
        minLen = min(minLen, right-left+1);

        sum -= nums[left];
        left++;
    }
}
```

Important:

This works because LC 209 contains positive numbers.

With negative numbers:

```text
sum increases/decreases unpredictably
```

so normal sliding-window sum logic may fail.

---

# 🟠 MODULE 3 — HASHMAP + SLIDING WINDOW

Use when the condition depends on:

```text
character frequencies
distinct values
duplicates
```

Common structures:

```cpp
unordered_map<char,int> freq;
unordered_map<int,int> freq;
```

---

# Pattern — Longest Without Duplicates

## LC 3 — Longest Substring Without Repeating Characters

Condition:

```text
frequency <= 1
```

Template:

```cpp
unordered_map<char,int> mp;

int left = 0;
int ans = 0;

for(int right = 0; right < s.size(); right++)
{
    mp[s[right]]++;

    while(mp[s[right]] > 1)
    {
        mp[s[left]]--;

        if(mp[s[left]] == 0)
            mp.erase(s[left]);

        left++;
    }

    ans = max(ans, right-left+1);
}
```

---

# Pattern — At Most K Distinct

Condition:

```text
mp.size() <= k
```

Template:

```cpp
unordered_map<char,int> mp;

int left = 0;
int ans = 0;

for(int right = 0; right < s.size(); right++)
{
    mp[s[right]]++;

    while(mp.size() > k)
    {
        mp[s[left]]--;

        if(mp[s[left]] == 0)
            mp.erase(s[left]);

        left++;
    }

    ans = max(ans, right-left+1);
}
```

Problems:

- Longest Substring With At Most K Distinct
- LC 904 — Fruits Into Baskets

---

# Important: `map.size()` vs Frequencies

`map.size()` tells:

```text
How many UNIQUE keys exist?
```

It does NOT tell whether required frequencies are satisfied.

Example:

```text
Need:

A : 2
B : 1
C : 1
```

Window:

```text
A : 1
B : 1
C : 1
```

Both maps have:

```text
size = 3
```

but the window is INVALID because one `A` is missing.

Therefore:

```text
Distinct-character problems → map.size()

Frequency requirement problems → compare frequencies / have-need
```

---

# 🔴 MODULE 4 — ATMOST(K) TRICK

Used mainly for:

```text
COUNT subarrays with EXACTLY K
```

Core formula:

```text
Exactly(K)

=

AtMost(K)

-

AtMost(K-1)
```

---

# Why Does It Work?

Suppose:

```text
AtMost(2)
```

counts subarrays having:

```text
0
1
2
```

qualifying items.

And:

```text
AtMost(1)
```

counts:

```text
0
1
```

Subtract:

```text
AtMost(2) - AtMost(1)

=

Exactly 2
```

---

# Most Important Counting Formula

Inside an AtMost window:

```cpp
count += right-left+1;
```

Why?

If:

```text
[left ........ right]
```

is valid,

then all valid subarrays **ending at `right`** are:

```text
[right]

[right-1 ... right]

[right-2 ... right]

...

[left ... right]
```

Number of choices:

```text
right-left+1
```

---

# Very Important Distinction

## Formula 1 — Total Number of Subarrays

For array length `n`:

```text
n(n+1)/2
```

NOT:

```text
n(n-1)/2
```

Example:

```text
[1,2,3]
```

Subarrays:

```text
[1]
[2]
[3]
[1,2]
[2,3]
[1,2,3]
```

Total:

```text
6 = 3×4/2
```

---

## Formula 2 — Number of Subarrays Containing Index i

```text
(i+1) × (n-i)
```

Why?

Choose:

```text
start from [0...i]

end from [i...n-1]
```

Example:

```text
[1,2,3]

i = 1 (element 2)
```

Subarrays containing `2`:

```text
[2]
[1,2]
[2,3]
[1,2,3]
```

Count:

```text
(1+1) × (3-1)

= 4
```

---

## Formula 3 — Subarrays Ending at `right`

For current valid window:

```text
[left ... right]
```

Number of valid subarrays ending exactly at `right`:

```text
right-left+1
```

This is NOT the same concept as:

```text
(i+1)*(n-i)
```

The first counts:

```text
all subarrays containing index i
```

The second counts:

```text
all valid subarrays ending at right
```

---

## Formula 4 — Monotonic Stack Contribution

```text
(i-prevSmaller) × (nextSmaller-i)
```

Used for contribution problems such as:

```text
Sum of Subarray Minimums
```

Different topic from sliding window.

---

# AtMost Template

```cpp
long long atMost(vector<int>& nums, int k)
{
    if(k < 0)
        return 0;

    int left = 0;
    long long ans = 0;

    for(int right = 0; right < nums.size(); right++)
    {
        // add right

        while(condition > k)
        {
            // remove left
            left++;
        }

        ans += right-left+1;
    }

    return ans;
}
```

Exactly K:

```cpp
return atMost(nums,k) - atMost(nums,k-1);
```

---

# LC 930 — Binary Subarrays With Sum

Two approaches:

```text
1. Prefix Sum + HashMap
2. AtMost Sliding Window
```

AtMost:

```text
ExactlySum(goal)

=

AtMostSum(goal)

-

AtMostSum(goal-1)
```

Template:

```cpp
int atMost(vector<int>& nums, int goal)
{
    if(goal < 0)
        return 0;

    int left = 0;
    int sum = 0;
    int ans = 0;

    for(int right = 0; right < nums.size(); right++)
    {
        sum += nums[right];

        while(sum > goal)
        {
            sum -= nums[left];
            left++;
        }

        ans += right-left+1;
    }

    return ans;
}
```

---

# Prefix Sum vs Sliding Window for Sum == K

## Prefix Sum + HashMap

Works with:

```text
positive
zero
negative
```

For exact sum:

```text
prefix - k
```

---

## Sliding Window

Works when values allow monotonic movement.

Usually:

```text
positive/non-negative numbers
```

Does NOT generally work with negative numbers.

Why?

Because with negatives:

```text
Expanding can decrease sum

Shrinking can increase sum
```

So we cannot reliably decide pointer movement.

---

# Important Rule

For:

```text
sum == K
```

Think:

```text
Negative numbers possible?

YES → Prefix Sum

NO, positive/non-negative → Sliding Window may work
```

For binary/non-negative counting:

```text
AtMost(K)-AtMost(K-1)
```

is very useful.

---

# LC 1248 — Count Number of Nice Subarrays

Convert idea:

```text
odd → contributes 1
even → contributes 0
```

Need:

```text
Exactly K odd numbers
```

Use:

```cpp
atMost(k) - atMost(k-1)
```

Condition:

```text
oddCount <= k
```

---

# LC 992 — Subarrays With K Different Integers

Need:

```text
Exactly K distinct
```

Use:

```text
AtMost(K) - AtMost(K-1)
```

AtMost function:

```cpp
int atMost(vector<int>& nums, int k)
{
    unordered_map<int,int> mp;

    int left = 0;
    int count = 0;

    for(int right = 0; right < nums.size(); right++)
    {
        mp[nums[right]]++;

        while(mp.size() > k)
        {
            mp[nums[left]]--;

            if(mp[nums[left]] == 0)
                mp.erase(nums[left]);

            left++;
        }

        count += right-left+1;
    }

    return count;
}
```

---

# Why Not Just `while(count == k)`?

Because when a window has exactly K,

there may be MANY valid starting positions for the same `right`.

AtMost creates a clean invariant:

```text
Every start from left to right is valid.
```

Therefore:

```text
right-left+1
```

counts all of them at once.

For exact K:

```text
AtMost(K)-AtMost(K-1)
```

isolates exactly K.

---

# 🟣 MODULE 5 — MINIMUM WINDOW PATTERN

Most important example:

```text
LC 76 — Minimum Window Substring
```

Need:

> Smallest substring containing all required characters with correct frequencies.

---

# Need Map

Built from target:

```cpp
unordered_map<char,int> need;

for(char c : t)
{
    need[c]++;
}
```

Example:

```text
t = "AABC"
```

Need:

```text
A : 2
B : 1
C : 1
```

This map does NOT change.

---

# Window Map

Tracks current window:

```cpp
unordered_map<char,int> window;
```

When expanding:

```cpp
window[s[right]]++;
```

When shrinking:

```cpp
window[s[left]]--;
```

---

# `need` vs `have`

Important terminology:

```text
need = number of UNIQUE required characters/categories

have = number of those categories currently fully satisfied
```

Example:

```text
Need map:

A : 2
B : 1
C : 1
```

Then:

```text
needCount = 3
```

NOT 4.

---

Suppose window:

```text
A : 2
B : 1
C : 0
```

Then:

```text
A satisfied ✔
B satisfied ✔
C not satisfied ✘

have = 2
needCount = 3
```

Window valid when:

```text
have == needCount
```

---

# Expanding Logic

```cpp
window[c]++;

if(need.count(c) &&
   window[c] == need[c])
{
    have++;
}
```

Why equality?

Suppose:

```text
need[A] = 2
```

Window changes:

```text
A:1 → not satisfied
A:2 → NOW satisfied → have++
A:3 → already satisfied → don't increment again
```

---

# Shrinking Logic

Store answer BEFORE removing.

Then:

```cpp
char c = s[left];

window[c]--;

if(need.count(c) &&
   window[c] < need[c])
{
    have--;
}

left++;
```

Why `<`?

Suppose:

```text
need[A] = 2
window[A] = 3
```

Remove one:

```text
3 → 2
```

Still satisfied.

Remove again:

```text
2 → 1
```

Now unsatisfied.

Therefore:

```text
window[A] < need[A]
```

causes:

```text
have--
```

---

# LC 76 Template

```cpp
unordered_map<char,int> need;
unordered_map<char,int> window;

for(char c : t)
    need[c]++;

int have = 0;
int needCount = need.size();

int left = 0;

int bestStart = 0;
int minLen = INT_MAX;

for(int right = 0; right < s.size(); right++)
{
    char c = s[right];

    window[c]++;

    if(need.count(c) &&
       window[c] == need[c])
    {
        have++;
    }

    while(have == needCount)
    {
        // STORE BEFORE SHRINKING

        if(right-left+1 < minLen)
        {
            minLen = right-left+1;
            bestStart = left;
        }

        char remove = s[left];

        window[remove]--;

        if(need.count(remove) &&
           window[remove] < need[remove])
        {
            have--;
        }

        left++;
    }
}

if(minLen == INT_MAX)
    return "";

return s.substr(bestStart,minLen);
```

---

# Critical Order in Minimum Window

```text
Window becomes valid

↓

STORE ANSWER

↓

REMOVE s[left]

↓

Update frequency

↓

If requirement breaks → have--

↓

left++
```

Do NOT:

```text
left++

then remove s[left]
```

because then you remove the wrong character.

---

# How to Store a Substring Answer

You usually do NOT need:

```cpp
vector<pair<int,int>>
```

Just store:

```cpp
int bestStart;
int bestLength;
```

Then:

```cpp
return s.substr(bestStart,bestLength);
```

For longest substring:

```cpp
if(right-left+1 > bestLength)
{
    bestLength = right-left+1;
    bestStart = left;
}
```

For minimum substring:

```cpp
if(right-left+1 < bestLength)
{
    bestLength = right-left+1;
    bestStart = left;
}
```

---

# LC 1658 — Minimum Operations to Reduce X to Zero

This is mainly a **transformation problem**.

You may remove only from:

```text
LEFT

or

RIGHT
```

If removed elements sum to:

```text
x
```

then the remaining middle subarray has sum:

```text
totalSum - x
```

Therefore transform:

```text
Minimum removals from ends

↓

Longest middle subarray with sum = totalSum-x
```

Answer:

```text
n - longestLength
```

---

## Template

```cpp
int target = totalSum - x;

if(target < 0)
    return -1;

if(target == 0)
    return n;

int left = 0;
int sum = 0;
int maxLen = -1;

for(int right = 0; right < n; right++)
{
    sum += nums[right];

    while(sum > target)
    {
        sum -= nums[left];
        left++;
    }

    if(sum == target)
    {
        maxLen = max(maxLen,right-left+1);
    }
}

return maxLen == -1 ? -1 : n-maxLen;
```

Important transformation:

```text
Remove minimum elements

=

Keep maximum elements
```

---

# 🟦 ANAGRAM / PERMUTATION PATTERN

# What is an Anagram?

Same characters with exactly the same frequencies.

Example:

```text
"aab"

"aba"

"baa"
```

All have:

```text
a : 2
b : 1
```

Duplicates absolutely matter.

---

# What is a Permutation?

A permutation is one rearrangement.

For:

```text
abc
```

Permutations include:

```text
abc
acb
bac
bca
cab
cba
```

For DSA problems such as LC 438 and LC 567:

```text
Anagram check

and

Permutation check
```

both reduce to:

```text
same length + same character frequencies
```

---

# LC 438 — Find All Anagrams in a String

This is best solved using:

```text
FIXED SIZE WINDOW
```

because every anagram has length:

```text
p.size()
```

Need map:

```cpp
for(char c:p)
    need[c]++;
```

Build a window of:

```text
k = p.size()
```

Then slide one character at a time.

---

## Important unordered_map Issue

When removing:

```cpp
window[c]--;
```

If it becomes:

```text
0
```

erase it:

```cpp
if(window[c] == 0)
    window.erase(c);
```

Why?

Because:

```text
{a:1,b:1,c:0}
```

is NOT equal as an `unordered_map` to:

```text
{a:1,b:1}
```

even though `c` has zero frequency.

---

## LC 438 Template

```cpp
if(s.size() < p.size())
    return {};

unordered_map<char,int> need;
unordered_map<char,int> window;

for(char c:p)
    need[c]++;

int k = p.size();

for(int i=0;i<k;i++)
{
    window[s[i]]++;
}

if(window == need)
    ans.push_back(0);

for(int i=k;i<s.size();i++)
{
    window[s[i]]++;

    char remove = s[i-k];

    window[remove]--;

    if(window[remove] == 0)
        window.erase(remove);

    if(window == need)
        ans.push_back(i-k+1);
}
```

---

# LC 567 — Permutation in String

Almost identical to LC 438.

Difference:

```text
LC 438

Return ALL starting indices
```

```text
LC 567

Return TRUE as soon as one matching window exists
```

---

# LC 438 vs LC 76

They both use frequency concepts, but window strategy differs.

## LC 438

```text
Answer length is known.

Length = p.size()

→ Fixed Window
```

## LC 76

```text
Answer length is unknown.

Need smallest valid window.

→ Variable Minimum Window
```

Rule:

```text
Known answer/window size → Fixed Window

Unknown smallest valid size → Minimum Window
```

---

# 🟤 LC 30 — SUBSTRING WITH CONCATENATION OF ALL WORDS

This is an important combination pattern.

Example:

```text
s = "barfoothefoobarman"

words = ["foo","bar"]
```

Valid:

```text
barfoo

foobar
```

---

# Main Observation 1 — Unit is a WORD

LC 438 stores:

```text
characters
```

LC 30 stores:

```text
whole words
```

Need map:

```cpp
unordered_map<string,int> need;
```

Example:

```text
words = ["foo","bar","foo"]
```

Need:

```text
foo : 2
bar : 1
```

Do NOT store character frequencies.

Why?

```text
"catdog"
```

and:

```text
"tacgod"
```

have the same character frequencies,

but:

```text
tac != cat
god != dog
```

LC 30 requires exact words.

---

# Main Observation 2 — All Words Have Same Length

Suppose:

```text
wordLength = 3
```

We process chunks:

```text
bar
foo
the
```

not individual characters.

Movement:

```cpp
right += wordLength;
left += wordLength;
```

---

# Main Observation 3 — Offsets

If:

```text
wordLength = 3
```

there are 3 possible alignments:

```text
Offset 0:

0,3,6,9,...
```

```text
Offset 1:

1,4,7,10,...
```

```text
Offset 2:

2,5,8,11,...
```

Why?

Suppose valid answer starts at:

```text
index = 7
```

Then:

```text
7 % 3 = 1
```

So it belongs to:

```text
offset 1
```

General rule:

```text
startingIndex % wordLength = offset
```

Therefore number of offsets:

```text
wordLength
```

---

# Mental Model for LC 30

Suppose word length = 3.

Think of separate tracks:

```text
Track 0:

0 → 3 → 6 → 9
```

```text
Track 1:

1 → 4 → 7 → 10
```

```text
Track 2:

2 → 5 → 8 → 11
```

Each track is its own sliding window.

---

# Outer Structure

```cpp
int wordLen = words[0].size();

for(int offset=0; offset<wordLen; offset++)
{
    int left = offset;

    for(int right=offset;
        right+wordLen<=s.size();
        right+=wordLen)
    {
        string word = s.substr(right,wordLen);

        // sliding-window logic
    }
}
```

Important:

```text
LC 30 = Sliding window over WORDS

not characters.
```

---

# 🔵 SLIDING WINDOW MAXIMUM — LC 239

Goal:

For every window of size `k`:

```text
return maximum
```

---

# Approach 1 — Priority Queue / Heap

A max heap can give:

```text
maximum = pq.top()
```

But there is a problem.

If we store only:

```cpp
priority_queue<int>
```

the heap knows:

```text
VALUE
```

but does NOT know:

```text
whether that value is still inside the current window
```

Duplicates make this even more important.

---

# Store Value + Index

Use:

```cpp
priority_queue<pair<int,int>> pq;
```

Store:

```text
(value,index)
```

Example:

```text
(100,0)
(5,3)
```

Now we can determine whether an element is expired.

---

# Current Window Boundaries

At index `right`:

```text
current window:

[right-k+1 ... right]
```

Therefore:

```text
left = right-k+1
```

Any heap element with:

```text
index < left
```

is expired.

Equivalent condition:

```cpp
pq.top().second <= right-k
```

---

# Lazy Deletion

Important concept:

We do NOT need to immediately remove every element when it leaves the window.

An expired element may stay hidden inside the heap.

We only care when it reaches:

```text
pq.top()
```

Then:

```cpp
while(!pq.empty() &&
      pq.top().second < left)
{
    pq.pop();
}
```

This is called:

```text
LAZY DELETION
```

Mental model:

```text
Heap may contain old garbage.

↓

If garbage reaches TOP

↓

Remove it.

↓

Continue until top belongs to current window.
```

---

# Why `== leavingIndex` Is Not Enough

Wrong idea:

```cpp
if(pq.top().second == right-k)
    pq.pop();
```

Suppose an old element left several iterations ago but was hidden below a larger value.

Later it reaches the top.

Its index might be:

```text
0
```

while current leaving index is:

```text
5
```

Checking:

```text
0 == 5
```

fails.

But index 0 is clearly expired.

Therefore check:

```text
index < currentLeft
```

not:

```text
index == justLeftIndex
```

---

# Heap Template

```cpp
priority_queue<pair<int,int>> pq;

vector<int> ans;

for(int right=0; right<nums.size(); right++)
{
    // Add current element
    pq.push({nums[right],right});

    // Current left boundary
    int left = right-k+1;

    // Remove expired TOP elements
    while(!pq.empty() &&
          pq.top().second < left)
    {
        pq.pop();
    }

    // Window is complete
    if(right >= k-1)
    {
        ans.push_back(pq.top().first);
    }
}
```

Complexity:

```text
O(n log n)
```

or effectively heap-based `O(n log n)`.

A better solution exists:

```text
Monotonic Deque → O(n)
```

That is the next pattern to learn.

---

# ⭐ MASTER DECISION TABLE

When you see a problem, ask these questions.

| Problem asks | Think |
|---|---|
| Window/subarray of exactly size K | Fixed Sliding Window |
| Longest window satisfying condition | Variable Window — shrink while invalid |
| Minimum/smallest valid window | Minimum Window — shrink while valid |
| Longest substring without duplicates | HashMap + Variable Window |
| At most K distinct | HashMap + Variable Window |
| Count subarrays with exactly K | AtMost(K) - AtMost(K-1) |
| Exact sum K with negatives | Prefix Sum + HashMap |
| Exact sum K with positive/non-negative values | Sliding Window may work |
| Pattern/anagram of fixed length | Fixed Window + Frequency |
| Smallest substring containing target frequencies | LC 76 have/need pattern |
| Remove from both ends minimum | Try keeping longest middle subarray |
| Equal-length words concatenated | Word-based Sliding Window + offsets |
| Maximum/minimum of every K window | Heap or Monotonic Deque |

---

# ⭐ WHICH `WHILE` CONDITION SHOULD I USE?

This was one of the biggest confusing areas.

## Longest valid window

Shrink when INVALID:

```cpp
while(condition > allowed)
{
    shrink();
}

updateLongest();
```

Example:

```cpp
while(zeros > k)
```

---

## Minimum valid window

Shrink while VALID:

```cpp
while(condition is satisfied)
{
    updateMinimum();

    shrink();
}
```

Example:

```cpp
while(sum >= target)
```

or LC 76:

```cpp
while(have == needCount)
```

---

## Exact target with positive numbers

Usually:

```cpp
while(sum > target)
{
    shrink();
}

if(sum == target)
{
    update();
}
```

---

## AtMost counting

```cpp
while(condition > k)
{
    shrink();
}

count += right-left+1;
```

---

# ⭐ PREFIX SUM VS SLIDING WINDOW

## Use Prefix Sum + HashMap when:

```text
Exact sum K

Negative numbers may exist

Need count of subarrays

Need longest exact-sum subarray with arbitrary integers
```

Typical logic:

```cpp
prefix += nums[i];

if(mp.count(prefix-k))
{
    ...
}
```

---

## Use Sliding Window when:

```text
Contiguous window

Condition changes monotonically

Positive/non-negative values for sum-based shrinking

At most K

Longest/shortest valid range
```

---

# ⭐ COMMON MISTAKES

## 1. Updating longest before fixing invalid window

Wrong:

```cpp
update();

while(invalid)
    shrink();
```

Usually:

```cpp
while(invalid)
    shrink();

update();
```

---

## 2. Minimum window: shrinking before storing

Wrong:

```cpp
remove left;

update answer;
```

Correct:

```cpp
update answer;

remove left;
```

Because current window is valid BEFORE removal.

---

## 3. Moving left before removing

Wrong:

```cpp
left++;
window[s[left]]--;
```

Correct:

```cpp
window[s[left]]--;
left++;
```

Otherwise you remove the next character.

---

## 4. Forgetting to erase zero-frequency map keys

```cpp
mp[x]--;

if(mp[x] == 0)
    mp.erase(x);
```

Important when using:

```text
mp.size()

or

map equality
```

---

## 5. Using map.size() when duplicates matter

Example:

```text
Need:

A:2
B:1
```

Map size is only:

```text
2
```

It doesn't tell whether two A's exist.

Use:

```text
frequency comparison

or

have/need
```

---

## 6. Counting only once in AtMost

Wrong:

```cpp
if(valid)
    count++;
```

Correct:

```cpp
count += right-left+1;
```

because multiple valid subarrays end at the same `right`.

---

## 7. Heap storing only values

Wrong:

```cpp
priority_queue<int>
```

for sliding-window expiry.

Better:

```cpp
priority_queue<pair<int,int>>
```

Store:

```text
value + index
```

so you know whether the element belongs to the current window.

---

# ⭐ CORE TEMPLATES TO MEMORIZE

## Template 1 — Fixed Window

```cpp
for(int right=0; right<n; right++)
{
    add(right);

    if(right-left+1 == k)
    {
        process();

        remove(left);
        left++;
    }
}
```

---

## Template 2 — Longest Valid

```cpp
for(int right=0; right<n; right++)
{
    add(right);

    while(invalid())
    {
        remove(left);
        left++;
    }

    ans = max(ans,right-left+1);
}
```

---

## Template 3 — Minimum Valid

```cpp
for(int right=0; right<n; right++)
{
    add(right);

    while(valid())
    {
        ans = min(ans,right-left+1);

        remove(left);
        left++;
    }
}
```

---

## Template 4 — AtMost Counting

```cpp
for(int right=0; right<n; right++)
{
    add(right);

    while(condition > k)
    {
        remove(left);
        left++;
    }

    count += right-left+1;
}
```

Exactly:

```cpp
exactly(k)
=
atMost(k)-atMost(k-1);
```

---

## Template 5 — Have / Need

```cpp
add(c);

if(required(c) &&
   window[c] == need[c])
{
    have++;
}

while(have == needCount)
{
    storeAnswer();

    remove(c);

    if(required(c) &&
       window[c] < need[c])
    {
        have--;
    }

    left++;
}
```

---

## Template 6 — Fixed Anagram Window

```cpp
Build need map;

Build first window of size k;

Compare;

for(each next character)
{
    add new character;

    remove old character;

    erase frequency if zero;

    compare maps;
}
```

---

## Template 7 — Heap Window

```cpp
for(int right=0; right<n; right++)
{
    pq.push({nums[right],right});

    int left = right-k+1;

    while(!pq.empty() &&
          pq.top().second < left)
    {
        pq.pop();
    }

    if(right >= k-1)
    {
        ans.push_back(pq.top().first);
    }
}
```

---

# 🧠 FINAL MENTAL MODEL

Do NOT memorize every problem separately.

Ask:

```text
1. Is the range contiguous?

2. Is window size fixed or variable?

3. What makes the window INVALID?

4. Am I finding LONGEST or MINIMUM?

5. Am I COUNTING all valid subarrays?

6. Do frequencies/duplicates matter?

7. Is this EXACTLY K?
   → Can AtMost(K)-AtMost(K-1) work?

8. Are there negative numbers?
   → Sum-based sliding window may fail.

9. Do I need to return the actual substring?
   → Store start + length.

10. Do elements expire from a data structure?
    → Store indices.
```

Then select the pattern:

```text
FIXED SIZE
        ↓
Fixed Sliding Window


LONGEST VALID
        ↓
Expand → Shrink while invalid → Update


MINIMUM VALID
        ↓
Expand → Shrink while valid → Update before removal


COUNT EXACTLY K
        ↓
AtMost(K) - AtMost(K-1)


FREQUENCY REQUIREMENTS
        ↓
Need Map + Window Map


DUPLICATE REQUIREMENTS
        ↓
Compare frequencies / Have-Need


ANAGRAM / PERMUTATION
        ↓
Fixed Window + Frequency


REMOVE FROM BOTH ENDS
        ↓
Think: Keep longest middle


EQUAL-LENGTH WORDS
        ↓
Word chunks + offsets


MAX/MIN OF EVERY WINDOW
        ↓
Heap with indices
        ↓
Then optimize to Monotonic Deque
```

---

# 📌 Problems Completed / Studied

## Fixed Window

- Maximum Sum Subarray of Size K
- LC 643
- LC 1343
- LC 1456
- LC 2090
- First Negative in Every Window
- Count Distinct in Every Window

## Variable Window

- LC 1004 — Max Consecutive Ones III
- LC 1493 — Longest Subarray After Deleting One
- LC 209 — Minimum Size Subarray Sum
- LC 674 — LCIS

## HashMap Window

- LC 3 — Longest Substring Without Repeating
- Longest Substring At Most K Distinct
- Longest Substring Exactly K Distinct
- LC 904 — Fruits Into Baskets
- LC 1695 — Maximum Erasure Value

## AtMost Trick

- LC 930 — Binary Subarrays With Sum
- LC 1248 — Count Nice Subarrays
- LC 992 — Subarrays With K Different Integers

## Minimum / Frequency Window

- LC 76 — Minimum Window Substring
- LC 1658 — Minimum Operations to Reduce X to Zero
- LC 438 — Find All Anagrams
- LC 567 — Permutation in String

## Advanced Combination

- LC 30 — Substring With Concatenation of All Words
- LC 239 — Sliding Window Maximum (Heap approach currently learned)

---

# 🚀 NEXT TOPIC

Next complete:

```text
Monotonic Deque
```

Main problem:

```text
LC 239 — Sliding Window Maximum
```

You currently know the heap idea:

```text
Store (value,index)

↓

Remove expired indices lazily

↓

Heap top = maximum
```

Next learn why a deque can remove useless elements immediately and achieve:

```text
O(n)
```

instead of heap-based:

```text
O(n log n)
```

After Monotonic Deque, the major placement-oriented Sliding Window patterns are essentially complete.