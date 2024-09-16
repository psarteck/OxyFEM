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
#include "forfun.h"


#define FORTRAN 0

float* Solver::vectorToArray(const std::vector<double>& vec, size_t startIndex) {
    // Allouer un tableau dynamique de la même taille que le vecteur
    float* array = new float[vec.size()];

    // Copier les éléments du vecteur dans le tableau
    std::copy(vec.begin() + startIndex, vec.end(), array);

    return array;  // Retourner le pointeur vers le tableau
}

int* Solver::vectorToArray(const std::vector<int>& vec) {
    // Allouer un tableau dynamique de la même taille que le vecteur
    int* array = new int[vec.size()];

    // Copier les éléments du vecteur dans le tableau
    std::copy(vec.begin(), vec.end(), array);

    return array;  // Retourner le pointeur vers le tableau
}

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

    A = std::vector<double>(NbLine + NbCoeff, 0.0);
    b = std::vector<double>(NbLine, 0.0);

    A2 = std::vector<std::vector<double> >(NbLine, std::vector<double>(NbLine, 0.0));
    b2 = std::vector<double>(NbLine, 0.0);


    AdPrCoefLi = std::vector<int>(NbLine, 0);
    NumDLDir = std::vector<int>(NbLine, 0);
    ValDLDir = std::vector<double>(NbLine, 0.0);

    AdSuccLi = std::vector<int>(NbCoeff, 0);
    NumCol = std::vector<int>(NbCoeff, -1);

    NextAd = 1;

    for(int i = 0 ; i < NumDLDir.size() ;i++){
        NumDLDir[i] = i + 1; 
    }

    system = std::make_unique<System>(ptsNb);

}

void Solver::assemble(){
    
    cout << "\nAssembling the matrix : ..." << endl;

//Integrate on the elements
    for(auto element : elementList){
        int I, J;
        const std::vector<int>& nodesIds = element.getNodeIDs();
        int nodePerElement = element.getNodeNumber();
        std::vector<std::vector<double> > MatElem(nodePerElement, std::vector<double>(nodePerElement, 0.0));

        std::vector<double> SMbrElem(nodePerElement, 0.0);
    
        element.intElem(MatElem, SMbrElem);

        for (int i = 0 ; i < nodePerElement ; i++) {
            I = nodesIds[i];

            b[I-1] += SMbrElem[i];

            for(int j = 0 ; j <= i ; j++){
                J = nodesIds[j];

                int* tabAdPrCoefLi = vectorToArray(AdPrCoefLi);
                int* tabNumCol = vectorToArray(NumCol);
                int* tabAdSuccLi = vectorToArray(AdSuccLi);
                float* tabA = vectorToArray(A, NbLine);

                float value = MatElem[i][j];

                if(I > J){
#if FORTRAN == 1
                    assmat_(&I,&J,&value, tabAdPrCoefLi, tabNumCol, tabAdSuccLi, tabA, &NextAd);
#else 
                    assmat(I,J,value, AdPrCoefLi, NumCol, AdSuccLi, A,  NbLine, NextAd);
#endif
                }
                else if(I < J){
#if FORTRAN == 1
                    assmat_(&J,&I,&value, tabAdPrCoefLi, tabNumCol, tabAdSuccLi, tabA, &NextAd);
#else
                    assmat(J,I,value, AdPrCoefLi, NumCol, AdSuccLi, A,  NbLine, NextAd);
#endif
                }
                else {
                    A[I-1] += MatElem[i][j];
                }
#if FORTRAN == 1
                for(int i =  NbLine ; i < A.size(); i++){
                    A[i] = tabA[i-NbLine];
                }
                for(int i =  0 ; i < AdPrCoefLi.size(); i++){
                    AdPrCoefLi[i] = tabAdPrCoefLi[i];
                }
                for(int i =  0 ; i < NumCol.size(); i++){
                    NumCol[i] = tabNumCol[i];
                }
                for(int i =  0 ; i < AdSuccLi.size(); i++){
                    AdSuccLi[i] = tabAdSuccLi[i];
                }
#endif
            }


        }
    }

    AdPrCoefLi[NbLine-1] = NextAd;

    for(auto edge : edgeList){
        int nodeNumberAret = edge.getNodeNumber();
        const std::vector<int>& nodesIds = edge.getNodeIDs();

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

            std::vector<std::vector<double>> matAret(nbOfNode, std::vector<double>(nbOfNode, 0.0));
            std::vector<double> fAret(nbOfNode, 0.0);

            edge.intAret(matAret, fAret);

            for (int i = 0 ; i < nbOfNode ; i++) {
                int I = nodesIds[i];
                b[I-1] += fAret[i];

                for(int j = 0 ; j <= i ; j++){
                    int J = nodesIds[j];

                    int* tabAdPrCoefLi = vectorToArray(AdPrCoefLi);
                    int* tabNumCol = vectorToArray(NumCol);
                    int* tabAdSuccLi = vectorToArray(AdSuccLi);
                    float* tabA = vectorToArray(A, NbLine);

                    float value = matAret[i][j];
                    
                    if(I > J){
#if FORTRAN == 1
                        assmat_(&I,&J,&value, tabAdPrCoefLi, tabNumCol, tabAdSuccLi, tabA, &NextAd);
#else
                        assmat(I,J,value, AdPrCoefLi, NumCol, AdSuccLi, A, NbLine, NextAd);
#endif
                    }
                    else if(I < J){
#if FORTRAN == 1
                        assmat_(&J,&I,&value, tabAdPrCoefLi, tabNumCol, tabAdSuccLi, tabA, &NextAd);
#else
                        assmat(J,I,value, AdPrCoefLi, NumCol, AdSuccLi, A, NbLine, NextAd);
#endif
                    }
                    else {
                        A[I-1] += matAret[i][j];
                    }
#if FORTRAN == 1
                    for(int i =  NbLine ; i < A.size(); i++){
                        A[i] = tabA[i-NbLine];
                    }
                    for(int i =  0 ; i < AdPrCoefLi.size(); i++){
                        AdPrCoefLi[i] = tabAdPrCoefLi[i];
                    }
                    for(int i =  0 ; i < NumCol.size(); i++){
                        NumCol[i] = tabNumCol[i];
                    }
                    for(int i =  0 ; i < AdSuccLi.size(); i++){
                        AdSuccLi[i] = tabAdSuccLi[i];
                    }
#endif
                }
            }

        }
        else {
            std::cerr << "Edge label " << edge.getLabel() << " is not correct." << std::endl;
        }

    }

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


