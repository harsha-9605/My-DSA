# SQL — Module 4: Aggregation + GROUP BY

## 1. Aggregate Functions

Aggregate functions perform calculations on **multiple rows** and return a result.

```text
COUNT() → Number of rows/values
SUM()   → Total
AVG()   → Average
MIN()   → Smallest value
MAX()   → Largest value
```

---

## 2. COUNT()

`COUNT()` is used to count rows or non-NULL values.

### COUNT(*)

```sql
SELECT COUNT(*)
FROM employees;
```

`COUNT(*)` counts **all rows**.

### COUNT(column)

```sql
SELECT COUNT(salary)
FROM employees;
```

`COUNT(column)` counts only **non-NULL values** in that column.

### Important

```text
COUNT(*)      → Counts rows
COUNT(column) → Counts non-NULL values
```

---

## 3. SUM()

`SUM()` calculates the total of a numeric column.

```sql
SELECT SUM(salary)
FROM employees;
```

Example:

```text
70000 + 60000 + 80000 + 50000 + 75000
= 335000
```

---

## 4. AVG()

`AVG()` calculates the average of a numeric column.

```sql
SELECT AVG(salary)
FROM employees;
```

Example:

```text
335000 / 5
= 67000
```

---

## 5. MIN() and MAX()

### MIN()

Returns the smallest value.

```sql
SELECT MIN(salary)
FROM employees;
```

```text
50000
```

### MAX()

Returns the largest value.

```sql
SELECT MAX(salary)
FROM employees;
```

```text
80000
```

---

## 6. Multiple Aggregate Functions

Multiple aggregate functions can be used in one query.

```sql
SELECT
    COUNT(*),
    SUM(salary),
    AVG(salary),
    MIN(salary),
    MAX(salary)
FROM employees;
```

This gives:

```text
Number of employees
Total salary
Average salary
Minimum salary
Maximum salary
```

---

## 7. Aggregate Functions with WHERE

`WHERE` filters rows **before** the aggregate function is applied.

Example:

> Find the average salary of AI employees.

```sql
SELECT AVG(salary)
FROM employees
WHERE department = 'AI';
```

Execution concept:

```text
employees
    ↓
WHERE department = 'AI'
    ↓
AI employees only
    ↓
AVG(salary)
```

---

## 8. Aggregate Result vs Employee Details

```sql
SELECT MAX(salary)
FROM employees;
```

This returns only:

```text
80000
```

It does **not automatically return the employee** earning 80000.

Finding the employee associated with the maximum salary is a separate SQL problem.

---

## 9. GROUP BY

`GROUP BY` divides rows into groups based on one or more columns.

It is mainly used with aggregate functions to calculate a result **for each group**.

Example:

```sql
SELECT department, COUNT(*)
FROM employees
GROUP BY department;
```

Result:

```text
AI  → 2
CSE → 2
HR  → 1
```

### Mental Model

```text
Rows
 ↓
GROUP BY department
 ↓
AI | CSE | HR
 ↓
Aggregate each group
```

---

## 10. GROUP BY with COUNT()

Question:

> How many employees are in each department?

```sql
SELECT department, COUNT(*)
FROM employees
GROUP BY department;
```

Result:

| department | count |
|---|---:|
| AI | 2 |
| CSE | 2 |
| HR | 1 |

---

## 11. GROUP BY with SUM()

Question:

> Find the total salary of each department.

```sql
SELECT department, SUM(salary)
FROM employees
GROUP BY department;
```

Result:

| department | total salary |
|---|---:|
| AI | 150000 |
| CSE | 135000 |
| HR | 50000 |

---

## 12. GROUP BY with AVG()

Question:

> Find the average salary of each department.

```sql
SELECT department, AVG(salary)
FROM employees
GROUP BY department;
```

Result:

| department | average salary |
|---|---:|
| AI | 75000 |
| CSE | 67500 |
| HR | 50000 |

---

## 13. GROUP BY with MIN() and MAX()

### Minimum salary in each department

```sql
SELECT department, MIN(salary)
FROM employees
GROUP BY department;
```

### Maximum salary in each department

```sql
SELECT department, MAX(salary)
FROM employees
GROUP BY department;
```

The aggregate function is applied **separately to each group**.

---

## 14. GROUP BY + WHERE

