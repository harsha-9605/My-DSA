# SQL — Module 3: SQL Fundamentals

> **Placement Focus:** Learn the SQL concepts and queries commonly asked in interviews and coding rounds.

---

## 1. What is SQL?

**SQL (Structured Query Language)** is a language used to interact with **relational databases**.

We use SQL to:

* Retrieve data
* Insert data
* Update data
* Delete data
* Create tables
* Modify database structures
* Filter and sort data

Example:

```sql
SELECT * FROM employees;
```

This retrieves all rows and columns from the `employees` table.

---

# 2. Example Table

Throughout these notes, we'll use:

### `employees`

| id | name   | department | salary | age |
| -: | ------ | ---------- | -----: | --: |
|  1 | Harsha | AI         |  70000 |  21 |
|  2 | Rahul  | CSE        |  60000 |  22 |
|  3 | Arjun  | AI         |  80000 |  24 |
|  4 | Priya  | HR         |  50000 |  25 |
|  5 | Kiran  | CSE        |  75000 |  23 |

---

# 3. SELECT

`SELECT` is used to retrieve data from a table.

### Select everything

```sql
SELECT * FROM employees;
```

`*` means **all columns**.

### Select specific columns

```sql
SELECT name, salary
FROM employees;
```

Result:

| name   | salary |
| ------ | -----: |
| Harsha |  70000 |
| Rahul  |  60000 |
| Arjun  |  80000 |
| Priya  |  50000 |
| Kiran  |  75000 |

### Mental model

```text
SELECT → What columns do I want?
FROM   → Which table?
```

---

# 4. WHERE

`WHERE` is used to **filter rows** based on a condition.

```sql
SELECT *
FROM employees
WHERE department = 'AI';
```

Result:

| id | name   | department | salary | age |
| -: | ------ | ---------- | -----: | --: |
|  1 | Harsha | AI         |  70000 |  21 |
|  3 | Arjun  | AI         |  80000 |  24 |

### Mental model

```text
WHERE → Which rows do I want?
```

---

# 5. Comparison Operators

SQL provides comparison operators for filtering.

| Operator | Meaning               |
| -------- | --------------------- |
| `=`      | Equal                 |
| `!=`     | Not equal             |
| `<>`     | Not equal             |
| `>`      | Greater than          |
| `<`      | Less than             |
| `>=`     | Greater than or equal |
| `<=`     | Less than or equal    |

### Examples

#### Salary greater than 70000

```sql
SELECT *
FROM employees
WHERE salary > 70000;
```

#### Salary less than or equal to 60000

```sql
SELECT *
FROM employees
WHERE salary <= 60000;
```

#### Department is not HR

```sql
SELECT *
FROM employees
WHERE department != 'HR';
```

`<>` can also be used:

```sql
SELECT *
FROM employees
WHERE department <> 'HR';
```

---

# 6. AND

`AND` is used when **all conditions must be true**.

```sql
SELECT *
FROM employees
WHERE department = 'AI'
AND salary > 70000;
```

Both conditions must be satisfied.

### Example

Arjun:

```text
department = AI      → TRUE
salary > 70000       → TRUE
```

Therefore Arjun is returned.

---

# 7. OR

`OR` is used when **at least one condition must be true**.

```sql
SELECT *
FROM employees
WHERE department = 'AI'
OR department = 'HR';
```

Employees from either AI or HR are returned.

### Mental model

```text
AND → both conditions
OR  → at least one condition
```

---

# 8. NOT

`NOT` reverses a condition.

```sql
SELECT *
FROM employees
WHERE NOT department = 'HR';
```

This returns employees who are **not in HR**.

Equivalent:

```sql
SELECT *
FROM employees
WHERE department != 'HR';
```

---

# 9. DISTINCT

`DISTINCT` removes duplicate values from the result.

Example:

```sql
SELECT DISTINCT department
FROM employees;
```

Result:

| department |
| ---------- |
| AI         |
| CSE        |
| HR         |

