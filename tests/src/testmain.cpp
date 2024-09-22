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

#include "FEMTests.hpp"



TEST(NonRegressionTest, CompareOutputWithReference) {

    std::string executablePath = "../exeFEM";
    std::string parametersFile = "../../tests/references/parametersNeDir.txt";
    std::string meshsPath = "../../Meshs/";
    std::string resultsFile = "../../tests/references/results.txt";

    std::string command = executablePath + " " + parametersFile + " " + resultsFile + " " + meshsPath;
    int result = system(command.c_str());
    
    ASSERT_EQ(result, 0) << "Error : The exectution of " << command << " crashed with the code : " << result;

    std::string referenceFile = "../../tests/references/refNeDir.txt";
    EXPECT_TRUE(FEMTests::CompareFiles(resultsFile, referenceFile, 1e-4));

}

// TEST(NonRegressionTestCircle, CompareOutputWithReference) {

//     std::string executablePath = "../exeFEM";
//     std::string parametersFile = "../../tests/references/parametersCircle.txt";
//     std::string meshsPath = "../../Meshs/";
//     std::string resultsFile = "../../tests/references/resultsCircle.txt";

//     std::string command = executablePath + " " + parametersFile + " " + resultsFile + " " + meshsPath;
//     int result = system(command.c_str());
    
//     ASSERT_EQ(result, 0) << "Error : The exectution of " << command << " crashed with the code : " << result;

//     std::string referenceFile = "../../tests/references/refCircle.txt";
//     EXPECT_TRUE(FEMTests::CompareFiles(resultsFile, referenceFile, 1e-4));

// }


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
