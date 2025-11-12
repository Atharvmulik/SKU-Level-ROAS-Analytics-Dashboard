#include <iostream>
#include "Dashboard.h"

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "   SKU-LEVEL ROAS ANALYTICS SYSTEM" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    Dashboard dashboard;
    
    std::cout << "Attempting to load existing data..." << std::endl;
    
    dashboard.run();
    
    return 0;
}