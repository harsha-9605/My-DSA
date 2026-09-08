# SQL — JOINs

## 1. What is a JOIN?

A **JOIN** is used to combine data from two or more tables using a related column.

Example:

### Students

| student_id | name |
|---:|---|
| 1 | Harsha |
| 2 | Rahul |
| 3 | Arjun |

### Orders

| order_id | student_id | amount |
|---:|---:|---:|
| 101 | 1 | 500 |
| 102 | 1 | 700 |
| 103 | 2 | 300 |

The relationship is:

```text
students.student_id
        ↓
orders.student_id
```

The `student_id` in `orders` tells us which student made the order.

### Mental Model

```text
JOIN
 ↓
Connect related tables
 ↓
ON
 ↓
Tell SQL how the tables are related
```

---

## 2. Basic JOIN Syntax

```sql
SELECT columns
FROM table1
JOIN table2
ON table1.column = table2.column;
```

Example:

```sql
SELECT students.name, orders.order_id, orders.amount
FROM students
JOIN orders
ON students.student_id = orders.student_id;
```

### Meaning

```text
SELECT → What do I want to display?

FROM → Which table am I starting with?

JOIN → Which table am I connecting?

ON → How are the tables related?
```

---

## 3. Table.Column Notation

When using multiple tables, we can specify which table a column belongs to.

```sql
students.student_id
orders.student_id
```

Meaning:

```text
students.student_id
→ student_id from students table

orders.student_id
→ student_id from orders table
```

General format:

```text
table_name.column_name
```

This is especially useful when both tables contain columns with the same name.

---

# INNER JOIN

## 4. INNER JOIN

**INNER JOIN returns only rows that have a match in both tables.**

```sql
SELECT students.name, orders.order_id, orders.amount
FROM students
INNER JOIN orders
ON students.student_id = orders.student_id;
```

Result:

| name | order_id | amount |
|---|---:|---:|
| Harsha | 101 | 500 |
| Harsha | 102 | 700 |
| Rahul | 103 | 300 |

Arjun is not included because Arjun has no matching order.

### Mental Model

```text
INNER JOIN
     ↓
Matching rows only
```

---

## 5. JOIN vs INNER JOIN

These are normally equivalent:

```sql
FROM students
JOIN orders
ON students.student_id = orders.student_id;
```

and:

```sql
FROM students
INNER JOIN orders
ON students.student_id = orders.student_id;
```

So:

```text
JOIN = INNER JOIN
```

when no other JOIN type is specified.

---

## 6. INNER JOIN Can Produce Duplicates

If Harsha has two orders:

```text
Harsha → Order 101
Harsha → Order 102
```

the JOIN produces:

| name | order_id |
|---|---:|
| Harsha | 101 |
| Harsha | 102 |

JOIN does **not** automatically give one row per student.

It produces matching row combinations.

---

## 7. DISTINCT with JOIN

If the question asks:

> Find students who have placed at least one order.

We may get duplicate students because one student can have multiple orders.

Use:

```sql
SELECT DISTINCT students.name
FROM students
JOIN orders
ON students.student_id = orders.student_id;
```

### Mental Model

```text
JOIN
 ↓
Find matching students
 ↓
DISTINCT
 ↓
Remove duplicate students
```

---

# LEFT JOIN

## 8. LEFT JOIN

A **LEFT JOIN keeps all rows from the left table** and matching rows from the right table.

```sql
SELECT students.name, orders.order_id
FROM students
LEFT JOIN orders
ON students.student_id = orders.student_id;
```

Result:

| name | order_id |
|---|---:|
| Harsha | 101 |
| Harsha | 102 |
| Rahul | 103 |
| Arjun | NULL |

Arjun stays even though he has no order.

### Mental Model

```text
LEFT JOIN
 ↓
Keep EVERYTHING from LEFT table
 +
Matching rows from RIGHT table
```

---

## 9. Why LEFT JOIN Gives NULL

Suppose:

```text
Arjun
student_id = 3
```

There is no order with:

```text
student_id = 3
```

LEFT JOIN still keeps Arjun.

