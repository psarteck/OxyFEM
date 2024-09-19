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
#include "FEMAssembly.hpp"


    class Solver {

        private : 

            std::unique_ptr<System> system;

            VectorReal A;
            VectorReal b;

            VectorInt AdPrCoefLi;
            VectorInt AdSuccLi;
            VectorInt NumDLDir;
            VectorReal ValDLDir;
            VectorInt NumCol;

            VectorReal MatriceO;
            VectorInt NumColO;

            VectorReal MatProf;
            VectorInt Profil;

            VectorReal U;


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

            void fromNOSStoOSS();

            void fromOSStoPR(); 

            void decompLU();


            bool isNeumannEdge(const int labelEdge);
            
            bool isDir0Edge(const int labelEdge);
            
            bool isDirNHEdge(const int labelEdge);



            void assmat(int I, int J, Real X, VectorInt& ADPRCL, VectorInt& NUMCOL, 
            VectorInt& ADSUCL, VectorReal& LMATRI, int& nbLign, int& NEXTAD);


            void printB();
            void printA();
            void printU();

            VectorReal& getU(){return U;}


    };

#endif
