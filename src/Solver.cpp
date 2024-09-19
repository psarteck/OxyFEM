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
#include "Solver.hpp"
#include "System.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <vector>



Solver::Solver(Mesh& mesh_, FEMParameters parameters_) : 
                mesh(mesh_), 
                parameters(parameters_),
                elementList(mesh_.getElements()),
                edgeList(mesh_.getEdges())
                {
    ptsNb = mesh.getNodesNumber();

    NbLine = ptsNb;

    NbCoeff = 0;
    for(int i = 0 ; i < NbLine ; i++){
        NbCoeff += i;
    }

    A = VectorReal(NbLine + NbCoeff, 0.0);
    b = VectorReal(NbLine, 0.0);

    AdPrCoefLi = VectorInt(NbLine, 0);
    AdSuccLi = VectorInt(NbCoeff, 0);
    NumCol = VectorInt(NbCoeff, -1);
    NumDLDir = VectorInt(NbLine, 0);
    ValDLDir = VectorReal(NbLine, 0.0);

    NextAd = 1;

    for(int i = 0 ; i < NumDLDir.size() ;i++){
        NumDLDir[i] = i + 1; 
    }

    system = std::make_unique<System>(ptsNb);

}

void Solver::assemble(){
    
    std::cout << endl << "--- Assembling the matrix : -----" << std::endl;

//Integrate on the elements
    int nbElements = elementList.size();
    float current = 1.0;

    std::cout << std::endl << "Integrate on the elements ... " << std::endl;

    for(auto element : elementList){
        float percentage = current / nbElements;
        FEMUtilities::showProgress(percentage);
        current += 1.0;
        int I, J;
        const VectorInt& nodesIds = element.getNodeIDs();
        int nodePerElement = element.getNodeNumber();
        MatrixReal MatElem(nodePerElement, VectorReal(nodePerElement, 0.0));

        VectorReal SMbrElem(nodePerElement, 0.0);
    
        element.intElem(MatElem, SMbrElem);

        for (int i = 0 ; i < nodePerElement ; i++) {
            I = nodesIds[i];

            b[I-1] += SMbrElem[i];

            for(int j = 0 ; j <= i ; j++){
                J = nodesIds[j];

                Real value = MatElem[i][j];

                if(I > J){
                    assmat(I,J,value, AdPrCoefLi, NumCol, AdSuccLi, A,  NbLine, NextAd);
                }
                else if(I < J){
                    assmat(J,I,value, AdPrCoefLi, NumCol, AdSuccLi, A,  NbLine, NextAd);
                }
                else {
                    A[I-1] += MatElem[i][j];
                }
            }


        }
    }
    
    AdPrCoefLi[NbLine-1] = NextAd;
    std::cout << std::endl << std::endl << "Integrate on the edges ... " << std::endl;

    nbElements = edgeList.size();
    current = 1.0;

    for(auto edge : edgeList){
        float percentage = current / nbElements;
        FEMUtilities::showProgress(percentage);
        current += 1.0;

        int nodeNumberAret = edge.getNodeNumber();
        const VectorInt& nodesIds = edge.getNodeIDs();

        if(isDir0Edge(edge.getLabel())){

            for(int i = 0 ; i < nodeNumberAret ; i++){
                int I = nodesIds[i];
                NumDLDir[I-1] = 0;
                ValDLDir[I-1] = 0;
            }
        }
        else if(isDirNHEdge(edge.getLabel())){

            for(int i = 0 ; i < nodeNumberAret ; i++){
                int I = nodesIds[i];
                NumDLDir[I-1] = -I;
                ValDLDir[I-1] = FEMProblem::UD(edge.getNodeAt(i));
            }
        }
        else if(isNeumannEdge(edge.getLabel())){
            //(TODO) Need to understand how assmat works 
            int nbOfNode = edge.getNodeNumber();

            MatrixReal matAret(nbOfNode, VectorReal(nbOfNode, 0.0));
            VectorReal fAret(nbOfNode, 0.0);

            edge.intAret(matAret, fAret);

            for (int i = 0 ; i < nbOfNode ; i++) {
                int I = nodesIds[i];
                b[I-1] += fAret[i];

                for(int j = 0 ; j <= i ; j++){
                    int J = nodesIds[j];

                    float value = matAret[i][j];
                    
                    if(I > J){
                        assmat(I,J,value, AdPrCoefLi, NumCol, AdSuccLi, A, NbLine, NextAd);
                    }
                    else if(I < J){
                        assmat(J,I,value, AdPrCoefLi, NumCol, AdSuccLi, A, NbLine, NextAd);
                    }
                    else {
                        A[I-1] += matAret[i][j];
                    }
                }
            }

        }
        else {
            std::cerr << "Edge label " << edge.getLabel() << " is not correct." << std::endl;
        }

    }

    std::cout << std::endl << std::endl << "Assembling done." << std::endl;
    std::cout << "---------------------------------" << std::endl << std::endl;

}


