#include "SKUAnalytics.h"
#include "CSVHandler.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>

void SKUAnalytics::addSKU(const SKU& sku) {
    skuDatabase[sku.getSkuId()] = sku;
    categoryMap[sku.getCategory()].push_back(sku.getSkuId());
}

bool SKUAnalytics::removeSKU(const std::string& skuId) {
    auto it = skuDatabase.find(skuId);
    if (it != skuDatabase.end()) {
        std::string category = it->second.getCategory();
        auto& categorySKUs = categoryMap[category];
        categorySKUs.erase(
            std::remove(categorySKUs.begin(), categorySKUs.end(), skuId),
            categorySKUs.end()
        );
        
        skuDatabase.erase(it);
        return true;
    }
    return false;
}

SKU* SKUAnalytics::getSKU(const std::string& skuId) {
    auto it = skuDatabase.find(skuId);
    return (it != skuDatabase.end()) ? &it->second : nullptr;
}

const SKU* SKUAnalytics::getSKU(const std::string& skuId) const {
    auto it = skuDatabase.find(skuId);
    return (it != skuDatabase.end()) ? &it->second : nullptr;
}

std::vector<std::pair<std::string, double>> SKUAnalytics::findTopPerformers(int topN) const {
    if (topN < 0) {
        throw std::invalid_argument("topN cannot be negative");
    }
    
    std::vector<std::pair<std::string, double>> performances;
    performances.reserve(skuDatabase.size());
    
    for (const auto& pair : skuDatabase) {
        double roas = pair.second.calculateTotalROAS();
        performances.emplace_back(pair.first, roas);
    }
    
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
    const auto& salesHistory = sku.getSalesHistory();
    if (salesHistory.empty()) return 0.0;
    
    double totalUnits = 0.0;
    for (const auto& sale : salesHistory) {
        totalUnits += sale.getUnitsSold();
    }
    
    return totalUnits / 4.0;
}

