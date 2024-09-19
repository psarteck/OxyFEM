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

            VectorReal A;
            VectorReal b;

            MatrixReal A2;
            VectorReal b2;

            VectorReal SecMember;

            VectorInt AdPrCoefLi;
            VectorInt NumDLDir;
            VectorInt AdSuccLi;
            VectorInt NumCol;

            VectorReal ValDLDir;
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



            // void assmat(int I, int J, Real X, VectorInt& AdPrCoefLi, VectorInt& NumCol,
            //     VectorInt& AdSuccLi, VectorReal& Matrice, int& NextAd);

            void assmat(int I, int J, Real X, VectorInt& ADPRCL, VectorInt& NUMCOL, 
            VectorInt& ADSUCL, VectorReal& LMATRI, int& nbLign, int& NEXTAD);

            void AFFSMD();

            void printB();
            void printA();

            MatrixReal& getA2(){return A2;}
            VectorReal& getA(){return A;}
            VectorReal&  getb(){return b;}

            VectorInt&  getAdPrCoefLi(){return AdPrCoefLi;}
            VectorInt& getNumDLDir(){return NumDLDir;}
            VectorInt& getAdSuccLi(){return AdSuccLi;}
            VectorInt& getNumCol(){return NumCol;}
            VectorReal& getValDLDir(){return ValDLDir;}


            int& getNbLign(){return NbLine;}
            int& getNbCoeff(){return NbCoeff;}


            // (TODO)
            int* vectorToArray(const VectorInt& vec);
            float* vectorToArray(const VectorReal& vec, size_t startIndex);
    };

#endif
