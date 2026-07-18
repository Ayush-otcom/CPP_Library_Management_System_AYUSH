#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Member.h"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>

using namespace std;

struct IssuedBook {
    string bookID;
    string memberID;
    string issueDate;
    string dueDate;
    string returnDate;
    string status;

    string toFileString() const;
    static IssuedBook fromFileString(const string& data);
};

class Library {
private:
    vector<Book> books;                 // Core storage for Books (Dynamic Array)
    vector<Member> members;             // Core storage for Members (Dynamic Array)
    vector<IssuedBook> issuedBooks;     // Transaction records

    // STL Containers to fulfill project requirements
    stack<string> recentActions;               // LIFO tracking of last actions
    set<string> uniqueAuthors;                 // Unique, sorted collection of authors
    map<string, int> categoryCounts;           // Sorted key-value pair of Category -> Count
    unordered_map<string, size_t> bookIDMap;   // Hash map for O(1) Book ID -> Index lookups

    const string booksFile = "books.txt";
    const string membersFile = "members.txt";
    const string issuedBooksFile = "issuedBooks.txt";

    void rebuildIndices();
    void logAction(string action);

public:
    Library();
    ~Library();

    void addBook();
    void updateBook();
    void deleteBook();
    void displayAllBooks() const;
    
    void registerMember();
    void updateMember();
    void deleteMember();
    void displayAllMembers() const;

    void issueBook();
    void returnBook();
    void displayIssuedBooks() const;
    void fineReport() const;
    void reserveBookWaitlist();

    void searchBook() const;
    
    void sortBooks();
    void bookStatistics() const;
    void mostBorrowedBooks() const;
    void topReaders() const;
    void viewRecentActions();

    void saveData() const;
    void loadData();

private:
    Book* findBookByID(const string& id);
    Member* findMemberByID(const string& id);
    bool isDuplicateISBN(const string& isbn) const;
};

#endif // LIBRARY_H
