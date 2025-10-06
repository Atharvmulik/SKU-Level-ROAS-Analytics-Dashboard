#ifndef SKUANALYTICS_H
#define SKUANALYTICS_H

#include <map>
#include <vector>
#include <string>
#include <utility> // for std::pair
#include "SKU.h"

class SKUAnalytics {
private:
    std::map<std::string, SKU> skuDatabase;
    std::map<std::string, std::vector<std::string>> categoryMap;

public:
    // SKU management
    void addSKU(const SKU& sku);
    bool removeSKU(const std::string& skuId);
    
    // CHANGED: Added const version of getSKU
    SKU* getSKU(const std::string& skuId);
    const SKU* getSKU(const std::string& skuId) const;  // Add this line
    
    // Analytics methods
    std::vector<std::pair<std::string, double>> findTopPerformers(int topN = 10) const;
    std::vector<std::string> detectStockoutRisk(double threshold = 0.3) const;
    std::vector<SKU> getSKUsByCategory(const std::string& category) const;
    
    // Reporting
    void generateCategoryReport() const;
    void displayAllSKUs() const;
    
    // Utility methods
    size_t getSKUCount() const;
    std::vector<std::string> getAllCategories() const;
    double calculateOverallROAS() const;
    
private:
    double calculateSalesVelocity(const SKU& sku) const;
};

#endif