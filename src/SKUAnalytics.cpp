#include "SKUAnalytics.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void SKUAnalytics::addSKU(const SKU& sku) {
    skuDatabase[sku.getSkuId()] = sku;
    categoryMap[sku.getCategory()].push_back(sku.getSkuId());
}

bool SKUAnalytics::removeSKU(const std::string& skuId) {
    auto it = skuDatabase.find(skuId);
    if (it != skuDatabase.end()) {
        // Remove from category map
        std::string category = it->second.getCategory();
        auto& categorySKUs = categoryMap[category];
        categorySKUs.erase(
            std::remove(categorySKUs.begin(), categorySKUs.end(), skuId),
            categorySKUs.end()
        );
        
        // Remove from main database
        skuDatabase.erase(it);
        return true;
    }
    return false;
}

SKU* SKUAnalytics::getSKU(const std::string& skuId) {
    auto it = skuDatabase.find(skuId);
    return (it != skuDatabase.end()) ? &it->second : nullptr;
}

// ADD THIS CONST VERSION OF getSKU
const SKU* SKUAnalytics::getSKU(const std::string& skuId) const {
    auto it = skuDatabase.find(skuId);
    return (it != skuDatabase.end()) ? &it->second : nullptr;
}

std::vector<std::pair<std::string, double>> SKUAnalytics::findTopPerformers(int topN) const {
    std::vector<std::pair<std::string, double>> performances;
    
    for (const auto& pair : skuDatabase) {
        double roas = pair.second.calculateTotalROAS();
        performances.emplace_back(pair.first, roas);
    }
    
    // FIXED: Replace auto with explicit types in lambda
    std::sort(performances.begin(), performances.end(),
        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
            return a.second > b.second;
        });
    
    if (topN > 0 && performances.size() > static_cast<size_t>(topN)) {
        performances.resize(topN);
    }
    
    return performances;
}

std::vector<std::string> SKUAnalytics::detectStockoutRisk(double threshold) const {
    std::vector<std::string> riskSKUs;
    
    for (const auto& pair : skuDatabase) {
        const SKU& sku = pair.second;
        double salesVelocity = calculateSalesVelocity(sku);
        
        if (salesVelocity > 0) {
            double weeksOfInventory = sku.getInventory() / salesVelocity;
            if (weeksOfInventory < threshold) {
                riskSKUs.push_back(pair.first);
            }
        }
    }
    
    return riskSKUs;
}

double SKUAnalytics::calculateSalesVelocity(const SKU& sku) const {
    // Simplified: average weekly sales based on historical data
    const auto& salesHistory = sku.getSalesHistory();
    if (salesHistory.empty()) return 0.0;
    
    double totalUnits = 0.0;
    for (const auto& sale : salesHistory) {
        totalUnits += sale.unitsSold;
    }
    
    // Assuming 4 weeks of data for simplicity
    return totalUnits / 4.0;
}

std::vector<SKU> SKUAnalytics::getSKUsByCategory(const std::string& category) const {
    std::vector<SKU> result;
    auto it = categoryMap.find(category);
    if (it != categoryMap.end()) {
        for (const auto& skuId : it->second) {
            auto skuIt = skuDatabase.find(skuId);
            if (skuIt != skuDatabase.end()) {
                result.push_back(skuIt->second);
            }
        }
    }
    return result;
}

void SKUAnalytics::generateCategoryReport() const {
    std::cout << "\n=== CATEGORY PERFORMANCE REPORT ===" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    for (const auto& categoryPair : categoryMap) {
        double totalROAS = 0.0;
        int skuCount = 0;
        double totalRevenue = 0.0;
        double totalAdSpend = 0.0;
        
        for (const auto& skuId : categoryPair.second) {
            auto it = skuDatabase.find(skuId);
            if (it != skuDatabase.end()) {
                totalROAS += it->second.calculateTotalROAS();
                totalRevenue += it->second.getTotalRevenue();
                totalAdSpend += it->second.getTotalAdSpend();
                skuCount++;
            }
        }
        
        double avgROAS = (skuCount > 0) ? totalROAS / skuCount : 0.0;
        
        std::cout << "Category: " << categoryPair.first << std::endl;
        std::cout << "  Avg ROAS: " << std::fixed << std::setprecision(2) << avgROAS << std::endl;
        std::cout << "  SKU Count: " << skuCount << std::endl;
        std::cout << "  Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
        std::cout << "  Total Ad Spend: $" << std::fixed << std::setprecision(2) << totalAdSpend << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}

void SKUAnalytics::displayAllSKUs() const {
    std::cout << "\n=== ALL SKUs ===" << std::endl;
    std::cout << "Total SKUs: " << skuDatabase.size() << std::endl;
    std::cout << "----------------" << std::endl;
    
    for (const auto& pair : skuDatabase) {
        pair.second.displayInfo();
    }
}

size_t SKUAnalytics::getSKUCount() const {
    return skuDatabase.size();
}

std::vector<std::string> SKUAnalytics::getAllCategories() const {
    std::vector<std::string> categories;
    for (const auto& pair : categoryMap) {
        categories.push_back(pair.first);
    }
    return categories;
}

double SKUAnalytics::calculateOverallROAS() const {
    double totalRevenue = 0.0;
    double totalAdSpend = 0.0;
    
    for (const auto& pair : skuDatabase) {
        totalRevenue += pair.second.getTotalRevenue();
        totalAdSpend += pair.second.getTotalAdSpend();
    }
    
    return (totalAdSpend > 0) ? totalRevenue / totalAdSpend : 0.0;
}