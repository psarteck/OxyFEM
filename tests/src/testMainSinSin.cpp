#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdlib>  
#include <cmath>
#include <unistd.h>
#include <unordered_map>
#include <sstream>

#include "Types.hpp"
#include "FEMUtilities.hpp"
#include "FEMParameters.hpp"
#include "Mesh.hpp"

#include "FEMTests.hpp"



TEST(NonRegressionTestSinSin, CompareOutputWithReferenceSinSin) {

    std::string executablePath = "../exeFEM";
    std::string parametersFile = "../../tests/references/parametersSinSin.txt";
    std::string meshsPath = "../../Meshs/";
    std::string resultsFile = "../../tests/references/resultsSinSin.txt";

    std::string command = executablePath + " " + parametersFile + " " + resultsFile + " " + meshsPath;
    int result = system(command.c_str());
    
    ASSERT_EQ(result, 0) << "Error : The execution of " << command << " crashed with the code : " << result;

    FEMParameters parameters(parametersFile);
    Mesh mesh;
    bool meshOk = mesh.loadMsh(meshsPath + parameters.getMeshName());
    VectorReal u = FEMTests::loadSolution(resultsFile);
    VectorReal uex = FEMTests::exactSinSin(mesh.getNodes());
    FEMUtilities::saveResults(uex, "../../tests/references/resultsUexSin.txt");
    EXPECT_TRUE(FEMTests::relativeError(u, uex, 0.01));

}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
