# SQL — Subqueries & SQL Problem Solving

## 1. What is a Subquery?

A **subquery** is a SQL query written inside another SQL query.

The inner query produces a result that is used by the outer query.

```sql
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

### Mental Model

```text
INNER QUERY
    ↓
produces a result
    ↓
OUTER QUERY uses that result
```

Think of it like a function returning a value:

```text
Programming:
average = calculateAverage()
salary > average

SQL:
salary > (SELECT AVG(salary) ...)
```

---

## 2. Basic Subquery Syntax

```sql
SELECT ...
FROM ...
WHERE column operator (
    SELECT ...
    FROM ...
);
```

The subquery is normally placed inside parentheses:

```sql
(
    SELECT ...
)
```

---

## 3. Single-Value Subquery

A subquery can return **one value**.

Example:

```sql
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

The inner query:

```sql
SELECT AVG(salary)
FROM employees;
```

returns one value, such as:

```text
67000
```

The outer query effectively becomes:

```sql
WHERE salary > 67000
```

### Common operators with single-value subqueries

```text
=       equal
>       greater than
<       less than
>=      greater than or equal
<=      less than or equal
<>      not equal
```

Example:

```sql
WHERE salary = (
    SELECT MAX(salary)
    FROM employees
);
```

---

## 4. Multi-Value Subquery

A subquery can return **multiple values**.

Example:

```sql
SELECT department
FROM departments;
```

might return:

```text
AI
CSE
HR
```

You cannot normally use:

```sql
WHERE department = (
    SELECT department
    FROM departments
);
```

because `=` expects a single value.

Use `IN` for multiple values:

```sql
SELECT name
FROM employees
WHERE department IN (
    SELECT department
    FROM departments
);
```

### Mental Model

```text
=   → one value
IN  → multiple values
```

---

## 5. `IN` with a Subquery

`IN` checks whether a value exists in the result produced by the subquery.

```sql
SELECT name
FROM employees
WHERE department IN (
    SELECT department
    FROM departments
);
```

Mental model:

```text
Subquery
    ↓
[AI, CSE, HR]
    ↓
Is employee.department inside this list?
    ↓
YES → keep employee
NO  → discard employee
```

---

## 6. `NOT IN`

`NOT IN` does the opposite.

```sql
SELECT name
FROM employees
WHERE department NOT IN (
    SELECT department
    FROM departments
);
```

Meaning:

> Return employees whose department does not appear in the subquery result.

### Important Interview Trap

Be careful with `NULL` and `NOT IN`.

If the subquery result contains `NULL`, `NOT IN` can produce unexpected results because SQL uses three-valued logic:

```text
TRUE
FALSE
UNKNOWN
```

For "doesn't exist" logic, `NOT EXISTS` is often safer when `NULL` may be involved.

---

## 7. `SELECT` in SQL

`SELECT` tells SQL **which columns/values should appear in the final result**.

It is somewhat similar to `return` in programming, but it is better to think of it as:

> "What do I want in my result?"

Example:

```sql
SELECT name, salary
FROM employees;
```

returns both:

```text
name
salary
```

If:

```sql
SELECT name
FROM employees;
```

only the name is returned.

If:

```sql
SELECT salary
FROM employees;
```

only the salary is returned.

If:

```sql
SELECT *
FROM employees;
```

all selected table columns are returned.

### Basic Mental Model

```text
FROM
↓
Where do the rows come from?

WHERE
↓
Which rows should remain?

SELECT
↓
What information should I show from those rows?
```

---

## 8. Aggregate Functions and `WHERE`

Aggregate functions such as:

```text
COUNT()
SUM()
AVG()
MIN()
MAX()
```

cannot normally be used directly in `WHERE` like this:

```sql
WHERE salary > AVG(salary);
```

❌ Invalid in this form.

Why?

```text
WHERE
↓
filters individual rows

AVG()
↓
calculates an aggregate over multiple rows
```

To compare an individual row with an aggregate value, use a subquery:

```sql
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

---

## 9. Aggregate Functions and `HAVING`

Aggregate functions can be used in `HAVING`.

```sql
SELECT department, AVG(salary)
FROM employees
GROUP BY department
HAVING AVG(salary) > 60000;
```

Why?

```text
WHERE
→ filters individual rows

