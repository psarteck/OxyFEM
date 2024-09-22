
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
    src/FEMProblem_test.cpp
    src/FEMTests.cpp
)

include_directories(include)

add_executable(oxyTest ${TEST_SOURCES} src/testmain.cpp)
target_link_libraries(oxyTest ${GTEST_LIBRARIES} pthread)

add_executable(oxyTestCircle ${TEST_SOURCES} src/testmainCircle.cpp)
target_link_libraries(oxyTestCircle ${GTEST_LIBRARIES} pthread)

add_test(NAME OxyTestNeDir COMMAND oxyTest)
add_test(NAME OxyTestsCircle COMMAND oxyTestCircle)
