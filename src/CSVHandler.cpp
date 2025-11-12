#include "CSVHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::vector<std::string>> CSVHandler::readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        data.push_back(split(line, ','));
    }
    
    return data;
}

bool CSVHandler::writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& row : data) {
        file << join(row, ",") << "\n";
    }
    
    file.close();
    return true;
}

std::vector<std::string> CSVHandler::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string CSVHandler::join(const std::vector<std::string>& elements, const std::string& delimiter) {
    std::ostringstream os;
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i > 0) os << delimiter;
        os << elements[i];
    }
    return os.str();
}