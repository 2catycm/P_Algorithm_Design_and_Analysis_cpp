include_directories(../../main/cpp)
include_directories(.)

find_package(GTest CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_executable(TestClosestPoint cn/edu/SUSTech/YeCanming/Algs/TestClosestPoint.cpp)
target_link_libraries(TestClosestPoint P_Algorithm_Design_and_Analysis_cpp_closest_point_lib)

add_executable(GTestClosestPoint cn/edu/SUSTech/YeCanming/Algs/GTestClosestPoint.cpp)
#target_link_libraries(GTestClosestPoint P_Algorithm_Design_and_Analysis_cpp_closest_point_lib)
target_link_libraries(GTestClosestPoint GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
#target_link_libraries(GTestClosestPoint Boost::boost)


add_executable(Includer cn/edu/SUSTech/YeCanming/Includer/includer.cpp)
#target_link_libraries(Includer Boost::boost Boost::Log)
