#include "Library.h"
#include <iostream>

using namespace std;

void showMenu() {
    cout << "\n=============================\n";
    cout << "  Library Management System  \n";
    cout << "=============================\n";
    cout << "1  Add Book\n";
    cout << "2  Update Book\n";
    cout << "3  Delete Book\n";
    cout << "4  Search Book\n";
    cout << "5  Display Books\n";
    cout << "\n";
    cout << "6  Register Member\n";
    cout << "7  Update Member\n";
    cout << "8  Delete Member\n";
    cout << "9  Display Members\n";
    cout << "\n";
    cout << "10 Issue Book\n";
    cout << "11 Return Book\n";
    cout << "12 Display Issued Books\n";
    cout << "13 Reserve Book (Waitlist)\n";
    cout << "\n";
    cout << "14 Fine Report\n";
    cout << "15 Book & Category Statistics\n";
    cout << "16 Sort Books\n";
    cout << "17 Most Borrowed Books\n";
    cout << "18 Top Readers\n";
    cout << "19 View Recent Actions\n";
    cout << "\n";
    cout << "20 Save Data\n";
    cout << "21 Exit\n";
    cout << "=============================\n";
    cout << "Enter your choice: ";
}

int main() {
    Library lib;
    int choice;

    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1: lib.addBook(); break;
                case 2: lib.updateBook(); break;
                case 3: lib.deleteBook(); break;
                case 4: lib.searchBook(); break;
                case 5: lib.displayAllBooks(); break;
                case 6: lib.registerMember(); break;
                case 7: lib.updateMember(); break;
                case 8: lib.deleteMember(); break;
                case 9: lib.displayAllMembers(); break;
                case 10: lib.issueBook(); break;
                case 11: lib.returnBook(); break;
                case 12: lib.displayIssuedBooks(); break;
                case 13: lib.reserveBookWaitlist(); break;
                case 14: lib.fineReport(); break;
                case 15: lib.bookStatistics(); break;
                case 16: lib.sortBooks(); break;
                case 17: lib.mostBorrowedBooks(); break;
                case 18: lib.topReaders(); break;
                case 19: lib.viewRecentActions(); break;
                case 20: 
                    lib.saveData(); 
                    cout << "Data saved successfully!\n";
                    break;
                case 21:
                    lib.saveData(); // Explicitly save before exit!
                    cout << "Exiting the system. Data is automatically saved. Goodbye!\n";
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } catch (const exception& e) {
            cout << "An error occurred: " << e.what() << endl;
        }
    }

    return 0;
}
