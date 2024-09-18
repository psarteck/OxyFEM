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
#include "FEMParameters.hpp"



    FEMParameters::FEMParameters(std::string fileName) : parameterFile(fileName){
        if(!getParameterValue()){
            std::cerr << "Error in the parameters" << parameterFile << std::endl;
        }
    }

    bool FEMParameters::getParameterValue() {
        std::ifstream file(parameterFile);

        if (!file.is_open()) {
            std::cerr << "Error : Impossible to open the parameter file " << parameterFile << std::endl;
            return false;
        }
        std::cout << "\033[34m" <<"---------------------------------------------------------------------------\n"
        " ██████╗ ██╗  ██╗██╗   ██╗     ███████╗███╗   ███╗\n"
        "██╔═══██╗╚██╗██╔╝╚██╗ ██╔╝     ██╔════╝████╗ ████║\n"
        "██║   ██║ ╚███╔╝  ╚████╔╝█████╗█████╗  ██╔████╔██║\n"
        "██║   ██║ ██╔██╗   ╚██╔╝ ╚════╝██╔══╝  ██║╚██╔╝██║\n"
        "╚██████╔╝██╔╝ ██╗   ██║        ██║     ██║ ╚═╝ ██║\n"
        " ╚═════╝ ╚═╝  ╚═╝   ╚═╝        ╚═╝     ╚═╝     ╚═╝\n"
        " * \n"
        " * Copyright (C) 2024 by Matthieu PETIT\n"
        "---------------------------------------------------------------------------\n" << "\033[0m" << std::endl;

        std::cout << "------ Loading parameters ------" << std::endl; 
        
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                if (key == "mesh") {
                    mesh = value;
                } else if (key == "lagrange") {
                    lagrange = value;
                } else if (key == "quadrature") {
                    quadrature = value;
                } else if (key == "DirichletLabel"){
                    std::istringstream Iss(value);
                    std::string nVal;
                    while (Iss >> nVal) {
                        dirichletLabels.push_back(nVal);
                    }
                } else if (key == "HomogeneousDirichletLabel"){
                    std::istringstream Iss(value);
                    std::string nVal;
                    while (Iss >> nVal) {
                        homogeneousDirichletLabels.push_back(nVal);
                    }
                } else if (key == "NeumannLabel"){
                    std::istringstream Iss(value);
                    std::string nVal;
                    while (Iss >> nVal) {
                        neumannLabels.push_back(nVal);
                    }
                } else if (key == "DomainLabels"){
                    std::istringstream Iss(value);
                    std::string nVal;
                    while (Iss >> nVal) {
                        domainLabels.push_back(nVal);
                    }
                }
            }
        }

        file.close();

        std::cout << "Parameters values : \nMesh : " << mesh 
                    << "\nLagrange method : " << lagrange << "\nQuadrature method : " << quadrature << "\n\nConditions :\n" 
                    << "Homogeneous Dirichlet : ";
        printLabel(homogeneousDirichletLabels);
        cout << "\nNon n homogeneous Dirichlet : ";
        printLabel(dirichletLabels);
        cout << "\nNeumann : "; 
        printLabel(neumannLabels);
        cout << std::endl;
        std::cout << "---------------------------------" << std::endl;

        return true;
    }

    void FEMParameters::printLabel(const std::vector<std::string> labels){
            for(auto label : labels){
                cout << label << " ";
            }
        }

    const std::string& FEMParameters::getMeshName() const {
        return mesh;
    }

    const std::string& FEMParameters::getLagrange() const {
        return lagrange;
    }

    const std::string& FEMParameters::getQuadrature() const {
        return quadrature;
    }

    const std::vector<std::string>& FEMParameters::getDirichletLabels() const {
        return dirichletLabels;
    }

    const std::vector<std::string>& FEMParameters::getHomogeneousDirichletLabels() const {
        return homogeneousDirichletLabels;
    }

    const std::vector<std::string>& FEMParameters::getNeumannLabels() const {
        return neumannLabels;
    }

    const std::vector<std::string>& FEMParameters::getDomainLabels() const {
        return domainLabels;
    }