GROUP BY
→ creates groups

HAVING
→ filters groups
→ aggregates are available here
```

### Important

```sql
WHERE salary > AVG(salary)
```

❌

```sql
HAVING AVG(salary) > 60000
```

✅

---

## 10. Normal Subquery vs Correlated Subquery

### Normal Subquery

The inner query is independent of the outer query.

```sql
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

The average is the same comparison value for every employee.

```text
Overall average
      ↓
Compare every employee
```

---

### Correlated Subquery

The inner query depends on the current row of the outer query.

```sql
SELECT e.name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM employees e2
    WHERE e2.department = e.department
);
```

Now the average depends on the employee's department.

```text
Current employee
      ↓
Find their department
      ↓
Calculate that department's average
      ↓
Compare employee salary
```

---

## 11. Why Aliases Are Used in Correlated Subqueries

In this query:

```sql
SELECT e.name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM employees e2
    WHERE e2.department = e.department
);
```

The same table is referenced twice:

```text
employees e
    ↓
outer query

employees e2
    ↓
inner query
```

Aliases distinguish the two references.

```text
e  → outer employee
e2 → inner employees
```

Therefore:

```sql
e2.department = e.department
```

means:

> The inner employee's department must equal the current outer employee's department.

### Important

Aliases are **not only for JOINs**.

They are useful whenever the same table is referenced multiple times.

---

## 12. Correlated Subquery — Programming Mental Model

Think of:

```sql
SELECT e.name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM employees e2
    WHERE e2.department = e.department
);
```

like:

```text
for each employee e:

    find employees e2
    whose department == e.department

    calculate their average salary

    if e.salary > that average:
        keep e
```

This is why correlated subqueries can conceptually resemble nested loops.

### Complexity Warning

A naive mental model can look like:

```text
Outer query → N rows
Inner query → potentially N rows
                 ↓
              O(N²)
```

But **do not assume the database literally executes it as O(N²)**.

The database optimizer may use indexes, rewrite the query, cache results, or choose another execution plan.

---

## 13. `EXISTS`

`EXISTS` asks:

> **Does the subquery return at least one row?**

It behaves like a boolean condition.

```text
matching row exists?
       ↓
YES → TRUE
NO  → FALSE
```

Example:

```sql
SELECT s.name
FROM students s
WHERE EXISTS (
    SELECT 1
    FROM orders o
    WHERE o.student_id = s.student_id
);
```

Meaning:

> For each student, does at least one matching order exist?

---

## 14. Why `SELECT 1` Is Used with `EXISTS`

Inside `EXISTS`, SQL does **not care about the actual selected value**.

These are all valid:

```sql
SELECT 1
FROM orders
WHERE student_id = s.student_id;
```

```sql
SELECT 0
FROM orders
WHERE student_id = s.student_id;
```

```sql
SELECT *
FROM orders
WHERE student_id = s.student_id;
```

```sql
SELECT order_id
FROM orders
WHERE student_id = s.student_id;
```

`EXISTS` only asks:

> Did the subquery return at least one row?

`SELECT 1` is simply a common convention that communicates:

> "I only care whether a row exists."

---

## 15. `NOT EXISTS`

`NOT EXISTS` reverses the condition.

```text
EXISTS
→ matching row exists

NOT EXISTS
→ matching row does not exist
```

Example:

```sql
SELECT s.name
FROM students s
WHERE NOT EXISTS (
    SELECT 1
    FROM orders o
    WHERE o.student_id = s.student_id
);
```

Meaning:

> Find students who have no orders.

---

## 16. `IN` vs `EXISTS`

### `IN`

Asks:

> Is this value present in the subquery's result?

```sql
SELECT name
FROM employees
WHERE department IN (
    SELECT department
    FROM departments
);
```

Mental model:

```text
Subquery
↓
[AI, CSE, HR]
↓
Is my department in this list?
```

---

### `EXISTS`

Asks:

> Does a matching row exist?

```sql
SELECT c.name
FROM customers c
WHERE EXISTS (
    SELECT 1
    FROM orders o
    WHERE o.customer_id = c.customer_id
);
```

Mental model:

```text
Current customer
      ↓
Does a matching order exist?
      ↓
YES → keep
NO  → discard
```