Without `DISTINCT`:

```sql
SELECT department
FROM employees;
```

Result:

```text
AI
CSE
AI
HR
CSE
```

With `DISTINCT`:

```text
AI
CSE
HR
```

### Important

`DISTINCT` applies to the **result of the selected columns**.

Example:

```sql
SELECT DISTINCT department, salary
FROM employees;
```

Here SQL considers the **combination** of `department + salary`.

---

# 10. ORDER BY

`ORDER BY` is used to **sort the result**.

## Ascending

```sql
SELECT *
FROM employees
ORDER BY salary ASC;
```

Lowest salary → highest salary.

```text
50000
60000
70000
75000
80000
```

`ASC` means ascending.

## Descending

```sql
SELECT *
FROM employees
ORDER BY salary DESC;
```

Highest salary → lowest salary.

```text
80000
75000
70000
60000
50000
```

`DESC` means descending.

### Important

If you don't specify `ASC` or `DESC`, ascending order is normally used.

```sql
ORDER BY salary;
```

is effectively:

```sql
ORDER BY salary ASC;
```

---

# 11. LIMIT

`LIMIT` restricts the number of rows returned.

```sql
SELECT *
FROM employees
LIMIT 2;
```

Only 2 rows are returned.

---

## LIMIT + ORDER BY

This combination is extremely important for placement questions.

### Highest-paid employee

```sql
SELECT *
FROM employees
ORDER BY salary DESC
LIMIT 1;
```

### Top 2 highest-paid employees

```sql
SELECT *
FROM employees
ORDER BY salary DESC
LIMIT 2;
```

### Top 2 AI employees by salary

```sql
SELECT *
FROM employees
WHERE department = 'AI'
ORDER BY salary DESC
LIMIT 2;
```

### Mental model

```text
WHERE      → filter rows
ORDER BY   → sort rows
LIMIT      → take only N rows
```

---

# 12. IN

`IN` is used when a value can match **one of several specified values**.

Instead of:

```sql
SELECT *
FROM employees
WHERE department = 'AI'
OR department = 'CSE';
```

We can write:

```sql
SELECT *
FROM employees
WHERE department IN ('AI', 'CSE');
```

This is cleaner.

### Example

```sql
SELECT *
FROM employees
WHERE id IN (1, 3, 5);
```

Returns employees whose IDs are 1, 3, or 5.

---

## NOT IN

To exclude specific values:

```sql
SELECT *
FROM employees
WHERE department NOT IN ('AI', 'HR');
```

This returns employees whose department is neither AI nor HR.

---

# 13. BETWEEN

`BETWEEN` checks whether a value falls within a range.

```sql
SELECT *
FROM employees
WHERE salary BETWEEN 60000 AND 75000;
```

### Important

`BETWEEN` is **inclusive**.

So this:

```sql
BETWEEN 60000 AND 75000
```

means:

```text
salary >= 60000
AND
salary <= 75000
```

Therefore salaries of:

```text
60000
70000
75000
```

are included.

---

# 14. LIKE

`LIKE` is used for **pattern matching**, mainly with strings.

It uses wildcard characters.

## `%`

`%` means **zero or more characters**.

---

## Starts with

Find names starting with `H`:

```sql
SELECT *
FROM employees
WHERE name LIKE 'H%';
```

Matches:

```text
Harsha
```

---

## Ends with

Find names ending with `a`:

```sql
SELECT *
FROM employees
WHERE name LIKE '%a';
```

Matches names such as:

```text
Harsha
Priya
```

---

## Contains

Find names containing `ar`:

```sql
SELECT *
FROM employees
WHERE name LIKE '%ar%';
```

Matches:

```text
Harsha
Arjun
```

depending on the database's case-sensitivity rules.

---

## LIKE Mental Model

```text
'H%'     → starts with H

'%a'     → ends with a

'%ar%'   → contains ar
```

---

# 15. NULL

`NULL` represents **missing, unknown, or unavailable data**.

It is NOT the same as:

