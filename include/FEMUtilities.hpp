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

#ifndef FEM_UTILITIES
#define FEM_UTILITIES

// #include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <vector>

#include "Types.hpp"

using namespace std;

namespace FEMUtilities {

    // Eigen::MatrixXd mat2Eigen(const std::vector<std::vector<double> >& vecOfVec); 

    // Eigen::VectorXd vec2Eigen(const std::vector<double>& vec);

    template <typename T>
    void printMat(std::vector<std::vector<T> > mat, std::string name);

    template <typename T>
    void printVec(std::vector<T> vec, std::string name);


    // void saveResults(Eigen::VectorXd vec, std::string filename);

    template <typename T>
    void saveResults(std::vector<T> vec, std::string filename);

    // std::vector<double> node2double(std::vector<Node> vec);

    void showProgress(float percentage);

}



#endif


