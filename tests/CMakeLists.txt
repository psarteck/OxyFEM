
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(oxyTest ${TEST_SOURCES} testmain.cpp)

target_link_libraries(oxyTest ${GTEST_LIBRARIES} pthread)


add_test(NAME OxyTests COMMAND oxyTest)
