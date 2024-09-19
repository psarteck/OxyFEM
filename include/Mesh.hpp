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

#include "Node.hpp"
#include "Element.hpp"

#include "Types.hpp"


    class Mesh {

        private : 
            std::string fileName;
            std::vector<Node> nodes;
            std::vector<Edge> edges;
            std::vector<Element> elements;
            int dimension;
            
            int nodesNumber;
            int edgeNumber;
            int elementNumber;
        public :
            Mesh();

            bool loadMeshObj(const std::string& fileName);

            bool loadMsh(const std::string& fileName);
            bool loadMeshGmsh(const std::string& fileName);
            bool loadMeshGmsh2(const std::string& fileName);

            void printMesh() const;

            void integrate();

            Node& getNodeAt(int position);

            const std::vector<Node>& getNodes() const;
            const std::vector<Element>& getElements() const;
            const std::vector<Edge>& getEdges() const;
            // std::vector<Node> getNodes();

            Edge& getEdgeAt(int position){return edges.at(position);}
            int getDimension(){ return dimension;}
            int getNodesNumber(){ return nodes.size();}
            int getTrianglesNumber(){ return elementNumber;}
            int getEdgesNumber(){ return edgeNumber;}


            std::unordered_set<int> getBoundaryNodes() const;

            void printEdges();

    };

#endif
