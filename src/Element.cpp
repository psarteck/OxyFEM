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
#include "Element.hpp"
#include <vector>
#include <cmath>


    using namespace std;

    Element::Element(int id_, VectorInt& nodeIds, std::vector<Node>& nodes_, int number_)
        : id(id_), nodeIds(nodeIds), nodes(nodes_), type("T1"), number(number_){


            valBase = VectorReal(nodes.size(), 0.0);
            valDerBase = MatrixReal(nodes.size(), VectorReal(2,0.0));
            nodeNb = nodes.size();

        // Assuming nodes and nodeIds have the same size
        // for (size_t i = 0; i < nodes.size() - 1; ++i) {
        //     edges.push_back(Edge(nodes[i], nodes[i + 1]));
        // }
        // edges.push_back(Edge(nodes.back(), nodes.front()));  // Closing the loop

        // elemMatrix = MatrixReal(nodes.size(), VectorReal(nodes.size(), 0.0));
        // fElem = VectorReal(nodes.size(), 0.0);
    }

    Element::Element(int id_, VectorInt& nodeIds, std::vector<Node>& nodes_, std::vector<Edge> & edges_)
        : id(id_), nodeIds(nodeIds), nodes(nodes_), edges(edges_), number(0){


        
        // Assuming nodes and nodeIds have the same size
        // for (size_t i = 0; i < nodes.size() - 1; ++i) {
        //     edges.push_back(Edge(nodes[i], nodes[i + 1]));
        // }
        // edges.push_back(Edge(nodes.back(), nodes.front()));  // Closing the loop

        // elemMatrix = MatrixReal(nodes.size(), VectorReal(nodes.size(), 0.0));
        // fElem = VectorReal(nodes.size(), 0.0);
    }


    void Element::intElem(MatrixReal& elemMatrix, VectorReal& fElem){

        Real eps = std::numeric_limits<Real>::epsilon();

        int q = FEMIntegrale::returnQ(type);

        quadraMethod.weightsPoints(type);

        std::vector<Node> pts = quadraMethod.getPoints();
        VectorReal pds = quadraMethod.getWeights();
            
        for(int indicepts = 0 ; indicepts < q ; indicepts ++){
                
            valBase = FEMIntegrale::baseFunctions(pts[indicepts], type, number); //check
            // valBase = FEMIntegrale::baseFunctions(pts[indicepts], type, nodes); //check

            valDerBase = FEMIntegrale::baseDerFunctions(pts[indicepts], type, number); //check
            // valDerBase = FEMIntegrale::baseDerFunctions(type, nodes); //check

            MatrixReal Jcob = FEMIntegrale::matJacob(nodes, valDerBase, type); 

            Real det;
            MatrixReal matInv = FEMIntegrale::invert2x2(Jcob, det);
            
            VectorReal imagPoint = FEMIntegrale::transFK(nodes, valBase);

            Real eltdif = det * pds[indicepts];

            if (std::fabs(det) > eps){
            
                MatrixReal cofvarAD(2, VectorReal(2,0.0));

                cofvarAD[0][0] = FEMProblem::A11(imagPoint);
                cofvarAD[0][1] = FEMProblem::A12(imagPoint);
                cofvarAD[1][0] = FEMProblem::A12(imagPoint);
                cofvarAD[1][1] = FEMProblem::A22(imagPoint);
                
                FEMIntegrale::ADWDW(nodes, valDerBase, eltdif, imagPoint, cofvarAD, matInv, elemMatrix);

                Real cofvarWW = FEMProblem::A00(imagPoint);

                if (std::fabs(cofvarWW) > eps)    
                    FEMIntegrale::WW(nodes, valBase, eltdif, cofvarWW, elemMatrix);
                        
                Real cofvarW = FEMProblem::FOMEGA(imagPoint);
                
                if (std::fabs(cofvarW) > eps)    
                    FEMIntegrale::W(nodes, valBase, eltdif, cofvarW, fElem);
            }

        }

    }



    void Element::impCalEl(int K, int typEl, int nbneel, MatrixReal MatElem, VectorReal SMbrElem,
                VectorInt NuDElem, VectorReal uDElem){
        int i, j;
        std::cout << std::endl;
        std::cout << " ELEMENT=" << std::setw(3) << K
            << "    DE TYPE=" << std::setw(5) << typEl
            << "    NB NOEUDS=" << std::setw(2) << nbneel << std::endl;

        std::cout << " NuDElem   uDElem    SMbrElem    MatElem" << std::endl;
        for (int i = 0; i < nbneel; i++) {
            std::cout << std::setw(6) << NuDElem[i]
                    << std::scientific << std::setw(14) << uDElem[i]
                    << std::scientific << std::setw(14) << SMbrElem[i];
            for (int j = 0; j <= i; j++) {
                std::cout << std::scientific << std::setw(14) << MatElem[i][j];
            }
            std::cout << std::endl;
        }
    }




    /*
        GETTERS AND SETTERS
    */
    const int Element::getId() const {  return id;  }

    const VectorInt& Element::getNodeIDs() const {   return nodeIds;   }

    Node Element::getNodeById(int nodeId) const {
        for (const Node& node : nodes) {
            if (node.getId() == nodeId) {
                return node;
            }
        }
        // Handle the case where the node with the specified ID is not found
        // You might want to throw an exception or handle it based on your needs.
        // For simplicity, we'll return the first node in the element.
        return nodes.front();
    }


    const std::vector<Edge>& Element::getEdges() const {
        return edges;
    }

    const std::vector<Node>& Element::getNodes() const {
        return nodes;
    }

    int Element::getNodeNumber(){
        return nodes.size();
    }