void Solver::fromNOSStoOSS(){
        
    std::cout << "-- Non-Ordered Sparse Storage to Ordered Sparse Storage... -- " << std::endl << std::endl;

    MatriceO = VectorReal(NbLine + NbCoeff, 0.0);
    NumColO = VectorInt(NbCoeff, 0);

    FEMAssembly::cdesse(NbLine, AdPrCoefLi, NumCol, AdSuccLi, A, b, NumDLDir, ValDLDir, AdPrCoefLi, NumColO, MatriceO, b);

    A.clear();
    A.shrink_to_fit();

    AdSuccLi.clear();
    AdSuccLi.shrink_to_fit();

    NumCol.clear();
    NumCol.shrink_to_fit();

    NumDLDir.clear();
    NumDLDir.shrink_to_fit();

    ValDLDir.clear();
    ValDLDir.shrink_to_fit();
    
}

void Solver::fromOSStoPR() {

    std::cout << "-- Ordered Sparse Storage to Profil Storage... -- " << std::endl << std::endl;

    Profil = VectorInt(NbLine, 0);

    int matSize = 1;
    Profil[0] = 1;
    for (int i = 1 ; i < NbLine ; i ++){
        if(AdPrCoefLi[i-1]!=AdPrCoefLi[i]){
            matSize += i+1 - NumColO[AdPrCoefLi[i-1]-1];
        }
        Profil[i] = matSize;
    }
    NbCoeff = matSize-1;

    MatProf.resize(NbLine+matSize-1);

    for (int i = 0 ; i < NbLine+matSize ; i ++){
        MatProf[i] = 0;
    }
    for (int i = 0 ; i < NbLine ; i ++){
        MatProf[i] = MatriceO[i];
    }
    
    for(int i = 0 ; i < NbLine-1 ; i ++){
        for(int j = AdPrCoefLi[i] ; j < AdPrCoefLi[i+1] ; j++){
            MatProf[NbLine+Profil[i]-1+NumColO[j-1]-NumColO[AdPrCoefLi[i]-1]]  = MatriceO[j-1+NbLine];
        }
    }

    MatriceO.clear();
    MatriceO.shrink_to_fit();

    NumColO.clear();
    NumColO.shrink_to_fit();
    
}


void Solver::decompLU() {
    
    std::cout << "-- LU Decomposition and resolution... -- " << std::endl << std::endl;

    U = VectorReal(NbLine, 0.0);

    VectorReal ld(NbLine, 0.0);
    VectorReal ll(NbCoeff, 0.0);
    
    Real eps = 0.0001;

    VectorReal Y(NbLine, 0.0);

    FEMAssembly::ltlpr(NbLine, Profil, MatProf.begin(), MatProf.begin() + NbLine, eps, ld, ll);

    FEMAssembly::rsprl(NbLine, Profil.begin(), ld.begin(), ll, b.begin(), Y.begin());

    FEMAssembly::rspru(NbLine, Profil, ld, ll, Y, U);

}


bool Solver::isNeumannEdge(const int labelEdge){
    for(auto label : parameters.getNeumannLabels()){
        if(labelEdge == std::stoi(label)){
            return true;
        }
    }
    return false;
}

bool Solver::isDir0Edge(const int labelEdge){
    for(auto label : parameters.getHomogeneousDirichletLabels()){
        if(labelEdge == std::stoi(label)){
            return true;
        }
    }
    return false;
}

bool Solver::isDirNHEdge(const int labelEdge){
    for(auto label : parameters.getDirichletLabels()){
        if(labelEdge == std::stoi(label)){
            return true;
        }
    }
    return false;
}


void Solver::assmat(int I, int J, Real X, VectorInt& ADPRCL, VectorInt& NUMCOL, 
            VectorInt& ADSUCL, VectorReal& LMATRI, int& nbLign, int& NEXTAD) {

    
    int IAD, NXT;

    if (I <= J) {
        std::cerr << "*Bug* La procedure AssMat n'est utilisee que pour l'assemblage de la partie triangulaire stricte. Vous etes sur le coefficient (" << I << "," << J << ")." << std::endl;
        return;
    }

    IAD = ADPRCL[I - 2];
    if (IAD > 0) {
        while (NUMCOL[IAD - 1] != J) {
            NXT = ADSUCL[IAD - 1];
            if (NXT <= 0) {
                break;
            }
            IAD = NXT;
        }

        if (NUMCOL[IAD - 1] == J) {
            LMATRI[IAD - 1 + nbLign] += X;
            return;
        }

        ADSUCL[IAD - 1] = NEXTAD;
    } else {
        ADPRCL[I - 2] = NEXTAD;
    }

    NUMCOL[NEXTAD - 1] = J;
    LMATRI[NEXTAD - 1 + nbLign] = X;
    ADSUCL[NEXTAD - 1] = 0;
    NEXTAD += 1;
}


void Solver::printB(){
    std::cout << "Second member b : \n";
    for(auto el : b){
        std::cout << el << " ";
    }
    std::cout << endl;
}


void Solver::printA(){
    
    std::cout << "Matrix A : \n";

    for(auto it : A){
        cout << it << " ";
    }
}

void Solver::printU(){

    std::cout << "Vector U : \n";

    for(auto it : U){
        cout << it << " ";
    }
}