### Main Difference

```text
IN
→ compare a value against returned values

EXISTS
→ check whether a matching row exists
```

`EXISTS` is especially useful with correlated subqueries.

---

## 17. `UNION`

`UNION` combines the result sets of two queries **vertically**.

It does NOT match rows like a JOIN.

```sql
SELECT name
FROM employees
WHERE department = 'AI'

UNION

SELECT name
FROM employees
WHERE department = 'CSE';
```

Mental model:

```text
Query 1
   ↓
rows

+

Query 2
   ↓
rows

↓

combined result
```

### JOIN vs UNION

```text
JOIN
→ combines tables horizontally
→ connects related rows
→ usually uses ON

UNION
→ combines result sets vertically
→ does not match rows
```

---

## 18. `UNION` Removes Duplicate Rows

Example:

```text
Query 1:
Harsha
Rahul

Query 2:
Rahul
Arjun
```

Using:

```sql
UNION
```

produces:

```text
Harsha
Rahul
Arjun
```

The duplicate `Rahul` is removed.

---

## 19. `UNION ALL`

`UNION ALL` combines result sets but **keeps duplicates**.

```sql
SELECT name
FROM table1

UNION ALL

SELECT name
FROM table2;
```

Example:

```text
Query 1:
Harsha
Rahul

Query 2:
Rahul
Arjun
```

Result:

```text
Harsha
Rahul
Rahul
Arjun
```

### Difference

```text
UNION
→ remove duplicate selected rows

UNION ALL
→ keep duplicate selected rows
```

---

## 20. Entire Selected Row Matters in Set Operations

For:

```text
UNION
INTERSECT
EXCEPT
```

the database compares the **entire row produced by the SELECT**.

Example:

Table 1:

```text
name    salary
Harsha  70000
Rahul   60000
```

Table 2:

```text
name    salary
Harsha  80000
Rahul   65000
```

Query:

```sql
SELECT name, salary
FROM table1

UNION

SELECT name, salary
FROM table2;
```

Result:

```text
Harsha  70000
Harsha  80000
Rahul   60000
Rahul   65000
```

Why?

```text
Rahul | 60000
Rahul | 65000
```

are different complete rows.

Therefore both remain.

---

## 21. If Only `name` Is Selected

Now:

```sql
SELECT name
FROM table1

UNION

SELECT name
FROM table2;
```

The result sets are:

```text
Table 1:
Harsha
Rahul

Table 2:
Harsha
Rahul
```

Result:

```text
Harsha
Rahul
```

The different salaries are completely ignored because `salary` was not selected.

### Rule

```text
SELECT name
→ comparison is based on name

SELECT name, salary
→ comparison is based on name + salary

SELECT name, salary, department
→ comparison is based on name + salary + department
```

This same rule applies to:

```text
UNION
INTERSECT
EXCEPT
```

---

## 22. `INTERSECT`

`INTERSECT` returns rows that exist in **both result sets**.

```sql
SELECT name
FROM table1

INTERSECT

SELECT name
FROM table2;
```

Example:

```text
Query 1:
Harsha
Rahul
Arjun

Query 2:
Rahul
Arjun
Priya
```

Result:

```text
Rahul
Arjun
```

### With Multiple Columns

If:

```sql
SELECT name, salary
FROM table1

INTERSECT

SELECT name, salary
FROM table2;
```

then the complete:

```text
name + salary
```

must match.

```text
Rahul | 60000
```

matches:

```text
Rahul | 60000
```

but:

```text
Rahul | 60000
```

does NOT match:

```text
Rahul | 65000
```

---

## 23. `EXCEPT`

`EXCEPT` returns rows that exist in the **first result but not the second result**.

```sql
SELECT name
FROM table1

EXCEPT

SELECT name
FROM table2;
```

Example:

```text
Table 1:
Harsha
Rahul
Arjun

Table 2:
Rahul
Arjun
Priya
```

Result:

```text
Harsha
```

### With Multiple Columns

```sql
SELECT name, salary
FROM table1

EXCEPT

SELECT name, salary
FROM table2;
```

Again, the **complete selected row** is compared.

---

## 24. Set Operations — Quick Comparison

