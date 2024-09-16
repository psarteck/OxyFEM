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
#include "FEMProblem.hpp"
#include <cmath>
#include <iostream>

namespace FEMProblem {
    /*
Définition des fonctions inhérentes à la l'opérateur différentiel et la formulation variationelle :

A_00
A_11, A_12, A_21, A_22
B_N
F_N
UD
F_OMEGA
*/
// extern int nucas;
// extern int dom;

double aij(double i, double j){
    return (i == j);
}

double A11(std::vector<double> x){
    return 1;
}

double A00(std::vector<double> x){
    return 1;
}

double A12(std::vector<double> x){
    return 0;
}

double A22(std::vector<double> x){
    return 1;
}

double BN(std::vector<double> x){
    return 0;
}

double FOMEGA(std::vector<double> x){

    return (1+2*M_PI*M_PI)*cos(M_PI*x[0])*cos(M_PI*x[1]);
}

double FN(std::vector<double> x_, int numAret){
    std::cout << "azeaze" << std::endl;
    double x(x_[0]);
    double y(x_[1]);

    switch (numAret) {
        case 1:
            return M_PI * cos(M_PI * x) * sin(M_PI * y);
        case 2:
            return - M_PI * sin(M_PI * x) * cos(M_PI * y);
        case 3:
            return - M_PI * cos(M_PI * x) * sin(M_PI * y);
        case 4:
            return M_PI * sin(M_PI * x) * cos(M_PI * y);

        default:
            std::cerr << "Edge label " <<   numAret <<"incorrect." << std::endl;
            return 0.0;
    }
}

double UD(const std::vector<double>& x){

    return 0.0;
}

double UD(const Node& x){
    return 100 * x.getX() + x.getY();
}

}