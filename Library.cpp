#include "Library.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

string IssuedBook::toFileString() const {
    return bookID + "|" + memberID + "|" + issueDate + "|" + dueDate + "|" + returnDate + "|" + status;
}
IssuedBook IssuedBook::fromFileString(const string& data) {
    IssuedBook ib;
    size_t pos1 = data.find('|');
    size_t pos2 = data.find('|', pos1 + 1);
    size_t pos3 = data.find('|', pos2 + 1);
    size_t pos4 = data.find('|', pos3 + 1);
    size_t pos5 = data.find('|', pos4 + 1);
    if (pos1 != string::npos && pos5 != string::npos) {
        ib.bookID = data.substr(0, pos1);
        ib.memberID = data.substr(pos1 + 1, pos2 - pos1 - 1);
        ib.issueDate = data.substr(pos2 + 1, pos3 - pos2 - 1);
        ib.dueDate = data.substr(pos3 + 1, pos4 - pos3 - 1);
        ib.returnDate = data.substr(pos4 + 1, pos5 - pos4 - 1);
        ib.status = data.substr(pos5 + 1);
    }
    return ib;
}

Library::Library() { loadData(); rebuildIndices(); }
Library::~Library() { saveData(); }

void Library::logAction(string action) {
    recentActions.push(action);
}

void Library::viewRecentActions() {
    cout << "\n--- Recent Actions (Last 5) ---\n";
    if (recentActions.empty()) {
        cout << "No recent actions.\n";
        return;
    }
    stack<string> temp = recentActions;
    int count = 0;
    while (!temp.empty() && count < 5) {
        cout << "- " << temp.top() << "\n";
        temp.pop();
        count++;
    }
}

void Library::rebuildIndices() {
    bookIDMap.clear();
    uniqueAuthors.clear();
    categoryCounts.clear();
    
    for (size_t i = 0; i < books.size(); ++i) {
        bookIDMap[books[i].getBookID()] = i;
        uniqueAuthors.insert(books[i].getAuthor());
        categoryCounts[books[i].getCategory()]++;
    }
}

Book* Library::findBookByID(const string& id) {
    if (bookIDMap.find(id) != bookIDMap.end()) {
        return &books[bookIDMap[id]]; // O(1) Lookup using unordered_map
    }
    return nullptr;
}

Member* Library::findMemberByID(const string& id) {
    for (auto& member : members) {
        if (member.getMemberID() == id) return &member;
    }
    return nullptr;
}

bool Library::isDuplicateISBN(const string& isbn) const {
    for (const auto& book : books) {
        if (book.getISBN() == isbn) return true;
    }
    return false;
}

void Library::addBook() {
    string id, isbn, title, author, category, pub, shelf;
    int year, copies; double price;

    cout << "\n--- Add New Book ---\n";
    cout << "Enter Book ID: "; cin >> id;
    if (findBookByID(id)) { cout << "Error: ID exists!\n"; return; }

    cout << "Enter ISBN: "; cin >> isbn;
    if (isDuplicateISBN(isbn)) { cout << "Error: ISBN exists!\n"; return; }

    cin.ignore();
    cout << "Enter Title: "; getline(cin, title);
    if (title.empty()) { cout << "Error: Title empty!\n"; return; }

    cout << "Enter Author: "; getline(cin, author);
    cout << "Enter Category: "; getline(cin, category);
    cout << "Enter Publisher: "; getline(cin, pub);
    cout << "Enter Year: "; cin >> year;
    cout << "Enter Total Copies: "; cin >> copies;
    if (copies < 0) return;
    cout << "Enter Price: "; cin >> price;
    if (price < 0) return;
    
    cin.ignore();
    cout << "Enter Shelf Number: "; getline(cin, shelf);

    Book newBook(id, isbn, title, author, category, pub, year, copies, shelf, price);
    books.push_back(newBook);
    rebuildIndices(); // Update maps
    logAction("Added Book: " + title);
    cout << "Book added successfully!\n";
}

void Library::updateBook() {
    string id; cout << "Enter Book ID: "; cin >> id;
    Book* book = findBookByID(id);
    if (!book) { cout << "Not found!\n"; return; }
    
    int copies; cout << "Current total: " << book->getTotalCopies() << ". New Total (-1 to skip): "; cin >> copies;
    if (copies != -1 && copies >= 0) {
        int issued = book->getTotalCopies() - book->getAvailableCopies();
        if (copies >= issued) {
            Book updated(book->getBookID(), book->getISBN(), book->getTitle(), book->getAuthor(),
                         book->getCategory(), book->getPublisher(), book->getPublicationYear(),
                         copies, book->getShelfNumber(), book->getPrice());
            updated.setAvailableCopies(copies - issued);
            *book = updated;
            logAction("Updated Book: " + book->getTitle());
            cout << "Updated!\n";
        }
    }
}

