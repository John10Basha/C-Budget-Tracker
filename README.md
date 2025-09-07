# Budget Tracker – COMP348 Assignment 1

## 📌 Project Overview
This project is a **Budget Tracking System** written in C for the COMP348: Principles of Programming Languages course.  
The program allows users to track income and expenses, sort and filter transactions, and view expense distributions.  
It is designed to give hands-on experience with **C programming fundamentals** such as:
- File I/O
- Structs
- Dynamic memory allocation
- Modular programming
- Pointers and arrays
- Error checking

---

## 🚀 Features
The application provides the following menu options:

1. **Display all entries** – Show all records in a neat table format with headers.  
2. **Expense Distribution** – Summarize total income, total expenses, needs vs wants, and net balance.  
3. **Sort Entries** – Sort transactions by ID, date, amount, or description.  
4. **Add Income/Expense Entry** – Add a new record with today’s date or a custom date.  
5. **Modify Entry** – Update an existing entry (date or amount).  
6. **Filter by Month** – Show only the entries for a specific month and year.  
7. **Exit** – Close the program with a goodbye message.

---

## 📂 Project Structure
The codebase is divided into multiple files for modularity:
main.c # Contains main function and menu logic
budget.c # Implements budget-related operations (add, modify, distribution, etc.)
data.c # Handles file reading, parsing, and data management
ordering.c # Sorting functionality
main.h, budget.h, data.h, ordering.h # Corresponding header files
