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
#include <unordered_map>

#include "Mesh.hpp"
#include "FEMParameters.hpp"
#include "Types.hpp"
#include "System.hpp"
#include "FEMAssembly.hpp"


    class Solver {

        private : 

            std::unique_ptr<System> system;

            // Matrix of the linear system
            VectorReal A;

            // Second member of the linear system
            VectorReal b;

            // Non Ordered Sparse Storage elements
            VectorInt AdPrCoefLi;
            VectorInt AdSuccLi;
            VectorInt NumDLDir;
            VectorReal ValDLDir;
            VectorInt NumCol;
            int NextAd;

            // Ordered Sparse Storage elements
            VectorReal MatriceO;
            VectorInt NumColO;

            // Profil Storage elements
            VectorReal MatProf;
            VectorInt Profil;

            // Solution of the linear system
            VectorReal U;

            // Number of nodes
            int ptsNb; 

            // Number of coefficient in the matrix diagonal
            int NbLine;
            // Number of coefficient in lower part of the system matrix
            int NbCoeff;

            // Mesh 
            Mesh mesh;

            // List of all elements in the mesh
            std::vector<Element>& elementList;

            // List of all edges on the boundary
            std::vector<Edge>& edgeList;

            // List of the homogeneous Dirichlet edges
            std::vector<const Edge*> dirHEdges;

            // List of the non-homogeneous Dirichlet edges
            std::unordered_map<int, std::vector<const Edge*>> dirNHEdges;
            
            // List of the Neumann edges
            std::unordered_map<int, std::vector<Edge*>> neumEdges;

            FEMParameters parameters;
            
        public : 

            /*!
            * Constructor
            * @param[in] mesh_          Loaded mesh
            * @param[in] parameters_    Parameters of the current problem
            */
            Solver(Mesh& mesh_, FEMParameters parameters_);

            /*
            * Assemble the linear system
            */
            void assemble();


            void assmat(int I, int J, Real X, VectorInt& ADPRCL, VectorInt& NUMCOL, 
            VectorInt& ADSUCL, VectorReal& LMATRI, int& nbLign, int& NEXTAD);
            
            /*
            * Change the storage from Non Ordered Sparse to Ordered Sparse
            */
            void fromNOSStoOSS();

            /*
            * Change the storage from  Ordered Sparse to Profil
            */
            void fromOSStoPR(); 

            /*!
            * LU decomposition and resolution
            */
            void decompLU();

            /*!
            * Sort the edge of the boundary in three lists
            * @param[in] dirH0Labels     List of the homogenous Dirichlet labels
            * @param[in] dirNHLabels     List of the non homogenous Dirichlet labels
            * @param[in] neumannLabels   List of the Neumann labels
            */
            void sortBoundaryEdges(VectorStr dirH0Labels,
                                 VectorStr dirNHLabels,
                                 VectorStr neumannLabels);

            bool isNeumannEdge(const int labelEdge);
            
            bool isDir0Edge(const int labelEdge);
            
            bool isDirNHEdge(const int labelEdge);



            void printEdgesLists();


            void printB();
            void printA();
            void printU();

            VectorReal& getU(){return U;}


    };

#endif
