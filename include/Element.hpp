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
// #include "Types.hpp"

    class Edge;

    class Element {

        // using MatrixD = std::vector<std::vector<double> >;
        // using VectorD = std::vector<double>;
        // using VectorI = std::vector<int>;
        // using VectorNo = std::vector<Node>;
        // using VectorEd = std::vector<Edge>;

        private : 
            const int id;   
            const int number; // Number of the element in the mesh
            const std::vector<int> nodeIds;
            std::vector<Edge> edges;
            std::vector<Node> nodes;
            std::vector<double> valBase;
            std::vector<std::vector<double> > valDerBase;
            // MatrixD elemMatrix;
            // std::vector<double> fElem;

            Quadrature quadraMethodS1;
            // Quadrature quadraMethodT1;
            // Quadrature quadraMethodQ1;


            std::vector<int> NuDElem;
            std::vector<double> uDElem;

            int nodeNb;
            std::string type;
            int label;
            int dimension;

        public :
            // Element(int id_, const std::vector<int>& nodeIds_);

            Element(int id_, std::vector<int>& nodeIds, std::vector<Node> & nodes_, int number = 0);

            Element(int id_, std::vector<int>& nodeIds, std::vector<Node> & nodes_, std::vector<Edge> & edges_);

            
            void intElem(std::vector<std::vector<double> >& elemMatrix, std::vector<double>& fElem);


            void cal1Elem(std::vector<double>& fElem, std::vector<std::vector<double>>& elemMatrix);


            void impCalEl(int K, int typEl, int nbneel, std::vector<std::vector<double> > MatElem, std::vector<double> SMbrElem,
                std::vector<int> NuDElem, std::vector<double> uDElem);

            

    /*
            GETTERS AND SETTERS
    */
            
            const int getId() const;
            const std::vector<Edge>& getEdges()const ;

            const std::vector<Node>& getNodes()const ;

            const std::vector<int>& getNodeIDs() const;

            Node getNodeById(int nodeId) const;

            int getNodeNumber();

            int getNuDElem(int i);
            double getuDElem(int i);
            void setNuDElem(int i, int val);
            void setuDElem(int i, double val);


    };

#endif

// void cal1Elem(std::vector<std::vector<double> >& MatElem, std::vector<double>& SMbrElem,
//               std::vector<int>& NuDElem, std::vector<double>& uDElem);
// void baseFunctions(const Node& pts);
// void baseDerFunctions(const Node& pts);
// std::vector<double> transFK(std::vector<Node> selectNodes);
// std::vector<std::vector<double> > matJacob(std::vector<Node> selectNodes);
// std::vector<std::vector<double> > invert2x2(std::vector<std::vector<double> >& mat, double& det);
// void ADWDW(double diffElement, std::vector<double> point, std::vector<std::vector<double> > cofvar, std::vector<std::vector<double> > matInv, std::vector<std::vector<double> >& elemMatrix);
// void WW(double diffElement, double cofvar, std::vector<std::vector<double> >& elemMatrix);
// void W(double diffElement, double cofvar, std::vector<double>& fElem);
// double prodScal(std::vector<std::vector<double> > Mat1, std::vector<std::vector<double> > Mat2, int indiceAB, int indiceIJ);
// void intAret(std::vector<std::vector<double> >& elemMatrix, std::vector<double>& fElem, std::vector<Node> coordAret);
// int returnQ(std::string type);