# SKU-Level-ROAS-Analytics-Dashboard
A comprehensive C++ application for analyzing Return on Ad Spend (ROAS) at the individual Stock Keeping Unit (SKU) level. This dashboard provides granular insights into product performance, inventory risks, and marketing efficiency for e-commerce and retail businesses.

📊 Features
1]SKU-Level ROAS Analysis: Calculate Return on Ad Spend for individual products
2]Inventory Risk Detection: Identify potential stockout risks based on sales velocity
3]Performance Analytics: Top performers identification and category-wise reporting
4]Visual Data Representation: ASCII charts for ROAS distribution and revenue share
5]Interactive Dashboard: Menu-driven console interface
6]Sample Data: Pre-loaded with 27 SKUs across 5 categories for immediate testing

🏗️ Project Structure
SKU_ROAS_Analytics/
├── include/
│   ├── Date.h              # Date structure and utilities
│   ├── SalesData.h         # Sales data point structure
│   ├── SKU.h              # SKU class definition
│   ├── SKUAnalytics.h     # Analytics engine class
│   └── Dashboard.h        # User interface class
├── src/
│   ├── main.cpp           # Program entry point
│   ├── SKU.cpp            # SKU class implementation
│   ├── SKUAnalytics.cpp   # Analytics algorithms
│   └── Dashboard.cpp      # Dashboard interface implementation
├── bin/                   # Compiled executables
├── obj/                  # Object files
└── Makefile              # Build configuration

** File Descriptions **

Date.h/cpp: Date handling utilities
SalesData.h: Sales transaction structure
SKU.h/cpp: Product representation and ROAS calculations
SKUAnalytics.h/cpp: Business logic and analytics algorithms
Dashboard.h/cpp: User interface and menu system
main.cpp: Application entry point
