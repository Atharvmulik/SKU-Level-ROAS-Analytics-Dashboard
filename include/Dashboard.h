#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "SKUAnalytics.h"
#include <vector>

class Dashboard {
private:
    SKUAnalytics analytics;

public:
    void run();
    
private:
    void displayMenu() const;
    void displayAllSKUs() const;
    void displayTopPerformers() const;
    void displayStockoutRisk() const;
    void displayCategoryAnalysis() const;
    void addSampleData();
    void addCustomSKU();
    void addSalesDataToSKU();
    void addSalesToSKU(SKU& sku, const std::vector<SalesData>& salesRecords);
    void displayROASChart() const;
    void displayCategoryPieChart() const;
    double getTotalRevenue() const;
};

#endif