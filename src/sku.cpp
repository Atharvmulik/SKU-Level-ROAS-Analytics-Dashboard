#include "SKU.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

SKU::SKU(const std::string& id, const std::string& n, const std::string& cat, 
         double p, double c, int inventory)
    : skuId(id), name(n), category(cat), price(p), cost(c), currentInventory(inventory) {
    validateValues(p, c, inventory);
}

std::string SKU::getSkuId() const { return skuId; }
std::string SKU::getName() const { return name; }
std::string SKU::getCategory() const { return category; }
double SKU::getPrice() const { return price; }
double SKU::getCost() const { return cost; }
int SKU::getInventory() const { return currentInventory; }
const std::vector<SalesData>& SKU::getSalesHistory() const { return salesHistory; }

void SKU::setInventory(int inventory) {
    if (inventory < 0) throw std::invalid_argument("Inventory cannot be negative");
    currentInventory = inventory;
}

void SKU::setPrice(double newPrice) {
    if (newPrice < 0) throw std::invalid_argument("Price cannot be negative");
    if (newPrice < cost) throw std::invalid_argument("Price cannot be less than cost");
    price = newPrice;
}

void SKU::setCost(double newCost) {
    if (newCost < 0) throw std::invalid_argument("Cost cannot be negative");
    if (newCost > price) throw std::invalid_argument("Cost cannot exceed price");
    cost = newCost;
}

void SKU::addSalesData(const SalesData& data) {
    salesHistory.push_back(data);
}

double SKU::calculateROAS(const Date& start, const Date& end) const {
    double totalRevenue = 0.0;
    double totalAdSpend = 0.0;
    
    for (const auto& sale : salesHistory) {
        if (!(sale.getDate() < start) && !(end < sale.getDate())) {
            totalRevenue += sale.getRevenue();
            totalAdSpend += sale.getAdSpend();
        }
    }
    
    
    return (totalAdSpend > std::numeric_limits<double>::epsilon()) ? 
           totalRevenue / totalAdSpend : 0.0;
}

double SKU::calculateTotalROAS() const {
    double totalRevenue = getTotalRevenue();
    double totalAdSpend = getTotalAdSpend();
    
    return (totalAdSpend > std::numeric_limits<double>::epsilon()) ? 
           totalRevenue / totalAdSpend : 0.0;
}

double SKU::getTotalRevenue() const {
    double total = 0.0;
    for (const auto& sale : salesHistory) {
        total += sale.getRevenue();
    }
    return total;
}

double SKU::getTotalAdSpend() const {
    double total = 0.0;
    for (const auto& sale : salesHistory) {
        total += sale.getAdSpend();
    }
    return total;
}

double SKU::getProfitMargin() const {
    if (price == 0.0) return 0.0;
    return (price - cost) / price;
}

void SKU::displayInfo() const {
    std::cout << "SKU: " << skuId << " | " << name 
              << " | Category: " << category 
              << " | Price: $" << std::fixed << std::setprecision(2) << price
              << " | Cost: $" << cost
              << " | ROAS: " << std::fixed << std::setprecision(2) 
              << calculateTotalROAS() 
              << " | Inventory: " << currentInventory 
              << " | Margin: " << std::fixed << std::setprecision(1) 
              << (getProfitMargin() * 100) << "%" << std::endl;
}