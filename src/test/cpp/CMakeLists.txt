include_directories(../../main/cpp)
include_directories(.)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(Boost COMPONENTS log REQUIRED)

set(GTEST_LIBRARIES GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

add_executable(GTestClosestPoint cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/GTestClosestPoint.cpp)
target_link_libraries(GTestClosestPoint ${GTEST_LIBRARIES})
#target_link_libraries(GTestClosestPoint ${Boost_LOG_LIBRARY})

add_executable(GTestBinarySearch cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/GTestBinarySearch.cpp)
target_link_libraries(GTestBinarySearch GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_link_libraries(GTestBinarySearch ${Boost_LOG_LIBRARY})


add_executable(Includer cn/edu/SUSTech/YeCanming/Includer/includer.cpp)
#target_link_libraries(Includer Boost::boost Boost::Log)

add_executable(GTestVector cn/edu/SUSTech/YeCanming/cpplang/GTestVector.cpp cn/edu/SUSTech/YeCanming/cpplang/GTestLiterals.cpp cn/edu/SUSTech/YeCanming/cpplang/GTestCMemory.cpp)
target_link_libraries(GTestVector GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

add_executable(GTestLab4B cn/edu/SUSTech/YeCanming/Algs/lab4/GTestLab4B.cpp cn/edu/SUSTech/YeCanming/Algs/lab4/GTestLab4A.cpp)
target_link_libraries(GTestLab4B GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

find_package(ZLIB REQUIRED)

add_executable(BinaryIO cn/edu/SUSTech/YeCanming/Algs/Zip/BinaryIO.cpp cn/edu/SUSTech/YeCanming/Algs/Zip/FileSystemTest.cpp cn/edu/SUSTech/YeCanming/Algs/Zip/ZlibTest.cpp)
target_link_libraries(BinaryIO ${GTEST_LIBRARIES})
target_link_libraries(BinaryIO ZLIB::ZLIB)
#target_link_libraries(BinaryIO GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
