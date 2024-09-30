
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
    # src/FEMProblem_test.cpp
    src/FEMTests.cpp
)

include_directories(include)

add_executable(oxyTest ${TEST_SOURCES} src/testmain.cpp src/FEMProblem_test.cpp)
target_link_libraries(oxyTest ${GTEST_LIBRARIES} pthread)

add_executable(oxyTestCircle ${TEST_SOURCES} src/testmainCircle.cpp src/FEMProblem_test.cpp)
target_link_libraries(oxyTestCircle ${GTEST_LIBRARIES} pthread)

add_executable(oxyTestDiffusion ${TEST_SOURCES} src/testMainDiffusion.cpp src/FEMProblem_testDiffusion.cpp)
target_link_libraries(oxyTestDiffusion ${GTEST_LIBRARIES} pthread)

add_executable(oxyTestSinSin ${TEST_SOURCES} src/testMainSinSin.cpp src/FEMProblem2_test.cpp)
target_link_libraries(oxyTestSinSin ${GTEST_LIBRARIES} pthread)

add_test(NAME OxyTestNeDir COMMAND oxyTest)
add_test(NAME OxyTestsCircle COMMAND oxyTestCircle)
add_test(NAME OxyTestsDiffusion COMMAND oxyTestDiffusion)
add_test(NAME OxyTestsSinSin COMMAND oxyTestSinSin)
