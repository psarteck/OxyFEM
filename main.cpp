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
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <Eigen/Dense>
#include <vector>
#include <memory>

#include "FEMAssembly.hpp"
#include "Mesh.hpp"
#include "Node.hpp"
#include "FEMParameters.hpp"
#include "Solver.hpp"
#include "Mesh.hpp"
#include "Solver.hpp"
#include "FEMParameters.hpp"
#include "Solver.hpp"

using namespace std;




int main(int argc, char *argv[]){
    
    FEMParameters parameters(argc, argv);
    Mesh mesh;

    bool meshOk = mesh.loadMsh(parameters.getMeshPath() + parameters.getMeshName());
    

    std::unique_ptr<Solver> solver = std::make_unique<Solver>(mesh, parameters);

    solver->assemble();

    solver->fromNOSStoOSS();

    solver->fromOSStoPR();

    solver->decompLU();

    VectorReal& U = solver->getU();
    FEMUtilities::saveResults(U, parameters.getSavingFile());

    std::cout << "-------- End of the simulation --------" << endl << endl;

    return 0;
}