void Library::deleteBook() {
    string id; cout << "Enter Book ID: "; cin >> id;
    if (bookIDMap.find(id) != bookIDMap.end()) {
        size_t idx = bookIDMap[id];
        if (books[idx].getAvailableCopies() != books[idx].getTotalCopies()) {
            cout << "Cannot delete. Copies are issued!\n";
        } else {
            string title = books[idx].getTitle();
            books.erase(books.begin() + idx);
            rebuildIndices();
            logAction("Deleted Book: " + title);
            cout << "Deleted!\n";
        }
    } else {
        cout << "Not found!\n";
    }
}

void Library::displayAllBooks() const {
    for (const auto& book : books) book.displayBook();
}

void Library::registerMember() {
    string id, name, email, phone, addr, type;
    cout << "Enter Member ID: "; cin >> id;
    if (findMemberByID(id)) { cout << "ID exists!\n"; return; }
    cin.ignore();
    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Email: "; getline(cin, email);
    if (!Utility::isValidEmail(email)) { cout << "Invalid Email!\n"; return; }
    cout << "Enter Phone (10 digits): "; getline(cin, phone);
    if (!Utility::isValidPhone(phone)) { cout << "Invalid Phone!\n"; return; }
    cout << "Enter Address: "; getline(cin, addr);
    cout << "Enter Membership Type (Student/Faculty/Public): "; getline(cin, type);

    members.push_back(Member(id, name, email, phone, addr, type, Utility::getCurrentDate()));
    logAction("Registered Member: " + name);
    cout << "Registered!\n";
}

void Library::updateMember() {
    string id; cout << "Enter ID: "; cin >> id;
    Member* m = findMemberByID(id);
    if (!m) return;
    string in; cin.ignore();
    cout << "New Phone (empty skip): "; getline(cin, in);
    if (!in.empty() && Utility::isValidPhone(in)) m->setPhone(in);
    cout << "New Address (empty skip): "; getline(cin, in);
    if (!in.empty()) m->setAddress(in);
    logAction("Updated Member: " + m->getName());
    cout << "Updated!\n";
}

void Library::deleteMember() {
    string id; cout << "Enter ID: "; cin >> id;
    auto it = find_if(members.begin(), members.end(), [&](const Member& m){ return m.getMemberID() == id; });
    if (it != members.end()) {
        if (!it->getBooksBorrowed().empty() || it->getFineAmount() > 0) {
            cout << "Clear dues/books first!\n";
        } else {
            string name = it->getName();
            members.erase(it);
            logAction("Deleted Member: " + name);
            cout << "Deleted!\n";
        }
    }
}

void Library::displayAllMembers() const {
    for (const auto& mem : members) mem.displayMember();
}

void Library::reserveBookWaitlist() {
    string bId, mId; cout << "Enter Book ID: "; cin >> bId; cout << "Enter Member ID: "; cin >> mId;
    Book* book = findBookByID(bId); Member* mem = findMemberByID(mId);
    if (book && mem && !book->checkAvailability()) {
        book->addToWaitlist(mId);
        logAction("Reserved waitlist for " + book->getTitle());
    } else {
        cout << "Invalid IDs or Book is currently available (no need to waitlist).\n";
    }
}

void Library::issueBook() {
    string mId, bId; cout << "Enter Member ID: "; cin >> mId;
    Member* mem = findMemberByID(mId);
    if (!mem || mem->getFineAmount() > 0 || mem->getBooksBorrowed().size() >= (size_t)mem->getBorrowLimit()) {
        cout << "Member invalid, max limit reached, or pending fine!\n"; return;
    }

    cout << "Enter Book ID: "; cin >> bId;
    Book* book = findBookByID(bId);
    if (!book) { cout << "Invalid Book!\n"; return; }

    const auto& bList = mem->getBooksBorrowed();
    if (find(bList.begin(), bList.end(), bId) != bList.end()) { cout << "Duplicate issue!\n"; return; }

    if (book->checkAvailability()) {
        if (book->hasWaitlist()) {
            string nextUser = book->popFromWaitlist();
            if (nextUser != mId) {
                cout << "Reserved for Waitlist user: " << nextUser << ".\n";
                return;
            }
        }
        
        book->issueCopy();
        mem->borrowBook(bId);
        IssuedBook ib = {bId, mId, Utility::getCurrentDate(), Utility::calculateDueDate(Utility::getCurrentDate(), 7), "Pending", "Issued"};
        issuedBooks.push_back(ib);
        logAction("Issued Book: " + book->getTitle());
        cout << "Issued successfully! Due: " << ib.dueDate << endl;
    } else {
        cout << "No copies available. Add to waitlist? (y/n): ";
        char ch; cin >> ch;
        if (ch == 'y' || ch == 'Y') book->addToWaitlist(mId);
    }
}

