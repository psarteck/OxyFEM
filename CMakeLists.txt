cmake_minimum_required(VERSION 3.12)

project(FEM LANGUAGES CXX Fortran)

# set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

set(CMAKE_CXX_FLAGS "-I /opt/homebrew/include/eigen3/Eigen")

set(SOURCES
    src/Node.cpp
    src/Element.cpp
    src/Mesh.cpp
    src/Edge.cpp
    src/FEMParameters.cpp
    src/Quadrature.cpp
    src/FEMUtilities.cpp
    src/FEMProblem.cpp
    src/Solver.cpp
    src/FEMIntegrale.cpp
    src/FEMAssembly.cpp
    src/System.cpp
    fortran/affsmd.f
    fortran/affsmo.f
    fortran/affsol.f
    fortran/assmat.f
    fortran/cdesse.f
    fortran/impmpr.f
    fortran/ltlpr.f
    fortran/rsprl.f
    fortran/rspru.f
    fortran/tri.f
    main.cpp
)

include_directories(include)

add_executable(exeFEM ${SOURCES})

target_compile_features(exeFEM PRIVATE cxx_std_17)