```text
0
```

or:

```text
''
```

or:

```text
'NULL'
```

### Difference

```text
NULL  → no known value
0     → actual numeric value zero
''    → empty string
'NULL' → actual text "NULL"
```

---

# 16. Why `= NULL` Does NOT Work

This is a very common interview trap.

❌ Wrong:

```sql
SELECT *
FROM employees
WHERE salary = NULL;
```

You should not compare `NULL` using `=`.

Why?

Because `NULL` means the value is **unknown**.

SQL uses special operators to check it.

---

# 17. IS NULL

Use `IS NULL` to find rows where a column contains `NULL`.

```sql
SELECT *
FROM employees
WHERE salary IS NULL;
```

This returns employees whose salary is missing.

---

# 18. IS NOT NULL

Use `IS NOT NULL` to find rows where a column has a value.

```sql
SELECT *
FROM employees
WHERE salary IS NOT NULL;
```

This returns employees whose salary is known.

---

# 19. Important SQL Query Structure

A basic SQL query follows this structure:

```sql
SELECT columns
FROM table
WHERE condition
ORDER BY column
LIMIT number;
```

Example:

```sql
SELECT name, salary
FROM employees
WHERE department = 'AI'
ORDER BY salary DESC
LIMIT 2;
```

### How to read it

```text
FROM
 ↓
WHERE
 ↓
SELECT
 ↓
ORDER BY
 ↓
LIMIT
```

Conceptually:

1. Look at `employees`
2. Filter AI employees
3. Select name and salary
4. Sort by salary descending
5. Return only 2 rows

> **Note:** The logical processing order of SQL is not exactly the same as the way we write it. We'll cover that when it becomes relevant to interview questions.

---

# 20. INSERT

`INSERT` is used to add new rows.

Syntax:

```sql
INSERT INTO table_name (column1, column2, ...)
VALUES (value1, value2, ...);
```

Example:

```sql
INSERT INTO employees (id, name, department, salary, age)
VALUES (6, 'Vijay', 'AI', 65000, 22);
```

This adds a new employee.

---

# 21. UPDATE

`UPDATE` modifies existing rows.

Syntax:

```sql
UPDATE table_name
SET column = value
WHERE condition;
```

Example:

```sql
UPDATE employees
SET salary = 72000
WHERE id = 1;
```

Harsha's salary becomes `72000`.

---

## ⚠️ Important UPDATE Trap

Always be careful with `WHERE`.

```sql
UPDATE employees
SET salary = 72000;
```

This updates **every employee's salary**.

So:

```sql
UPDATE + WHERE
```

is extremely important.

---

# 22. DELETE

`DELETE` removes rows from a table.

Syntax:

```sql
DELETE FROM table_name
WHERE condition;
```

Example:

```sql
DELETE FROM employees
WHERE id = 4;
```

This deletes the employee whose ID is 4.

---

## ⚠️ Important DELETE Trap

Without `WHERE`:

```sql
DELETE FROM employees;
```

This removes **all rows** from the table.

The table itself still exists.

---

# 23. SELECT vs INSERT vs UPDATE vs DELETE

| Command  | Purpose              |
| -------- | -------------------- |
| `SELECT` | Read/retrieve data   |
| `INSERT` | Add rows             |
| `UPDATE` | Modify existing rows |
| `DELETE` | Remove rows          |

These are part of **DML** (Data Manipulation Language).

---

# 24. Common Placement Query Patterns

## Find AI employees

```sql
SELECT *
FROM employees
WHERE department = 'AI';
```

---

## Find employees earning more than 70000

```sql
SELECT *
FROM employees
WHERE salary > 70000;
```

---

## Find CSE employees earning more than 60000

```sql
SELECT *
FROM employees
WHERE department = 'CSE'
AND salary > 60000;
```

---

## Find employees from AI or CSE

```sql
SELECT *
FROM employees
WHERE department IN ('AI', 'CSE');
```

---

## Find employees between ages 21 and 24