void Solver::assmat(int I, int J, double X, std::vector<int>& ADPRCL, std::vector<int>& NUMCOL, 
            std::vector<int>& ADSUCL, std::vector<double>& LMATRI, int& nbLign, int& NEXTAD) {

    
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


// void Solver::assmat(int I, int J, double X, std::vector<int>& AdPrCoefLi, std::vector<int>& NumCol,
//             std::vector<int>& AdSuccLi, std::vector<double>& Matrice, int& NextAd) {

//     if (I <= J) {
//         // (TODO)
//         std::cout << "*Bug* The assmat function n'est utilisée que pour l'assemblage de la partie triangulaire stricte. Vous êtes sur le coefficient (" << I << "," << J << ")." << std::endl;
//         exit(EXIT_FAILURE);
//     }
//     int IAD = AdPrCoefLi[I - 2];
//     // cout << "IAD : " << IAD << endl;
//     if (IAD > 0) {
//         // La ligne I a déjà été rencontrée : recherche de la colonne J
//         while (NumCol[IAD - 1] != J) {
//             // Parcours des éléments de la ligne I
//             int NXT = AdSuccLi[IAD];
//             cout << "NXT " << NXT << endl;
//             if (NXT <= 0)
//                 break;
//             IAD = NXT;
            
//         }

//         // L'élément A(i,j) existe : on l'incrémente et on sort
//         Matrice[IAD -1] += X;
//         // *(Matrice + IAD - 1) += X;
//         return;
//     } else {
//         // Création de la ligne I
//         AdPrCoefLi[I - 1] = NextAd;
//     }

//     // Création de la colonne J
//     AdSuccLi[IAD] = NextAd;

//     // Création du coefficient A(i,j) (nouvelle ligne ou colonne)
//     NumCol[NextAd - 1] = J;
//     // *(Matrice + NextAd - 1) = X;
//     Matrice[NextAd - 1] = X;
//     AdSuccLi[NextAd - 1] = 0;
//     NextAd++;
// }


void Solver::printB(){
    std::cout << "Second member b : \n";
    for(auto el : b){
        std::cout << el << " ";
    }
    std::cout << endl;
}


void Solver::printA(){
    std::cout << "Matrix A : \n";

    // for(int i = 0 ; i < NbLine ; i++){
    //     for(int j = 0 ; j < i ; j++){
    //         cout << A[NbLine+j+NbLine*i] << " ";
    //     } 
    //     cout << A[i] << endl;
    // }    
    for(auto it : A){
        cout << it << " ";
    }
}




void Solver::AFFSMD() {
    int Lmin, Lmax;

    std::cout << "****** Affichage de la S.M.D. ******" << std::endl;

    do {
        std::cout << "Donner, dans l'intervalle [1," << NbLine << "], les indices min et max des lignes à afficher. Taper q pour arrêter." << std::endl;
        std::cin >> Lmin;
        if (std::cin.fail()) {
            // Gestion de l'entrée non valide (q pour quitter)
            std::cin.clear();  // Réinitialiser le flux d'entrée
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignorer la ligne invalide
            break;
        }
        std::cin >> Lmax;

        if (Lmin > Lmax || Lmin < 1 || Lmax > NbLine) {
            std::cout << "Indices invalides. Réessayez." << std::endl;
        } else {
            std::cout << std::endl;
            for (int i = Lmin; i <= Lmax; ++i) {
                std::cout << "Ligne " << i << ": SecMbr " << b[i] << std::endl;
                // std::cout << "Ligne " << i << ": SecMbr " << b[i] << " Nuddir " << NumDLDir[i] << " Valdir " << ValDLDir[i] << std::endl;
            }

            std::cout << "=== MATRICE ===========================" << std::endl;
            if (Lmin == 1) {
                std::cout << "--- Ligne 1 ---" << std::endl;
                std::cout << "Col 1 : " << A[0] << std::endl;
                Lmin = 2;
            }

            for (int i = Lmin; i <= Lmax; ++i) {
                std::cout << "--- Ligne " << i << " ---" << std::endl;
                int j = AdPrCoefLi[i - 1];
                while (j != 0) {
                    std::cout << "Col " << NumCol[j] << " : " << A[NbLine + j] << std::endl;
                    j = AdSuccLi[j];
                }
                std::cout << "Col " << i << " : " << A[i] << std::endl;
            }
        }
    } while (true);
}