| Operator | Meaning |
|---|---|
| `UNION` | Combine both results, remove duplicate rows |
| `UNION ALL` | Combine both results, keep duplicates |
| `INTERSECT` | Rows common to both results |
| `EXCEPT` | Rows in first result but not second |

Mental model:

```text
A + B       → UNION
A + B with duplicates → UNION ALL
A ∩ B       → INTERSECT
A - B       → EXCEPT
```

---

## 25. Set Operation Column Rule

Queries combined with set operators must return compatible numbers/types of columns.

Valid:

```sql
SELECT name
FROM employees

UNION

SELECT name
FROM contractors;
```

Both return one column.

Invalid:

```sql
SELECT name, salary
FROM employees

UNION

SELECT name
FROM contractors;
```

One query returns two columns while the other returns one.

---

# Placement SQL Problems

## 26. Second Highest Salary

Given:

```text
employees
--------------------------------
id | name   | department | salary
1  | Harsha | AI         | 70000
2  | Rahul  | CSE        | 60000
3  | Arjun  | AI         | 80000
4  | Priya  | HR         | 50000
5  | Kiran  | CSE        | 75000
```

Goal:

> Find the second-highest salary.

### Logic

```text
Highest salary
      ↓
80000

Salaries below highest
      ↓
60000, 70000, 75000

MAX of those
      ↓
75000
```

### Query

```sql
SELECT MAX(e1.salary)
FROM employees e1
WHERE e1.salary < (
    SELECT MAX(e2.salary)
    FROM employees e2
);
```

Result:

```text
75000
```

### Key Trick

The subquery acts like a value:

```sql
e1.salary < (
    SELECT MAX(e2.salary)
    FROM employees e2
)
```

The inner `MAX()` produces `80000`, which becomes the comparison value.

---

## 27. Second Highest Salary — Returning Employee

```sql
SELECT e.name, e.salary
FROM employees e
WHERE e.salary = (
    SELECT MAX(e1.salary)
    FROM employees e1
    WHERE e1.salary < (
        SELECT MAX(e2.salary)
        FROM employees e2
    )
);
```

Result:

```text
Kiran | 75000
```

### Important

Do not think you need a programming variable such as:

```text
maxSalary = ...
```

A scalar subquery can directly produce the value.

---

## 28. Third Highest Salary — Nested Logic

The same logic can be extended:

```text
1st highest
    ↓
MAX(all salaries)

2nd highest
    ↓
MAX(salary below 1st)

3rd highest
    ↓
MAX(salary below 2nd)
```

Manual nesting becomes increasingly ugly for larger `N`.

For general Nth-highest problems, window functions are usually more practical, but **window functions are intentionally being skipped for now**.

---

## 29. Finding Duplicate Values

Question:

> Find customer names that appear more than once.

The simplest solution does **not** require a subquery.

```sql
SELECT name
FROM customers
GROUP BY name
HAVING COUNT(name) > 1;
```

Mental model:

```text
GROUP BY name
      ↓
create one group per name
      ↓
COUNT()
      ↓
HAVING COUNT() > 1
      ↓
duplicates
```

### Placement Pattern

Whenever the question says:

> "Find values that occur more than once"

think:

```text
GROUP BY column
      ↓
COUNT()
      ↓
HAVING COUNT() > 1
```

Do not force a subquery when `GROUP BY + HAVING` solves it directly.

---

## 30. Duplicate Customer IDs

Given:

```text
orders
--------------------------------
order_id | customer_id | amount
101      | 1            | 500
102      | 2            | 300
103      | 1            | 700
104      | 3            | 200
105      | 1            | 400
106      | 2            | 800
```

Question:

> Find customer IDs who placed more than one order.

Answer:

```sql
SELECT customer_id
FROM orders
GROUP BY customer_id
HAVING COUNT(customer_id) > 1;
```

Result:

```text
1
2
```

---

## 31. Employees Above Overall Average

Question:

> Find employees whose salary is greater than the overall average salary.

```sql
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

### Pattern

```text
overall average
      ↓
subquery
      ↓
compare each employee
      ↓
WHERE
```

This is a **normal subquery** because the inner query does not depend on the outer employee.

---

## 32. Employees Above Their Department Average

Question:

> Find employees whose salary is greater than the average salary of their own department.

```sql
SELECT e.name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM employees e2
    WHERE e2.department = e.department
);
```

### Why Correlated?

The inner query depends on:

```sql
e.department
```

from the outer query.

Therefore:

```text
current employee
      ↓