```sql
SELECT *
FROM employees
WHERE age BETWEEN 21 AND 24;
```

Remember:

> `BETWEEN` is inclusive.

---

## Find employees whose name starts with H

```sql
SELECT *
FROM employees
WHERE name LIKE 'H%';
```

---

## Find highest-paid employee

```sql
SELECT *
FROM employees
ORDER BY salary DESC
LIMIT 1;
```

---

## Find top 2 highest-paid employees

```sql
SELECT *
FROM employees
ORDER BY salary DESC
LIMIT 2;
```

---

## Find top 2 highest-paid AI employees

```sql
SELECT *
FROM employees
WHERE department = 'AI'
ORDER BY salary DESC
LIMIT 2;
```

---

# 25. SQL Quick Mental Map

```text
SQL
│
├── SELECT      → retrieve data
│
├── FROM        → choose table
│
├── WHERE       → filter rows
│
├── DISTINCT    → remove duplicate results
│
├── ORDER BY    → sort results
│
├── LIMIT       → restrict number of rows
│
├── AND / OR    → combine conditions
│
├── NOT         → reverse condition
│
├── IN          → match multiple values
│
├── BETWEEN     → filter a range (inclusive)
│
├── LIKE        → pattern matching
│
├── IS NULL     → find missing values
│
├── IS NOT NULL → find non-missing values
│
├── INSERT      → add rows
│
├── UPDATE      → modify rows
│
└── DELETE      → remove rows
```

---
# SQL — DDL, Constraints & DELETE/TRUNCATE/DROP

## 27. DDL — Data Definition Language

**DDL (Data Definition Language)** is used to **create, modify, and delete the structure of database objects**, especially tables.

Main DDL commands:

```text
CREATE
ALTER
DROP
TRUNCATE
```

### Mental Model

```text
DDL → Changes the structure of the database
```

---

## 28. CREATE

`CREATE` is used to create a new database object such as a table.

### Syntax

```sql
CREATE TABLE table_name (
    column1 datatype,
    column2 datatype,
    column3 datatype
);
```

### Example

```sql
CREATE TABLE employees (
    id INT,
    name VARCHAR(50),
    department VARCHAR(50),
    salary INT,
    age INT
);
```

This creates the **structure** of the table.

At this point:

```text
Table exists  → ✅
Columns exist → ✅
Data          → ❌
```

### Mental Model

```text
CREATE → Create the structure
```

---

## 29. ALTER

`ALTER` is used to **modify the structure of an existing table**.

### Add a column

```sql
ALTER TABLE employees
ADD email VARCHAR(100);
```

Now the table has:

```text
id
name
department
salary
age
email
```

### Rename a column

```sql
ALTER TABLE employees
RENAME COLUMN name TO employee_name;
```

### Remove a column

```sql
ALTER TABLE employees
DROP COLUMN email;
```

### Mental Model

```text
ALTER → Change existing structure
```

---

## 30. DROP

`DROP` completely removes a table.

```sql
DROP TABLE employees;
```

After this:

```text
Table structure → ❌
Columns         → ❌
Data            → ❌
Table           → ❌
```

The table itself no longer exists.

### Mental Model

```text
DROP → Destroy the table
```

---

## 31. TRUNCATE

`TRUNCATE` removes **all rows** from a table while keeping the table structure.

```sql
TRUNCATE TABLE employees;
```

After this:

```text
Table exists  → ✅
Columns exist → ✅
Rows          → ❌
```

You can still insert new data into the table afterward.

### Important

`TRUNCATE` does **not** support `WHERE`.

❌ Invalid:

```sql
TRUNCATE TABLE employees
WHERE id = 3;
```

If you need selective deletion, use `DELETE`.

### Mental Model

```text
TRUNCATE → Empty the entire table
```

---

# Constraints

## 32. What are Constraints?

A **constraint** is a rule applied to a table/column to ensure that the data follows certain conditions.

### Mental Model

```text
Constraints = Rules that protect data
```

Common SQL constraints:

