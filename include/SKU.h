#ifndef SKU_H
#define SKU_H

#include <string>
#include <vector>
#include <stdexcept>
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

    void validateValues(double p, double c, int inv) const {
        if (p < 0) throw std::invalid_argument("Price cannot be negative");
        if (c < 0) throw std::invalid_argument("Cost cannot be negative");
        if (inv < 0) throw std::invalid_argument("Inventory cannot be negative");
        if (c > p) throw std::invalid_argument("Cost cannot exceed price");
    }

public:
    SKU(const std::string& id = "", const std::string& n = "", const std::string& cat = "", 
        double p = 0.0, double c = 0.0, int inventory = 0);
    
    // Rule of five
    SKU(const SKU& other) = default;
    SKU& operator=(const SKU& other) = default;
    SKU(SKU&& other) = default;
    SKU& operator=(SKU&& other) = default;
    ~SKU() = default;
    
    // Getters
    std::string getSkuId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    double getCost() const;  // Added getter for cost
    int getInventory() const;
    const std::vector<SalesData>& getSalesHistory() const;
    
    // Setters with validation
    void setInventory(int inventory);
    void setPrice(double newPrice);
    void setCost(double newCost);
    
    // Business logic methods
    void addSalesData(const SalesData& data);
    double calculateROAS(const Date& start, const Date& end) const;
    double calculateTotalROAS() const;
    void displayInfo() const;
    
    // Utility methods
    double getTotalRevenue() const;
    double getTotalAdSpend() const;
    double getProfitMargin() const;  // Added profit margin calculation
};

#endif