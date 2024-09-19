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
#ifndef ELEMENT_H
#define ELEMENT_H

#include <iomanip>
#include <vector>
#include <string>
#include "Edge.hpp"
#include "Node.hpp"
#include <iostream>
#include "FEMProblem.hpp"
#include "Quadrature.hpp"
#include "FEMUtilities.hpp"
#include "FEMIntegrale.hpp"

#include "Types.hpp"

    class Edge;

    class Element {

        private : 
            const int id;   
            const int number; // Number of the element in the mesh
            const VectorInt nodeIds;
            std::vector<Edge> edges;
            std::vector<Node> nodes;
            VectorReal valBase;
            MatrixReal valDerBase;
            // MatrixD elemMatrix;
            // VectorReal fElem;

            Quadrature quadraMethodS1;
            // Quadrature quadraMethodT1;
            // Quadrature quadraMethodQ1;


            VectorInt NuDElem;
            VectorReal uDElem;

            int nodeNb;
            std::string type;
            int label;
            int dimension;

        public :
            // Element(int id_, const VectorInt& nodeIds_);

            Element(int id_, VectorInt& nodeIds, std::vector<Node> & nodes_, int number = 0);

            Element(int id_, VectorInt& nodeIds, std::vector<Node> & nodes_, std::vector<Edge> & edges_);

            
            void intElem(MatrixReal& elemMatrix, VectorReal& fElem);


            void cal1Elem(VectorReal& fElem, MatrixReal& elemMatrix);


            void impCalEl(int K, int typEl, int nbneel, MatrixReal MatElem, VectorReal SMbrElem,
                VectorInt NuDElem, VectorReal uDElem);

            

    /*
            GETTERS AND SETTERS
    */
            
            const int getId() const;
            const std::vector<Edge>& getEdges()const ;

            const std::vector<Node>& getNodes()const ;

            const VectorInt& getNodeIDs() const;

            Node getNodeById(int nodeId) const;

            int getNodeNumber();

            int getNuDElem(int i);
            Real getuDElem(int i);
            void setNuDElem(int i, int val);
            void setuDElem(int i, Real val);


    };

#endif

// void cal1Elem(MatrixReal& MatElem, VectorReal& SMbrElem,
//               VectorInt& NuDElem, VectorReal& uDElem);
// void baseFunctions(const Node& pts);
// void baseDerFunctions(const Node& pts);
// VectorReal transFK(std::vector<Node> selectNodes);
// MatrixReal matJacob(std::vector<Node> selectNodes);
// MatrixReal invert2x2(MatrixReal& mat, Real& det);
// void ADWDW(Real diffElement, VectorReal point, MatrixReal cofvar, MatrixReal matInv, MatrixReal& elemMatrix);
// void WW(Real diffElement, Real cofvar, MatrixReal& elemMatrix);
// void W(Real diffElement, Real cofvar, VectorReal& fElem);
// Real prodScal(MatrixReal Mat1, MatrixReal Mat2, int indiceAB, int indiceIJ);
// void intAret(MatrixReal& elemMatrix, VectorReal& fElem, std::vector<Node> coordAret);
// int returnQ(std::string type);