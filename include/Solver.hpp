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
#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include "Mesh.hpp"
#include "FEMParameters.hpp"
#include "Types.hpp"
#include "System.hpp"


    class Solver {

        private : 

            std::unique_ptr<System> system;

            std::vector<double> A;
            std::vector<double> b;

            std::vector<std::vector<double> > A2;
            std::vector<double> b2;

            std::vector<double> SecMember;

            std::vector<int> AdPrCoefLi;
            std::vector<int> NumDLDir;
            std::vector<int> AdSuccLi;
            std::vector<int> NumCol;

            std::vector<double> ValDLDir;
            int NextAd;

            int ptsNb; 
            int NbLine;
            int NbCoeff;

            Mesh mesh;
            const std::vector<Element>& elementList;
            const std::vector<Edge>& edgeList;
            FEMParameters parameters;
            
        public : 
            Solver(Mesh& mesh_, FEMParameters parameters_);

            void assemble();

            bool isNeumannEdge(const int labelEdge);
            
            bool isDir0Edge(const int labelEdge);
            
            bool isDirNHEdge(const int labelEdge);



            // void assmat(int I, int J, double X, std::vector<int>& AdPrCoefLi, std::vector<int>& NumCol,
            //     std::vector<int>& AdSuccLi, std::vector<double>& Matrice, int& NextAd);

            void assmat(int I, int J, double X, std::vector<int>& ADPRCL, std::vector<int>& NUMCOL, 
            std::vector<int>& ADSUCL, std::vector<double>& LMATRI, int& nbLign, int& NEXTAD);

            void AFFSMD();

            void printB();
            void printA();

            std::vector<std::vector<double> >& getA2(){return A2;}
            std::vector<double>& getA(){return A;}
            std::vector<double>&  getb(){return b;}

            std::vector<int>&  getAdPrCoefLi(){return AdPrCoefLi;}
            std::vector<int>& getNumDLDir(){return NumDLDir;}
            std::vector<int>& getAdSuccLi(){return AdSuccLi;}
            std::vector<int>& getNumCol(){return NumCol;}
            std::vector<double>& getValDLDir(){return ValDLDir;}


            int& getNbLign(){return NbLine;}
            int& getNbCoeff(){return NbCoeff;}


            // (TODO)
            int* vectorToArray(const std::vector<int>& vec);
            float* vectorToArray(const std::vector<double>& vec, size_t startIndex);
    };

#endif
