#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Member class representing a library user
class Member {
private:
    string memberID;
    string name;
    string email;
    string phone;
    string address;
    string membershipType; // e.g., "Student", "Faculty", "Public"
    string dateOfJoining;
    vector<string> booksBorrowed; // Stores Book IDs
    double fineAmount;

public:
    // Default constructor
    Member();

    // Parameterized constructor
    Member(string id, string name, string email, string phone, 
           string address, string type, string joinDate);

    // Getters
    string getMemberID() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    string getAddress() const;
    string getMembershipType() const;
    string getDateOfJoining() const;
    double getFineAmount() const;
    const vector<string>& getBooksBorrowed() const;

    // Setters
    void setName(string newName);
    void setEmail(string newEmail);
    void setPhone(string newPhone);
    void setAddress(string newAddress);

    // Core functionality
    bool borrowBook(string bookID);
    bool returnBook(string bookID);
    void addFine(double amount);
    void payFine(double amount);
    void viewBorrowedBooks() const;
    void displayMember() const;
    
    // Check borrow limit based on membership type
    int getBorrowLimit() const;

    // File Handling formats
    string toFileString() const;
    static Member fromFileString(const string& data);
};

#endif // MEMBER_H
