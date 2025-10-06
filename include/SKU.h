#ifndef SKU_H
#define SKU_H

#include <string>
#include <vector>
#include "SalesData.h"

class SKU {
private:
    std::string skuId;
    std::string name;
    std::string category;
    double price;
    double cost;
    int currentInventory;
    std::vector<SalesData> salesHistory;

public:
    SKU(const std::string& id = "", const std::string& n = "", const std::string& cat = "", 
        double p = 0.0, double c = 0.0, int inventory = 0);
    
    // Getters
    std::string getSkuId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getInventory() const;
    const std::vector<SalesData>& getSalesHistory() const;
    
    // Setters
    void setInventory(int inventory);
    
    // Business logic methods
    void addSalesData(const SalesData& data);
    double calculateROAS(const Date& start, const Date& end) const;
    double calculateTotalROAS() const;
    void displayInfo() const;
    
    // Utility methods
    double getTotalRevenue() const;
    double getTotalAdSpend() const;
};

#endif