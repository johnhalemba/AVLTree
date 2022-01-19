cmake_minimum_required(VERSION 3.20)
project(LAB3-EADS-JAN-HALEMBA)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

add_executable(Tree main.cpp Dictionary.h externalFunctions.h)
add_executable(TreeTests tests.cpp Dictionary.h externalFunctions.h)

target_link_libraries(TreeTests PUBLIC gtest_main)
