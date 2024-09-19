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
// Types.hpp

#ifndef FEM_TYPES_H
#define FEM_TYPES_H

#include <vector>

#ifdef USE_FLOAT
    using Real = float;
#else
    using Real = double;
#endif

using MatrixReal = std::vector<std::vector<Real>>;
using MatrixInt = std::vector<std::vector<int>>;
using MatrixStr = std::vector<std::vector<std::string>>;

using VectorReal = std::vector<Real>;
using VectorInt = std::vector<int>;
using VectorStr = std::vector<std::string>;

#endif


