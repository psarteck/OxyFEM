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

#include "Types.hpp"


// TO DOOOOO MAKE MORE NODE POSSIBLE THAN 2 !!!!!!!!!
// AFTER THAT GO TO SOLVER.CPP AND CHANGE THE WAY MATARET IS DEFINE


    class Edge{
        private :

            // List of the nodes in the edge
            std::vector<Node> nodeList;

            // List of the node ids 
            VectorInt nodeIdList;

            // Number of node per edge
            int nbNodePerAret;

            // Quadrature method
            Quadrature quadraMethodS1;

            // Label of the edge
            int label;

            // Type of the edge
            std::string type;

        public :
            /*!
            *    Constructor
            *    @param[in] node1_       First node
            *    @param[in] node1_       Seconde node
            *    @param[in] node1_       Label of the edge
            */
            Edge(Node& node1_, Node& node2_, int label_);

            /*!
            *    Constructor
            *    @param[in] nodeList_    List of the node of the edge
            *    @param[in] label_       Label of the edge
            */
            Edge(std::vector<Node> nodeList_, int label_);

            /*!
            *    Integrate the edge
            *    @param[in] elemMatrix   Elementary matrix of the edge
            *    @param[in] fElem        Seconde membre of the edge
            */
            void intAret(MatrixReal& elemMatrix, VectorReal& fElem);

            // bool isOnEdge(const std::vector<Edge>& edgeList);
            
            // bool operator==(const Edge& other) const;


            /* 
                    GETTER AND SETTER
            */

            void setLabel(int newlabel) {label = newlabel;};

            const int getLabel() const {return label;};


            Node& getNodeAt(int position) {return nodeList[position];}

            const int getNodeNumber() const {return nodeList.size();};

            const VectorInt& getNodeIDs() const {return nodeIdList;};

            const int getNodeIdAt(int i) const {return nodeIdList[i];};

            const std::vector<Node> getNodeList() const {return nodeList;};

            const void printEdge() const;
    };

#endif