Since there is no matching order:

```text
Arjun | NULL
```

The columns from the unmatched right table become `NULL`.

---

## 10. Choosing the LEFT Table

If the question says:

> Show ALL students, including students who have no orders.

Use:

```sql
FROM students
LEFT JOIN orders
ON students.student_id = orders.student_id;
```

Because `students` is the table that must be preserved.

If the question says:

> Show ALL orders, including orders without a matching student.

You can instead start with:

```sql
FROM orders
LEFT JOIN students
ON orders.student_id = students.student_id;
```

### Trick

```text
Question says ALL X
        ↓
Start with X
        ↓
LEFT JOIN the other table
```

---

## 11. Finding Records With No Match

Classic placement pattern:

> Find students who have never placed an order.

```sql
SELECT students.name
FROM students
LEFT JOIN orders
ON students.student_id = orders.student_id
WHERE orders.order_id IS NULL;
```

### Why?

First:

```text
LEFT JOIN
 ↓
Keep every student
```

Students without orders get:

```text
orders.order_id = NULL
```

Then:

```sql
WHERE orders.order_id IS NULL
```

keeps only students with no matching order.

### General Pattern

```sql
SELECT ...
FROM A
LEFT JOIN B
ON A.key = B.key
WHERE B.some_column IS NULL;
```

Meaning:

> Find rows from A that have no matching row in B.

---

# RIGHT JOIN

## 12. RIGHT JOIN

A **RIGHT JOIN keeps all rows from the right table** and matching rows from the left table.

```sql
SELECT students.name, orders.order_id
FROM students
RIGHT JOIN orders
ON students.student_id = orders.student_id;
```

### Mental Model

```text
RIGHT JOIN
 ↓
Keep EVERYTHING from RIGHT table
 +
Matching rows from LEFT table
```

For:

```sql
FROM students
RIGHT JOIN orders
```

the `orders` table is the right table.

Therefore all orders remain.

---

## 13. LEFT JOIN vs RIGHT JOIN

```text
LEFT JOIN
→ Keep everything from LEFT

RIGHT JOIN
→ Keep everything from RIGHT
```

Example:

```sql
FROM students
LEFT JOIN orders
```

→ Keep all students.

```sql
FROM students
RIGHT JOIN orders
```

→ Keep all orders.

### Practical Note

A RIGHT JOIN can often be rewritten as a LEFT JOIN by swapping the tables.

```sql
FROM students
RIGHT JOIN orders
ON students.student_id = orders.student_id;
```

is equivalent in purpose to:

```sql
FROM orders
LEFT JOIN students
ON orders.student_id = students.student_id;
```

---

# FULL OUTER JOIN

## 14. FULL OUTER JOIN

A **FULL OUTER JOIN keeps everything from both tables**.

```sql
SELECT students.name, orders.order_id
FROM students
FULL OUTER JOIN orders
ON students.student_id = orders.student_id;
```

### Mental Model

```text
FULL OUTER JOIN
 ↓
Everything from LEFT
 +
Everything from RIGHT
 +
Matches where available
```

If a student has no order:

```text
Arjun | NULL
```

If an order has no matching student:

```text
NULL | 104
```

---

## 15. FULL OUTER JOIN Example

Students:

| student_id | name |
|---:|---|
| 1 | Harsha |
| 2 | Rahul |
| 3 | Arjun |

Orders:

| order_id | student_id |
|---:|---:|
| 101 | 1 |
| 102 | 2 |
| 103 | 5 |

Result:

| name | order_id |
|---|---:|
| Harsha | 101 |
| Rahul | 102 |
| Arjun | NULL |
| NULL | 103 |

Both unmatched sides are kept.

---

## 16. FULL OUTER JOIN Database Support

PostgreSQL and SQL Server support `FULL OUTER JOIN`.

MySQL does not have native `FULL OUTER JOIN` syntax.

For placement interviews, remember the concept first.

---

# SELF JOIN

## 17. SELF JOIN

A **SELF JOIN** means joining a table with itself.

