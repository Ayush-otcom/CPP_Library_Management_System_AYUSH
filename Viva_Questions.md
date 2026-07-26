# Viva Questions for Library Management System

1. **What is the main objective of this project?**
   To manage books, members, and transactions in a library efficiently using C++.
2. **Why did you use C++ instead of C?**
   C++ provides Object-Oriented Programming (OOP) features like classes, encapsulation, and STL containers, which make managing complex entities like books and members easier.
3. **What is Encapsulation, and how is it used here?**
   Encapsulation is data hiding. The attributes in `Book` and `Member` classes are private and only accessed via public getters and setters.
4. **Why did you use `std::vector`?**
   Vectors are dynamic arrays that resize automatically. They provide fast O(1) access and are ideal for storing our lists of books and members.
5. **How does File Handling work in your project?**
   I used `<fstream>`. `ifstream` reads data from `.txt` files into vectors on startup. `ofstream` writes data from vectors back to the files when exiting.
6. **How do you calculate fines?**
   I use the `<chrono>` library to parse dates, calculate the difference in days between the Due Date and Return Date. If it's positive, the fine is Rs 5 per day.
7. **What is a struct, and why did you use it for IssuedBook?**
   A struct is similar to a class but its members are public by default. I used it for `IssuedBook` because it's a simple data container holding transaction details.
8. **What is a namespace?**
   A namespace defines a scope. I used a `Utility` namespace to group independent helper functions (like date math and string manipulation) so they don't pollute the global scope.
9. **How did you implement search?**
   I used a linear search with string partial matching (by converting both strings to lowercase) so users don't need exact matches.
10. **Why use `#ifndef`, `#define`, and `#endif`?**
    These are header guards. They prevent multiple inclusions of the same header file during compilation, which would cause redefinition errors.
11. **What is `std::chrono`?**
    It's a C++ library for date and time utilities.
12. **How do you handle case-insensitive search?**
    I wrote a utility function to transform both the search query and the target string to lowercase using `std::transform` before comparing.
13. **Why did you use `std::find_if`?**
    `find_if` allows searching through a container using a custom condition (a lambda function). It's cleaner and more expressive than a raw `for` loop.
14. **What is a constructor?**
    A special member function automatically called when an object is created. I used parameterized constructors to initialize books/members easily.
15. **What is a default constructor?**
    A constructor with no arguments. It initializes the object with default, empty, or zero values.
16. **Why do your getters have `const` at the end?**
    It promises that calling the getter will not modify the object's state. It allows reading data from `const` objects.
17. **What is a lambda function?**
    An anonymous inline function. Used heavily in `std::find_if` and `std::sort` for custom conditions.
18. **How does `std::sort` work?**
    It sorts a range. By default, it uses `<`. I passed lambda functions to sort books by specific fields (e.g., price, title).
19. **What happens if the data files don't exist?**
    `ifstream` simply fails to open, so the system starts with empty lists. `ofstream` will create the files automatically on saving.
20. **Why use `std::ostringstream` for saving data?**
    It allows building a single formatted string (with delimiters like `|`) from multiple variables easily before writing to a file.
21. **How do you parse data back from the file?**
    I read line by line, then use `std::stringstream` with `getline(ss, token, '|')` to split the string by the pipe delimiter.
22. **What does `cin.ignore()` do?**
    It clears characters from the input buffer. Necessary before `getline` when a previous `cin >>` leaves a newline character in the buffer.
23. **What is `std::regex`?**
    Regular expressions library. Used to validate email and phone formats.
24. **How do you prevent a member from borrowing too many books?**
    Before issuing, I check `booksBorrowed.size() < getBorrowLimit()`.
25. **Can a member be deleted if they owe a fine?**
    No, the logic strictly checks if `fineAmount > 0` and denies deletion if true.
26. **What is exception handling?**
    Using `try-catch` blocks to catch runtime errors (like invalid input that causes `cin` to fail) and gracefully prevent the program from crashing.
27. **Why not use a database like MySQL?**
    To keep the project lightweight and focus heavily on file handling and data structures as per the academic syllabus.
28. **What is the time complexity of searching a book by ID?**
    O(N) where N is the number of books, as it's a linear search over an unordered vector.
29. **Could you improve search performance?**
    Yes, by using `std::unordered_map<string, Book>` (hash map) to search by ID in O(1) time.
30. **What does `std::fixed` and `std::setprecision` do?**
    Formats floating-point outputs (like price and fine) to exactly a specific number of decimal places (e.g., 2).
*(Questions 31-50 would follow similarly covering memory leaks, OOP principles deep-dives, C++17 specific features, error states in I/O, etc.)*
