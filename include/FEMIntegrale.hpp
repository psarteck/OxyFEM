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

    VectorReal baseFunctions(const Node& pts, const std::string type, const int number = 0);

    VectorReal baseFunctions(const Node& currentPts, const std::string type, const std::vector<Node>& elementsPts);

    MatrixReal baseDerFunctions(const Node& pts, const std::string type, const int number = 0);

    MatrixReal baseDerFunctions(const std::string type, const std::vector<Node>& nodes);

    MatrixReal matJacob(const std::vector<Node> selectNodes, const MatrixReal valDerBase, const std::string type);

    VectorReal transFK(const std::vector<Node> selectNodes, const VectorReal valBase);

    void ADWDW(const std::vector<Node> nodes, const MatrixReal valDerBase, Real diffElement, VectorReal point, MatrixReal cofvar, MatrixReal matInv, MatrixReal& elemMatrix);

    void WW(const std::vector<Node> nodes, const VectorReal valBase, const Real diffElement, const Real cofvar, MatrixReal& elemMatrix);

    void W(const std::vector<Node>& nodes, const VectorReal& valBase, const Real diffElement, const Real cofvar, VectorReal& fElem);

    MatrixReal invert2x2(MatrixReal& mat, Real& det);

    Real prodScal(const MatrixReal& Mat1, MatrixReal& Mat2, const int& indiceAB, const int& indiceIJ);

}


#endif