```text
Same table
    ↓
Use it twice
    ↓
Give each use a different alias
    ↓
Compare/connect rows
```

Basic structure:

```sql
FROM employees e
JOIN employees m
ON ...;
```

Here:

```text
employees → e
employees → m
```

Both refer to the same table.

---

## 18. Important: Aliases Do NOT Have Fixed Meanings

If we write:

```sql
FROM employees e
JOIN employees m
```

SQL does NOT automatically know:

```text
e = employee
m = manager
```

`e` and `m` are just aliases.

We decide what role each alias represents.

For example:

```text
e = employee
m = manager
```

or:

```text
e = manager
m = employee
```

---

## 19. SELF JOIN — Employee and Manager

Suppose:

| emp_id | name | manager_id |
|---:|---|---:|
| 1 | Harsha | NULL |
| 2 | Rahul | 1 |
| 3 | Arjun | 1 |
| 4 | Priya | 2 |

Here:

```text
Rahul.manager_id = 1
```

The employee whose:

```text
emp_id = 1
```

is Harsha.

Therefore:

```text
Rahul → Harsha
employee → manager
```

---

## 20. Employee → Manager SELF JOIN

If:

```text
e = employee
m = manager
```

then:

```sql
SELECT e.name AS employee,
       m.name AS manager
FROM employees e
JOIN employees m
ON e.manager_id = m.emp_id;
```

### Important relationship

```text
employee.manager_id = manager.emp_id
```

This means:

> The employee's `manager_id` points to the manager's `emp_id`.

---

## 21. SELF JOIN — Reverse Direction

We can also write:

```sql
ON e.emp_id = m.manager_id
```

But now the aliases represent the opposite roles:

```text
e = manager
m = employee
```

So:

```sql
SELECT e.name AS manager,
       m.name AS employee
FROM employees e
JOIN employees m
ON e.emp_id = m.manager_id;
```

Result:

| manager | employee |
|---|---|
| Harsha | Rahul |
| Harsha | Arjun |
| Rahul | Priya |

### Key Understanding

These describe the same relationship from opposite directions:

```sql
e.manager_id = m.emp_id
```

and:

```sql
e.emp_id = m.manager_id
```

The aliases simply have different roles.

---

## 22. SELF JOIN — How to Avoid Confusion

Never assume:

```text
e = employee
m = manager
```

because of the letters.

First decide:

```text
What does e represent?
What does m represent?
```

Then write the condition.

If:

```text
e = employee
m = manager
```

use:

```sql
ON e.manager_id = m.emp_id
```

If:

```text
e = manager
m = employee
```

use:

```sql
ON e.emp_id = m.manager_id
```

### Most Important Relationship

```text
employee.manager_id
        ↓
points to
        ↓
another employee's emp_id
```

---

## 23. SELF JOIN — Same Table, Different Example

SELF JOIN can also compare rows in the same table.

Example:

| product_id | product_name | price |
|---:|---|---:|
| 1 | Laptop | 50000 |
| 2 | Phone | 30000 |
| 3 | Tablet | 50000 |
| 4 | Mouse | 1000 |

Find products with the same price:

```sql
SELECT p1.product_name, p2.product_name
FROM products p1
JOIN products p2
ON p1.price = p2.price;
```

Here:

```text
p1 = first copy of products
p2 = second copy of products
```

---

## 24. SELF JOIN — Avoid Self Matching

The previous query can produce:

```text
Laptop → Laptop
Tablet → Tablet
```

because a product's price equals its own price.

It can also produce:

```text
Laptop → Tablet
Tablet → Laptop
```

To avoid this:

```sql
SELECT p1.product_name, p2.product_name
FROM products p1
JOIN products p2
ON p1.price = p2.price
AND p1.product_id < p2.product_id;
```

The `<` condition:

- prevents a product from matching itself
- prevents the same pair from appearing in reverse order

---

# CROSS JOIN

## 25. CROSS JOIN

A **CROSS JOIN** creates every possible combination of rows from two tables.

There is no `ON` condition.

```sql
SELECT students.name, courses.course
FROM students
CROSS JOIN courses;
```

### Mental Model

