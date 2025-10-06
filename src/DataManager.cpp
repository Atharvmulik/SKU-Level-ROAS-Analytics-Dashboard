// class Dashboard {
// private:
//     SKUAnalytics analytics;

// public:
//     void displayMenu() {
//         std::cout << "\n=== SKU-LEVEL ROAS ANALYTICS DASHBOARD ===" << std::endl;
//         std::cout << "1. View All SKUs" << std::endl;
//         std::cout << "2. Top Performing SKUs" << std::endl;
//         std::cout << "3. Stockout Risk Analysis" << std::endl;
//         std::cout << "4. Category Performance Report" << std::endl;
//         std::cout << "5. Add Sample Data" << std::endl;
//         std::cout << "6. Exit" << std::endl;
//         std::cout << "Choose an option: ";
//     }
    
//     void run() {
//         int choice;
//         do {
//             displayMenu();
//             std::cin >> choice;
            
//             switch (choice) {
//                 case 1:
//                     displayAllSKUs();
//                     break;
//                 case 2:
//                     displayTopPerformers();
//                     break;
//                 case 3:
//                     displayStockoutRisk();
//                     break;
//                 case 4:
//                     analytics.generateCategoryReport();
//                     break;
//                 case 5:
//                     addSampleData();
//                     break;
//                 case 6:
//                     std::cout << "Exiting..." << std::endl;
//                     break;
//                 default:
//                     std::cout << "Invalid option!" << std::endl;
//             }
//         } while (choice != 6);
//     }
    
//     void displayAllSKUs() {
//         std::cout << "\n=== ALL SKUs ===" << std::endl;
//         // This would iterate through all SKUs in actual implementation
//         std::cout << "Displaying all SKU functionality..." << std::endl;
//     }
    
//     void displayTopPerformers() {
//         auto topPerformers = analytics.findTopPerformers(5);
        
//         std::cout << "\n=== TOP 5 PERFORMING SKUs ===" << std::endl;
//         for (size_t i = 0; i < topPerformers.size(); ++i) {
//             std::cout << i + 1 << ". SKU: " << topPerformers[i].first 
//                       << " | ROAS: " << std::fixed << std::setprecision(2) 
//                       << topPerformers[i].second << std::endl;
//         }
//     }
    
//     void displayStockoutRisk() {
//         auto riskSKUs = analytics.detectStockoutRisk();
        
//         std::cout << "\n=== SKUs WITH STOCKOUT RISK ===" << std::endl;
//         if (riskSKUs.empty()) {
//             std::cout << "No SKUs at risk!" << std::endl;
//         } else {
//             for (const auto& skuId : riskSKUs) {
//                 std::cout << "Risk: " << skuId << std::endl;
//             }
//         }
//     }
    
//     void addSampleData() {
//         // Add sample SKUs with sales data
//         SKU sku1("IP14-128-BLK", "iPhone 14 128GB Black", "Electronics", 999.99, 700.00, 150);
//         SKU sku2("IP14-256-WHT", "iPhone 14 256GB White", "Electronics", 1149.99, 800.00, 75);
//         SKU sku3("MBP-14-M1", "MacBook Pro 14 M1", "Electronics", 1999.99, 1500.00, 50);
        
//         // Add sales data
//         sku1.addSalesData(SalesData(Date(2024, 1, 1), 5000.0, 1000.0, 5));
//         sku1.addSalesData(SalesData(Date(2024, 1, 2), 6000.0, 1200.0, 6));
        
//         sku2.addSalesData(SalesData(Date(2024, 1, 1), 3000.0, 800.0, 3));
//         sku2.addSalesData(SalesData(Date(2024, 1, 2), 4000.0, 1000.0, 4));
        
//         sku3.addSalesData(SalesData(Date(2024, 1, 1), 8000.0, 2000.0, 4));
//         sku3.addSalesData(SalesData(Date(2024, 1, 2), 10000.0, 2500.0, 5));
        
//         analytics.addSKU(sku1);
//         analytics.addSKU(sku2);
//         analytics.addSKU(sku3);
        
//         std::cout << "Sample data added successfully!" << std::endl;
//     }
// };