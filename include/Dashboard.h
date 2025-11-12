#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "SKUAnalytics.h"
#include <vector>
#include <string>

class Dashboard {
private:
    SKUAnalytics analytics;
    std::string dataFile = "skudata.csv";

public:
    void run();
    
    // Data persistence
    bool loadFromFile(const std::string& filename = "");
    bool saveToFile(const std::string& filename = "") const;
    
private:
    void displayMenu() const;
    void displayAllSKUs() const;
    void displayTopPerformers() const;
    void displayStockoutRisk() const;
    void displayCategoryAnalysis() const;
    void addSampleData();
    void addCustomSKU();
    void addSalesDataToSKU();
    void updateSKU();
    void deleteSKU();
    void addSalesToSKU(SKU& sku, const std::vector<SalesData>& salesRecords);
    void displayROASChart() const;
    void displayCategoryPieChart() const;
    void exportData();
    double getTotalRevenue() const;
    
    // Input validation helpers
    double getValidatedDouble(const std::string& prompt, double min = 0.0) const;
    int getValidatedInt(const std::string& prompt, int min = 0) const;
    std::string getValidatedString(const std::string& prompt) const;
    
    // CSV operations
    void loadFromCSV();
    void saveToCSV();
};

#endif