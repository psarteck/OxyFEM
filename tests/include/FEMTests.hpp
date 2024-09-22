

#ifndef FEMTests_H
#define FEMTests_H

#include "Types.hpp"
#include <unordered_map>



namespace FEMTests {


struct ConfigData {
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::vector<std::string> keys; 

};

ConfigData readConfigFile(const std::string& filename);

void updateConfigFile(const std::string& filename, const std::string& key, const std::vector<std::string>& newValues);

void printConfigData(const FEMTests::ConfigData& config);

std::string GetCurrentWorkingDirectory();

bool CompareFiles(const std::string& resultFile, const std::string& referenceFile, Real tolerance);

}

#endif