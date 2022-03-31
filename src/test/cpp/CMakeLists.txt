include_directories(../../main/cpp)
include_directories(.)

find_package(GTest CONFIG REQUIRED)

add_executable(TestClosestPoint cn/edu/SUSTech/YeCanming/Algs/TestClosestPoint.cpp)
target_link_libraries(TestClosestPoint P_Algorithm_Design_and_Analysis_cpp_closest_point_lib)

target_link_libraries(TestClosestPoint GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
