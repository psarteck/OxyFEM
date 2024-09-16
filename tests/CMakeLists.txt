
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# find_package(Eigen3 REQUIRED)
# include_directories(${EIGEN3_INCLUDE_DIR})

# set(TEST_SOURCES
#     ../src/Node.cpp
#     ../src/Element.cpp
#     ../src/Mesh.cpp
#     ../src/Edge.cpp
#     ../src/FEMParameters.cpp
#     ../src/Quadrature.cpp
#     ../src/FEMUtilities.cpp
#     # ../src/FEMProblem.cpp
#     ../src/Solver.cpp
#     ../src/FEMIntegrale.cpp
#     ../src/FEMAssembly.cpp
#     ../src/System.cpp
#     ../fortran/affsmd.f
#     ../fortran/affsmo.f
#     ../fortran/affsol.f
#     ../fortran/assmat.f
#     ../fortran/cdesse.f
#     ../fortran/impmpr.f
#     ../fortran/ltlpr.f
#     ../fortran/rsprl.f
#     ../fortran/rspru.f
#     ../fortran/tri.f
# )

add_executable(oxyTest ${TEST_SOURCES} testmain.cpp)

target_link_libraries(oxyTest ${GTEST_LIBRARIES} pthread)


add_test(NAME OxyTests COMMAND oxyTest)
