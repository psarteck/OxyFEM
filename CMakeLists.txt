cmake_minimum_required(VERSION 3.12)

project(FEM LANGUAGES CXX)

# set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

add_subdirectory(external/eigen)

# add_subdirectory(external/googletest)

option(USE_TEST_PROBLEM "Use the file FEMProblem_test.cpp instead of FEMProblem.cpp" OFF)

option(USE_FLOAT "Utiliser float au lieu de double" OFF)


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
)

# add_compile_options(-Wall -Wextra -Wpedantic)

if(USE_TEST_PROBLEM)
    message(STATUS "Use of tests/FEMProblem_test.cpp for CI")
    set(PROBLEM_FILE tests/src/FEMProblem_test.cpp)
else()
    message(STATUS "Use of src/FEMProblem.cpp")
    set(PROBLEM_FILE src/FEMProblem.cpp)
endif()

if(USE_FLOAT)
    add_compile_definitions(USE_FLOAT)
endif()

include_directories(include)

add_executable(exeFEM ${SOURCES} ${PROBLEM_FILE} main.cpp)

target_compile_features(exeFEM PRIVATE cxx_std_17)

target_link_libraries(exeFEM Eigen3::Eigen)


enable_testing()
add_subdirectory(tests)