```text
PRIMARY KEY
FOREIGN KEY
UNIQUE
NOT NULL
CHECK
DEFAULT
```

---

## 33. PRIMARY KEY

A **Primary Key** uniquely identifies every row in a table.

### Example

```sql
CREATE TABLE employees (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    department VARCHAR(50),
    salary INT
);
```

Here:

```text
id → PRIMARY KEY
```

Therefore:

```text
id = 1 → Harsha
id = 2 → Rahul
id = 3 → Arjun
```

Two rows cannot have the same primary-key value.

A primary key also **cannot contain NULL**.

### Primary Key Rules

```text
PRIMARY KEY
    ↓
Unique
    +
NOT NULL
```

### How many primary keys can a table have?

A table can have **only one PRIMARY KEY constraint**.

However, that one primary key can contain multiple columns.

Example:

```sql
PRIMARY KEY (student_id, course_id)
```

This is called a **Composite Primary Key**.

### Mental Model

```text
PRIMARY KEY → Unique identity of a row
```

---

## 34. UNIQUE

`UNIQUE` ensures that values in a column are not duplicated.

### Example

```sql
CREATE TABLE employees (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    email VARCHAR(100) UNIQUE
);
```

Now:

```text
harsha@gmail.com → ✅
rahul@gmail.com  → ✅
harsha@gmail.com → ❌
```

The same email cannot be stored twice under that `UNIQUE` constraint.

### PRIMARY KEY vs UNIQUE

| PRIMARY KEY                          | UNIQUE                              |
| ------------------------------------ | ----------------------------------- |
| Uniquely identifies a row            | Prevents duplicate values           |
| Cannot be NULL                       | NULL handling is DBMS-dependent     |
| One PRIMARY KEY constraint per table | Multiple UNIQUE constraints allowed |
| Main identifier                      | Additional uniqueness rule          |

### Mental Model

```text
PRIMARY KEY → "Who are you?"
UNIQUE      → "Nobody else can have this value."
```

---

## 35. NOT NULL

`NOT NULL` means a column **must contain a value**.

### Example

```sql
CREATE TABLE employees (
    id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    salary INT
);
```

This is allowed:

```sql
INSERT INTO employees
VALUES (1, 'Harsha', 70000);
```

But this is not:

```sql
INSERT INTO employees
VALUES (2, NULL, 60000);
```

Because:

```text
name → NOT NULL
```

### Mental Model

```text
NOT NULL → "You must provide a value."
```

---

## 36. CHECK

`CHECK` ensures that a value satisfies a specified condition.

### Example

```sql
CREATE TABLE employees (
    id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    age INT CHECK (age >= 18)
);
```

This is allowed:

```sql
INSERT INTO employees
VALUES (1, 'Harsha', 21);
```

But:

```sql
INSERT INTO employees
VALUES (2, 'Rahul', 15);
```

is rejected because:

```text
age >= 18
```

is false.

Another example:

```sql
salary INT CHECK (salary > 0)
```

### Mental Model

```text
CHECK → "Does this value satisfy my condition?"
```

---

## 37. DEFAULT

`DEFAULT` automatically provides a value when no value is supplied for that column.

### Example

```sql
CREATE TABLE employees (
    id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    department VARCHAR(50) DEFAULT 'Unknown',
    salary INT
);
```

Now:

```sql
INSERT INTO employees (id, name, salary)
VALUES (1, 'Harsha', 70000);
```

We didn't provide a department.

The database uses:

```text
department = 'Unknown'
```

### Mental Model

```text
DEFAULT → "If you don't provide a value, use this."
```

---

## 38. FOREIGN KEY

A **Foreign Key** is used to establish a relationship between tables and maintain **referential integrity**.

Consider two tables.

### Students

```text
student_id | name
-----------|-------
1          | Harsha
2          | Rahul
```

### Orders

```text
order_id | student_id | amount
---------|------------|-------
101      | 1          | 500
102      | 1          | 700
103      | 2          | 300
```

