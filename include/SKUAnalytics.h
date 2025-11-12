#ifndef SKUANALYTICS_H
#define SKUANALYTICS_H

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include "SKU.h"

class SKUAnalytics {
private:
    std::map<std::string, SKU> skuDatabase;
    std::map<std::string, std::vector<std::string>> categoryMap;

public:
    // SKU management
    void addSKU(const SKU& sku);
    bool removeSKU(const std::string& skuId);
    bool updateSKU(const std::string& skuId, const SKU& updatedSKU);
    
    SKU* getSKU(const std::string& skuId);
    const SKU* getSKU(const std::string& skuId) const;
    
    // Analytics methods
    std::vector<std::pair<std::string, double>> findTopPerformers(int topN = 10) const;
    std::vector<std::string> detectStockoutRisk(double threshold = 2.0) const;
    std::vector<SKU> getSKUsByCategory(const std::string& category) const;
    
    // CSV operations
    bool loadFromCSV(const std::string& filename);
    bool saveToCSV(const std::string& filename) const;
    bool exportSalesDataToCSV(const std::string& filename) const;
    
    // Reporting
    void generateCategoryReport() const;
    void displayAllSKUs() const;
    
    // Utility methods
    size_t getSKUCount() const;
    std::vector<std::string> getAllCategories() const;
    double calculateOverallROAS() const;
    
    // Optional - remove if causing issues
    const std::vector<std::string>& getSKUIdsByCategory(const std::string& category) const;
    
private:
    double calculateSalesVelocity(const SKU& sku) const;
};

#endif