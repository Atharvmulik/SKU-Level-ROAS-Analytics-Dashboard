#include <iostream>
#include "Dashboard.h"

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "   SKU-LEVEL ROAS ANALYTICS SYSTEM" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    Dashboard dashboard;
    
    // Try to load existing data on startup
    std::cout << "Attempting to load existing data..." << std::endl;
    // This would call dashboard.loadFromCSV() if you add it to public interface
    
    dashboard.run();
    
    return 0;
}