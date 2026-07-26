# Library Management System (C++)

## Project Introduction
This is a comprehensive, production-grade Library Management System implemented in C++17. The system is designed for managing books, library members, and the process of issuing/returning books. It features automated fine calculations, robust file handling for persistent data storage, and uses advanced Object-Oriented Programming (OOP) and Standard Template Library (STL) concepts.

## Objectives
- To build a menu-driven C++ application.
- To demonstrate practical use of OOP paradigms like Encapsulation, Abstraction, and Data Hiding.
- To use STL containers (`vector`, `string`, etc.) efficiently for data management.
- To handle dates and times properly using the `<chrono>` library.
- To implement persistent storage using C++ file streams (`<fstream>`).

## Features
- **Book Management:** Add, Update, Delete, Search, and Display books.
- **Member Management:** Register, Update, Delete, and Display members.
- **Issue/Return Logic:** Real-time tracking of book availability, member borrow limits, and duplicate issues.
- **Fine Calculation:** Automated calculation of fines (Rs 5/day after 7 days) using date logic.
- **Search System:** Case-insensitive partial matching for Books by Title, Author, Category, ID, or ISBN.
- **Statistics & Sorting:** View library statistics and sort books by title, author, price, or publication year.
- **Persistent Data:** Automatic saving and loading of data on startup/exit.

## Technologies Used
- C++17
- Standard Template Library (STL)
- `<chrono>` API for time handling
- File I/O (`<fstream>`)

## OOP Concepts Used
1. **Encapsulation:** Attributes of `Book` and `Member` are private, accessed via getters/setters.
2. **Abstraction:** Core logic (date calculations, parsing strings) is abstracted into a `Utility` namespace.
3. **Modularity:** System is divided into clean headers (`.h`) and implementations (`.cpp`).

## STL Used
- `std::vector`: Used as the primary dynamic array to store Books, Members, and IssuedBook records because it provides O(1) random access and is cache-friendly for continuous memory reading.
- `std::string`: Extensively used for text manipulation.
- `std::find`, `std::find_if`: Used from `<algorithm>` for searching through collections efficiently.
- `std::sort`: Used for sorting book records based on custom lambda comparators.

## How to Compile & Run

**For Ayush's Mac (Direct Copy-Paste):**
If you are running this locally on the specific MacBook setup, copy and paste this single line to compile and run:
```bash
cd "/Users/ayush/Desktop/cipher project/LibraryManagementSystem" && g++ -std=c++17 main.cpp Book.cpp Member.cpp Library.cpp Utility.cpp -o library_system && ./library_system
```

**For General Users (Mac / Linux):**
First, open your terminal and navigate to the downloaded project folder, then run:
```bash
g++ -std=c++17 main.cpp Book.cpp Member.cpp Library.cpp Utility.cpp -o library_system
./library_system
```

**For General Users (Windows):**
First, open Command Prompt or PowerShell and navigate to the downloaded project folder, then run:
```cmd
g++ -std=c++17 main.cpp Book.cpp Member.cpp Library.cpp Utility.cpp -o library_system
library_system.exe
```

## Screenshots Placeholder
*(Add your screenshots here demonstrating the menu, adding a book, and calculating a fine)*

## Future Scope
- Transition from text files to a relational database (e.g., SQLite).
- Implement a Graphical User Interface (GUI) using Qt or wxWidgets.
- Add user authentication (Admin vs User login).
- Implement barcode integration for scanning ISBNs directly.