```text
CROSS JOIN
 ↓
Every row × Every row
 ↓
Every possible combination
```

---

## 26. CROSS JOIN Example

Students:

| id | name |
|---:|---|
| 1 | Harsha |
| 2 | Rahul |
| 3 | Arjun |

Courses:

| id | course |
|---:|---|
| 1 | AI |
| 2 | DBMS |

Result:

| name | course |
|---|---|
| Harsha | AI |
| Harsha | DBMS |
| Rahul | AI |
| Rahul | DBMS |
| Arjun | AI |
| Arjun | DBMS |

There are:

```text
3 students × 2 courses = 6 combinations
```

---

## 27. CROSS JOIN Does NOT Match IDs

Even if:

```text
Students IDs = 1, 2, 3
Course IDs   = 1, 2
```

CROSS JOIN does not do:

```text
1 → 1
2 → 2
```

Instead:

```text
1 → 1
1 → 2

2 → 1
2 → 2

3 → 1
3 → 2
```

It does not care about matching IDs.

### Compare

```text
INNER JOIN
→ Find matching rows

CROSS JOIN
→ Ignore matching
→ Create every possible combination
```

---

## 28. CROSS JOIN Result Size

If table A has `N` rows and table B has `M` rows:

```text
CROSS JOIN result = N × M
```

Example:

```text
5 employees × 4 projects = 20 rows
```

This is called the **Cartesian Product**.

---

# MULTIPLE-TABLE JOINS

## 29. Joining 3 or More Tables

When joining multiple tables, connect them **one at a time**.

Example:

```text
Customers
    ↓ customer_id
Orders
    ↓ product_id
Products
```

Query:

```sql
SELECT customers.name,
       orders.order_id,
       products.product_name
FROM customers
JOIN orders
ON customers.customer_id = orders.customer_id
JOIN products
ON orders.product_id = products.product_id;
```

---

## 30. Multiple JOINs — Important Rule

You use:

```text
ONE FROM
+
multiple JOINs
```

Correct:

```sql
FROM customers
JOIN orders
ON customers.customer_id = orders.customer_id
JOIN products
ON orders.product_id = products.product_id;
```

Wrong:

```sql
FROM customers
JOIN orders
ON ...

FROM orders
JOIN products
ON ...
```

You cannot start another `FROM` for every table.

---

## 31. Multiple JOINs — Mental Model

For three tables:

```text
Table 1
   ↓
JOIN Table 2
   ↓
JOIN Table 3
```

Example:

```text
Customers
    │
    │ customer_id
    ↓
Orders
    │
    │ product_id
    ↓
Products
```

Each new table is connected using another `JOIN`.

---

## 32. Multiple Tables — How to Find the Connections

Before writing the query, identify the relationship.

Example:

```text
Customers
customer_id

Orders
customer_id
product_id

Products
product_id
```

Connections:

```text
Customers.customer_id
        ↕
Orders.customer_id

Orders.product_id
        ↕
Products.product_id
```

Therefore:

```sql
FROM customers
JOIN orders
ON customers.customer_id = orders.customer_id
JOIN products
ON orders.product_id = products.product_id;
```

---

## 33. Multiple Tables — You Don't Always Need Every Table

Don't JOIN every table just because it exists.

Ask:

> Which columns does the question actually require?

Example:

> Find each customer's total purchased quantity.

Required:

```text
customer name
→ Customers

quantity
→ Purchases
```

If `Products` is not needed, don't JOIN it.

Use:

```sql
SELECT customers.name,
       SUM(purchases.quantity)
FROM customers
JOIN purchases
ON customers.customer_id = purchases.customer_id
GROUP BY customers.customer_id, customers.name;
```

### Rule

```text
Only JOIN tables that are necessary for the answer.
```

---

# JOIN + WHERE + GROUP BY + HAVING

## 34. JOIN + WHERE

`WHERE` filters **individual rows**.

Example:

> Only consider orders greater than ₹400.

```sql
SELECT students.name,
       SUM(orders.amount)
FROM students
JOIN orders
ON students.student_id = orders.student_id
WHERE orders.amount > 400
GROUP BY students.name;
```

