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

    Real aij(Real i, Real j){
        return (i == j);
    }

    Real A11(VectorReal x){
        return 1;
    }

    Real A00(VectorReal x){
        return 1;
    }

    Real A12(VectorReal x){
        return 0;
    }

    Real A22(VectorReal x){
        return 1;
    }

    Real BN(VectorReal x){
        return 0;
    }

    Real FOMEGA(VectorReal x){
        return (1+2*M_PI*M_PI) * std::cos(M_PI * x[0]) * std::cos(M_PI*x[1]);
    }

    Real FN(VectorReal x_, int numAret){
        Real x(x_[0]);
        Real y(x_[1]);

        switch (numAret) {
            case 2:
                return - M_PI * sin(M_PI * x) * cos(M_PI * y);
            case 3:
                return - M_PI * cos(M_PI * x) * sin(M_PI * y);
            default:
                std::cerr << "Edge label " <<   numAret <<"incorrect." << std::endl;
                return 0.0;
        }
    }

    Real UD(const VectorReal& x){

        return std::cos(M_PI * x[0]) *std::cos(M_PI*x[1]);
    }

    Real UD(const Node& x){
        return std::cos(M_PI * x.getX()) *std::cos(M_PI*x.getY());
    }

}