their department
      ↓
calculate that department's average
      ↓
compare salary
```

---

## 33. Highest Salary Per Department

Question:

> Find the employee with the highest salary in each department.

```sql
SELECT e.name, e.department, e.salary
FROM employees e
WHERE e.salary = (
    SELECT MAX(e2.salary)
    FROM employees e2
    WHERE e2.department = e.department
);
```

### Important Trick

This query:

```sql
SELECT MAX(e.salary)
FROM employees e
GROUP BY department;
```

returns **multiple values**:

```text
80000
75000
50000
```

Therefore this is wrong:

```sql
WHERE salary = (
    SELECT MAX(salary)
    FROM employees
    GROUP BY department
);
```

because `=` expects one value.

The correlated version calculates the maximum for the **current employee's department**.

---

## 34. Employees Earning More Than Their Manager — SELF JOIN

Given:

```text
employees
------------------------------------
emp_id | name   | salary | manager_id
1      | Harsha | 90000  | NULL
2      | Rahul  | 60000  | 1
3      | Arjun  | 95000  | 1
4      | Priya  | 50000  | 2
5      | Kiran  | 70000  | 2
```

A SELF JOIN solution:

```sql
SELECT e.name, e.salary
FROM employees e
JOIN employees m
ON e.manager_id = m.emp_id
WHERE e.salary > m.salary;
```

Here:

```text
e → employee
m → manager
```

The relationship is:

```text
employee.manager_id
        ↓
manager.emp_id
```

---

## 35. Employees Earning More Than Their Manager — Correlated Subquery

The same problem can be solved using a correlated subquery:

```sql
SELECT e.name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT m.salary
    FROM employees m
    WHERE m.emp_id = e.manager_id
);
```

### Mental Model

For each employee:

```text
employee
   ↓
get manager_id
   ↓
find employee whose emp_id = manager_id
   ↓
get manager salary
   ↓
compare salaries
```

Example:

```text
Arjun
salary = 95000
manager_id = 1
        ↓
manager salary = 90000
        ↓
95000 > 90000
        ↓
YES
```

Result:

```text
Arjun
Kiran
```

### JOIN vs Correlated Subquery

```text
SELF JOIN
→ connect employee to manager
→ compare

CORRELATED SUBQUERY
→ for current employee, find manager
→ get manager salary
→ compare
```

Both can solve the same problem.

---

## 36. JOIN vs Subquery — Do Not Force One Technique

A question may have multiple valid solutions.

Example:

> Employees above department average.

Can be solved using a correlated subquery:

```sql
SELECT e.name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM employees e2
    WHERE e2.department = e.department
);
```

Or by calculating department averages first and joining them:

```sql
SELECT e.name, e.salary
FROM employees e
JOIN (
    SELECT department, AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
) d
ON e.department = d.department
WHERE e.salary > d.avg_salary;
```

### Placement Lesson

Do not think:

```text
"I'm studying subqueries"
        ↓
"Every question must use a subquery"
```

Instead:

```text
Understand the requirement
        ↓
Choose the simplest suitable SQL technique
```

---

## 37. Most Important Subquery Mental Models

### Single value

```text
Subquery
   ↓
one value
   ↓
=, >, <, >=, <= ...
```

### Multiple values

```text
Subquery
   ↓
multiple values
   ↓
IN / NOT IN
```

### Correlated

```text
Outer current row
       ↓
Inner query depends on it
       ↓
result
```

### EXISTS

```text
Does at least one matching row exist?
       ↓
TRUE / FALSE
```

### NOT EXISTS

```text
Does a matching row NOT exist?
       ↓
TRUE / FALSE
```

---

## 38. Subquery Placement Tricks

### "Greater than the average"

```text
average → subquery
```

```sql
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

### "Equal to maximum"

```text
MAX → subquery
```

```sql
WHERE salary = (
    SELECT MAX(salary)
    FROM employees
);
```

### "Belongs to one of these values"

```text
multiple values → IN
```

```sql
WHERE department IN (
    SELECT department
    FROM departments
);
```

