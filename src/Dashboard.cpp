#include "Dashboard.h"
#include <iostream>
#include <limits>
#include <iomanip>  
#include <string>  
#include <vector>   
#include <algorithm> 

void Dashboard::displayMenu() const {
    std::cout << "\n=== SKU-LEVEL ROAS ANALYTICS DASHBOARD ===" << std::endl;
    std::cout << "1. View All SKUs" << std::endl;
    std::cout << "2. Top Performing SKUs" << std::endl;
    std::cout << "3. Stockout Risk Analysis" << std::endl;
    std::cout << "4. Category Performance Report" << std::endl;
    std::cout << "5. Add Sample Data" << std::endl;
    std::cout << "6. Add Custom SKU" << std::endl;
    std::cout << "7. Add Sales Data to SKU" << std::endl;
    std::cout << "8. Overall Analytics" << std::endl;
    std::cout << "9. ROAS Distribution Chart" << std::endl;        // NEW OPTION
    std::cout << "10. Category Revenue Chart" << std::endl;        // NEW OPTION
    std::cout << "11. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

void Dashboard::run() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: displayAllSKUs(); break;
            case 2: displayTopPerformers(); break;
            case 3: displayStockoutRisk(); break;
            case 4: displayCategoryAnalysis(); break;
            case 5: addSampleData(); break;
            case 6: addCustomSKU(); break;
            case 7: addSalesDataToSKU(); break;
            case 8: 
                std::cout << "\n=== OVERALL ANALYTICS ===" << std::endl;
                std::cout << "Total SKUs: " << analytics.getSKUCount() << std::endl;
                std::cout << "Overall ROAS: " << analytics.calculateOverallROAS() << std::endl;
                break;
            case 9: displayROASChart(); break;                    // NEW
            case 10: displayCategoryPieChart(); break;            // NEW
            case 11: 
                std::cout << "Exiting... Thank you for using SKU ROAS Analytics!" << std::endl;
                break;
            default:
                std::cout << "Invalid option! Please try again." << std::endl;
        }
    } while (choice != 11);
}

void Dashboard::displayAllSKUs() const {
    analytics.displayAllSKUs();
}

void Dashboard::displayTopPerformers() const {
    auto topPerformers = analytics.findTopPerformers(10); // Show top 10
    
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "                           TOP 10 PERFORMING SKUs BY ROAS" << std::endl;
    std::cout << std::string(100, '=') << std::endl;
    
    // Table Header
    std::cout << std::left 
              << std::setw(4) << "RANK" 
              << std::setw(18) << "SKU ID" 
              << std::setw(35) << "PRODUCT NAME" 
              << std::setw(15) << "CATEGORY" 
              << std::setw(10) << "ROAS" 
              << std::setw(12) << "INVENTORY" 
              << std::setw(15) << "PERFORMANCE" 
              << std::endl;
    
    std::cout << std::string(100, '-') << std::endl;
    
    if (topPerformers.empty()) {
        std::cout << "No SKUs available! Please add sample data first." << std::endl;
        return;
    }
    
    // Table Rows
    for (size_t i = 0; i < topPerformers.size(); ++i) {
        const SKU* sku = analytics.getSKU(topPerformers[i].first);
        if (sku) {
            double roas = topPerformers[i].second;
            std::string performance;
            
            if (roas >= 5.0) performance = "EXCELLENT ★";
            else if (roas >= 3.0) performance = "GOOD ✓";
            else if (roas >= 1.0) performance = "AVERAGE ●";
            else performance = "POOR ✗";
            
            std::cout << std::left 
                      << std::setw(4) << i + 1
                      << std::setw(18) << sku->getSkuId().substr(0, 17)
                      << std::setw(35) << sku->getName().substr(0, 34)
                      << std::setw(15) << sku->getCategory().substr(0, 14)
                      << std::setw(10) << std::fixed << std::setprecision(2) << roas
                      << std::setw(12) << sku->getInventory()
                      << std::setw(15) << performance
                      << std::endl;
        }
    }
    
    std::cout << std::string(100, '=') << std::endl;
}

