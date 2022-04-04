cmake_minimum_required(VERSION 3.16)
project(P_Algorithm_Design_and_Analysis_cpp)

set(CMAKE_CXX_STANDARD 17)
include(CMakeTools/add_oj_submittable.cmake)
add_subdirectory(src/main/cpp)
add_subdirectory(src/test/cpp)
