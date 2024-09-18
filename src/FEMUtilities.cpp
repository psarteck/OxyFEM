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

        // Copier la matrice pour garantir une copie indépendante
        return eigenMap;
    }

    Eigen::VectorXd vec2Eigen(const std::vector<double>& vec) {
        // Taille du vecteur
        int size = vec.size();
        if(size == 0){
            std::cerr << "Error : Vector is empty." << std::endl;
            return Eigen::VectorXd();
        }

        // Créer un vecteur Eigen
        Eigen::VectorXd eigenVec(size);

        // Copier les valeurs du vecteur std::vector<double> vers le vecteur Eigen::VectorXd
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
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
            abort();
        }
    }

    void saveResults(std::vector<double> vec, std::string filename){

        std::ofstream file(filename);

        if (file.is_open()) {

            for (int i = 0; i < vec.size(); ++i) {
                file << vec[i] << "\n";
            }

            file.close();
            std::cout << "Vector has been saved inside : " << filename << std::endl;
        } else {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
            abort();
        }
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

    
    template void printMat<int>(std::vector<std::vector<int> > mat, std::string name);
    template void printMat<double>(std::vector<std::vector<double> > mat, std::string name);
    template void printMat<float>(std::vector<std::vector<float> > mat, std::string name);
    template void printMat<std::string>(std::vector<std::vector<std::string> > mat, std::string name);

    template void printVec<int>(std::vector<int> vec, std::string name);
    template void printVec<double>(std::vector<double> vec, std::string name);
    template void printVec<float>(std::vector<float> vec, std::string name);
    template void printVec<std::string>(std::vector<std::string> vec, std::string name);

}