void Dashboard::displayStockoutRisk() const {
    auto riskSKUs = analytics.detectStockoutRisk(2.0); // 2 weeks threshold
    
    std::cout << "\n" << std::string(90, '=') << std::endl;
    std::cout << "                      SKUs WITH STOCKOUT RISK (Less than 2 weeks inventory)" << std::endl;
    std::cout << std::string(90, '=') << std::endl;
    
    // Table Header
    std::cout << std::left 
              << std::setw(18) << "SKU ID" 
              << std::setw(30) << "PRODUCT NAME" 
              << std::setw(15) << "CATEGORY" 
              << std::setw(10) << "ROAS" 
              << std::setw(12) << "INVENTORY" 
              << std::setw(15) << "RISK LEVEL" 
              << std::endl;
    
    std::cout << std::string(90, '-') << std::endl;
    
    if (riskSKUs.empty()) {
        std::cout << "🎉 No SKUs at risk! Excellent inventory management." << std::endl;
    } else {
        for (const auto& skuId : riskSKUs) {
            const SKU* sku = analytics.getSKU(skuId);
            if (sku) {
                double roas = sku->calculateTotalROAS();
                std::string riskLevel = "HIGH ⚠️";
                
                std::cout << std::left 
                          << std::setw(18) << sku->getSkuId().substr(0, 17)
                          << std::setw(30) << sku->getName().substr(0, 29)
                          << std::setw(15) << sku->getCategory().substr(0, 14)
                          << std::setw(10) << std::fixed << std::setprecision(2) << roas
                          << std::setw(12) << sku->getInventory()
                          << std::setw(15) << riskLevel
                          << std::endl;
            }
        }
        std::cout << "💡 Recommendation: Consider restocking these items to avoid lost sales." << std::endl;
    }
    
    std::cout << std::string(90, '=') << std::endl;
}

void Dashboard::displayCategoryAnalysis() const {
    analytics.generateCategoryReport();
}

