#ifndef UTILITY_H
#define UTILITY_H

#include <string>

using namespace std;

namespace Utility {
    // String Manipulations
    string toLowerCase(const string& str);
    bool partialMatch(const string& text, const string& query);

    // Date & Time Handling using <chrono>
    string getCurrentDate();
    string calculateDueDate(const string& issueDateStr, int daysToAdd = 7);
    int calculateLateDays(const string& dueDateStr, const string& returnDateStr);
    
    // Fine calculation
    double calculateFine(int lateDays);

    // Input Validation
    bool isValidEmail(const string& email);
    bool isValidPhone(const string& phone);
}

#endif // UTILITY_H