void Library::returnBook() {
    string mId, bId; cout << "Enter Member ID: "; cin >> mId; cout << "Enter Book ID: "; cin >> bId;
    auto ib = find_if(issuedBooks.begin(), issuedBooks.end(), [&](const IssuedBook& i) {
        return i.memberID == mId && i.bookID == bId && i.status == "Issued";
    });
    if (ib == issuedBooks.end()) { cout << "Record not found!\n"; return; }

    Member* mem = findMemberByID(mId); Book* book = findBookByID(bId);
    if (mem && book) {
        book->returnCopy();
        mem->returnBook(bId);
        ib->returnDate = Utility::getCurrentDate();
        ib->status = "Returned";
        int late = Utility::calculateLateDays(ib->dueDate, ib->returnDate);
        if (late > 0) mem->addFine(Utility::calculateFine(late));
        logAction("Returned Book: " + book->getTitle());
        cout << "Returned successfully!\n";
        if (book->hasWaitlist()) cout << "NOTE: Users are waiting for this book!\n";
    }
}

void Library::displayIssuedBooks() const {
    cout << "\n--- Issued Books ---\n";
    for (const auto& ib : issuedBooks) cout << ib.bookID << " -> " << ib.memberID << " | Status: " << ib.status << endl;
}

void Library::fineReport() const {
    for (const auto& mem : members) {
        if (mem.getFineAmount() > 0) cout << mem.getName() << " | Fine: " << mem.getFineAmount() << endl;
    }
}

void Library::searchBook() const {
    int ch; cout << "Search 1.Title 2.Author 3.Category 4.ID 5.ISBN: "; cin >> ch;
    string query; cin.ignore(); cout << "Enter query: "; getline(cin, query);
    for (const auto& book : books) {
        bool m = false;
        if (ch==1) m = Utility::partialMatch(book.getTitle(), query);
        else if (ch==2) m = Utility::partialMatch(book.getAuthor(), query);
        else if (ch==3) m = Utility::partialMatch(book.getCategory(), query);
        else if (ch==4) m = Utility::partialMatch(book.getBookID(), query);
        else if (ch==5) m = Utility::partialMatch(book.getISBN(), query);
        if (m) book.displayBook();
    }
}

void Library::sortBooks() {
    int ch; cout << "Sort by 1.Title 2.Author 3.Price 4.Year: "; cin >> ch;
    if (ch==1) sort(books.begin(), books.end(), [](const Book& a, const Book& b) { return a.getTitle() < b.getTitle(); });
    else if (ch==2) sort(books.begin(), books.end(), [](const Book& a, const Book& b) { return a.getAuthor() < b.getAuthor(); });
    else if (ch==3) sort(books.begin(), books.end(), [](const Book& a, const Book& b) { return a.getPrice() < b.getPrice(); });
    else if (ch==4) sort(books.begin(), books.end(), [](const Book& a, const Book& b) { return a.getPublicationYear() < b.getPublicationYear(); });
    rebuildIndices(); // Vector order changed, update unordered_map!
    cout << "Sorted!\n"; displayAllBooks();
}

void Library::bookStatistics() const {
    cout << "\n--- Library Stats ---\n";
    cout << "Total Books: " << books.size() << " | Unique Authors: " << uniqueAuthors.size() << endl;
    cout << "Category Breakdown:\n";
    for (const auto& pair : categoryCounts) cout << "- " << pair.first << ": " << pair.second << " books\n";
}

void Library::mostBorrowedBooks() const {
    vector<Book> temp = books;
    sort(temp.begin(), temp.end(), [](const Book& a, const Book& b) { return a.getBorrowCount() > b.getBorrowCount(); });
    cout << "\n--- Top Borrowed Books ---\n";
    for (int i = 0; i < min(5, (int)temp.size()); i++) {
        if (temp[i].getBorrowCount() > 0)
            cout << i+1 << ". " << temp[i].getTitle() << " (Borrowed " << temp[i].getBorrowCount() << " times)\n";
    }
}

void Library::topReaders() const {
    vector<Member> temp = members;
    sort(temp.begin(), temp.end(), [](const Member& a, const Member& b) { return a.getBooksBorrowed().size() > b.getBooksBorrowed().size(); });
    cout << "\n--- Top Readers (Active Borrows) ---\n";
    for (int i = 0; i < min(5, (int)temp.size()); i++) {
        if (!temp[i].getBooksBorrowed().empty())
            cout << i+1 << ". " << temp[i].getName() << " (" << temp[i].getBooksBorrowed().size() << " books)\n";
    }
}

void Library::saveData() const {
    ofstream bFile(booksFile); for (const auto& b : books) bFile << b.toFileString() << endl;
    ofstream mFile(membersFile); for (const auto& m : members) mFile << m.toFileString() << endl;
    ofstream iFile(issuedBooksFile); for (const auto& ib : issuedBooks) iFile << ib.toFileString() << endl;
}

void Library::loadData() {
    books.clear(); members.clear(); issuedBooks.clear();
    ifstream bFile(booksFile); string line;
    if (bFile.is_open()) { while (getline(bFile, line)) if (!line.empty()) books.push_back(Book::fromFileString(line)); }
    ifstream mFile(membersFile);
    if (mFile.is_open()) { while (getline(mFile, line)) if (!line.empty()) members.push_back(Member::fromFileString(line)); }
    ifstream iFile(issuedBooksFile);
    if (iFile.is_open()) { while (getline(iFile, line)) if (!line.empty()) issuedBooks.push_back(IssuedBook::fromFileString(line)); }
}
