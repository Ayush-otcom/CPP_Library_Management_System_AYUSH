# Time Complexity Analysis

Let **B** be the number of Books.
Let **M** be the number of Members.
Let **I** be the number of Issued Records.

## 1. Book Management
- **Add Book:** O(B) due to checking for Duplicate IDs/ISBNs across the existing vector.
- **Update Book:** O(B) for finding the book by ID via linear search.
- **Delete Book:** O(B) to find the book + O(B) to erase it from the vector (elements shift).
- **Display Books:** O(B).

## 2. Member Management
- **Register Member:** O(M) for checking duplicate IDs.
- **Update Member:** O(M) for finding the member by ID.
- **Delete Member:** O(M) to find and O(M) to erase.

## 3. Issue and Return
- **Issue Book:** O(M) + O(B) to find the member and book. Appending to `issuedBooks` is O(1) amortized.
- **Return Book:** O(I) to find the active issued record. Updating records is O(1). 

## 4. Search
- **Search by Title/Author (Partial String Match):** O(B * L), where L is the length of the string.
- **Search by ID/ISBN:** O(B * L). 

## 5. File I/O
- **Load Data:** O(B + M + I). Parses every line exactly once.
- **Save Data:** O(B + M + I). Writes every record exactly once.

## 6. Sorting
- **Sort Books (using std::sort):** O(B log B).

## Potential Optimization
If `std::unordered_map` was used instead of `std::vector` for storing data by ID:
- Finding, Updating, Deleting (by ID) would reduce from O(N) to **O(1)**.
