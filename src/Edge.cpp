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
#include "Edge.hpp"
#include <cmath>

// TO DO CHANGE THE TYPE IN THE CONSTRUCTOR
Edge::Edge(Node& node1_, Node& node2_, int label_) : label(label_), type("S1"){

    nodeList.push_back(node1_);
    nodeList.push_back(node2_);

    nodeIdList.push_back(node1_.getId());
    nodeIdList.push_back(node2_.getId());

    nbNodePerAret = nodeList.size();

    // quadraMethodS1 = Quadrature();

}

// TO DO CHANGE THE TYPE IN THE CONSTRUCTOR
Edge::Edge(std::vector<Node> nodeList_, int label_) : nodeList(nodeList_), label(label_), type("S1"){
    for(auto node : nodeList){
        nodeIdList.push_back(node.getId());
    }

    nbNodePerAret = nodeList.size();

}


void Edge::intAret(MatrixReal& elemMatrix, VectorReal& fElem){

    int d = 1;
    
    int q = FEMIntegrale::returnQ(type);
    
    quadraMethodS1.weightsPoints(type);
    
    
    for(int indicepts = 0 ; indicepts < q ; indicepts ++){
        
        std::vector<Node> pts = quadraMethodS1.getPoints();
        VectorReal pds = quadraMethodS1.getWeights();

        VectorReal baseFct = FEMIntegrale::baseFunctions(pts[indicepts], type);

        MatrixReal baseDerFct = FEMIntegrale::baseDerFunctions(pts[indicepts], type);
        
        MatrixReal Jcob = FEMIntegrale::matJacob(nodeList, baseDerFct, type);
        
        VectorReal imagPoint = FEMIntegrale::transFK(nodeList, baseFct);

        Real eltdif = pds[indicepts] * std::sqrt(Jcob[0][0]*Jcob[0][0] + Jcob[0][1]*Jcob[0][1]);
        
        Real cofvarWW = FEMProblem::BN(imagPoint);
        
        FEMIntegrale::WW(nodeList, baseFct, eltdif, cofvarWW, elemMatrix);
        
        Real cofvarW = FEMProblem::FN(imagPoint, label);

        FEMIntegrale::W(nodeList, baseFct, eltdif, cofvarW, fElem);
        
    }

}


// bool Edge::operator==(const Edge& other) const {
//     return ((node1 == other.node1) && (node2 == other.node2) || (node2 == other.node1) && (node1 == other.node2));

//     for(auto node : nodeList){
//         if()
//     }
// }


// bool Edge::isOnEdge(const std::vector<Edge>& edgeList){
//     for(auto edge : edgeList){
//         if(*this == edge){
//             return true;
//         }
//     }
//     return false;
// }

void Edge::setLabel(int newlabel){
    label = newlabel;
}

int Edge::getLabel() const{
    return label;
}

int Edge::getNodeNumber(){
    return nodeList.size();
}

const VectorInt& Edge::getNodeIDs() const{
    return nodeIdList;
}

std::vector<Node> Edge::getNodeList(){
    return nodeList;
}

void Edge::printEdge(){
    std::cout << "EdgeLabel : " << getLabel() << std::endl;
    for(auto node : nodeList){
        std::cout << node.getId() << " | ";
    }
    std::cout << std::endl;
}