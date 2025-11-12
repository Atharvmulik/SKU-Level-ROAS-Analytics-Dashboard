#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <vector>
#include <string>
#include <map>

class CSVHandler {
public:
    static std::vector<std::vector<std::string>> readCSV(const std::string& filename);
    static bool writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static std::string join(const std::vector<std::string>& elements, const std::string& delimiter);
};

#endif