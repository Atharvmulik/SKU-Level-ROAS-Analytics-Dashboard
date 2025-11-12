#ifndef SALESDATA_H
#define SALESDATA_H

#include "Date.h"

struct SalesData {
    Date date;
    double revenue;
    double adSpend;
    int unitsSold;
    
    SalesData(Date d = Date(), double rev = 0.0, double ad = 0.0, int units = 0) 
        : date(d), revenue(rev), adSpend(ad), unitsSold(units) {}
    
    // Getters
    Date getDate() const { return date; }
    double getRevenue() const { return revenue; }
    double getAdSpend() const { return adSpend; }
    int getUnitsSold() const { return unitsSold; }
};

#endif