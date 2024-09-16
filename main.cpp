#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <Eigen/Dense>
#include <vector>

#include "Mesh.hpp"
#include "Node.hpp"
#include "FEMParameters.hpp"
#include "Solver.hpp"
#include "Mesh.hpp"
#include "Solver.hpp"
#include "include/FEMParameters.hpp"
#include "include/Solver.hpp"

#include "forfun.h"

using namespace std;


void dSMDaSMO(int NbLign, int AdPrCoefLi[], int NumCol[], int AdSuccLi[], float Matrice[], 
            float SecMembre[], int NumDLDir[], float ValDLDir[], int NumColO[], float MatriceO[]){
    
    
    cdesse_(&NbLign, AdPrCoefLi, NumCol, AdSuccLi, Matrice,SecMembre, NumDLDir, ValDLDir, AdPrCoefLi, NumColO, MatriceO, SecMembre);
    
    
}


void dSMOaPR(int NbLign, int *NbCoeff, int AdPrCoefLiO[], float MatriceO[], int NumColO[], 
            float **MatProf, int Profil[]){
    
    int tailleMat = 1;
    Profil[0] = 1;
    for (int i = 1 ; i < NbLign ; i ++){
        if(AdPrCoefLiO[i-1]!=AdPrCoefLiO[i]){
            tailleMat += i+1 - NumColO[AdPrCoefLiO[i-1]-1];
        }
        Profil[i] = tailleMat;
    }
    *NbCoeff = tailleMat-1;

    *MatProf = new float[NbLign+tailleMat-1];

    for (int i = 0 ; i < NbLign+tailleMat ; i ++){
        (*MatProf)[i] = 0;
    }
    for (int i = 0 ; i < NbLign ; i ++){
        (*MatProf)[i] = MatriceO[i];
    }
    
    for(int i = 0 ; i < NbLign-1 ; i ++){
        for(int j = AdPrCoefLiO[i] ; j < AdPrCoefLiO[i+1] ; j++){
            (*MatProf)[NbLign+Profil[i]-1+NumColO[j-1]-NumColO[AdPrCoefLiO[i]-1]]  = MatriceO[j-1+NbLign];
        }
    }
    
    
}


void decompLU(int NbLign, int NbCoeff, float MatProf[], int Profil[], float U[], float SecMembre[]){
    
    float *ld = new float[NbLign];
    float *ll = new float[NbCoeff];
    
    float eps = 0.0001;

    float *Y = new float[NbLign];

    ltlpr_(&NbLign, Profil, &MatProf[0], &MatProf[NbLign], &eps, ld, ll);
    rsprl_(&NbLign, Profil, ld, ll, SecMembre, Y);
    rspru_(&NbLign, Profil, ld, ll, Y, U);

    free(ld);
    free(ll);
    free(Y);
}


float* vectorToArray(std::vector<double>& vec, size_t startIndex = 0) {
    // Allouer un tableau dynamique de la même taille que le vecteur
    float* array = new float[vec.size()];

    // Copier les éléments du vecteur dans le tableau
    std::copy(vec.begin() + startIndex, vec.end(), array);

    return array;  // Retourner le pointeur vers le tableau
}

int* vectorToArray(std::vector<int>& vec) {
    // Allouer un tableau dynamique de la même taille que le vecteur
    int* array = new int[vec.size()];

    // Copier les éléments du vecteur dans le tableau
    std::copy(vec.begin(), vec.end(), array);

    return array;  // Retourner le pointeur vers le tableau
}


int main(){

    FEMParameters parameters;
    Mesh mesh;

    bool meshOk = mesh.loadMsh(parameters.getMeshName());
    if(!meshOk){
        cout << "Problem reading the mesh " << endl;
    }
    // mesh.printMesh();

    Solver solver(mesh, parameters);

    solver.assemble();

    std::vector<double> Ad = solver.getA();
    std::vector<double> bd = solver.getb();

    float* A = vectorToArray(Ad, 0);
    float* b = vectorToArray(bd, 0);

    int nbLign = solver.getNbLign();
    int nbCoeff = solver.getNbCoeff();


    std::vector<int>& dAdPrCoefLi = solver.getAdPrCoefLi();
    std::vector<int>& dNumCol = solver.getNumCol();
    
    std::vector<int>& dAdSuccLi = solver.getAdSuccLi();
    std::vector<int>& dNumDLDir = solver.getNumDLDir();
    std::vector<double>& dValDLDir = solver.getValDLDir();

    int* AdPrCoefLi = vectorToArray(dAdPrCoefLi);
    int* NumCol = vectorToArray(dNumCol);
    int* AdSuccLi = vectorToArray(dAdSuccLi);
    int* NumDLDir = vectorToArray(dNumDLDir);
    float* ValDLDir = vectorToArray(dValDLDir);


    float* MatriceO = new float[nbLign+nbCoeff];
    int* NumColO = new int[nbCoeff];
    
    dSMDaSMO(nbLign, AdPrCoefLi, NumCol, AdSuccLi, A, b, NumDLDir, ValDLDir, NumColO, MatriceO);

    float *MatProf;
    
    int *Profil = new int[nbLign];

    dSMOaPR(nbLign, &nbCoeff, AdPrCoefLi, MatriceO, NumColO, &MatProf, Profil);


    float *U = new float[nbLign];

    decompLU(nbLign, nbCoeff, MatProf, Profil, U, b);

    std::vector<double> x(nbLign, 0.0);

    for(int i = 0 ; i < nbLign ; i++){
        x[i] = U[i];
    }

    FEMUtilities::saveResults(x, "/Users/djo/Desktop/MEF/C++/results/simu1.txt");


    // Eigen::MatrixXd lower = FEMUtilities::mat2Eigen(solver.getA());
    // Eigen::VectorXd b = FEMUtilities::vec2Eigen(solver.getb());

    // Eigen::MatrixXd A = lower.selfadjointView<Eigen::Upper>();


    // Eigen::VectorXd x = A.fullPivLu().solve(b);    

    // printf("Size : %td", x.size());

    // FEMUtilities::saveResults(x, "results/simu1.txt");

    return 0;
}