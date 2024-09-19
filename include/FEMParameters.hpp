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
#ifndef FEM_PARAMETERS_H
#define FEM_PARAMETERS_H

#include "Mesh.hpp"
#include <string>

#include "Types.hpp"


    class FEMParameters{
    private:

        std::string mesh;
        std::string lagrange;
        std::string quadrature;
        std::string parameterFile;

        std::string savingFile;
        std::string meshPath;

        VectorStr dirichletLabels;
        VectorStr homogeneousDirichletLabels;
        VectorStr neumannLabels;
        VectorStr domainLabels;


    public:
    
        FEMParameters(std::string fileName);

        FEMParameters(int argc, char *argv[]);

        bool getParameterValue();

        void printLabel(const VectorStr labels);

        const std::string& getMeshName() const;
        const std::string& getLagrange() const;
        const std::string& getQuadrature() const;

        const std::string& getMeshPath() const;
        const std::string& getSavingFile() const;

        const VectorStr& getDirichletLabels() const;
        const VectorStr& getHomogeneousDirichletLabels() const;
        const VectorStr& getNeumannLabels() const;
        const VectorStr& getDomainLabels() const;
    };




#endif
