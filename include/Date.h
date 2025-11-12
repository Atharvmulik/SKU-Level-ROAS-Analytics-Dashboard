#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>

class Date {
private:
    int year, month, day;
    
    bool isValidDate(int y, int m, int d) const {
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > 31) return false;
        // Add more validation for specific month days
        return true;
    }

public:
    Date(int y = 2000, int m = 1, int d = 1) : year(y), month(m), day(d) {
        if (!isValidDate(y, m, d)) {
            throw std::invalid_argument("Invalid date");
        }
    }
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }
    
    // Getters for serialization
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
};

inline std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
    return os;
}

#endif