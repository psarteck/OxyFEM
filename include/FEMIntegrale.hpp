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
#ifndef FEM_INTEGRALE_H
#define FEM_INTEGRALE_H


#include <string>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include "FEMProblem.hpp"
#include "Types.hpp"

using namespace std;


namespace FEMIntegrale {
    

    int returnQ(std::string type);

    std::vector<double> baseFunctions(const Node& pts, const std::string type, const int number = 0);

    std::vector<std::vector<double> > baseDerFunctions(const Node& pts, const std::string type, const int number = 0);

    std::vector<std::vector<double> > matJacob(const std::vector<Node> selectNodes, const std::vector<std::vector<double> > valDerBase, const std::string type);

    std::vector<double> transFK(const std::vector<Node> selectNodes, const std::vector<double> valBase);

    void ADWDW(const std::vector<Node> nodes, const std::vector<std::vector<double> > valDerBase, double diffElement, std::vector<double> point, std::vector<std::vector<double> > cofvar, std::vector<std::vector<double> > matInv, std::vector<std::vector<double> >& elemMatrix);

    void WW(const std::vector<Node> nodes, const std::vector<double> valBase, const double diffElement, const double cofvar, std::vector<std::vector<double> >& elemMatrix);

    void W(const std::vector<Node> nodes, const std::vector<double> valBase, const double diffElement, const double cofvar, std::vector<double>& fElem);

    std::vector<std::vector<double> > invert2x2(std::vector<std::vector<double> >& mat, double& det);

    double prodScal(std::vector<std::vector<double> > Mat1, std::vector<std::vector<double> > Mat2, int indiceAB, int indiceIJ);

}


#endif