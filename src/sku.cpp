#include "SKU.h"
#include <iostream>
#include <iomanip>

SKU::SKU(const std::string& id, const std::string& n, const std::string& cat, 
         double p, double c, int inventory)
    : skuId(id), name(n), category(cat), price(p), cost(c), currentInventory(inventory) {}

std::string SKU::getSkuId() const { return skuId; }
std::string SKU::getName() const { return name; }
std::string SKU::getCategory() const { return category; }
double SKU::getPrice() const { return price; }
int SKU::getInventory() const { return currentInventory; }
const std::vector<SalesData>& SKU::getSalesHistory() const { return salesHistory; }

void SKU::setInventory(int inventory) { currentInventory = inventory; }

void SKU::addSalesData(const SalesData& data) {
    salesHistory.push_back(data);
}

double SKU::calculateROAS(const Date& start, const Date& end) const {
    double totalRevenue = 0.0;
    double totalAdSpend = 0.0;
    
    for (const auto& sale : salesHistory) {
        if (!(sale.date < start) && !(end < sale.date)) {
            totalRevenue += sale.revenue;
            totalAdSpend += sale.adSpend;
        }
    }
    
    return (totalAdSpend > 0) ? totalRevenue / totalAdSpend : 0.0;
}

double SKU::calculateTotalROAS() const {
    double totalRevenue = getTotalRevenue();
    double totalAdSpend = getTotalAdSpend();
    return (totalAdSpend > 0) ? totalRevenue / totalAdSpend : 0.0;
}

double SKU::getTotalRevenue() const {
    double total = 0.0;
    for (const auto& sale : salesHistory) {
        total += sale.revenue;
    }
    return total;
}

double SKU::getTotalAdSpend() const {
    double total = 0.0;
    for (const auto& sale : salesHistory) {
        total += sale.adSpend;
    }
    return total;
}

void SKU::displayInfo() const {
    std::cout << "SKU: " << skuId << " | " << name 
              << " | Category: " << category 
              << " | Price: $" << std::fixed << std::setprecision(2) << price
              << " | ROAS: " << std::fixed << std::setprecision(2) 
              << calculateTotalROAS() 
              << " | Inventory: " << currentInventory << std::endl;
}