### Processing Idea

```text
JOIN
 ↓
Connect tables
 ↓
WHERE
 ↓
Filter individual orders
 ↓
GROUP BY
 ↓
Create groups
 ↓
SUM
 ↓
Calculate totals
```

---

## 35. JOIN + GROUP BY

Example:

> Find each student's total order amount.

```sql
SELECT students.name,
       SUM(orders.amount)
FROM students
JOIN orders
ON students.student_id = orders.student_id
GROUP BY students.name;
```

### Mental Model

```text
JOIN
 ↓
Connect student and orders
 ↓
GROUP BY student
 ↓
SUM their orders
```

---

## 36. JOIN + HAVING

`HAVING` filters **groups after aggregation**.

Example:

> Find students whose total order amount is greater than ₹1000.

```sql
SELECT students.name,
       SUM(orders.amount)
FROM students
JOIN orders
ON students.student_id = orders.student_id
GROUP BY students.name
HAVING SUM(orders.amount) > 1000;
```

### Mental Model

```text
JOIN
 ↓
GROUP BY
 ↓
SUM
 ↓
HAVING
 ↓
Filter completed groups
```

---

## 37. WHERE vs HAVING in JOIN Questions

### WHERE

Filters individual rows.

```sql
WHERE orders.amount > 400
```

Meaning:

> Ignore orders whose amount is 400 or less.

### HAVING

Filters groups after aggregation.

```sql
HAVING SUM(orders.amount) > 1000
```

Meaning:

> Calculate each student's total, then keep students whose total is greater than 1000.

### Easy Trick

```text
Individual row condition
→ WHERE

Aggregate/group condition
→ HAVING
```

---

## 38. JOIN + WHERE + GROUP BY + HAVING

All can be combined:

```sql
SELECT students.name,
       SUM(orders.amount)
FROM students
JOIN orders
ON students.student_id = orders.student_id
WHERE orders.amount > 400
GROUP BY students.name
HAVING SUM(orders.amount) > 1000;
```

Think:

```text
JOIN
 ↓
Connect tables

WHERE
 ↓
Filter individual rows

GROUP BY
 ↓
Create groups

SUM
 ↓
Calculate total

HAVING
 ↓
Filter groups
```

---

# JOIN QUESTION-SOLVING STRATEGY

## 39. How to Solve JOIN Questions

Don't immediately write SQL.

Use this process.

### Step 1 — Identify what the question wants

Example:

```text
customer name
order ID
product name
```

### Step 2 — Find which tables contain those columns

```text
customer name → Customers
order ID      → Orders
product name  → Products
```

### Step 3 — Find how the tables are connected

```text
Customers.customer_id
        ↓
Orders.customer_id

Orders.product_id
        ↓
Products.product_id
```

### Step 4 — Decide which table must be preserved

If the question says:

```text
ALL customers
```

use:

```text
customers LEFT JOIN ...
```

If it says:

```text
ONLY customers who have orders
```

use:

```text
customers INNER JOIN orders
```

### Step 5 — Check filtering

Ask:

```text
Am I filtering individual rows?
→ WHERE

Am I filtering an aggregate/group?
→ HAVING
```

### Step 6 — Check aggregation

If using:

```text
COUNT
SUM
AVG
MIN
MAX
```

ask whether you need one result per group.

If yes:

```text
GROUP BY
```

---

# COMMON INTERVIEW PATTERNS

## 40. Find Records With At Least One Match

Question:

> Find customers who have placed at least one order.

Typical solution:

```sql
SELECT DISTINCT customers.name
FROM customers
JOIN orders
ON customers.customer_id = orders.customer_id;
```

### Pattern

```text
At least one matching row
→ INNER JOIN

Need each customer only once
→ DISTINCT
```

---

## 41. Find Records With No Match

Question:

> Find departments that have no employees.

Pattern:

```sql
SELECT departments.dept_name
FROM departments
LEFT JOIN employees
ON departments.dept_id = employees.dept_id
WHERE employees.emp_id IS NULL;
```

