#include "Book.h"
#include <iomanip>

Book::Book() : publicationYear(0), totalCopies(0), availableCopies(0), price(0.0), borrowCount(0) {
    status = "Unavailable";
}

Book::Book(string id, string isbn, string title, string author, string category, 
           string publisher, int year, int total, string shelf, double price)
    : bookID(id), isbn(isbn), title(title), author(author), category(category), 
      publisher(publisher), publicationYear(year), totalCopies(total), 
      availableCopies(total), shelfNumber(shelf), price(price), borrowCount(0) {
    status = (availableCopies > 0) ? "Available" : "Unavailable";
}

string Book::getBookID() const { return bookID; }
string Book::getISBN() const { return isbn; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getCategory() const { return category; }
string Book::getPublisher() const { return publisher; }
int Book::getPublicationYear() const { return publicationYear; }
int Book::getTotalCopies() const { return totalCopies; }
int Book::getAvailableCopies() const { return availableCopies; }
string Book::getShelfNumber() const { return shelfNumber; }
string Book::getStatus() const { return status; }
double Book::getPrice() const { return price; }
int Book::getBorrowCount() const { return borrowCount; }

void Book::setAvailableCopies(int copies) {
    if (copies >= 0 && copies <= totalCopies) {
        availableCopies = copies;
        status = (availableCopies > 0) ? "Available" : "Unavailable";
    }
}

void Book::setStatus(string newStatus) { status = newStatus; }
void Book::incrementBorrowCount() { borrowCount++; }

void Book::addToWaitlist(string memberID) {
    waitlist.push(memberID);
    cout << "Member " << memberID << " added to waitlist for book " << title << ".\n";
}

string Book::popFromWaitlist() {
    if (waitlist.empty()) return "";
    string nextMember = waitlist.front();
    waitlist.pop();
    return nextMember;
}

bool Book::hasWaitlist() const { return !waitlist.empty(); }

void Book::displayWaitlist() const {
    if (waitlist.empty()) {
        cout << "No members in waitlist.\n";
        return;
    }
    queue<string> temp = waitlist;
    cout << "Waitlist for " << title << ": ";
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
}

void Book::displayBook() const {
    cout << "---------------------------------------" << endl;
    cout << "Book ID: " << bookID << " | ISBN: " << isbn << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << " | Category: " << category << endl;
    cout << "Price: Rs " << fixed << setprecision(2) << price << " | Year: " << publicationYear << endl;
    cout << "Total Copies: " << totalCopies << " | Available: " << availableCopies << endl;
    cout << "Shelf: " << shelfNumber << " | Status: " << status << " | Borrowed: " << borrowCount << " times\n";
    cout << "Waitlist count: " << waitlist.size() << endl;
    cout << "---------------------------------------" << endl;
}

bool Book::checkAvailability() const { return availableCopies > 0; }

bool Book::issueCopy() {
    if (availableCopies > 0) {
        availableCopies--;
        if (availableCopies == 0) status = "Unavailable";
        borrowCount++;
        return true;
    }
    return false;
}

bool Book::returnCopy() {
    if (availableCopies < totalCopies) {
        availableCopies++;
        status = "Available";
        return true;
    }
    return false;
}

string Book::toFileString() const {
    ostringstream oss;
    oss << bookID << "|" << isbn << "|" << title << "|" << author << "|"
        << category << "|" << publisher << "|" << publicationYear << "|"
        << totalCopies << "|" << availableCopies << "|" << shelfNumber << "|"
        << status << "|" << fixed << setprecision(2) << price << "|" << borrowCount;
    
    queue<string> temp = waitlist;
    if (!temp.empty()) {
        oss << "|";
        while (!temp.empty()) {
            oss << temp.front();
            temp.pop();
            if (!temp.empty()) oss << ",";
        }
    }
    return oss.str();
}

Book Book::fromFileString(const string& data) {
    stringstream ss(data);
    string token;
    vector<string> tokens;
    while (getline(ss, token, '|')) tokens.push_back(token);

    Book b;
    if (tokens.size() >= 13) {
        b.bookID = tokens[0];
        b.isbn = tokens[1];
        b.title = tokens[2];
        b.author = tokens[3];
        b.category = tokens[4];
        b.publisher = tokens[5];
        b.publicationYear = stoi(tokens[6]);
        b.totalCopies = stoi(tokens[7]);
        b.availableCopies = stoi(tokens[8]);
        b.shelfNumber = tokens[9];
        b.status = tokens[10];
        b.price = stod(tokens[11]);
        b.borrowCount = stoi(tokens[12]);

        if (tokens.size() == 14 && !tokens[13].empty()) {
            stringstream waitSS(tokens[13]);
            string wToken;
            while (getline(waitSS, wToken, ',')) {
                b.waitlist.push(wToken);
            }
        }
    }
    return b;
}
