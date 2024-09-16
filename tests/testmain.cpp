#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdlib>  
#include <cmath>
#include <unistd.h>

std::string GetCurrentWorkingDirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        return std::string(cwd);
    } else {
        return "Erreur : Impossible d'obtenir le répertoire de travail actuel.";
    }
}


bool CompareFiles(const std::string& resultFile, const std::string& referenceFile, double tolerance) {
    
    std::ifstream resultStream(resultFile);
    std::ifstream referenceStream(referenceFile);
    
    if (!resultStream.is_open()) {
        std::cerr << "Error: Unable to open results file " << resultFile << std::endl;
        return false;
    }

    if (!referenceStream.is_open()) {
        std::cerr << "Error: Unable to open reference file " << referenceFile << std::endl;
        return false;
    }

    double resultValue;
    double referenceValue;
    
    while (resultStream >> resultValue && referenceStream >> referenceValue) {
        if (std::fabs(resultValue - referenceValue) > tolerance) {
            std::cerr << "Error : Different values found : " 
                      << "Results = " << resultValue << ", "
                      << "References = " << referenceValue << std::endl;
            return false;
        }
    }
    
    if ((resultStream >> resultValue) || (referenceStream >> referenceValue)) {
        std::cerr << "Error : Files have different number of lines." << std::endl;
        return false;
    }

    return true;
}

TEST(NonRegressionTest, CompareOutputWithReference) {

    std::cout << "Current directory : " << GetCurrentWorkingDirectory() << std::endl;

    std::string executablePath = "./exeFEM";
    std::string parametersFile = "./tests/references/parameters.txt";
    std::string meshsPath = "./Meshs/";
    std::string resultsFile = "./tests/references/results.txt";

    std::string command = executablePath + " " + parametersFile + " " + resultsFile + " " + meshsPath;
    int result = system(command.c_str());
    
    ASSERT_EQ(result, 0) << "Error : The exectution of " << command << " crashed with the code : " << result;

    std::string referenceFile = "./tests/references/refNeumann.txt";
    EXPECT_TRUE(CompareFiles(resultsFile, referenceFile, 1e-6));

}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
