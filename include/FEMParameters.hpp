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
        VectorStr dirichletLabels;
        VectorStr homogeneousDirichletLabels;
        VectorStr neumannLabels;
        VectorStr domainLabels;


    public:
    
        FEMParameters(std::string fileName);

        bool getParameterValue();

        void printLabel(const VectorStr labels);

        const std::string& getMeshName() const;
        const std::string& getLagrange() const;
        const std::string& getQuadrature() const;

        const VectorStr& getDirichletLabels() const;
        const VectorStr& getHomogeneousDirichletLabels() const;
        const VectorStr& getNeumannLabels() const;
        const VectorStr& getDomainLabels() const;
    };




#endif
