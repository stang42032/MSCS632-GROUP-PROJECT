#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Expense struct with four member variables
struct Expense {
    string date;
    double amount;
    string category;
    string description;
};

// Creating a Expense Tracker class
class ExpenseTracker {
private:
    vector<Expense> expenses; 

public:
    // method to add expense object
    void addExpense(const string &date, double amount, const string &category, const string &description) {
        Expense exp{date, amount, category, description};
        expenses.push_back(exp);
    }

    // method to view all expenses
    void viewExpenses() {
        if (expenses.empty()) {
            cout << "No expenses entered yet.\n";
            return;
        }
        cout << "\nYour Expenses List:\n";
        cout << left << setw(12) << "Date" << setw(10) << "Amount"
             << setw(15) << "Category" << "Description\n";
        cout << "------------------------------------------------------\n";
        for (const auto &e : expenses) {
            cout << left << setw(12) << e.date
                 << setw(10) << e.amount
                 << setw(15) << e.category
                 << e.description << "\n";
        }
    }

    // method to filter by category
    void filterByCategory(const string &cat) {
        cout << "\nExpenses in category: " << cat << "\n";
        bool found = false;
        for (const auto &exp : expenses) {
            if (exp.category == cat) {
                cout << exp.date << " | " << exp.amount << " | " << exp.description << "\n";
                found = true;
            }
        }
        if (!found) cout << "No expenses found in this category.\n";
    }

    // method to filter by date range
    void filterByDateRange(const string &start, const string &end) {
        cout << "\nExpenses from " << start << " to " << end << "\n";
        bool found = false;
        for (const auto &exp : expenses) {
            if (exp.date >= start && exp.date <= end) {
                cout << exp.date << " | " << exp.amount << " | "
                     << exp.category << " | " << exp.description << "\n";
                found = true;
            }
        }
        if (!found) cout << "No expenses found in this range.\n";
    }

    // print the summary of all expense records
    void summaryOfYourExpense() {
        if (expenses.empty()) {
            cout << "No expenses to summarize.\n";
            return;
        }

        double total = 0.0;
        cout << "\nSummary by Category:\n";

        vector<string> categories;
        for (const auto &exp : expenses) {
            if (find(categories.begin(), categories.end(), exp.category) == categories.end()) {
                categories.push_back(exp.category);
            }
        }

        for (const auto &cat : categories) {
            double sum = 0;
            for (const auto &exp : expenses) {
                if (exp.category == cat)
                    sum += exp.amount;
            }
            cout << "  " << cat << ": " << sum << "\n";
            total += sum;
        }
        cout << "Overall Total: " << total << "\n";
    }

    // method to save expenses to a CSV file
    void saveToFile(const string &filename) {
        ofstream file(filename);
        if (!file) {
            cerr << "Error opening file for writing.\n";
            return;
        }
        file << "date, amount, category, description \n"; // adding the header in file
        for (const auto &exp : expenses) {
            file << exp.date << "," << exp.amount << ","
                 << exp.category << "," << exp.description << "\n";
        }
        file.close();
        cout << "Expenses saved to " << filename << "\n";
    }

    // method to load expenses from file
    void loadFromFile(const string &filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file for reading.\n";
            return;
        }
        expenses.clear();
        string line;
        getline(file, line); // ignore the first line(header) from file
        while (getline(file, line)) {
            stringstream ss(line);
            Expense exp;
            string amountStr;

            getline(ss, exp.date, ',');
            getline(ss, amountStr, ',');
            getline(ss, exp.category, ',');
            getline(ss, exp.description, ',');

            exp.amount = stod(amountStr);
            expenses.push_back(exp);
        }
        file.close();
        cout << "Expenses loaded from " << filename << "\n";
    }
};

// Main interactive expense tracker menu
int main() {
    ExpenseTracker tracker;
    string filename = "my_expenses.csv"; // file to read or write the expenses record
    int choice;

    do {
        cout << "\n==== Expense Tracker ====\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Filter by Category\n";
        cout << "4. Filter by Date Range\n";
        cout << "5. Summary\n";
        cout << "6. Save to File\n";
        cout << "7. Load from File\n";
        cout << "8. Exit\n";
        cout << "Please enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string date, category, description;
            double amount;
            cout << "Please enter date in (YYYY-MM-DD) format: ";
            getline(cin, date);
            cout << "Enter the amount you spend: ";
            cin >> amount;
            cin.ignore();
            cout << "Enter the category of your expenditure: ";
            getline(cin, category);
            cout << "Please enter the description of your expense: ";
            getline(cin, description);
            tracker.addExpense(date, amount, category, description);

        } else if (choice == 2) {
            tracker.viewExpenses();

        } else if (choice == 3) {
            string cat;
            cout << "Enter category: ";
            getline(cin, cat);
            tracker.filterByCategory(cat);

        } else if (choice == 4) {
            string start, end;
            cout << "Enter start date (YYYY-MM-DD): ";
            getline(cin, start);
            cout << "Enter end date (YYYY-MM-DD): ";
            getline(cin, end);
            tracker.filterByDateRange(start, end);

        } else if (choice == 5) {
            tracker.summaryOfYourExpense();

        } else if (choice == 6) {
            tracker.saveToFile(filename);

        } else if (choice == 7) {
            tracker.loadFromFile(filename);

        } else if (choice == 8) {
            cout << "Exiting the Expense tracker program...\n";

        } else {
            cout << "Invalid choice. Please choose a valid number ranging from 1-8.\n";
        }

    } while (choice != 8);

    return 0;
}