#include "Member.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

// Default Constructor
Member::Member() : fineAmount(0.0) {}

// Parameterized Constructor
Member::Member(string id, string name, string email, string phone, 
               string address, string type, string joinDate)
    : memberID(id), name(name), email(email), phone(phone), 
      address(address), membershipType(type), dateOfJoining(joinDate), fineAmount(0.0) {}

// Getters
string Member::getMemberID() const { return memberID; }
string Member::getName() const { return name; }
string Member::getEmail() const { return email; }
string Member::getPhone() const { return phone; }
string Member::getAddress() const { return address; }
string Member::getMembershipType() const { return membershipType; }
string Member::getDateOfJoining() const { return dateOfJoining; }
double Member::getFineAmount() const { return fineAmount; }
const vector<string>& Member::getBooksBorrowed() const { return booksBorrowed; }

// Setters
void Member::setName(string newName) { name = newName; }
void Member::setEmail(string newEmail) { email = newEmail; }
void Member::setPhone(string newPhone) { phone = newPhone; }
void Member::setAddress(string newAddress) { address = newAddress; }

// Borrow Book
bool Member::borrowBook(string bookID) {
    if (booksBorrowed.size() < (size_t)getBorrowLimit()) {
        booksBorrowed.push_back(bookID);
        return true;
    }
    return false;
}

// Return Book
bool Member::returnBook(string bookID) {
    auto it = find(booksBorrowed.begin(), booksBorrowed.end(), bookID);
    if (it != booksBorrowed.end()) {
        booksBorrowed.erase(it);
        return true;
    }
    return false;
}

// Fine management
void Member::addFine(double amount) {
    if (amount > 0) {
        fineAmount += amount;
    }
}

void Member::payFine(double amount) {
    if (amount > 0 && amount <= fineAmount) {
        fineAmount -= amount;
    } else if (amount > fineAmount) {
        fineAmount = 0.0; // Paid more than required, reset to 0
    }
}

// Display borrowed books
void Member::viewBorrowedBooks() const {
    if (booksBorrowed.empty()) {
        cout << "No books currently borrowed." << endl;
        return;
    }
    cout << "Borrowed Book IDs: ";
    for (const auto& id : booksBorrowed) {
        cout << id << " ";
    }
    cout << endl;
}

// Display Member Details
void Member::displayMember() const {
    cout << "---------------------------------------" << endl;
    cout << "Member ID: " << memberID << " | Name: " << name << endl;
    cout << "Email: " << email << " | Phone: " << phone << endl;
    cout << "Address: " << address << endl;
    cout << "Membership: " << membershipType << " | Join Date: " << dateOfJoining << endl;
    cout << "Fine Due: Rs " << fixed << setprecision(2) << fineAmount << endl;
    viewBorrowedBooks();
    cout << "---------------------------------------" << endl;
}

// Get Borrow Limit based on type
int Member::getBorrowLimit() const {
    if (membershipType == "Student") return 3;
    if (membershipType == "Faculty") return 5;
    return 2; // Default limit
}

// Convert Member object to a string for saving
string Member::toFileString() const {
    ostringstream oss;
    oss << memberID << "|" << name << "|" << email << "|" << phone << "|"
        << address << "|" << membershipType << "|" << dateOfJoining << "|"
        << fixed << setprecision(2) << fineAmount;
    
    // Append borrowed books
    if (!booksBorrowed.empty()) {
        oss << "|";
        for (size_t i = 0; i < booksBorrowed.size(); ++i) {
            oss << booksBorrowed[i];
            if (i < booksBorrowed.size() - 1) oss << ",";
        }
    }
    return oss.str();
}

// Create a Member object from a file string
Member Member::fromFileString(const string& data) {
    stringstream ss(data);
    string token;
    vector<string> tokens;
    
    while (getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() >= 8) {
        Member m;
        m.memberID = tokens[0];
        m.name = tokens[1];
        m.email = tokens[2];
        m.phone = tokens[3];
        m.address = tokens[4];
        m.membershipType = tokens[5];
        m.dateOfJoining = tokens[6];
        m.fineAmount = stod(tokens[7]);
        
        if (tokens.size() == 9 && !tokens[8].empty()) {
            stringstream bookSS(tokens[8]);
            string bookIdToken;
            while (getline(bookSS, bookIdToken, ',')) {
                m.booksBorrowed.push_back(bookIdToken);
            }
        }
        return m;
    }
    return Member(); // Return empty member if parsing fails
}
