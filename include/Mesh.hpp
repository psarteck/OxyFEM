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

#ifndef MESH_H
#define MESH_H


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

#include "Edge.hpp"
#include "Node.hpp"
#include "Element.hpp"

#include "Types.hpp"


    class Mesh {

        private : 

            // Name of the mesh file
            std::string fileName;

            // Nodes from the mesh
            std::vector<Node> nodes;

            // Edges on the boundary 
            std::vector<Edge> edges;

            // Elements from the mesh (triangle, ...)
            std::vector<Element> elements;

            // Dimension of the mesh 2D or 3D
            int dimension;
            
            // Number of node in the mesh
            int nodesNumber;

            // Number of edge on the boundary
            int edgeNumber;

            // Number of elements in the mesh
            int elementNumber;

        public :

            /*!
            * Constructor
            */
            Mesh();


            /*!
            * Load the mesh from a .msh format (FreeFem)
            * @param[in] fileName   Name of the mesh file
            */
            bool loadMsh(const std::string& fileName);


            bool loadMeshObj(const std::string& fileName);
            bool loadMeshGmsh(const std::string& fileName);
            bool loadMeshGmsh2(const std::string& fileName);

            /*!
            * Print the current loaded mesh
            */
            void printMesh() const;

            /*!
            * Print the all the boundary edges 
            */
            void printEdges();


            void integrate();


            /*
            *           GETTERS AND SETTER
            */

            Node& getNodeAt(int position) {return nodes.at(position);};

            std::vector<Node>& getNodes() {return nodes;};
            std::vector<Element>& getElements() {return elements;};
            std::vector<Edge>& getEdges() {return edges;};
            // std::vector<Node> getNodes();

            Edge& getEdgeAt(int position){return edges.at(position);}
            int getDimension(){ return dimension;}
            int getNodesNumber(){ return nodes.size();}
            int getTrianglesNumber(){ return elementNumber;}
            int getEdgesNumber(){ return edgeNumber;}

            std::unordered_set<int> getBoundaryNodes() const;


    };

#endif
