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
    return 0;
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
    // switch(nucas){
    //     case 1:
    //         return 32*(x[0]-x[0]*x[0]+x[1]-x[1]*x[1]);
    //         break;
    //     case 2:
    //         return 2*M_PI*M_PI*sin(M_PI*x[0])*sin(M_PI*x[1]);
    //         break;
    //     case 3:
    //         return (1+2*M_PI*M_PI)*cos(M_PI*x[0])*cos(M_PI*x[1]);
    //         break;
    //     default:
    //         printf("\nMauvaise valeur de nucas !\n");
    //         return 0;
    //         break;
    // }
    // return 32*(x[0]*(1-x[0])+x[1]*(1-x[1]));
    return 2 * M_PI * M_PI * sin(M_PI * x[0]) * sin(M_PI * x[1]);
    // return (1+2*M_PI*M_PI)*cos(M_PI*x[0])*cos(M_PI*x[1]);
}

Real FN(VectorReal x_, int numAret){

    Real x(x_[0]);
    Real y(x_[1]);

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
    // return 10*x[0] - 5*x[1];
}

Real UD(const VectorReal& x){
    
    // switch(nucas){
    //     case 1:
    //         return 16*x[0]*x[1]*(1-x[0])*(1-x[1]);
    //         break;
    //     case 2:
    //         return sin(x[0]*M_PI)*sin(x[1]*M_PI);
    //         break;
    //     case 3:
    //         return cos(M_PI*x[0])*cos(M_PI*x[1]);
    //         break;
    //     default:
    //         printf("\nMauvaise valeur de nucas !\n");
    //         return 0;
    //         break;
    //     }
    // return 0;
    // return 100*x[0] + x[1];
    return 0.0;
}

Real UD(const Node& x){
    return 100 * x.getX() + x.getY();
}

}