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



    FEMParameters::FEMParameters(std::string fileName) : parameterFile(fileName) {
        if(!getParameterValue()){
            std::cerr << "Error in the parameters" << parameterFile << std::endl;
        }
    }


    FEMParameters::FEMParameters(int argc, char *argv[]) {

        std::string defaultParam = "/Users/djo/Dev/OxyFEM/parameters.txt";
        std::string defaultSaveFile = "/Users/djo/Dev/OxyFEM/results/simu1.txt";
        std::string defaultMeshPath = "/Users/djo/Dev/OxyFEM/Meshs/";

        if (argc == 4){
            parameterFile = argv[1];
            savingFile = argv[2];
            meshPath = argv[3];
        } else if (argc == 3) {
            parameterFile = argv[1];
            savingFile = argv[2];
            meshPath = defaultMeshPath;
        } else if (argc == 2) {
            parameterFile = argv[1];
            savingFile = defaultSaveFile;
            meshPath = defaultMeshPath;
        } else if (argc == 1) {
            parameterFile = defaultParam;
            savingFile = defaultSaveFile;
            meshPath = defaultMeshPath;
        } else {
            std::cerr << "Too much arguments. Needed 2." << std::endl;
        }
        
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

    void FEMParameters::printLabel(const VectorStr labels){
            for(auto label : labels){
                cout << label << " ";
            }
        }

    const std::string& FEMParameters::getMeshName() const {
        return mesh;
    }
    
    const std::string& FEMParameters::getMeshPath() const {
        return meshPath;
    }

    const std::string& FEMParameters::getSavingFile() const {
        return savingFile;
    }

    const std::string& FEMParameters::getLagrange() const {
        return lagrange;
    }

    const std::string& FEMParameters::getQuadrature() const {
        return quadrature;
    }

    const VectorStr& FEMParameters::getDirichletLabels() const {
        return dirichletLabels;
    }

    const VectorStr& FEMParameters::getHomogeneousDirichletLabels() const {
        return homogeneousDirichletLabels;
    }

    const VectorStr& FEMParameters::getNeumannLabels() const {
        return neumannLabels;
    }

    const VectorStr& FEMParameters::getDomainLabels() const {
        return domainLabels;
    }


