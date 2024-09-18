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
#include <Eigen/Dense>
#include <iostream>
#include <fstream>

using namespace std;

namespace FEMUtilities {

    Eigen::MatrixXd mat2Eigen(const std::vector<std::vector<double> >& vecOfVec); 

    Eigen::VectorXd vec2Eigen(const std::vector<double>& vec);

    template <typename T>
    void printMat(std::vector<std::vector<T> > mat, std::string name);

    template <typename T>
    void printVec(std::vector<T> vec, std::string name);


    void saveResults(Eigen::VectorXd vec, std::string filename);

    void saveResults(std::vector<double> vec, std::string filename);

    // std::vector<double> node2double(std::vector<Node> vec);

    void showProgress(float percentage);

}