### "Has at least one matching record"

```text
EXISTS
```

### "Has no matching record"

```text
NOT EXISTS
```

### "Of their department/team/category"

🚨 Think:

```text
correlated subquery
```

because the inner calculation depends on the current outer row.

---

## 39. Common Subquery Mistakes

### Mistake 1 — Aggregate directly in WHERE

```sql
WHERE salary > AVG(salary)
```

❌

Use:

```sql
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
)
```

---

### Mistake 2 — Using `=` when subquery returns multiple rows

```sql
WHERE salary = (
    SELECT MAX(salary)
    FROM employees
    GROUP BY department
);
```

❌

Because the subquery returns multiple values.

Possible alternative:

```sql
WHERE salary IN (
    SELECT MAX(salary)
    FROM employees
    GROUP BY department
);
```

But this has different semantics from matching each employee to the maximum of **their own department**.

For that requirement, use a correlated subquery.

---

### Mistake 3 — Forgetting correlation

Wrong idea:

```sql
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
```

This compares against the **overall average**.

If the question says:

> average of their department

you need:

```sql
WHERE e2.department = e.department
```

---

### Mistake 4 — Confusing `IN` and `EXISTS`

```text
IN
→ compare value with returned values

EXISTS
→ check whether a matching row exists
```

---

### Mistake 5 — Thinking `SELECT 1` is mandatory for EXISTS

It isn't.

```sql
SELECT 1
```

is just the common convention.

`EXISTS` cares about whether the subquery returns a row.

---

### Mistake 6 — Forcing subqueries

Not every problem needs a subquery.

For duplicates:

```sql
SELECT name
FROM customers
GROUP BY name
HAVING COUNT(name) > 1;
```

is simpler than inventing a subquery.

---

# 40. Subqueries — Quick Interview Revision

```text
Subquery
→ query inside another query

Single-value subquery
→ returns one value
→ use =, >, <, etc.

Multi-value subquery
→ returns multiple values
→ use IN / NOT IN

Correlated subquery
→ inner query depends on outer query

EXISTS
→ does at least one matching row exist?

NOT EXISTS
→ does no matching row exist?

UNION
→ vertically combines result sets
→ removes duplicate selected rows

UNION ALL
→ vertically combines result sets
→ keeps duplicates

INTERSECT
→ common selected rows

EXCEPT
→ rows from first result not in second

Set operators compare
→ the complete row produced by SELECT
```

---

# 41. Important Placement Patterns

```text
"greater than average"
→ AVG() subquery

"equal to maximum"
→ MAX() subquery

"equal to minimum"
→ MIN() subquery

"belongs to departments returned by another query"
→ IN

"does a matching record exist?"
→ EXISTS

"doesn't have a matching record?"
→ NOT EXISTS

"of their department/team/category"
→ correlated subquery

"second highest"
→ MAX() + condition below highest

"duplicates"
→ GROUP BY + COUNT + HAVING

"highest per department"
→ correlated subquery or GROUP BY + JOIN

"employee greater than manager"
→ SELF JOIN or correlated subquery
```

---

# 42. Module 5 Progress

```text
Subqueries                  ✅
Single-value subqueries     ✅
Multi-value subqueries      ✅
IN / NOT IN                 ✅
Correlated subqueries       ✅
EXISTS / NOT EXISTS         ✅
UNION / UNION ALL           ✅
INTERSECT / EXCEPT          ✅

Placement Problems:
Second highest salary       ✅
Duplicate values            ✅
Above overall average       ✅
Highest per department      ✅
Above manager salary        ✅

Still to practice:
Employees without department
Customers without orders
Consecutive records
More classic placement problems
```

---

# 43. Final Mental Model

```text
SQL Problem
     ↓
Understand what the question is asking
     ↓
Does it need an aggregate value?
     ↓
Can GROUP BY/HAVING solve it?
     ↓
If a value comes from another query
     → Subquery
     ↓
One value?
     → =, >, <, etc.
     ↓
Multiple values?
     → IN
     ↓
Need to check whether a row exists?
     → EXISTS
     ↓
Need the result to depend on the current outer row?
     → Correlated Subquery
```

> **Don't memorize subquery syntax first. Identify what result you need from the inner query, then decide how the outer query should use that result.**