We can define them as:

```sql
CREATE TABLE students (
    student_id INT PRIMARY KEY,
    name VARCHAR(50)
);
```

And:

```sql
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    student_id INT,
    amount INT,

    FOREIGN KEY (student_id)
        REFERENCES students(student_id)
);
```

Here:

```text
students.student_id
        ↑
        |
orders.student_id
```

`orders.student_id` is the **Foreign Key**.

It references:

```text
students.student_id
```

which is the primary key of the `students` table.

---

### Why do we need FOREIGN KEY?

It maintains **referential integrity**.

For example:

```sql
INSERT INTO orders
VALUES (104, 999, 500);
```

If student `999` doesn't exist in the `students` table, the foreign-key constraint can reject the operation.

This prevents an order from referring to a nonexistent student.

### Important

A foreign key **can contain duplicate values**.

For example:

```text
student_id
----------
1
1
1
2
2
```

This is completely valid.

Why?

Because multiple orders can belong to the same student.

### Mental Model

```text
PRIMARY KEY → Identifies a row

FOREIGN KEY → References a key in another table
```

---

## 39. All SQL Constraints — Quick Comparison

| Constraint    | Purpose                         |
| ------------- | ------------------------------- |
| `PRIMARY KEY` | Uniquely identifies each row    |
| `FOREIGN KEY` | Links to a key in another table |
| `UNIQUE`      | Prevents duplicate values       |
| `NOT NULL`    | Value must be provided          |
| `CHECK`       | Value must satisfy a condition  |
| `DEFAULT`     | Provides a value automatically  |

### Easy Memory Trick

```text
PRIMARY KEY → Unique identity
FOREIGN KEY → Relationship
UNIQUE      → No duplicates
NOT NULL    → Must have value
CHECK       → Must satisfy condition
DEFAULT     → Automatic value
```

---

# DELETE vs TRUNCATE vs DROP

## 40. DELETE

`DELETE` removes rows from a table.

### Delete a specific row

```sql
DELETE FROM employees
WHERE id = 3;
```

Only the row with `id = 3` is removed.

### Delete multiple rows

```sql
DELETE FROM employees
WHERE department = 'AI';
```

All AI employees are removed.

### Delete all rows

```sql
DELETE FROM employees;
```

All rows are removed, but the table remains.

```text
Table exists  → ✅
Structure     → ✅
Rows          → ❌
```

### Important

`DELETE` supports `WHERE`.

```sql
DELETE FROM employees
WHERE salary < 60000;
```

---

## 41. TRUNCATE

`TRUNCATE` removes **all rows** from a table.

```sql
TRUNCATE TABLE employees;
```

Afterward:

```text
Table exists  → ✅
Structure     → ✅
Rows          → ❌
```

But you cannot selectively remove rows.

```text
TRUNCATE → all rows
DELETE   → selected rows or all rows
```

---

## 42. DROP

`DROP` removes the **entire table**.

```sql
DROP TABLE employees;
```

Afterward:

```text
Table exists  → ❌
Structure     → ❌
Columns       → ❌
Rows          → ❌
```

---

## 43. DELETE vs TRUNCATE vs DROP

This is a **very common placement interview question**.

| Feature                 | DELETE      | TRUNCATE    | DROP         |
| ----------------------- | ----------- | ----------- | ------------ |
| Removes rows            | ✅           | ✅ All rows  | ✅            |
| Removes table structure | ❌           | ❌           | ✅            |
| `WHERE` allowed         | ✅           | ❌           | ❌            |
| Selective deletion      | ✅           | ❌           | ❌            |
| Table remains           | ✅           | ✅           | ❌            |
| Main purpose            | Remove rows | Empty table | Remove table |

### Easy Mental Model

```text
DELETE
↓
Remove rows
↓
WHERE allowed
↓
Table remains


TRUNCATE
↓
Remove ALL rows
↓
WHERE not allowed
↓
Table remains


DROP
↓
Remove entire table
↓
Structure + data gone
```

