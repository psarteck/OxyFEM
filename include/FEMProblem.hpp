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
#include <iostream>
#include <vector>
#include "Node.hpp"

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

    double aij(double i, double j);

    double A11(std::vector<double> x);

    double A00(std::vector<double> x);

    double A12(std::vector<double> x);

    double A22(std::vector<double> x);

    double BN(std::vector<double> x);

    double FOMEGA(std::vector<double> x);

    double FN(std::vector<double> x, int numAret);

    double UD(const std::vector<double>& x);
    double UD(const Node& x);

}

