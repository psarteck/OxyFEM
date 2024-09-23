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

#ifndef FEM_UTILITIES
#define FEM_UTILITIES

#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

#include "Types.hpp"
#include "Node.hpp"

using namespace std;

namespace FEMUtilities {

    /*!
    * Change a std::vector<std::vector<double>> to Eigen::MatrixXd
    * @param vecOfVec   The matrix to change
    */
    Eigen::MatrixXd mat2Eigen(const std::vector<std::vector<double>>& vecOfVec); 

    /*!
    * Change a std::vector<double> to Eigen::VectorXd
    * @param vec   The vector to change
    */
    Eigen::VectorXd vec2Eigen(const std::vector<double>& vec);


    /*!
    * Print a matrix in the terminal
    * @param mat    The matrix to print
    * @param name   The name of the matrix
    */
    template <typename T>
    void printMat(std::vector<std::vector<T> > mat, std::string name);

    /*!
    * Print a vector in the terminal
    * @param vec    The vector to print
    * @param name   The name of the vector
    */
    template <typename T>
    void printVec(std::vector<T> vec, std::string name);

    /*!
    * Save a Eigen::VectorXd vector in a file
    * @param vec        The vector to save
    * @param filename   The name of the file 
    */
    void saveResults(Eigen::VectorXd& vec, std::string filename);

    /*!
    * Save a std::vector<T> vector in a file
    * @param vec        The vector to save
    * @param filename   The name of the file 
    */
    template <typename T>
    void saveResults(std::vector<T>& vec, std::string filename);

    /*!
    * Save a std::vector<T> vector in a file with coordinates
    * @param vec        The vector to save
    * @param nodes      The coordinates
    * @param filename   The name of the file 
    */
    template <typename T>
    void saveResults(std::vector<T>& vec, std::vector<Node>& nodes, std::string filename);

    /*!
    * Function to read the configuration file and store it in a dictionary (std::map)
    * @param nameFile   Name of the parameter file
    */
    std::map<std::string, std::string> readParameterFile(const std::string& nomFichier);

    /*!
    * Function to get a value from a key in the the configuration file 
    * @param config     String which contains config 
    * @param key        Key for the value
    */
    std::string getValue(const std::map<std::string, std::string>& config, const std::string& key);
    
    /*!
    * Function to modify the value associated with a key
    * @param config         String which contains config 
    * @param key            Key for the value
    * @param newValue       New value
    */
    void changeValue(std::map<std::string, std::string>& config, const std::string& key, const std::string& newValue);

    /*!
    * Function to write changes to the file
    * @param fileName           Name of the file
    * @param config             String which contains config 
    */
    void writeParameterFile(const std::string& fileName, const std::map<std::string, std::string>& config);

    // std::vector<double> node2double(std::vector<Node> vec);

    /*!
    * Allow to print a loading bar
    * @param percentage         Percentage of the loading bar
    */
    void showProgress(float percentage);

}



#endif


