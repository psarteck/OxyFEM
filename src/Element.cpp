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
            NuDElem = VectorInt(nodeNb, 0);
            uDElem = VectorReal(nodeNb, 0);

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

        quadraMethodS1.weightsPoints(type);

        std::vector<Node> pts = quadraMethodS1.getPoints();
        VectorReal pds = quadraMethodS1.getWeights();
            
        for(int indicepts = 0 ; indicepts < q ; indicepts ++){
                
            valBase = FEMIntegrale::baseFunctions(pts[indicepts], type, number); //check

            valDerBase = FEMIntegrale::baseDerFunctions(pts[indicepts], type, number); //check

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


    void Element::cal1Elem(VectorReal& SMbrElem, MatrixReal& MatElem) {
        for(int j = 0 ; j < this->nodeNb ; j ++){
            NuDElem[j] = 1;
            uDElem[j] = 0;
        }

        intElem(MatElem, SMbrElem);

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

    int Element::getNuDElem(int i){
        return NuDElem[i];
    }
    Real Element::getuDElem(int i){
        return uDElem[i];
    }
    void Element::setNuDElem(int i, int val){
        NuDElem[i] = val;
    }
    void Element::setuDElem(int i, Real val){
        uDElem[i] = val;
    }




    // void Element::cal1Elem(MatrixReal& MatElem, VectorReal& SMbrElem,
    //               VectorInt& NuDElem, VectorReal& uDElem){
    //     for(int j = 0 ; j < nodes.size() ; j ++){
    //         NuDElem[j] = 1;
    //         uDElem[j] = 0;
    //     }
    //     for(int k = 0 ; k < nodes.size() ; k ++){
    //         SMbrElem[k] = 0;
    //         for(int l = 0 ; l < nodes.size() ; l++){
    //             MatElem[k][l] = 0;
    //         }
    //     }

    //     intElem(MatElem, SMbrElem);

    //     int nbneAr = 2;
    //     MatrixReal MatAret(nbneAr, VectorReal(nbneAr, 0.0));
    //     VectorReal SMbrAret(VectorReal(nbneAr, 0.0));

    //     for(auto aret : edges){
    //         // if(aret.isOnEdge(edges)){
    //         //     intAret(MatAret, SMbrAret, {aret.getNodeAt(0), aret.getNodeAt(1)});
    //         //     std::cout << "azejoaizejz " << std::endl;
    //         // }
    //     }

    //     for (int m = 0 ; m < nbneAr ; m++){
                            
    //         SMbrElem[m] = SMbrElem[m] + SMbrAret[m];
            
    //         for (int a = 0 ; a < nbneAr ; a++){
    //             int nm=m;
    //             int na= a;
    //             MatElem[nm][na] = MatElem[nm][na] + MatAret[m][a];
                
    //         }
    //     }

    // }






    //void Element::baseFunctions(const Node& pts){
    //     valBase.clear();
    //     if(type == "Q1"){            
    //         valBase.push_back(pts.getX() - pts.getX()*pts.getY());
    //         valBase.push_back(pts.getX()*pts.getY());
    //         valBase.push_back(pts.getY() - pts.getX()*pts.getY());
    //         valBase.push_back(pts.getX()*pts.getY() - pts.getY() - pts.getX() + 1);   
    //     }
    //     else if(type == "T1"){
    //         valBase.push_back(pts.getX());
    //         valBase.push_back(pts.getY());
    //         valBase.push_back(1 - pts.getX() - pts.getY());
    //     }
    //     else if(type == "S1"){
    //         valBase.push_back(pts.getX());
    //         valBase.push_back(1-pts.getX());
    //     }
    //     else{
    //             std::cout << "Error : Unkown element type." << std::endl;
    //     }
    // }

    // void Element::baseDerFunctions(const Node& pts){

    //     valDerBase.clear();
    //     if(type == "Q1"){            
    //         valDerBase.push_back({1-pts.getY(), -pts.getX()});
    //         valDerBase.push_back({pts.getY(), pts.getX()});
    //         valDerBase.push_back({-pts.getY(), 1-pts.getX()});
    //         valDerBase.push_back({pts.getY() - 1, pts.getX() - 1});

    //         // valDerBase.push_back({1-pts.getY(), pts.getY(), -pts.getY(), pts.getY() - 1});
    //         // valDerBase.push_back({-pts.getX(), pts.getX(), 1-pts.getX(), pts.getX() - 1});   
    //     }
    //     else if(type == "T1"){

    //         valDerBase.push_back({1, 0});
    //         valDerBase.push_back({0, 1});
    //         valDerBase.push_back({-1, -1});
    //         // valDerBase.push_back({1, 0, -1});
    //         // valDerBase.push_back({0, 1, -1});
    //     }
    //     else if(type == "S1"){
    //         valDerBase.push_back({1, -1});
    //     }
    //     else{
    //             printf("\nError : Unkown element type.\n");
    //     }
    // }

    // VectorReal Element::transFK(std::vector<Node> selectNodes){
    //     // float **ai, float *valBase, int Pk, float *res){
    //     // TO DO Make it 3D
    //     VectorReal evaluatedPoint(2, 0.0);
    //     for(int i = 0 ; i < selectNodes.size() ; i++){
    //         evaluatedPoint[0] += selectNodes[i].getX() * valBase[i];
    //         evaluatedPoint[1] += selectNodes[i].getY() * valBase[i];
    //     }
    //     return evaluatedPoint;
    // }


    // MatrixReal Element::matJacob(std::vector<Node> selectNodes){

    //     // TO DOO MAKE IT 3D AND BETTER !!!!
        
    //     int d;
    //     if(type == "S1"){
    //         d = 1;
    //     }
    //     else{
    //         d = 2;
    //     }   
    //     MatrixReal Jcob(2, VectorReal(d, 0.0));

    //     for(int j = 0 ; j < d ; j++){
    //         for(int k = 0 ; k < selectNodes.size() ; k++){
    //             Jcob[0][j] += selectNodes[k].getX() * valDerBase[k][j];
    //         }
    //     }
    //     for(int j = 0 ; j < d ; j++){
    //         for(int k = 0 ; k < selectNodes.size() ; k++){
    //             Jcob[1][j] += selectNodes[k].getY() * valDerBase[k][j];
    //         }
    //     }



    //     return Jcob;
    // }


    // MatrixReal Element::invert2x2(MatrixReal& mat, Real& det){
    //     // TO DO FAIRE MIEUX -> EIGEN ???

    //     // Eigen::MatrixXd matEigen = FEMUtilities::vector2EigenMatrix(mat); 

    //     MatrixReal invMat(mat.size(), VectorReal(mat[0].size(), 0.0));

    //     det = mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
        
    //     invMat[0][0] = 1/ det * mat[1][1];
    //     invMat[0][1] = -1/ det * mat[0][1];
    //     invMat[1][0] = -1/ det * mat[1][0];
    //     invMat[1][1] = 1/ det * mat[0][0];

    //     return invMat;

    // }


    // void Element::WW(Real diffElement, Real cofvar, MatrixReal& elemMatrix){

    // 	Real coeff;
    //     // Real cofvar = FEMProblem::A00(point);

    // 	for (int i = 0; i < nodes.size() ; i++) {
    //     	coeff = diffElement*cofvar*valBase[i];
    //     	for (int j = 0 ; j < nodes.size() ; j++) {
    //       		elemMatrix[i][j] = elemMatrix[i][j] + coeff*valBase[j];
    //     	}
    //   	}
    // }

    // void Element::W(Real diffElement, Real cofvar, VectorReal& fElem){
    //     for (int i = 0 ; i < nodes.size() ; i++) {
    //         fElem[i] += diffElement * cofvar * valBase[i];
    //   	}
    // }

    // void Element::ADWDW(Real diffElement, VectorReal point, MatrixReal cofvar, MatrixReal matInv, MatrixReal& elemMatrix){

    //     int i, j, alpha, beta;
    // 	for (i = 0 ; i < nodes.size() ; i++) {
    //     	for (j = 0 ; j < nodes.size() ; j++) {
    //     		for(alpha = 0 ; alpha < 2 ; alpha++){
    //                 float pdscai = prodScal(valDerBase, matInv, alpha, j);
                    
    //     			for(beta = 0 ; beta < 2 ; beta++){
    //                     float pdscaj = prodScal(valDerBase, matInv, beta, i);
    //       				elemMatrix[i][j] += diffElement * cofvar[alpha][beta] * pdscai * pdscaj;
    //       			}
    //       		}
    //     	}
    //   	}

    // }

    // Real Element::prodScal(MatrixReal Mat1, MatrixReal Mat2, int indiceAB, int indiceIJ){
    //     float somme = 0;
    //     for(int k = 0 ; k < 2 ; k++){
    //         somme += Mat1[indiceIJ][k]*Mat2[indiceAB][k];
    //     }
    //     return somme;
    // }


    // int Element::returnQ(std::string type){
    // 	if(type == "Q1"){
    // 		return 9;
    // 	}
    // 	else if(type == "T1"|| type == "S1"){
    // 		return 3;
    // 	}
    //     return 0;
    // }



    // void Element::intAret(MatrixReal& elemMatrix, VectorReal& fElem, std::vector<Node> coordAret){

    //     // TO DO : MOVE IN Edge class ??

    //     int d = 1;
        
    //     int q = returnQ("S1");
        
    //     quadraMethodS1.weightsPoints("S1");
        
        
    //     for(int indicepts = 0 ; indicepts < q ; indicepts ++){
            
    //         std::vector<Node> pts = quadraMethodS1.getPoints();
    //         VectorReal pds = quadraMethodS1.getWeights();

    //         baseFunctions(pts[indicepts]);

    //         baseDerFunctions(pts[indicepts]);
            
    //         MatrixReal Jcob = matJacob(coordAret);
            
    //         VectorReal imagPoint = transFK(coordAret);

    //         Real eltdif = pds[indicepts] * std::sqrt(Jcob[0][0]*Jcob[0][0] + Jcob[0][1]*Jcob[0][1]);
            
    //         Real cofvarWW = FEMProblem::BN(imagPoint);
            
    //         WW(eltdif, cofvarWW, elemMatrix);
            

    //         // TODO BRING THE NUMBER OF AR ET ?
    //         int numAret = 1; // ?
    //         Real cofvarW = FEMProblem::FN(imagPoint, numAret);

    //         W(eltdif, cofvarW, fElem);
            
    //     }

    // }

