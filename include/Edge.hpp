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
#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include "Node.hpp"
#include <iostream>
#include "FEMIntegrale.hpp"
#include "Quadrature.hpp"
#include "FEMUtilities.hpp"


// TO DOOOOO MAKE MORE NODE POSSIBLE THAN 2 !!!!!!!!!
// AFTER THAT GO TO SOLVER.CPP AND CHANGE THE WAY MATARET IS DEFINE


    class Edge{
        private :
            // Node node1;
            // Node node2;

            std::vector<Node> nodeList;

            std::vector<int> nodeIdList;
            int nbNodePerAret;

            Quadrature quadraMethodS1;

            int label;

            std::string type;

        public :
            Edge(Node& node1_, Node& node2_, int label_);

            Edge(std::vector<Node> nodeList_, int label_);

            void intAret(std::vector<std::vector<double> >& elemMatrix, std::vector<double>& fElem);

            // bool isOnEdge(const std::vector<Edge>& edgeList);
            
            // bool operator==(const Edge& other) const;

            void setLabel(int newlabel);

            int getLabel() const;

            // Node& getNode1() {return node1;}
            // Node& getNode2() {return node2;}

            Node& getNodeAt(int position) {return nodeList[position];}

            int getNodeNumber();

            const std::vector<int>& getNodeIDs() const;

            std::vector<Node> getNodeList();

            void printEdge();
    };

#endif