`WHERE` filters the rows **before grouping**.

Question:

> Find the number of employees in each department whose salary is greater than 60000.

```sql
SELECT department, COUNT(*)
FROM employees
WHERE salary > 60000
GROUP BY department;
```

Execution:

```text
All employees
     ↓
WHERE salary > 60000
     ↓
Filtered employees
     ↓
GROUP BY department
     ↓
COUNT(*)
```

Result:

| department | count |
|---|---:|
| AI | 2 |
| CSE | 1 |

### Important

```text
WHERE → Filters individual rows
GROUP BY → Creates groups
```

---

## 15. GROUP BY Multiple Columns

You can group by multiple columns.

```sql
SELECT department, age, COUNT(*)
FROM employees
GROUP BY department, age;
```

Rows are grouped according to the **combination** of both columns.

```text
department + age
```

So:

```text
AI + 21
AI + 24
CSE + 22
CSE + 23
HR + 25
```

are separate groups.

---

## 16. GROUP BY Rule

When using `GROUP BY`, every selected column that is **not an aggregate** should generally appear in the `GROUP BY`.

### Correct

```sql
SELECT department, COUNT(*)
FROM employees
GROUP BY department;
```

```text
department → GROUP BY
COUNT(*)   → Aggregate
```

### Generally Invalid

```sql
SELECT department, name, COUNT(*)
FROM employees
GROUP BY department;
```

Why?

For the `AI` group there are multiple names:

```text
Harsha
Arjun
```

SQL cannot decide which `name` to return.

Therefore, `name` must either be grouped or aggregated.

---

## 17. GROUP BY vs DISTINCT

These can look similar but have different purposes.

### DISTINCT

Removes duplicate values from the result.

```sql
SELECT DISTINCT department
FROM employees;
```

Result:

```text
AI
CSE
HR
```

### GROUP BY

Creates groups, usually so that an aggregate can be applied to each group.

```sql
SELECT department, COUNT(*)
FROM employees
GROUP BY department;
```

Result:

```text
AI  → 2
CSE → 2
HR  → 1
```

### Difference

```text
DISTINCT → Remove duplicate results

GROUP BY → Create groups for aggregation
```

---

## 18. Aggregate Without GROUP BY vs With GROUP BY

### Without GROUP BY

```sql
SELECT COUNT(*)
FROM employees;
```

Returns one overall result:

```text
5
```

### With GROUP BY

```sql
SELECT department, COUNT(*)
FROM employees
GROUP BY department;
```

Returns one result for each department:

```text
AI  → 2
CSE → 2
HR  → 1
```

### Remember

```text
Without GROUP BY → One overall result

With GROUP BY → One result per group
```

---

# 19. GROUP BY — Final Mental Model

```text
SELECT
    department,
    AVG(salary)
FROM employees
GROUP BY department;
```

Read it as:

> Group employees by department, then calculate the average salary for each department.

General pattern:

```text
FROM
 ↓
WHERE
 ↓
GROUP BY
 ↓
Aggregate
```

For now, remember:

```text
WHERE → Filter rows
GROUP BY → Create groups
Aggregate → Calculate for each group
```

---

## 20. HAVING

`HAVING` is used to **filter groups** created by `GROUP BY`.

```text
WHERE  → Filters rows
HAVING → Filters groups
```

---

## 21. Basic HAVING

Question:

> Find departments having more than 1 employee.

```sql
SELECT department, COUNT(*)
FROM employees
GROUP BY department
HAVING COUNT(*) > 1;
```

First `GROUP BY` creates:

```text
AI  → 2
CSE → 2
HR  → 1
```

Then `HAVING` filters the groups:

```text
AI  → 2 > 1 → ✅
CSE → 2 > 1 → ✅
HR  → 1 > 1 → ❌
```

Result:

| department | count |
|---|---:|
| AI | 2 |
| CSE | 2 |

---

## 22. HAVING with SUM()

Question:

> Find departments whose total salary is greater than 100000.

```sql
SELECT department, SUM(salary)
FROM employees
GROUP BY department
HAVING SUM(salary) > 100000;
```

Result:

| department | total salary |
|---|---:|
| AI | 150000 |
| CSE | 135000 |

`HR` is excluded because its total salary is `50000`.

---

## 23. HAVING with AVG()

