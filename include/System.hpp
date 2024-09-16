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
class System {

    public:

        // System matrix vector
        std::unique_ptr<std::vector<double>> matrix; 
        // std::vector<double>* matrix; 
        std::unique_ptr<std::vector<double>> secMember;

        // SMD
        std::unique_ptr<std::vector<int>> adPrCoefLi;
        std::unique_ptr<std::vector<int>> adSuccLi;
        std::unique_ptr<std::vector<int>> numCol;
        std::unique_ptr<std::vector<int>> numDLDir;
        std::unique_ptr<std::vector<double>> valDLDir;


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