### Simplest way to remember

> **DELETE = rows**
> **TRUNCATE = all rows**
> **DROP = table**

---

## 44. DELETE vs TRUNCATE — Important Interview Nuance

You may hear:

> "DELETE can be rolled back but TRUNCATE cannot."

Don't treat this as an absolute rule.

Transaction and rollback behavior of `TRUNCATE` depends on the **DBMS**.

For example, PostgreSQL supports transactional `TRUNCATE`.

For placement interviews, remember:

```text
DELETE → DML operation
TRUNCATE → DDL-style operation in many DBMSs
```

And:

> The exact transaction/rollback behavior of `TRUNCATE` is DBMS-dependent.

We will properly cover **transactions, COMMIT, ROLLBACK, and ACID** later.

---

## 45. Important Placement Traps

### Trap 1 — DELETE without WHERE

```sql
DELETE FROM employees;
```

❗ Removes **all rows**.

The table still exists.

---

### Trap 2 — UPDATE without WHERE

```sql
UPDATE employees
SET salary = 50000;
```

❗ Updates **every row**.

---

### Trap 3 — TRUNCATE with WHERE

❌ Invalid:

```sql
TRUNCATE TABLE employees
WHERE id = 3;
```

`TRUNCATE` does not support `WHERE`.

---

### Trap 4 — DROP vs TRUNCATE

```sql
TRUNCATE TABLE employees;
```

```text
Table → ✅
Rows  → ❌
```

Whereas:

```sql
DROP TABLE employees;
```

```text
Table → ❌
Rows  → ❌
```

---

### Trap 5 — NULL with PRIMARY KEY

A primary key cannot contain `NULL`.

```text
PRIMARY KEY → UNIQUE + NOT NULL
```

---

### Trap 6 — Foreign Key duplicates

A foreign key **can** contain duplicate values.

```text
student_id
----------
1
1
1
2
2
```

This is valid.

---

# 46. Complete Example with Constraints

```sql
CREATE TABLE employees (
    id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE,
    age INT CHECK (age >= 18),
    department VARCHAR(50) DEFAULT 'Unknown',
    salary INT
);
```

Here:

```text
id          → PRIMARY KEY
name        → NOT NULL
email       → UNIQUE
age         → CHECK
department  → DEFAULT
salary      → No constraint
```

---

# 47. DDL + Constraints — Final Mental Map

```text
SQL
│
├── DDL
│   │
│   ├── CREATE    → Create structure
│   ├── ALTER     → Modify structure
│   ├── TRUNCATE  → Remove all rows
│   └── DROP      → Remove table
│
└── Constraints
    │
    ├── PRIMARY KEY → Unique identity
    ├── FOREIGN KEY → Relationship
    ├── UNIQUE      → No duplicates
    ├── NOT NULL    → Must have value
    ├── CHECK       → Condition must be satisfied
    └── DEFAULT     → Automatic value
```

---

# 48. Module 3 — Completion Status

### SQL Fundamentals

* [x] `SELECT`
* [x] `FROM`
* [x] `WHERE`
* [x] Comparison operators
* [x] `AND`
* [x] `OR`
* [x] `NOT`
* [x] `DISTINCT`
* [x] `ORDER BY`
* [x] `LIMIT`
* [x] `IN`
* [x] `NOT IN`
* [x] `BETWEEN`
* [x] `LIKE`
* [x] `NULL`
* [x] `IS NULL`
* [x] `IS NOT NULL`
* [x] `INSERT`
* [x] `UPDATE`
* [x] `DELETE`

### DDL

* [x] `CREATE`
* [x] `ALTER`
* [x] `DROP`
* [x] `TRUNCATE`

### Constraints

* [x] `PRIMARY KEY`
* [x] `FOREIGN KEY`
* [x] `UNIQUE`
* [x] `NOT NULL`
* [x] `CHECK`
* [x] `DEFAULT`

### Important Comparisons

* [x] `DELETE vs TRUNCATE vs DROP`

---