Question:

> Find departments whose average salary is greater than 70000.

```sql
SELECT department, AVG(salary)
FROM employees
GROUP BY department
HAVING AVG(salary) > 70000;
```

Result:

| department | average salary |
|---|---:|
| AI | 75000 |

---

## 24. HAVING Without GROUP BY

`HAVING` can be used without an explicit `GROUP BY` when the query uses an aggregate.

```sql
SELECT COUNT(*)
FROM employees
HAVING COUNT(*) > 1;
```

Without `GROUP BY`, the entire table is treated as **one overall group**.

```text
All employees
     ↓
One group
     ↓
COUNT(*) = 5
     ↓
5 > 1 → ✅
```

Result:

```text
5
```

However:

```sql
SELECT department, COUNT(*)
FROM employees
HAVING COUNT(*) > 1;
```

is generally invalid because `department` is neither grouped nor aggregated.

---

## 25. WHERE + GROUP BY + HAVING

All three can be used together.

Question:

> Find departments having more than 1 employee whose salary is greater than 60000.

```sql
SELECT department, COUNT(*)
FROM employees
WHERE salary > 60000
GROUP BY department
HAVING COUNT(*) > 1;
```

Execution:

```text
FROM
 ↓
WHERE
 ↓
GROUP BY
 ↓
HAVING
 ↓
SELECT
```

First `WHERE` filters the rows:

```text
Harsha → AI
Arjun  → AI
Kiran  → CSE
```

Then `GROUP BY`:

```text
AI  → 2
CSE → 1
```

Then `HAVING COUNT(*) > 1`:

```text
AI  → 2 > 1 → ✅
CSE → 1 > 1 → ❌
```

Final result:

```text
AI → 2
```

---

## 26. WHERE vs HAVING

| WHERE | HAVING |
|---|---|
| Filters rows | Filters groups |
| Applied before `GROUP BY` | Applied after `GROUP BY` |
| Used for row-level conditions | Used for group-level conditions |
| `salary > 60000` | `COUNT(*) > 1` |
| `department = 'AI'` | `AVG(salary) > 70000` |

### Easy Memory Trick

```text
WHERE
→ Which rows do I want?

HAVING
→ Which groups do I want?
```

---

## 27. WHERE vs HAVING — Example

### WHERE

```sql
SELECT department, COUNT(*)
FROM employees
WHERE salary > 60000
GROUP BY department;
```

Here, `WHERE` filters individual rows **before grouping**.

```text
Rows
 ↓
WHERE
 ↓
Filtered Rows
 ↓
GROUP BY
 ↓
Groups
```

### HAVING

```sql
SELECT department, COUNT(*)
FROM employees
GROUP BY department
HAVING COUNT(*) > 1;
```

Here, `HAVING` filters groups **after grouping**.

```text
Rows
 ↓
GROUP BY
 ↓
Groups
 ↓
HAVING
 ↓
Filtered Groups
```

---

## 28. HAVING with Multiple Conditions

`HAVING` can contain multiple conditions using `AND` or `OR`.

Example:

> Find departments having more than 1 employee and an average salary greater than 65000.

```sql
SELECT department, COUNT(*), AVG(salary)
FROM employees
GROUP BY department
HAVING COUNT(*) > 1
   AND AVG(salary) > 65000;
```

Result:

| department | count | avg salary |
|---|---:|---:|
| AI | 2 | 75000 |
| CSE | 2 | 67500 |

---

## 29. HAVING — Final Mental Model

```text
FROM
 ↓
WHERE
 ↓
GROUP BY
 ↓
HAVING
 ↓
SELECT
```

Remember:

```text
WHERE  → Filters individual rows
GROUP BY → Creates groups
HAVING → Filters those groups
```

### Example

```sql
SELECT department, COUNT(*)
FROM employees
WHERE salary > 60000
GROUP BY department
HAVING COUNT(*) > 1;
```

Read it as:

> First keep employees whose salary is greater than 60000, group them by department, count each department, and keep only departments whose count is greater than 1.

---

## 30. Next Topic

### JOINs

```text
INNER JOIN
LEFT JOIN
RIGHT JOIN
FULL OUTER JOIN
SELF JOIN
CROSS JOIN
```

> JOINs are used to combine related data from multiple tables.
> 