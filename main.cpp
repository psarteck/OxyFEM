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
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <Eigen/Dense>
#include <vector>

#include "FEMAssembly.hpp"
#include "Mesh.hpp"
#include "Node.hpp"
#include "FEMParameters.hpp"
#include "Solver.hpp"
#include "Mesh.hpp"
#include "Solver.hpp"
#include "FEMParameters.hpp"
#include "Solver.hpp"

using namespace std;

void fromNOSStoOSS(int& NbLign, VectorInt& AdPrCoefLi, VectorInt& NumCol, VectorInt& AdSuccLi, VectorReal& Matrice, 
            VectorReal& SecMembre, VectorInt& NumDLDir, VectorReal& ValDLDir, VectorInt& NumColO, VectorReal& MatriceO){
        
    std::cout << "-- Non-Ordered Sparse Storage to Ordered Sparse Storage... -- " << std::endl << std::endl;

    FEMAssembly::cdesse(NbLign, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir, AdPrCoefLi, NumColO, MatriceO, SecMembre);
    
}

void fromOSStoPR(const int NbLign, int& NbCoeff, VectorInt& AdPrCoefLiO, VectorReal& MatriceO, VectorInt& NumColO, 
            VectorReal& MatProf, VectorInt& Profil){

    std::cout << "-- Ordered Sparse Storage to Profil Storage... -- " << std::endl << std::endl;

    int matSize = 1;
    Profil[0] = 1;
    for (int i = 1 ; i < NbLign ; i ++){
        if(AdPrCoefLiO[i-1]!=AdPrCoefLiO[i]){
            matSize += i+1 - NumColO[AdPrCoefLiO[i-1]-1];
        }
        Profil[i] = matSize;
    }
    NbCoeff = matSize-1;

    MatProf.resize(NbLign+matSize-1);

    for (int i = 0 ; i < NbLign+matSize ; i ++){
        MatProf[i] = 0;
    }
    for (int i = 0 ; i < NbLign ; i ++){
        MatProf[i] = MatriceO[i];
    }
    
    for(int i = 0 ; i < NbLign-1 ; i ++){
        for(int j = AdPrCoefLiO[i] ; j < AdPrCoefLiO[i+1] ; j++){
            MatProf[NbLign+Profil[i]-1+NumColO[j-1]-NumColO[AdPrCoefLiO[i]-1]]  = MatriceO[j-1+NbLign];
        }
    }
    
    
}

void decompLU(int NbLign, int NbCoeff, VectorReal& MatProf, VectorInt& Profil, VectorReal& U, VectorReal& SecMembre){
    
    std::cout << "-- LU Decomposition and resolution... -- " << std::endl << std::endl;

    VectorReal ld(NbLign, 0.0);
    VectorReal ll(NbCoeff, 0.0);
    
    Real eps = 0.0001;

    VectorReal Y(NbLign, 0.0);

    FEMAssembly::ltlpr(NbLign, Profil, MatProf.begin(), MatProf.begin() + NbLign, eps, ld, ll);

    FEMAssembly::rsprl(NbLign, Profil.begin(), ld.begin(), ll, SecMembre.begin(), Y.begin());

    FEMAssembly::rspru(NbLign, Profil, ld, ll, Y, U);

}


int main(int argc, char *argv[]){

    std::string defaultParam = "/Users/djo/Dev/OxyFEM/parameters.txt";
    std::string defaultSaveFile = "/Users/djo/Dev/OxyFEM/results/simu1.txt";
    std::string defaultMeshPath = "/Users/djo/Dev/OxyFEM/Meshs/";

    std::string firstArgument;
    std::string secondArgument;
    std::string thirdArgument;

    if (argc == 4){
        firstArgument = argv[1];
        secondArgument = argv[2];
        thirdArgument = argv[3];
    } else if (argc == 3) {
        firstArgument = argv[1];
        secondArgument = argv[2];
        thirdArgument = defaultMeshPath;
    } else if (argc == 2) {
        firstArgument = argv[1];
        secondArgument = defaultSaveFile;
        thirdArgument = defaultMeshPath;
    } else if (argc == 1) {
        firstArgument = defaultParam;
        secondArgument = defaultSaveFile;
        thirdArgument = defaultMeshPath;
    } else {
        std::cerr << "Too much arguments. Needed 2." << std::endl;
    }

    FEMParameters parameters(firstArgument);
    Mesh mesh;

    bool meshOk = mesh.loadMsh(thirdArgument + parameters.getMeshName());
    

    Solver solver(mesh, parameters);

    solver.assemble();

    VectorReal& A = solver.getA();
    VectorReal& b = solver.getb();

    int nbLign = solver.getNbLign();
    int nbCoeff = solver.getNbCoeff();


    VectorInt& AdPrCoefLi = solver.getAdPrCoefLi();
    VectorInt& NumCol = solver.getNumCol();
    
    VectorInt& AdSuccLi = solver.getAdSuccLi();
    VectorInt& NumDLDir = solver.getNumDLDir();
    VectorReal& ValDLDir = solver.getValDLDir();
    
    VectorReal MatriceO(nbCoeff+nbLign, 0.0);
    VectorInt NumColO(nbCoeff, 0);


    fromNOSStoOSS(nbLign, AdPrCoefLi, NumCol, AdSuccLi, A, b, NumDLDir, ValDLDir, NumColO, MatriceO);

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

    VectorReal MatProf;
    VectorInt Profil(nbLign, 0);

    fromOSStoPR(nbLign, nbCoeff, AdPrCoefLi, MatriceO, NumColO, MatProf, Profil);

    MatriceO.clear();
    MatriceO.shrink_to_fit();

    NumColO.clear();
    NumColO.shrink_to_fit();

    VectorReal U(nbLign, 0.0);

    decompLU(nbLign, nbCoeff, MatProf, Profil, U, b);


    FEMUtilities::saveResults(U, secondArgument);

    std::cout << "-------- End of the simulation --------" << endl << endl;

    return 0;
}