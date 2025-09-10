##!/usr/bin/env python3
"""
Expense Tracker Application (Python)
------------------------------------
Usage:
  python expense_tracker.py           # interactive mode
"""

import json
import os
from datetime import datetime

## A constant that stores the filename where expenses will be saved
DATA_FILE = "expenses.json"    

## parse JSON and load expenses as a Python list of dictionaries
def load_expenses():
    if not os.path.exists(DATA_FILE):
        return []
    with open(DATA_FILE, "r", encoding="utf-8") as f:
        return json.load(f)

## save the expenses list back into the JSON file
def save_expenses(expenses):
    with open(DATA_FILE, "w", encoding="utf-8") as f:
        json.dump(expenses, f, indent=2)

## add a new expense and enter a valid date string, amount, category, description
def add_expense(expenses):
    date_str = input("Enter date (YYYY-MM-DD): ")
    try:
        datetime.strptime(date_str, "%Y-%m-%d")
    except ValueError:
        print("Invalid date format.")
        return
    amount = float(input("Enter amount: "))
    category = input("Enter category: ")
    description = input("Enter description: ")

## Create a dictionary representing one expense record
    expense = {
        "date": date_str,
        "amount": amount,
        "category": category,
        "description": description,
    }
## add the new dictionary to the expense list and save the updated list to the JSON file
    expenses.append(expense)
    save_expenses(expenses)
    print("Expense added successfully.")

## display the expenses
def view_expenses(expenses):
    if not expenses:
        print("No expenses recorded.")
        return
    for i, e in enumerate(expenses, start=1):
        print(f"{i}. {e['date']} - ${e['amount']:.2f} - {e['category']} - {e['description']}")

##filter expenses by category and date range
def filter_expenses(expenses):
    print("Filter by:")
    print("1. Category")
    print("2. Date range")
    choice = input("Enter choice: ")
    if choice == "1":
        category = input("Enter category: ")
        filtered = [e for e in expenses if e['category'].lower() == category.lower()]
    elif choice == "2":
        start = input("Start date (YYYY-MM-DD): ")
        end = input("End date (YYYY-MM-DD): ")
        try:
            start_dt = datetime.strptime(start, "%Y-%m-%d")
            end_dt = datetime.strptime(end, "%Y-%m-%d")
        except ValueError:
            print("Invalid date format.")
            return
        filtered = [
            e for e in expenses
            if start_dt <= datetime.strptime(e['date'], "%Y-%m-%d") <= end_dt
        ]
    else:
        print("Invalid choice.")
        return
    view_expenses(filtered)

## summarize the overall total and each category's total
def summary(expenses):
    total = 0
    category_totals = {}
    for e in expenses:
        total += e["amount"]
        category_totals[e["category"]] = category_totals.get(e["category"], 0) + e["amount"]

    print("Expense Summary:")
    print(f"Overall total: ${total:.2f}")
    for cat, amt in category_totals.items():
        print(f"  {cat}: ${amt:.2f}")

## Interactive application interface to allow users to choose the function they wnat to use
def main():
    expenses = load_expenses()
    while True:
        print("\n--- Expense Tracker ---")
        print("1. Add expense")
        print("2. View expenses")
        print("3. Filter expenses")
        print("4. Summary")
        print("5. Exit")
        choice = input("Choose an option: ")
        if choice == "1":
            add_expense(expenses)
        elif choice == "2":
            view_expenses(expenses)
        elif choice == "3":
            filter_expenses(expenses)
        elif choice == "4":
            summary(expenses)
        elif choice == "5":
            print("Goodbye!")
            break
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
