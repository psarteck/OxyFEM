#include <cstddef>
#include <fstream>
#include <string>
#include <cstdlib>  
#include <cmath>
#include <unistd.h>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>


#include "FEMTests.hpp"
#include "Types.hpp"

namespace FEMTests {



FEMTests::ConfigData readConfigFile(const std::string& filename) {
    FEMTests::ConfigData config;
    std::ifstream file(filename);
    
    if (!file) {
        std::cerr << "Error : Impossible to open the file : " << filename << std::endl;
        return config;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            std::istringstream iss(value);
            std::vector<std::string> values;
            std::string val;

            while (iss >> val) {
                values.push_back(val);
            }

            config.data[key].insert(config.data[key].end(), values.begin(), values.end());
            config.keys.push_back(key); 

        }
    }

    file.close();
    return config;
}

void updateConfigFile(const std::string& filename, const std::string& key, const std::vector<std::string>& newValues) {
    ConfigData config = readConfigFile(filename);
    
    if (config.data.find(key) != config.data.end()) {
        config.data[key] = newValues; 
    } else {
        std::cerr << "Key not found : " << key << std::endl;
        return;
    }

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error : Impossible to open the file for writing : " << filename << std::endl;
        return;
    }

    for (const auto& key : config.keys) {
        file << key << "=";
        for (const auto& val : config.data[key]) {
            file << val << " ";
        }
        file << std::endl;
    }

    file.close();
}

void printConfigData(const ConfigData& config) {
    for (const auto& pair : config.data) {
        std::cout << pair.first << " = ";
        for (const auto& val : pair.second) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}


std::string GetCurrentWorkingDirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        return std::string(cwd);
    } else {
        return "Erreur : Impossible d'obtenir le répertoire de travail actuel.";
    }
}


bool CompareFiles(const std::string& resultFile, const std::string& referenceFile, Real tolerance) {
    
    std::ifstream resultStream(resultFile);
    std::ifstream referenceStream(referenceFile);
    
    if (!resultStream.is_open()) {
        std::cerr << "Error: Unable to open results file " << resultFile << std::endl;
        return false;
    }

    if (!referenceStream.is_open()) {
        std::cerr << "Error: Unable to open reference file " << referenceFile << std::endl;
        return false;
    }

    Real resultValue;
    Real referenceValue;
    
    while (resultStream >> resultValue && referenceStream >> referenceValue) {
        if ((std::fabs((resultValue - referenceValue) / referenceValue)) > tolerance) {
            std::cerr << "Error : Different values found, relative error : " 
                      <<  (std::fabs((resultValue - referenceValue) / referenceValue))
                      << std::endl
                      << "Results = " << resultValue << ", "
                      << "References = " << referenceValue << std::endl;
            return false;
        }
    }
    
    if ((resultStream >> resultValue) || (referenceStream >> referenceValue)) {
        std::cerr << "Error : Files have different number of lines." << std::endl;
        return false;
    }

    return true;
}

VectorReal loadSolution(const std::string& resultFile){
    std::ifstream resultStream(resultFile);
    if (!resultStream.is_open()) {
        std::cerr << "Error: Unable to open results file " << resultFile << std::endl;
        return {-1};
    }
    VectorReal sol;
    Real resultValue;
    while (resultStream >> resultValue ) {
        sol.push_back(resultValue);
    }
    return sol;
}


VectorReal exactDiffusion(const std::vector<Node>& nodes){
    VectorReal uex;
    for(auto node : nodes){
        uex.push_back(std::cos(M_PI * node.getX()) * std::cos(M_PI * node.getY()));
    }
    return uex;
}

VectorReal exactSinSin(const std::vector<Node>& nodes){
    VectorReal uex;
    for(auto node : nodes){
        uex.push_back(std::sin(M_PI * node.getX()) * std::sin(M_PI * node.getY()));
    }
    return uex;
}

bool relativeError(const VectorReal& u, const VectorReal& uex, const Real eps){
    if(u.size() != uex.size()){
        return false;
    }
    Real error = 0.0;
    for(size_t i = 0 ; i < u.size() ; i++){
        if (std::abs(u[i]) > std::numeric_limits<Real>::epsilon()) {
            error += std::abs((u[i] - uex[i]) / uex[i]);
        }
    }
    error = error / uex.size();
    if(error > eps) return false;
    else return true;
}


}