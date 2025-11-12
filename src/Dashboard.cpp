#include "Dashboard.h"
#include "CSVHandler.h"
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
    std::cout << "8. Update SKU" << std::endl;
    std::cout << "9. Delete SKU" << std::endl;
    std::cout << "10. Load from CSV" << std::endl;
    std::cout << "11. Save to CSV" << std::endl;
    std::cout << "12. Export Data" << std::endl;
    std::cout << "13. Overall Analytics" << std::endl;
    std::cout << "14. ROAS Distribution Chart" << std::endl;
    std::cout << "15. Category Revenue Chart" << std::endl;
    std::cout << "16. Exit" << std::endl;
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
            case 8: updateSKU(); break;
            case 9: deleteSKU(); break;
            case 10: loadFromCSV(); break;
            case 11: saveToCSV(); break;
            case 12: exportData(); break;
            case 13: 
                std::cout << "\n=== OVERALL ANALYTICS ===" << std::endl;
                std::cout << "Total SKUs: " << analytics.getSKUCount() << std::endl;
                std::cout << "Overall ROAS: " << std::fixed << std::setprecision(2) << analytics.calculateOverallROAS() << std::endl;
                std::cout << "Total Revenue: $" << std::fixed << std::setprecision(2) << getTotalRevenue() << std::endl;
                break;
            case 14: displayROASChart(); break;
            case 15: displayCategoryPieChart(); break;
            case 16: 
                std::cout << "Exiting... Thank you for using SKU ROAS Analytics!" << std::endl;
                break;
            default:
                std::cout << "Invalid option! Please try again." << std::endl;
        }
    } while (choice != 16);
}

void Dashboard::updateSKU() {
    std::string skuId;
    std::cout << "\n=== UPDATE SKU ===" << std::endl;
    std::cout << "Enter SKU ID to update: ";
    std::getline(std::cin, skuId);
    
    SKU* existingSKU = analytics.getSKU(skuId);
    if (!existingSKU) {
        std::cout << "SKU not found!" << std::endl;
        return;
    }
    
    std::cout << "Current SKU Details:" << std::endl;
    existingSKU->displayInfo();
    
    std::string name, category;
    double price, cost;
    int inventory;
    
    std::cout << "Enter new name (current: " << existingSKU->getName() << "): ";
    std::getline(std::cin, name);
    if (name.empty()) name = existingSKU->getName();
    
    std::cout << "Enter new category (current: " << existingSKU->getCategory() << "): ";
    std::getline(std::cin, category);
    if (category.empty()) category = existingSKU->getCategory();
    
    std::cout << "Enter new price (current: " << existingSKU->getPrice() << "): ";
    std::string priceStr;
    std::getline(std::cin, priceStr);
    price = priceStr.empty() ? existingSKU->getPrice() : std::stod(priceStr);
    
    std::cout << "Enter new cost (current: " << existingSKU->getCost() << "): ";
    std::string costStr;
    std::getline(std::cin, costStr);
    cost = costStr.empty() ? existingSKU->getCost() : std::stod(costStr);
    
    std::cout << "Enter new inventory (current: " << existingSKU->getInventory() << "): ";
    std::string invStr;
    std::getline(std::cin, invStr);
    inventory = invStr.empty() ? existingSKU->getInventory() : std::stoi(invStr);
    
    SKU updatedSKU(skuId, name, category, price, cost, inventory);
    
    for (const auto& sale : existingSKU->getSalesHistory()) {
        updatedSKU.addSalesData(sale);
    }
    
    if (analytics.updateSKU(skuId, updatedSKU)) {
        std::cout << "SKU updated successfully!" << std::endl;
    } else {
        std::cout << "Failed to update SKU!" << std::endl;
    }
}

void Dashboard::deleteSKU() {
    std::string skuId;
    std::cout << "\n=== DELETE SKU ===" << std::endl;
    std::cout << "Enter SKU ID to delete: ";
    std::getline(std::cin, skuId);
    
    SKU* sku = analytics.getSKU(skuId);
    if (!sku) {
        std::cout << "SKU not found!" << std::endl;
        return;
    }
    
    std::cout << "SKU Details:" << std::endl;
    sku->displayInfo();
    
    std::cout << "Are you sure you want to delete this SKU? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (confirm == 'y' || confirm == 'Y') {
        if (analytics.removeSKU(skuId)) {
            std::cout << "SKU deleted successfully!" << std::endl;
        } else {
            std::cout << "Failed to delete SKU!" << std::endl;
        }
    } else {
        std::cout << "Deletion cancelled." << std::endl;
    }
}

void Dashboard::loadFromCSV() {
    std::string filename;
    std::cout << "\n=== LOAD FROM CSV ===" << std::endl;
    std::cout << "Enter CSV filename (default: skudata.csv): ";
    std::getline(std::cin, filename);
    
    if (filename.empty()) {
        filename = "skudata.csv";
    }
    
    if (analytics.loadFromCSV(filename)) {
        std::cout << "Data loaded successfully from " << filename << std::endl;
        std::cout << "Loaded " << analytics.getSKUCount() << " SKUs" << std::endl;
    } else {
        std::cout << "Failed to load data from " << filename << std::endl;
    }
}

void Dashboard::saveToCSV() {
    std::string filename;
    std::cout << "\n=== SAVE TO CSV ===" << std::endl;
    std::cout << "Enter CSV filename (default: skudata.csv): ";
    std::getline(std::cin, filename);
    
    if (filename.empty()) {
        filename = "skudata.csv";
    }
    
    if (analytics.saveToCSV(filename)) {
        std::cout << "Data saved successfully to " << filename << std::endl;
    } else {
        std::cout << "Failed to save data to " << filename << std::endl;
    }
}

void Dashboard::exportData() {
    std::string filename;
    std::cout << "\n=== EXPORT DATA ===" << std::endl;
    std::cout << "Enter filename for sales data export (default: sales_export.csv): ";
    std::getline(std::cin, filename);
    
    if (filename.empty()) {
        filename = "sales_export.csv";
    }
    
    if (analytics.exportSalesDataToCSV(filename)) {
        std::cout << "Sales data exported successfully to " << filename << std::endl;
    } else {
        std::cout << "Failed to export sales data!" << std::endl;
    }
}

void Dashboard::addCustomSKU() {
    std::string id, name, category;
    double price, cost;
    int inventory;
    
    std::cout << "\n=== ADD CUSTOM SKU ===" << std::endl;
    std::cout << "SKU ID: ";
    std::getline(std::cin, id);
    
    // Check if SKU already exists
    if (analytics.getSKU(id)) {
        std::cout << "SKU ID already exists!" << std::endl;
        return;
    }
    
    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Category: ";
    std::getline(std::cin, category);
    
    price = getValidatedDouble("Price: $");
    cost = getValidatedDouble("Cost: $");
    inventory = getValidatedInt("Inventory: ");
    
    SKU newSKU(id, name, category, price, cost, inventory);
    analytics.addSKU(newSKU);
    
    std::cout << "SKU added successfully!" << std::endl;
    
    // Show immediate ROAS calculation
    const SKU* addedSKU = analytics.getSKU(id);
    if (addedSKU) {
        std::cout << "Current ROAS: " << std::fixed << std::setprecision(2) 
                  << addedSKU->calculateTotalROAS() << " (Add sales data to improve ROAS)" << std::endl;
    }
}