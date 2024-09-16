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
#ifndef QUADRATURE_H
#define QUADRATURE_H

#include "Node.hpp"
#include <string>

// #include "FEMParameters.hpp"


    class Quadrature{
    private:
        std::string methodName;
        std::string elementType;
        int order;

        // FEMParameters parameters;

        std::vector<double> weights;
        std::vector<Node> points;
    public:
        Quadrature(std::string methodName_, std::string elementType_, int order_);
        // Quadrature(FEMParameters parameters);
        Quadrature(){};



        void weightsPoints(std::string elementType);

        std::vector<double> getWeights();
        std::vector<Node> getPoints();

    };



#endif
