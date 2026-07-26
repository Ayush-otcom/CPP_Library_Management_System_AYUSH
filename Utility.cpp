#include "Utility.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <regex>
#include <iostream>

using namespace std;
using namespace std::chrono;

namespace Utility {

    // Convert string to lowercase
    string toLowerCase(const string& str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                  [](unsigned char c){ return tolower(c); });
        return lowerStr;
    }

    // Partial match for case-insensitive search
    bool partialMatch(const string& text, const string& query) {
        string lowerText = toLowerCase(text);
        string lowerQuery = toLowerCase(query);
        return lowerText.find(lowerQuery) != string::npos;
    }

    // Convert string (YYYY-MM-DD) to time_point
    system_clock::time_point parseDate(const string& dateStr) {
        tm tm = {};
        stringstream ss(dateStr);
        ss >> get_time(&tm, "%Y-%m-%d");
        return system_clock::from_time_t(mktime(&tm));
    }

    // Convert time_point to string (YYYY-MM-DD)
    string formatDate(const system_clock::time_point& tp) {
        time_t t = system_clock::to_time_t(tp);
        tm tm = *localtime(&t);
        stringstream ss;
        ss << put_time(&tm, "%Y-%m-%d");
        return ss.str();
    }

    // Get Current Date in YYYY-MM-DD format
    string getCurrentDate() {
        return formatDate(system_clock::now());
    }

    // Calculate Due Date by adding days to issue date
    string calculateDueDate(const string& issueDateStr, int daysToAdd) {
        auto issueDateTp = parseDate(issueDateStr);
        auto dueDateTp = issueDateTp + hours(24 * daysToAdd);
        return formatDate(dueDateTp);
    }

    // Calculate Late Days
    int calculateLateDays(const string& dueDateStr, const string& returnDateStr) {
        auto dueDateTp = parseDate(dueDateStr);
        auto returnDateTp = parseDate(returnDateStr);
        
        if (returnDateTp <= dueDateTp) {
            return 0; // Not late
        }
        
        auto duration = duration_cast<hours>(returnDateTp - dueDateTp);
        return duration.count() / 24;
    }

    // Calculate Fine (Rs 5 per day after 7 days, though late days already accounts for due date)
    double calculateFine(int lateDays) {
        if (lateDays > 0) {
            return lateDays * 5.0; // Rs 5 per late day
        }
        return 0.0;
    }

    // Email validation using regex
    bool isValidEmail(const string& email) {
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(email, pattern);
    }

    // Phone validation (exactly 10 digits)
    bool isValidPhone(const string& phone) {
        const regex pattern("^[0-9]{10}$");
        return regex_match(phone, pattern);
    }
}
