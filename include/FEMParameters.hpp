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


    class FEMParameters{
    private:

        std::string mesh;
        std::string lagrange;
        std::string quadrature;
        std::string parameterFile;
        std::vector<std::string> dirichletLabels;
        std::vector<std::string> homogeneousDirichletLabels;
        std::vector<std::string> neumannLabels;
        std::vector<std::string> domainLabels;


    public:
    
        FEMParameters(std::string fileName);

        bool getParameterValue();

        void printLabel(const std::vector<std::string> labels);

        const std::string& getMeshName() const;
        const std::string& getLagrange() const;
        const std::string& getQuadrature() const;

        const std::vector<std::string>& getDirichletLabels() const;
        const std::vector<std::string>& getHomogeneousDirichletLabels() const;
        const std::vector<std::string>& getNeumannLabels() const;
        const std::vector<std::string>& getDomainLabels() const;
    };




#endif
