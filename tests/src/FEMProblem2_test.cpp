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
        return 1.0;
    }

    Real A00(VectorReal x){
        return 0.0;
    }

    Real A12(VectorReal x){
        return 0.0;
    }

    Real A22(VectorReal x){
        return 1.0;
    }

    Real BN(VectorReal x){
        return 0.0;
    }

    Real FOMEGA(VectorReal x){
        return 2*M_PI*M_PI * std::sin(M_PI * x[0]) * std::sin(M_PI*x[1]);
    }

    Real FN(VectorReal x_, int numAret){
        return 0.0;
    }

    Real UD(const VectorReal& x){
        return 0.0;
    }

    Real UD(const Node& x){
        return 0.0;
    }


}