void Dashboard::addSampleData() {
    // Clear any existing data first
    // Note: You might want to add a clear() method to SKUAnalytics
    
    // ===== ELECTRONICS =====
    SKU sku1("IP14-128-BLK", "iPhone 14 128GB Black", "Electronics", 999.99, 700.00, 150);
    SKU sku2("IP14-256-WHT", "iPhone 14 256GB White", "Electronics", 1149.99, 800.00, 75);
    SKU sku3("MBP-14-M1", "MacBook Pro 14 M1", "Electronics", 1999.99, 1500.00, 50);
    SKU sku4("SAMS-S22-128", "Samsung Galaxy S22 128GB", "Electronics", 799.99, 550.00, 200);
    SKU sku5("AIRPODS-PRO", "AirPods Pro 2nd Gen", "Electronics", 249.99, 150.00, 300);
    SKU sku6("IPAD-AIR-64", "iPad Air 64GB", "Electronics", 599.99, 400.00, 120);
    SKU sku7("SWH-1000XM4", "Sony WH-1000XM4 Headphones", "Electronics", 349.99, 220.00, 180);
    SKU sku8("GALAXY-TAB", "Samsung Galaxy Tab S8", "Electronics", 699.99, 480.00, 90);

    // ===== APPAREL =====
    SKU sku9("TSHIRT-BLUE-M", "Blue Cotton T-Shirt Medium", "Apparel", 29.99, 12.00, 500);
    SKU sku10("JEANS-DARK-32", "Dark Wash Jeans Size 32", "Apparel", 79.99, 35.00, 250);
    SKU sku11("HOODIE-BLACK-L", "Black Hoodie Large", "Apparel", 59.99, 25.00, 180);
    SKU sku12("SNEAKER-WHITE-9", "White Running Shoes Size 9", "Apparel", 89.99, 45.00, 150);
    SKU sku13("JACKET-DENIM-M", "Denim Jacket Medium", "Apparel", 99.99, 50.00, 100);
    SKU sku14("DRESS-RED-S", "Red Summer Dress Small", "Apparel", 49.99, 22.00, 200);

    // ===== HOME & KITCHEN =====
    SKU sku15("BLENDER-PRO", "Professional Blender", "Home & Kitchen", 129.99, 70.00, 80);
    SKU sku16("AIR-FRYER-XL", "XL Air Fryer", "Home & Kitchen", 149.99, 85.00, 120);
    SKU sku17("COFFEE-MAKER", "Drip Coffee Maker", "Home & Kitchen", 79.99, 45.00, 200);
    SKU sku18("COOKWARE-SET", "10-Piece Cookware Set", "Home & Kitchen", 199.99, 120.00, 60);
    SKU sku19("TOASTER-4SLICE", "4-Slice Toaster", "Home & Kitchen", 49.99, 25.00, 150);

    // ===== BEAUTY & HEALTH =====
    SKU sku20("FACE-CREAM", "Anti-Aging Face Cream", "Beauty & Health", 39.99, 15.00, 300);
    SKU sku21("HAIR-DRYER", "Professional Hair Dryer", "Beauty & Health", 89.99, 50.00, 100);
    SKU sku22("VITAMIN-C", "Vitamin C Supplements 100ct", "Beauty & Health", 24.99, 8.00, 400);
    SKU sku23("PERFUME-50ML", "Designer Perfume 50ml", "Beauty & Health", 79.99, 30.00, 150);

    // ===== SPORTS & OUTDOORS =====
    SKU sku24("YOGA-MAT", "Premium Yoga Mat", "Sports & Outdoors", 29.99, 12.00, 200);
    SKU sku25("DUMBBELL-10LB", "10lb Dumbbell Pair", "Sports & Outdoors", 39.99, 20.00, 180);
    SKU sku26("BACKPACK-30L", "30L Hiking Backpack", "Sports & Outdoors", 89.99, 45.00, 120);
    SKU sku27("TENT-4P", "4-Person Camping Tent", "Sports & Outdoors", 199.99, 110.00, 50);

    // ===== Add Sales Data for Each SKU =====
    
    // High ROAS Products (ROAS > 5)
    addSalesToSKU(sku1, {
        {Date(2024, 1, 1), 19999.80, 3000.00, 20},
        {Date(2024, 1, 2), 14999.85, 2500.00, 15},
        {Date(2024, 1, 3), 9999.90, 1800.00, 10}
    });
    
    // Medium ROAS Products (ROAS 2-5)
    addSalesToSKU(sku2, {
        {Date(2024, 1, 1), 11499.90, 2800.00, 10},
        {Date(2024, 1, 2), 6899.94, 1800.00, 6}
    });
    
    // Low ROAS Products (ROAS < 2)
    addSalesToSKU(sku3, {
        {Date(2024, 1, 1), 39999.80, 25000.00, 20},
        {Date(2024, 1, 2), 19999.90, 15000.00, 10}
    });
    
    // High Volume, Low Margin
    addSalesToSKU(sku9, {
        {Date(2024, 1, 1), 2999.00, 800.00, 100},
        {Date(2024, 1, 2), 2399.20, 650.00, 80},
        {Date(2024, 1, 3), 1799.40, 500.00, 60}
    });
    
    // Seasonal Product (High sales in specific period)
    addSalesToSKU(sku14, {
        {Date(2024, 5, 1), 4999.00, 1200.00, 100},
        {Date(2024, 5, 2), 3999.20, 1000.00, 80},
        {Date(2024, 6, 1), 2999.40, 800.00, 60}
    });
    
    // Consistent Performer
    addSalesToSKU(sku20, {
        {Date(2024, 1, 1), 1999.50, 400.00, 50},
        {Date(2024, 1, 8), 1599.60, 350.00, 40},
        {Date(2024, 1, 15), 1199.70, 300.00, 30},
        {Date(2024, 1, 22), 799.80, 200.00, 20}
    });
    
    // Add more sales data for other SKUs...
    addSalesToSKU(sku4, {{Date(2024, 1, 1), 7999.90, 2000.00, 10}});
    addSalesToSKU(sku5, {{Date(2024, 1, 1), 4999.80, 1200.00, 20}});
    addSalesToSKU(sku6, {{Date(2024, 1, 1), 5999.90, 1500.00, 10}});
    addSalesToSKU(sku10, {{Date(2024, 1, 1), 3999.50, 1000.00, 50}});
    addSalesToSKU(sku11, {{Date(2024, 1, 1), 2999.50, 800.00, 50}});
    addSalesToSKU(sku12, {{Date(2024, 1, 1), 4499.50, 1200.00, 50}});
    addSalesToSKU(sku15, {{Date(2024, 1, 1), 2599.80, 800.00, 20}});
    addSalesToSKU(sku16, {{Date(2024, 1, 1), 2999.80, 900.00, 20}});
    addSalesToSKU(sku21, {{Date(2024, 1, 1), 1799.80, 500.00, 20}});
    addSalesToSKU(sku24, {{Date(2024, 1, 1), 1499.50, 400.00, 50}});

    // Add all SKUs to analytics
    analytics.addSKU(sku1);
    analytics.addSKU(sku2);
    analytics.addSKU(sku3);
    analytics.addSKU(sku4);
    analytics.addSKU(sku5);
    analytics.addSKU(sku6);
    analytics.addSKU(sku7);
    analytics.addSKU(sku8);
    analytics.addSKU(sku9);
    analytics.addSKU(sku10);
    analytics.addSKU(sku11);
    analytics.addSKU(sku12);
    analytics.addSKU(sku13);
    analytics.addSKU(sku14);
    analytics.addSKU(sku15);
    analytics.addSKU(sku16);
    analytics.addSKU(sku17);
    analytics.addSKU(sku18);
    analytics.addSKU(sku19);
    analytics.addSKU(sku20);
    analytics.addSKU(sku21);
    analytics.addSKU(sku22);
    analytics.addSKU(sku23);
    analytics.addSKU(sku24);
    analytics.addSKU(sku25);
    analytics.addSKU(sku26);
    analytics.addSKU(sku27);

    std::cout << "Large sample dataset added successfully!" << std::endl;
    std::cout << "Added 27 SKUs across 5 categories with sales data." << std::endl;
    std::cout << "Categories: Electronics, Apparel, Home & Kitchen, Beauty & Health, Sports & Outdoors" << std::endl;
}

