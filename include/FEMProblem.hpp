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
#ifndef FEM_PROBLEM
#define FEM_PROBLEM

#include <iostream>
#include <vector>
#include "Node.hpp"

#include "Types.hpp"

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

    Real aij(Real i, Real j);

    Real A11(VectorReal x);

    Real A00(VectorReal x);

    Real A12(VectorReal x);

    Real A22(VectorReal x);

    Real BN(VectorReal x);

    Real FOMEGA(VectorReal x);

    Real FN(VectorReal x, int numAret);

    Real UD(const VectorReal& x);
    Real UD(const Node& x);

}

#endif