/*---------------------------------------------------------------------------*\

 ██████╗ ██╗  ██╗██╗   ██╗     ███████╗███╗   ███╗
██╔═══██╗╚██╗██╔╝╚██╗ ██╔╝     ██╔════╝████╗ ████║
██║   ██║ ╚███╔╝  ╚████╔╝█████╗█████╗  ██╔████╔██║
██║   ██║ ██╔██╗   ╚██╔╝ ╚════╝██╔══╝  ██║╚██╔╝██║
╚██████╔╝██╔╝ ██╗   ██║        ██║     ██║ ╚═╝ ██║
 ╚═════╝ ╚═╝  ╚═╝   ╚═╝        ╚═╝     ╚═╝     ╚═╝
 * 
 * Copyright (C) 2024 by Matthieu PETIT
\*---------------------------------------------------------------------------*/
#include "FEMUtilities.hpp"

namespace FEMUtilities {

    Eigen::MatrixXd mat2Eigen(const std::vector<std::vector<double> >& vecOfVec) {
        if (vecOfVec.empty() || vecOfVec[0].empty()) {
            std::cerr << "Error : Vector of vectors is empty." << std::endl;
            return Eigen::MatrixXd();
        }

        int rows = static_cast<int>(vecOfVec.size());
        int cols = static_cast<int>(vecOfVec[0].size());

        for (const auto& row : vecOfVec) {
            if (static_cast<int>(row.size()) != cols) {
                std::cerr << "Error : Vector is irregular." << std::endl;
                return Eigen::MatrixXd();
            }
        }

        Eigen::Map<const Eigen::MatrixXd> eigenMap(vecOfVec[0].data(), rows, cols);

        return eigenMap;
    }

    Eigen::VectorXd vec2Eigen(const std::vector<double>& vec) {
        int size = vec.size();
        if(size == 0){
            std::cerr << "Error : Vector is empty." << std::endl;
            return Eigen::VectorXd();
        }

        Eigen::VectorXd eigenVec(size);

        for (int i = 0; i < size; ++i) {
            eigenVec(i) = vec[i];
        }

        return eigenVec;
    }

    template <typename T>
    void printMat(std::vector<std::vector<T> > mat, std::string name){
        cout << "\n" << name << " : " << endl;
        for(auto line : mat){
            for(auto col : line){
                cout << col << " ";
            }
            cout << endl;
        }
        cout << "\n";
    }

    template <typename T>
    void printVec(std::vector<T> vec, std::string name){
        cout << "\n" << name << endl;
        for(auto i : vec){
            cout << i << " ";
        }
        cout << "\n";
    }


    void saveResults(Eigen::VectorXd vec, std::string filename){

        std::ofstream file(filename);

        if (file.is_open()) {

            for (int i = 0; i < vec.size(); ++i) {
                file << vec(i) << "\n";
            }

            file.close();
            std::cout << "Vector has been saved inside : " << filename << std::endl;
        } else {
            std::cerr << "Error : Impossible to open the file " << filename << std::endl;
            abort();
        }
    }

    void saveResults(Eigen::VectorXd& vec, std::string filename){

        std::ofstream file(filename);

        if (file.is_open()) {

            for (int i = 0; i < vec.size(); ++i) {
                file << vec[i] << "\n";
            }

            file.close();
            std::cout << "Vector has been saved inside : " << filename << std::endl << std::endl;
        } else {
            std::cerr << "Error : Impossible to open the file " << filename << std::endl;
            abort();
        }
    }

    template <typename T>
    void saveResults(std::vector<T>& vec, std::string filename){

        std::ofstream file(filename);

        if (file.is_open()) {

            for (int i = 0; i < vec.size(); ++i) {
                file << vec[i] << "\n";
            }

            file.close();
            std::cout << "Vector has been saved inside : " << filename << std::endl << std::endl;
        } else {
            std::cerr << "Error : Impossible to open the file " << filename << std::endl;
            abort();
        }
    }

    template <typename T>
    void saveResults(std::vector<T>& vec, std::vector<Node>& nodes, std::string filename){

        std::ofstream file(filename);

        if (file.is_open()) {

            for (int i = 0; i < vec.size(); ++i) {
                file << nodes[i].getX() << " " << nodes[i].getY() << " " << vec[i] << "\n";
            }

            file.close();
            std::cout << "Vector has been saved inside : " << filename << std::endl << std::endl;
        } else {
            std::cerr << "Error : Impossible to open the file " << filename << std::endl;
            abort();
        }
    }


    
    std::map<std::string, std::string> readParameterFile(const std::string& nameFile) {
        std::ifstream file(nameFile);
        std::map<std::string, std::string> config;
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Error : Impossible to open the file " << nameFile << std::endl;
            return config;
        }

        while (std::getline(file, line)) {
            std::istringstream streamLigne(line);
            std::string cle, value;

            if (std::getline(streamLigne, cle, '=') && std::getline(streamLigne, value)) {
                config[cle] = value;
            }
        }

        file.close();
        return config;
    }

    std::string getValue(const std::map<std::string, std::string>& config, const std::string& key) {
        auto it = config.find(key);
        if (it != config.end()) {
            return it->second; 
        } else {
            return "";
        }
    }

    void changeValue(std::map<std::string, std::string>& config, const std::string& key, const std::string& newValue) {
        config[key] = newValue; 
    }


    void writeParameterFile(const std::string& fileName, const std::map<std::string, std::string>& config) {
        std::ofstream fichier(fileName);
        if (!fichier.is_open()) {
            std::cerr << "Error : Impossible to open the file to write : " << fileName << std::endl;
            return;
        }

        for (const auto& pair : config) {
            fichier << pair.first << "=" << pair.second << std::endl;
        }

        fichier.close();
    }

    void showProgress(float percentage) {
        int width = 50;
        int pos = width * percentage;
        

        std::cout << "\033[32m" << "[";
        for (int i = 0; i < width; ++i) {
            if (i < pos) std::cout << "=";
            else std::cout << " ";
        }
        std::cout << "] " << int(percentage * 100) << " %\r" << "\033[0m";
        std::cout.flush();
    }

    
    template void printMat<int>(std::vector<VectorInt > mat, std::string name);
    template void printMat<double>(std::vector<std::vector<double> > mat, std::string name);
    template void printMat<float>(std::vector<std::vector<float> > mat, std::string name);
    template void printMat<std::string>(MatrixStr mat, std::string name);

    template void printVec<int>(VectorInt vec, std::string name);
    template void printVec<double>(std::vector<double> vec, std::string name);
    template void printVec<float>(std::vector<float> vec, std::string name);
    template void printVec<std::string>(VectorStr vec, std::string name);
    
    template void saveResults<int>(VectorInt& vec, std::string filename);
    template void saveResults<double>(std::vector<double>& vec, std::string filename);
    template void saveResults<float>(std::vector<float>& vec, std::string filename);
    template void saveResults<std::string>(VectorStr& vec, std::string filename);

    template void saveResults<int>(VectorInt& vec, std::vector<Node>& nodes, std::string filename);
    template void saveResults<double>(std::vector<double>& vec, std::vector<Node>& nodes, std::string filename);
    template void saveResults<float>(std::vector<float>& vec, std::vector<Node>& nodes, std::string filename);
    template void saveResults<std::string>(VectorStr& vec, std::vector<Node>& nodes, std::string filename);

}