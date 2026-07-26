# Architecture & Diagrams

## 1. Flowchart of Issue Book Process
1. Start -> User Selects "Issue Book"
2. Input Member ID -> Search Member
   - If not found -> Show Error -> End
3. Input Book ID -> Search Book
   - If not found -> Show Error -> End
4. Check Member Fine > 0?
   - If Yes -> Show Error "Pay Fine First" -> End
5. Check Member Borrow Limit Reached?
   - If Yes -> Show Error "Limit Reached" -> End
6. Check Book Available Copies > 0?
   - If No -> Show Error "No copies available" -> End
7. Check if Member already has this book?
   - If Yes -> Show Error "Duplicate Issue" -> End
8. Decrease Book Copies by 1.
9. Add Book ID to Member's Borrowed List.
10. Generate Issue Date and Due Date (Issue + 7).
11. Create IssuedBook Record -> Save to List.
12. Display Success.
13. End.

## 2. UML Class Diagram Description

### `Book` Class
- **-** (private) `bookID`, `isbn`, `title`, `availableCopies`, etc.
- **+** (public) `getBookID()`, `issueCopy()`, `returnCopy()`, `toFileString()`, `fromFileString()`

### `Member` Class
- **-** (private) `memberID`, `name`, `booksBorrowed`, `fineAmount`, etc.
- **+** (public) `borrowBook()`, `returnBook()`, `payFine()`, `getBorrowLimit()`, `toFileString()`, `fromFileString()`

### `Library` Class
- **-** (private) `vector<Book>`, `vector<Member>`, `vector<IssuedBook>`
- **-** (private) `findBookByID()`, `findMemberByID()`
- **+** (public) `addBook()`, `registerMember()`, `issueBook()`, `returnBook()`, `saveData()`, `loadData()`

*(Note: Draw this using a UML tool for your actual presentation.)*

## 3. Future Improvements
- **Database Integration:** Move from `.txt` to SQLite or PostgreSQL for better reliability and ACID compliance.
- **GUI:** Use ImGui or Qt for a professional visual interface instead of the console.
- **Multithreading:** Make the saving process asynchronous so the UI doesn't freeze during a huge data dump.
- **Authentication:** Add user roles (Admin vs Standard User). Standard users can only view books; Admins can edit.