### Pattern

```text
Need A with NO match in B

A
 ↓
LEFT JOIN B
 ↓
WHERE B.some_column IS NULL
```

---

## 42. Aggregate Per Group

Question:

> Find each department's average salary.

```sql
SELECT departments.dept_name,
       AVG(employees.salary)
FROM employees
JOIN departments
ON employees.dept_id = departments.dept_id
GROUP BY departments.dept_id, departments.dept_name;
```

### Pattern

```text
JOIN
 ↓
GROUP BY
 ↓
Aggregate
```

---

## 43. Aggregate + HAVING

Question:

> Find departments whose average salary is greater than ₹60000.

```sql
SELECT departments.dept_name,
       AVG(employees.salary)
FROM employees
JOIN departments
ON employees.dept_id = departments.dept_id
GROUP BY departments.dept_id, departments.dept_name
HAVING AVG(employees.salary) > 60000;
```

### Pattern

```text
Aggregate condition
→ HAVING
```

---

## 44. Multiple-Table JOIN Pattern

Question:

> Display customer name, order ID and product name.

```sql
SELECT customers.name,
       orders.order_id,
       products.product_name
FROM customers
JOIN orders
ON customers.customer_id = orders.customer_id
JOIN products
ON orders.product_id = products.product_id;
```

### Pattern

```text
Customer
   ↓
Order
   ↓
Product
```

---

# IMPORTANT INTERVIEW TRAPS

## 45. Trap — Wrong NULL Check

Wrong:

```sql
WHERE departments.emp_id IS NULL
```

if `emp_id` belongs to `employees`.

Correct:

```sql
WHERE employees.emp_id IS NULL
```

### Rule

If:

```text
A LEFT JOIN B
```

is used to find unmatched rows, check a column from `B`.

```text
A LEFT JOIN B
        ↓
WHERE B.column IS NULL
```

---

## 46. Trap — LEFT JOIN vs INNER JOIN

Question:

> Show all customers, including customers with no orders.

Wrong:

```sql
FROM customers
JOIN orders
```

INNER JOIN removes customers without orders.

Correct:

```sql
FROM customers
LEFT JOIN orders
```

### Keywords that often indicate LEFT JOIN

```text
ALL
including those with no...
even if they don't have...
```

---

## 47. Trap — Duplicate Rows

If one row in A matches multiple rows in B:

```text
A row
 ↓
B row 1
B row 2
B row 3
```

JOIN can produce:

```text
A | B1
A | B2
A | B3
```

Therefore:

```text
JOIN ≠ automatically one row per entity
```

Use:

```sql
DISTINCT
```

when the question requires unique entities.

---

## 48. Trap — Unnecessary Tables

Don't JOIN every table in the database.

First ask:

> Do I actually need information from this table?

If not, don't JOIN it.

This makes the query simpler and avoids unnecessary work.

---

## 49. Trap — Multiple FROM Clauses

Wrong:

```sql
FROM customers
JOIN orders
ON ...

FROM orders
JOIN products
ON ...
```

Correct:

```sql
FROM customers
JOIN orders
ON ...
JOIN products
ON ...;
```

### Rule

```text
ONE FROM
+
multiple JOINs
```

---

## 50. Trap — ON vs GROUP BY

These have completely different purposes.

### ON

Connects tables:

```sql
ON employees.dept_id = departments.dept_id
```

### GROUP BY

Creates groups for aggregation:

```sql
GROUP BY departments.dept_name
```

### Mental Model

```text
ON
 ↓
Connect tables

GROUP BY
 ↓
Create groups
```

The columns used for JOIN and GROUP BY do not have to be the same.

---

## 51. GROUP BY Does Not Need a Common Column

Example:

```sql
SELECT departments.dept_name,
       AVG(employees.salary)
FROM employees
JOIN departments
ON employees.dept_id = departments.dept_id
GROUP BY departments.dept_name;
```

`dept_name` doesn't need to exist in `employees`.

The tables are connected through:

```text
employees.dept_id
        ↕
departments.dept_id
```

