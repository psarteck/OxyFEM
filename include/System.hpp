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
#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <memory>

#include "Types.hpp"

class System {

    public:

        // System matrix vector
        std::unique_ptr<VectorReal> matrix; 
        // VectorReal* matrix; 
        std::unique_ptr<VectorReal> secMember;

        // SMD
        std::unique_ptr<VectorInt> adPrCoefLi;
        std::unique_ptr<VectorInt> adSuccLi;
        std::unique_ptr<VectorInt> numCol;
        std::unique_ptr<VectorInt> numDLDir;
        std::unique_ptr<VectorReal> valDLDir;


        // Size of the system
        int nbLign;
        int nbCoeff;
        int nextAd;

        /*!
            Constructor
            @param nbNode   number of node in the mesh
        */
        System(int nbNode);



};


#endif