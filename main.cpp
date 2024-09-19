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

#include "forfun.h"

using namespace std;

void fromNOSStoOSS(int& NbLign, std::vector<int>& AdPrCoefLi, std::vector<int>& NumCol, std::vector<int>& AdSuccLi, std::vector<double>& Matrice, 
            std::vector<double>& SecMembre, std::vector<int>& NumDLDir, std::vector<double>& ValDLDir, std::vector<int>& NumColO, std::vector<double>& MatriceO){
        
    std::cout << "-- Non-Ordered Sparse Storage to Ordered Sparse Storage... -- " << std::endl << std::endl;

    FEMAssembly::cdesse(NbLign, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir, AdPrCoefLi, NumColO, MatriceO, SecMembre);
    
}

void fromOSStoPR(const int NbLign, int& NbCoeff, std::vector<int>& AdPrCoefLiO, std::vector<double>& MatriceO, std::vector<int>& NumColO, 
            std::vector<double>& MatProf, std::vector<int>& Profil){

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

void decompLU(int NbLign, int NbCoeff, std::vector<double>& MatProf, std::vector<int>& Profil, std::vector<double>& U, std::vector<double>& SecMembre){
    
    std::cout << "-- LU Decomposition and resolution... -- " << std::endl << std::endl;

    std::vector<double> ld(NbLign, 0.0);
    std::vector<double> ll(NbCoeff, 0.0);
    
    double eps = 0.0001;

    std::vector<double> Y(NbLign, 0.0);

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

    std::vector<double>& A = solver.getA();
    std::vector<double>& b = solver.getb();

    int nbLign = solver.getNbLign();
    int nbCoeff = solver.getNbCoeff();


    std::vector<int>& AdPrCoefLi = solver.getAdPrCoefLi();
    std::vector<int>& NumCol = solver.getNumCol();
    
    std::vector<int>& AdSuccLi = solver.getAdSuccLi();
    std::vector<int>& NumDLDir = solver.getNumDLDir();
    std::vector<double>& ValDLDir = solver.getValDLDir();
    
    std::vector<double> MatriceO(nbCoeff+nbLign, 0.0);
    std::vector<int> NumColO(nbCoeff, 0);


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

    std::vector<double> MatProf;
    std::vector<int> Profil(nbLign, 0);

    fromOSStoPR(nbLign, nbCoeff, AdPrCoefLi, MatriceO, NumColO, MatProf, Profil);

    MatriceO.clear();
    MatriceO.shrink_to_fit();

    NumColO.clear();
    NumColO.shrink_to_fit();

    std::vector<double> U(nbLign, 0.0);

    decompLU(nbLign, nbCoeff, MatProf, Profil, U, b);


    FEMUtilities::saveResults(U, secondArgument);

    std::cout << "-------- End of the simulation --------" << endl << endl;

    return 0;
}