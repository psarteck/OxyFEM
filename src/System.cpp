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
#include "System.hpp"
#include <vector>


System::System(int nbNode): nbLign(nbNode), nbCoeff(nbNode * nbNode), nextAd(1) {

    matrix = std::make_unique<std::vector<double>>(nbLign + nbCoeff, 0.0);
    // matrix = new std::vector<double>(nbLign + nbCoeff, 0.0);
    secMember = std::make_unique<std::vector<double>>(nbLign, 0.0);

    adPrCoefLi = std::make_unique<std::vector<int>>(nbLign + nbCoeff, 0);
    adSuccLi = std::make_unique<std::vector<int>>(nbLign + nbCoeff, 0);
    numCol = std::make_unique<std::vector<int>>(nbLign + nbCoeff, 0);
    numDLDir = std::make_unique<std::vector<int>>(nbLign + nbCoeff, 0);
    valDLDir = std::make_unique<std::vector<double>>(nbLign + nbCoeff, 0.0);

}