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

            // Id of the element
            const int id;   
            // Number of the element in the mesh
            const int number; 

            // Ids of the constituting nodes of the element
            const VectorInt nodeIds;

            // Edges of the element
            std::vector<Edge> edges;
            
            // Nodes of the element
            std::vector<Node> nodes;

            // Value of the basis functions
            VectorReal valBase;

            // Value of the derivated basis functions
            MatrixReal valDerBase;

            // Quadrature methods 
            Quadrature quadraMethod;
            // Quadrature quadraMethodT1;
            // Quadrature quadraMethodQ1;

            // Number of nodes
            int nodeNb;

            // Type of the element
            std::string type;

            // Label of the element
            int label;

            // Dimension of the element 2D or 3D
            int dimension;

        public :
            // Element(int id_, const VectorInt& nodeIds_);

            Element(int id_, VectorInt& nodeIds, std::vector<Node> & nodes_, int number = 0);

            Element(int id_, VectorInt& nodeIds, std::vector<Node> & nodes_, std::vector<Edge> & edges_);


            
            void intElem(MatrixReal& elemMatrix, VectorReal& fElem);


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

            void printNodes() { 
                for(auto node : nodes){
                    cout << node.getLabel() << " ";
                }
                cout << endl;
            }


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