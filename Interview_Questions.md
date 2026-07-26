# Technical Interview Questions based on this Project

1. **How would you scale this application for a library with millions of books?**
   *Answer Hint:* Replace `std::vector` with a database (SQL/NoSQL) and replace file I/O with database queries. Implement indexing for fast searches. Load data lazily or use pagination instead of loading millions of records into RAM.
   
2. **If multiple users are using this system simultaneously, what issues might occur?**
   *Answer Hint:* Race conditions. If two users try to borrow the last available copy at the exact same millisecond, both might succeed, causing a negative available copies count.
   
3. **How would you solve the concurrency issue?**
   *Answer Hint:* Implement thread safety using Mutexes (`std::mutex` and `std::lock_guard`) around the `issueCopy()` function, or use transaction locks in a database.
   
4. **How would you optimize the search functionality if the system is read-heavy?**
   *Answer Hint:* Introduce Hash Maps (`std::unordered_map`) for ID-based lookups (O(1)). For partial text searches, implement a Trie data structure or Inverted Index.
   
5. **How do you ensure data isn't corrupted if the program crashes during `saveData()`?**
   *Answer Hint:* Write to a temporary file first (e.g., `books_temp.txt`). Once the write is completely successful, delete the original `books.txt` and rename `books_temp.txt` to `books.txt`.

6. **Explain your memory management. Are there any memory leaks?**
   *Answer Hint:* I primarily stack-allocate STL containers (`std::vector`, `std::string`) which manage their own heap memory via RAII (Resource Acquisition Is Initialization). There are no naked `new` or `delete` calls, so memory leaks are inherently prevented.

7. **How would you implement Polymorphism in this system?**
   *Answer Hint:* Create an abstract base class `Item` with virtual functions `checkout()` and `returnItem()`. Derive `Book`, `Magazine`, and `DVD` from `Item`. The library can hold a `std::vector<std::unique_ptr<Item>>`.
