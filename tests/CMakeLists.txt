
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCES
    ../src/Node.cpp
    ../src/Element.cpp
    ../src/Mesh.cpp
    ../src/Edge.cpp
    ../src/FEMParameters.cpp
    ../src/Quadrature.cpp
    ../src/FEMUtilities.cpp
    # src/FEMProblem.cpp
    ../src/Solver.cpp
    ../src/FEMIntegrale.cpp
    ../src/FEMAssembly.cpp
    ../src/System.cpp
    FEMProblem_test.cpp
)

add_executable(oxyTest ${TEST_SOURCES} testmain.cpp)

target_link_libraries(oxyTest ${GTEST_LIBRARIES} pthread)


add_test(NAME OxyTests COMMAND oxyTest)
