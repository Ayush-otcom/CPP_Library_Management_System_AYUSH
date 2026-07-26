#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

// Book class representing a book in the library
class Book {
private:
    string bookID;
    string isbn;
    string title;
    string author;
    string category;
    string publisher;
    int publicationYear;
    int totalCopies;
    int availableCopies;
    string shelfNumber;
    string status; 
    double price;
    int borrowCount; // Track how many times the book was borrowed
    queue<string> waitlist; // STL Queue: Manages member IDs waiting for this book (FIFO)

public:
    Book();
    Book(string id, string isbn, string title, string author, string category, 
         string publisher, int year, int total, string shelf, double price);

    // Getters
    string getBookID() const;
    string getISBN() const;
    string getTitle() const;
    string getAuthor() const;
    string getCategory() const;
    string getPublisher() const;
    int getPublicationYear() const;
    int getTotalCopies() const;
    int getAvailableCopies() const;
    string getShelfNumber() const;
    string getStatus() const;
    double getPrice() const;
    int getBorrowCount() const;

    // Setters
    void setAvailableCopies(int copies);
    void setStatus(string newStatus);
    void incrementBorrowCount();

    // Waitlist Management
    void addToWaitlist(string memberID);
    string popFromWaitlist();
    bool hasWaitlist() const;
    void displayWaitlist() const;

    // Core functionality
    void displayBook() const;
    bool checkAvailability() const;
    bool issueCopy();
    bool returnCopy();

    string toFileString() const;
    static Book fromFileString(const string& data);
};

#endif // BOOK_H
