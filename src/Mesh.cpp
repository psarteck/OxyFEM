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
#include "Mesh.hpp"
#include <unordered_map>


        
    using namespace std;

    Mesh::Mesh(){}


    Node& Mesh::getNodeAt(int position){
        return nodes.at(position);
    }

    const std::vector<Node>& Mesh::getNodes() const{
        return nodes;
    }
    const std::vector<Element>& Mesh::getElements() const{
        return elements;
    }
    const std::vector<Edge>& Mesh::getEdges() const{
        return edges;
    }


    void Mesh::printMesh() const{
        std::cout << "Nodes:" << std::endl;
        std::cout << nodes.size() << std::endl;
        std::cout << "Element:" << std::endl;
        std::cout << elements.size() << std::endl;


        for (const auto& node : nodes) {
            std::cout << "Node ID: " << node.getId() << "  X: " << node.getX() << "  Y: " << node.getY() << "  Z: " << node.getZ() << std::endl;
        }

        std::cout << "\nElements:" << std::endl;
        for (const auto& element : elements) {
            std::cout << "Element ID: " << element.getId() << "  Node IDs: ";
            for (int nodeID : element.getNodeIDs()) {
                std::cout << nodeID << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "\nEdges :" << std::endl;
        for (const auto& edge : edges) {
            std::cout << "Edge ID: " << edge.getLabel() << "  Node IDs: ";
            for (int nodeID : edge.getNodeIDs()) {
                std::cout << nodeID << " ";
            }
            std::cout << std::endl;
        }
    }

    // Function to parse a line into a vector of Reals
    VectorReal parseLine(const std::string& line) {
        VectorReal result;
        std::istringstream iss(line);
        Real value;
        while (iss >> value) {
            result.push_back(value);
        }
        return result;
    }

    std::unordered_set<int> Mesh::getBoundaryNodes() const {
        std::unordered_set<int> boundaryNodes;

        // Count the number of times each node appears
        std::unordered_map<int, int> nodeCount;
        for (const auto& element : elements) {
            for (int nodeID : element.getNodeIDs()) {
                auto result = nodeCount.emplace(nodeID, 1);
                if (!result.second) {
                    // The node already exists, increment the counter
                    result.first->second++;
                }
            }
        }

        // Identify knots on edges
        for (const auto& element : elements) {
            for (int nodeID : element.getNodeIDs()) {
                if (nodeCount.at(nodeID) == 1) {
                    // This node is used by a single element, so it's on the edge
                    boundaryNodes.insert(nodeID);
                }
            }
        }

        return boundaryNodes;
    }





    bool Mesh::loadMeshGmsh(const std::string& fileName){

        int nbVertices;
        int nbEdges;
        int nbTriangles;

        // Ouvrir le fichier en lecture
        std::ifstream file(fileName);

        // Vérifier si le fichier est ouvert correctement
        if (!file.is_open()) {
            std::cerr << "Error : impossible to open the file : "<< fileName << std::endl;
            return 1;
        }

        // Lire les lignes du fichier jusqu'à ce que la ligne commence par "Dimension"
        std::string line;
        while (std::getline(file, line) && line.find("Dimension") != 0) {}
        file >> dimension ;
        while (std::getline(file, line) && line.find("Vertices") != 0) {}
        file >> nbVertices ;

        for(int i = 0 ; i < nbVertices ; i++){
            Real x, y, z(0.0), label;
            if (dimension == 2){
                file >> x >> y >> label;
            }
            else if (dimension == 3){
                file >> x >> y >> z >> label;
            }
            
            Node newNode(x,y,z,label);
            nodes.push_back(newNode);
        }


        while (std::getline(file, line) && line.find("Edges") != 0) {}
        file >> nbEdges;
        
        for(int i = 0 ; i < nbEdges ; i++){
            int node1, node2, label;
            file >> node1 >> node2 >> label;
            Edge newEdge(getNodeAt(node1-1), getNodeAt(node2-1), label);
            edges.push_back(newEdge);
        }

        while (std::getline(file, line) && line.find("Triangles") != 0) {}

        file >> nbTriangles;

        for(int i = 0 ; i < nbTriangles ; i++){
            int x, y, z, label;
            file >> x >> y >> z >> label;
            VectorInt nodeIdList = {x,y,z};
            std::vector<Node> nodeList = {getNodeAt(x-1),getNodeAt(y-1),getNodeAt(z-1)};

            // std::vector<Edge> edgeList = {getNodeAt(x-1),getNodeAt(y-1),getNodeAt(z-1)};
            Element newElem(i+1, nodeIdList, nodeList);
            elements.push_back(newElem);
        }



        // Fermer le fichier
        file.close();

        nodesNumber = nbVertices;
        edgeNumber = nbEdges;
        elementNumber = nbTriangles;

        return true;

    }


    bool Mesh::loadMsh(const std::string& fileName){
        std::cout << endl << "-------- Reading the mesh -------" << std::endl;
        int nbVertices;
        int nbEdges;
        int nbTriangles;

        std::ifstream file(fileName);

        if (!file.is_open()) {
            std::cerr << "Error : impossible to open the file : "<< fileName << std::endl;
            std::cerr << "Problem reading the mesh " << endl;
            return 1;
        }

        file >> nbVertices >> nbTriangles >> nbEdges;

        for(int i = 0 ; i < nbVertices ; i++){
            Real x,y,label;
            file >> x >> y >> label;
            nodes.push_back(Node(x, y, 0.0, i+1));
        }

        for(int i = 0 ; i < nbTriangles ; i++){
            int id1, id2, id3, label;
            file >> id1 >> id2 >> id3 >> label;
            std::vector<Node> nodeList = {getNodeAt(id1-1), getNodeAt(id2-1), getNodeAt(id3-1)};
            VectorInt nodeIdList = {id1,id2,id3};
            elements.push_back(Element(label, nodeIdList, nodeList, i));
        }

        for(int i = 0 ; i < nbEdges ; i++){
            int id1, id2, label;
            file >> id1 >> id2 >> label;
            std::vector<Node> nodeList = {getNodeAt(id1-1), getNodeAt(id2-1)};
            edges.push_back(Edge(nodeList, label));
        }
        cout << "The mesh file " << fileName << " has been correctly read." << endl;

        std::cout << "---------------------------------" << std::endl;
        return true;

    }

    bool Mesh::loadMeshGmsh2(const std::string& fileName){
    // TO DO changer cette merde 
        int nbVertices;
        int nbEdges;
        int nbTriangles;

        // Ouvrir le fichier en lecture
        std::ifstream file(fileName);

        // Vérifier si le fichier est ouvert correctement
        if (!file.is_open()) {
            std::cerr << "Error : impossible to open the file : "<< fileName << std::endl;
            return 1;
        }

        // Lire les lignes du fichier jusqu'à ce que la ligne commence par "Dimension"
        std::string line;
        while (std::getline(file, line) && line.find("Dimension") != 0) {}
        file >> dimension ;
        while (std::getline(file, line) && line.find("Vertices") != 0) {}
        file >> nbVertices ;

        for(int i = 0 ; i < nbVertices ; i++){
            Real x, y, z(0.0), label;
            if (dimension == 2){
                file >> x >> y >> label;
            }
            else if (dimension == 3){
                file >> x >> y >> z >> label;
            }
            
            Node newNode(x,y,z,label);
            nodes.push_back(newNode);
        }


        while (std::getline(file, line) && line.find("Edges") != 0) {}
        file >> nbEdges;
        
        for(int i = 0 ; i < nbEdges ; i++){
            int node1, node2, label;
            file >> node1 >> node2 >> label;
            Edge newEdge(getNodeAt(node1-1), getNodeAt(node2-1), label);
            edges.push_back(newEdge);
        }

        while (std::getline(file, line) && line.find("Triangles") != 0) {}

        file >> nbTriangles;
        for(int i = 0 ; i < nbTriangles ; i++){
            int x, y, z, label;
            file >> x >> y >> z >> label;
            VectorInt nodeIdList = {x,y,z};
            std::vector<Node> nodeList = {getNodeAt(x-1),getNodeAt(y-1),getNodeAt(z-1)};


            std::vector<Edge> edgeList = {Edge(getNodeAt(x-1),getNodeAt(y-1),0), Edge(getNodeAt(y-1),getNodeAt(z-1),0), Edge(getNodeAt(z-1),getNodeAt(x-1),0)};

            // for(auto edge : edgeList){
            //     edge.setLabel(edge.isOnEdge(edges));
            // }
            
            Element newElem(i+1, nodeIdList, nodeList, edgeList);
            elements.push_back(newElem);
        }



        // Fermer le fichier
        file.close();

        nodesNumber = nbVertices;
        edgeNumber = nbEdges;
        elementNumber = nbTriangles;

        return true;

    }



    void Mesh::printEdges(){
        for(auto edge : edges){
            edge.printEdge();
        }
    }

    void Mesh::integrate(){
        
        // for(auto& element : elements){
        //     element.cal1Elem();
        // }
    }





    // A REFAIRE : 

    // bool Mesh::loadMeshObj(const std::string& fileName) {
    //     std::ifstream file(fileName);

    //     if (!file.is_open()) {
    //         std::cerr << "Erreur : Impossible d'ouvrir le fichier " << fileName << std::endl;
    //         return false;
    //     }

    //     std::string line;
    //     while (std::getline(file, line)) {
    //         std::istringstream iss(line);
    //         std::string token;
    //         iss >> token;

    //         if (token == "v") {
    //             // Lire les coordonnées d'un nœud
    //             Real x, y, z;
    //             iss >> x >> y >> z;
    //             nodes.push_back(Node(x, y, z, nodes.size() + 1));
    //         } else if (token == "f") {
    //             // Lire les indices de nœuds d'un élément
    //             VectorInt nodeIndices;
    //             int index;
    //             while (iss >> index) {
    //                 nodeIndices.push_back(index);
    //             }

    //             // Créer un élément avec les indices lus
    //             elements.push_back(Element(elements.size() + 1, nodeIndices, nodes));
    //         }
    //     }

    //     file.close();
    //     return true;
    // }