const std::vector<std::string>& SKUAnalytics::getSKUIdsByCategory(const std::string& category) const {
    static const std::vector<std::string> empty;
    auto it = categoryMap.find(category);
    return (it != categoryMap.end()) ? it->second : empty;
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
    std::cout << "\n" << std::string(120, '=') << std::endl;
    std::cout << "ALL SKUs INVENTORY (" << skuDatabase.size() << " ITEMS)" << std::endl;
    std::cout << std::string(120, '=') << std::endl;
    
   
    std::cout << std::left 
              << std::setw(18) << "SKU ID" 
              << std::setw(30) << "PRODUCT NAME" 
              << std::setw(18) << "CATEGORY" 
              << std::setw(12) << "PRICE" 
              << std::setw(10) << "ROAS" 
              << std::setw(12) << "INVENTORY" 
              << std::setw(15) << "STATUS" 
              << std::endl;
    
    std::cout << std::string(120, '-') << std::endl;
    
    for (const auto& pair : skuDatabase) {
        const SKU& sku = pair.second;
        double roas = sku.calculateTotalROAS();
        
        std::string status;
        if (roas == 0.0) {
            status = "NO SALES";
        } else if (roas >= 5.0) {
            status = "HIGH ROAS";
        } else if (roas >= 3.0) {
            status = "GOOD ROAS";
        } else if (roas >= 1.0) {
            status = "LOW ROAS";
        } else {
            status = "POOR ROAS";
        }
        
        double salesVelocity = calculateSalesVelocity(sku);
        if (salesVelocity > 0 && sku.getInventory() / salesVelocity < 2.0) {
            status += " | RISK";
        }
        
        std::cout << std::left 
                  << std::setw(18) << sku.getSkuId().substr(0, 17)
                  << std::setw(30) << sku.getName().substr(0, 29)
                  << std::setw(18) << sku.getCategory().substr(0, 17)
                  << "$" << std::setw(11) << std::fixed << std::setprecision(2) << sku.getPrice()
                  << std::setw(10) << std::fixed << std::setprecision(2) << roas
                  << std::setw(12) << sku.getInventory()
                  << std::setw(15) << status
                  << std::endl;
    }
    
    std::cout << std::string(120, '=') << std::endl;
    
    int highROAS = 0, goodROAS = 0, lowROAS = 0, poorROAS = 0, noSales = 0;
    for (const auto& pair : skuDatabase) {
        double roas = pair.second.calculateTotalROAS();
        if (roas == 0.0) noSales++;
        else if (roas >= 5.0) highROAS++;
        else if (roas >= 3.0) goodROAS++;
        else if (roas >= 1.0) lowROAS++;
        else poorROAS++;
    }
    
    std::cout << "SUMMARY: " << highROAS << " High ROAS | " << goodROAS << " Good ROAS | " 
              << lowROAS << " Low ROAS | " << poorROAS << " Poor ROAS | " << noSales << " No Sales Data" << std::endl;
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

bool SKUAnalytics::loadFromCSV(const std::string& filename) {
    try {
        auto data = CSVHandler::readCSV(filename);
        if (data.empty()) return false;
        
        skuDatabase.clear();
        categoryMap.clear();
        
        size_t startRow = (data[0][0] == "SKU_ID" || data[0][0] == "sku_id") ? 1 : 0;
        
        for (size_t i = startRow; i < data.size(); ++i) {
            const auto& row = data[i];
            if (row.size() >= 6) {
                std::string id = row[0];
                std::string name = row[1];
                std::string category = row[2];
                double price = std::stod(row[3]);
                double cost = std::stod(row[4]);
                int inventory = std::stoi(row[5]);
                
                SKU sku(id, name, category, price, cost, inventory);
                addSKU(sku);
            }
        }
        
        std::string salesFilename = "sales_" + filename;
        std::ifstream salesFile(salesFilename);
        if (salesFile.good()) {
            salesFile.close();
            auto salesData = CSVHandler::readCSV(salesFilename);
            for (size_t i = (salesData[0][0] == "SKU_ID" ? 1 : 0); i < salesData.size(); ++i) {
                const auto& row = salesData[i];
                if (row.size() >= 7) {  // Fixed: should be 7 columns
                    std::string skuId = row[0];
                    Date date(std::stoi(row[1]), std::stoi(row[2]), std::stoi(row[3]));
                    double revenue = std::stod(row[4]);
                    double adSpend = std::stod(row[5]);
                    int units = std::stoi(row[6]);
                    
                    SKU* sku = getSKU(skuId);
                    if (sku) {
                        sku->addSalesData(SalesData(date, revenue, adSpend, units));
                    }
                }
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading CSV: " << e.what() << std::endl;
        return false;
    }
}

bool SKUAnalytics::saveToCSV(const std::string& filename) const {
    try {
        std::vector<std::vector<std::string>> data;
        
        data.push_back({"SKU_ID", "NAME", "CATEGORY", "PRICE", "COST", "INVENTORY"});
        
        for (const auto& pair : skuDatabase) {
            const SKU& sku = pair.second;
            data.push_back({
                sku.getSkuId(),
                sku.getName(),
                sku.getCategory(),
                std::to_string(sku.getPrice()),
                std::to_string(sku.getCost()),
                std::to_string(sku.getInventory())
            });
        }
        
        return CSVHandler::writeCSV(filename, data);
    } catch (const std::exception& e) {
        std::cerr << "Error saving to CSV: " << e.what() << std::endl;
        return false;
    }
}

bool SKUAnalytics::exportSalesDataToCSV(const std::string& filename) const {
    try {
        std::vector<std::vector<std::string>> data;
        
        data.push_back({"SKU_ID", "YEAR", "MONTH", "DAY", "REVENUE", "AD_SPEND", "UNITS_SOLD"});
        
        for (const auto& pair : skuDatabase) {
            const SKU& sku = pair.second;
            for (const auto& sale : sku.getSalesHistory()) {
                data.push_back({
                    sku.getSkuId(),
                    std::to_string(sale.getDate().getYear()),    // Use getter
                    std::to_string(sale.getDate().getMonth()),   // Use getter
                    std::to_string(sale.getDate().getDay()),     // Use getter
                    std::to_string(sale.getRevenue()),
                    std::to_string(sale.getAdSpend()),
                    std::to_string(sale.getUnitsSold())
                });
            }
        }
        
        return CSVHandler::writeCSV(filename, data);
    } catch (const std::exception& e) {
        std::cerr << "Error exporting sales data: " << e.what() << std::endl;
        return false;
    }
}

bool SKUAnalytics::updateSKU(const std::string& skuId, const SKU& updatedSKU) {
    auto it = skuDatabase.find(skuId);
    if (it != skuDatabase.end()) {
        std::string oldCategory = it->second.getCategory();
        auto& oldCategorySKUs = categoryMap[oldCategory];
        oldCategorySKUs.erase(
            std::remove(oldCategorySKUs.begin(), oldCategorySKUs.end(), skuId),
            oldCategorySKUs.end()
        );
        
        if (oldCategorySKUs.empty()) {
            categoryMap.erase(oldCategory);
        }
        
        skuDatabase[skuId] = updatedSKU;
        categoryMap[updatedSKU.getCategory()].push_back(skuId);
        
        return true;
    }
    return false;
}