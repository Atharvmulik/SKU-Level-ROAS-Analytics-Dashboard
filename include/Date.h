#ifndef DATE_H
#define DATE_H

#include <iostream>

struct Date {
    int year, month, day;
    Date(int y = 2000, int m = 1, int d = 1) : year(y), month(m), day(d) {}
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

// Add this function outside the struct
inline std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.year << "-" << date.month << "-" << date.day;
    return os;
}

#endif