After joining, `departments.dept_name` is available and can be used for grouping.

### Remember

```text
ON
→ Connect tables

GROUP BY
→ Group the joined rows
```

---

# JOIN CHEAT SHEETS

## 52. JOIN Types

| JOIN | What it returns |
|---|---|
| `INNER JOIN` | Matching rows only |
| `JOIN` | Normally same as INNER JOIN |
| `LEFT JOIN` | All left rows + matching right rows |
| `RIGHT JOIN` | All right rows + matching left rows |
| `FULL OUTER JOIN` | All rows from both tables |
| `SELF JOIN` | Same table used twice |
| `CROSS JOIN` | Every possible combination |

---

## 53. JOIN Decision Cheat Sheet

```text
Need only matching records?
→ INNER JOIN

Need ALL records from the first/left table?
→ LEFT JOIN

Need ALL records from the right table?
→ RIGHT JOIN

Need ALL records from both tables?
→ FULL OUTER JOIN

Need to compare/connect rows inside the same table?
→ SELF JOIN

Need every possible combination?
→ CROSS JOIN
```

---

## 54. Filtering Cheat Sheet

```text
WHERE
→ Filter individual rows

GROUP BY
→ Create groups

HAVING
→ Filter groups after aggregation

DISTINCT
→ Remove duplicate output values
```

---

## 55. The Most Important LEFT JOIN Pattern

```sql
SELECT ...
FROM A
LEFT JOIN B
ON A.key = B.key
WHERE B.key IS NULL;
```

Meaning:

> Find records in A that have no matching record in B.

---

## 56. The Most Important SELF JOIN Pattern

If:

```text
employee.manager_id → manager.emp_id
```

then:

```sql
SELECT e.name AS employee,
       m.name AS manager
FROM employees e
JOIN employees m
ON e.manager_id = m.emp_id;
```

Remember:

```text
e = employee
m = manager
```

because **we decided those roles**, not because SQL automatically assigns them.

---

## 57. The Most Important Multiple-JOIN Pattern

```sql
FROM table1
JOIN table2
ON table1.key = table2.key
JOIN table3
ON table2.key = table3.key;
```

Think:

```text
Table 1
   ↓
Table 2
   ↓
Table 3
```

Build the JOIN chain one table at a time.

---

## 58. Complete JOIN Problem-Solving Flow

```text
Question
   ↓
What information do I need?
   ↓
Which tables contain that information?
   ↓
How are those tables related?
   ↓
Which table must be preserved?
   ↓
Choose JOIN type
   ↓
Write ON conditions
   ↓
Need to filter individual rows?
   ↓
WHERE
   ↓
Need grouping?
   ↓
GROUP BY
   ↓
Need to filter aggregate results?
   ↓
HAVING
```

---

## 59. Final JOIN Mental Model

```text
JOIN
→ Connect tables

ON
→ Explain how tables are related

INNER JOIN
→ Matching only

LEFT JOIN
→ Keep left

RIGHT JOIN
→ Keep right

FULL OUTER JOIN
→ Keep both

SELF JOIN
→ Same table twice

CROSS JOIN
→ Everything × everything

WHERE
→ Filter rows

GROUP BY
→ Create groups

HAVING
→ Filter groups

DISTINCT
→ Remove duplicates
```

---

## 60. JOIN Module — Completed ✅

### Covered

- JOIN fundamentals
- JOIN syntax
- `ON`
- `table.column` notation
- INNER JOIN
- JOIN vs INNER JOIN
- LEFT JOIN
- RIGHT JOIN
- FULL OUTER JOIN
- SELF JOIN
- SELF JOIN aliases
- Employee → Manager SELF JOIN
- Reverse SELF JOIN
- SELF JOIN comparison example
- CROSS JOIN
- Cartesian product
- Multiple-table JOINs
- JOIN + WHERE
- JOIN + GROUP BY
- JOIN + HAVING
- JOIN + aggregation
- DISTINCT with JOIN
- Finding matching records
- Finding unmatched records
- JOIN interview traps
- JOIN question-solving strategy

# JOINs — DONE ✅