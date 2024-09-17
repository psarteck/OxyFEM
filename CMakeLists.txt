cmake_minimum_required(VERSION 3.12)

project(FEM LANGUAGES CXX Fortran)

# set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

add_subdirectory(external/eigen)

# add_subdirectory(external/googletest)

option(USE_TEST_PROBLEM "Use the file FEMProblem_test.cpp instead of FEMProblem.cpp" OFF)

set(SOURCES
    src/Node.cpp
    src/Element.cpp
    src/Mesh.cpp
    src/Edge.cpp
    src/FEMParameters.cpp
    src/Quadrature.cpp
    src/FEMUtilities.cpp
    # src/FEMProblem.cpp
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
)


if(USE_TEST_PROBLEM)
    message(STATUS "Use of tests/FEMProblem_test.cpp for CI")
    set(PROBLEM_FILE tests/FEMProblem_test.cpp)
else()
    message(STATUS "Use of src/FEMProblem.cpp")
    set(PROBLEM_FILE src/FEMProblem.cpp)
endif()


include_directories(include)
include(Dart)

add_executable(exeFEM ${SOURCES} ${PROBLEM_FILE} main.cpp)

target_compile_features(exeFEM PRIVATE cxx_std_17)

target_link_libraries(exeFEM Eigen3::Eigen)


enable_testing()
add_subdirectory(tests)