// Helper function to add multiple sales records
void Dashboard::addSalesToSKU(SKU& sku, const std::vector<SalesData>& salesRecords) {
    for (const auto& sale : salesRecords) {
        sku.addSalesData(sale);
    }
}

void Dashboard::addCustomSKU() {
    std::string id, name, category;
    double price, cost;
    int inventory;
    
    std::cout << "\n=== ADD CUSTOM SKU ===" << std::endl;
    std::cout << "SKU ID: ";
    std::getline(std::cin, id);
    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Category: ";
    std::getline(std::cin, category);
    std::cout << "Price: ";
    std::cin >> price;
    std::cout << "Cost: ";
    std::cin >> cost;
    std::cout << "Inventory: ";
    std::cin >> inventory;
    
    SKU newSKU(id, name, category, price, cost, inventory);
    analytics.addSKU(newSKU);
    
    std::cout << "SKU added successfully!" << std::endl;
}

void Dashboard::addSalesDataToSKU() {
    std::string skuId;
    int year, month, day, units;
    double revenue, adSpend;
    
    std::cout << "\n=== ADD SALES DATA ===" << std::endl;
    std::cout << "SKU ID: ";
    std::getline(std::cin, skuId);
    
    // Note: This can use non-const version since it's a non-const method
    SKU* sku = analytics.getSKU(skuId);
    if (!sku) {
        std::cout << "SKU not found!" << std::endl;
        return;
    }
    
    std::cout << "Date (YYYY MM DD): ";
    std::cin >> year >> month >> day;
    std::cout << "Revenue: ";
    std::cin >> revenue;
    std::cout << "Ad Spend: ";
    std::cin >> adSpend;
    std::cout << "Units Sold: ";
    std::cin >> units;
    
    SalesData newData(Date(year, month, day), revenue, adSpend, units);
    sku->addSalesData(newData);
    
    std::cout << "Sales data added successfully!" << std::endl;
}
void Dashboard::displayROASChart() const {
    auto topPerformers = analytics.findTopPerformers(10);
    
    if (topPerformers.empty()) {
        std::cout << "No data available! Please add sample data first (Option 5)." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "                            TOP PERFORMING SKUs BY ROAS" << std::endl;
    std::cout << std::string(100, '=') << std::endl;
    
    // Table Header
    std::cout << std::left 
              << std::setw(5) << "RANK" 
              << std::setw(28) << "PRODUCT NAME" 
              << std::setw(16) << "CATEGORY" 
              << std::setw(8) << "ROAS" 
              << std::setw(12) << "INVENTORY" 
              << std::setw(25) << "PERFORMANCE LEVEL" 
              << std::endl;
    
    std::cout << std::string(100, '-') << std::endl;
    
    int rank = 1;
    for (const auto& performer : topPerformers) {
        const SKU* sku = analytics.getSKU(performer.first);
        if (sku) {
            std::string performance;
            std::string indicator;
            
            if (performer.second >= 6.0) {
                performance = "EXCELLENT";
                indicator = "[#######]";
            } else if (performer.second >= 4.0) {
                performance = "GOOD     ";
                indicator = "[#####  ]";
            } else if (performer.second >= 2.0) {
                performance = "AVERAGE  ";
                indicator = "[###    ]";
            } else {
                performance = "NEEDS WORK";
                indicator = "[#      ]";
            }
            
            std::cout << std::left 
                      << std::setw(5) << rank
                      << std::setw(28) << sku->getName().substr(0, 27)
                      << std::setw(16) << sku->getCategory().substr(0, 15)
                      << std::setw(8) << std::fixed << std::setprecision(2) << performer.second
                      << std::setw(12) << sku->getInventory()
                      << std::setw(25) << (performance + " " + indicator)
                      << std::endl;
            rank++;
        }
    }
    
    std::cout << std::string(100, '=') << std::endl;
    
    // Performance legend
    std::cout << "PERFORMANCE SCALE:" << std::endl;
    std::cout << "EXCELLENT [#######] (ROAS >= 6.0) - Outstanding performance" << std::endl;
    std::cout << "GOOD      [#####  ] (ROAS >= 4.0) - Strong performance" << std::endl;
    std::cout << "AVERAGE   [###    ] (ROAS >= 2.0) - Acceptable performance" << std::endl;
    std::cout << "NEEDS WORK[#      ] (ROAS < 2.0)  - Requires optimization" << std::endl;
}

void Dashboard::displayCategoryPieChart() const {
    auto categories = analytics.getAllCategories();
    
    if (categories.empty()) {
        std::cout << "No data available! Please add sample data first (Option 5)." << std::endl;
        return;
    }
    
    std::map<std::string, double> categoryRevenue;
    double totalRevenue = 0.0;
    int totalSKUs = 0;
    
    // Calculate total revenue and SKU count per category
    for (const auto& category : categories) {
        auto skus = analytics.getSKUsByCategory(category);
        double categoryTotal = 0.0;
        for (const auto& sku : skus) {
            categoryTotal += sku.getTotalRevenue();
        }
        categoryRevenue[category] = categoryTotal;
        totalRevenue += categoryTotal;
        totalSKUs += skus.size();
    }
    
    std::cout << "\n" << std::string(90, '=') << std::endl;
    std::cout << "                        CATEGORY PERFORMANCE REPORT" << std::endl;
    std::cout << std::string(90, '=') << std::endl;
    
    // Table Header
    std::cout << std::left 
              << std::setw(5) << "RANK"
              << std::setw(20) << "CATEGORY" 
              << std::setw(8) << "SKUs" 
              << std::setw(10) << "SHARE" 
              << std::setw(25) << "MARKET SHARE" 
              << std::setw(18) << "REVENUE" 
              << std::endl;
    
    std::cout << std::string(90, '-') << std::endl;
    
    // Sort categories by revenue (descending) - FIXED: using explicit types
    std::vector<std::pair<std::string, double>> sortedCategories(categoryRevenue.begin(), categoryRevenue.end());
    std::sort(sortedCategories.begin(), sortedCategories.end(),
        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
            return a.second > b.second;
        });
    
    int rank = 1;
    for (const auto& pair : sortedCategories) {
        auto skus = analytics.getSKUsByCategory(pair.first);
        int skuCount = skus.size();
        int percentage = static_cast<int>((pair.second / totalRevenue) * 100);
        
        // Create market share bar
        std::string marketShareBar;
        int barLength = static_cast<int>((percentage / 100.0) * 20);
        for (int i = 0; i < 20; i++) {
            if (i < barLength) marketShareBar += "|";
            else marketShareBar += " ";
        }
        marketShareBar = "[" + marketShareBar + "]";
        
        // Business impact rating
        std::string impact;
        if (percentage >= 30) impact = "HIGH IMPACT";
        else if (percentage >= 15) impact = "MEDIUM IMPACT";
        else impact = "LOW IMPACT";
        
        std::cout << std::left 
                  << std::setw(5) << rank
                  << std::setw(20) << pair.first 
                  << std::setw(8) << skuCount
                  << std::setw(10) << (std::to_string(percentage) + "%")
                  << std::setw(25) << marketShareBar
                  << "$" << std::setw(17) << std::fixed << std::setprecision(2) << pair.second
                  << std::endl;
        rank++;
    }
    
    std::cout << std::string(90, '-') << std::endl;
    
    // Business insights
    std::cout << "BUSINESS INSIGHTS:" << std::endl;
    std::cout << "• Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
    std::cout << "• Total SKUs: " << totalSKUs << " across " << categories.size() << " categories" << std::endl;
    
    if (!sortedCategories.empty()) {
        std::cout << "• Top Category: " << sortedCategories[0].first << " ("
                  << static_cast<int>((sortedCategories[0].second / totalRevenue) * 100) 
                  << "% of total revenue)" << std::endl;
    }
}

double Dashboard::getTotalRevenue() const {
    double total = 0.0;
    auto categories = analytics.getAllCategories();
    for (const auto& category : categories) {
        auto skus = analytics.getSKUsByCategory(category);
        for (const auto& sku : skus) {
            total += sku.getTotalRevenue();
        }
    }
    return total;

}

