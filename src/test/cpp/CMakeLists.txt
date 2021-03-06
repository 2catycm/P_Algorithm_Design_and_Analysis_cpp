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


add_executable(Includer cn/edu/SUSTech/YeCanming/Includer/includer_console.cpp)
#target_link_libraries(Includer Boost::boost Boost::Log)
add_executable(OJSubmissionGenerator cn/edu/SUSTech/YeCanming/Includer/OJSubmissionGenerator.cpp)
target_link_libraries(OJSubmissionGenerator ${GTEST_LIBRARIES})


add_executable(GTestVector cn/edu/SUSTech/YeCanming/cpplang/GTestVector.cpp cn/edu/SUSTech/YeCanming/cpplang/GTestLiterals.cpp cn/edu/SUSTech/YeCanming/cpplang/GTestCMemory.cpp)
target_link_libraries(GTestVector GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

add_executable(GTestLab4B cn/edu/SUSTech/YeCanming/Algs/lab4/GTestLab4B.cpp cn/edu/SUSTech/YeCanming/Algs/lab4/GTestLab4A.cpp)
target_link_libraries(GTestLab4B GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

find_package(ZLIB REQUIRED)

add_executable(ZipProjectTest cn/edu/SUSTech/YeCanming/Algs/Zip/BinaryIO.cpp
        cn/edu/SUSTech/YeCanming/Algs/Zip/FileSystemTest.cpp
        cn/edu/SUSTech/YeCanming/Algs/Zip/ZlibTest.cpp
        cn/edu/SUSTech/YeCanming/Algs/Zip/EntityTest.cpp
        )
target_link_libraries(ZipProjectTest ${GTEST_LIBRARIES})
target_link_libraries(ZipProjectTest ZLIB::ZLIB)

add_executable(ZipUtilsTest cn/edu/SUSTech/YeCanming/Algs/Zip/ZipUtilsTest.cpp)
target_link_libraries(ZipUtilsTest ${GTEST_LIBRARIES})
target_link_libraries(ZipUtilsTest ZLIB::ZLIB)
#target_link_libraries(BinaryIO GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

add_executable(ZipAlgorithmTest cn/edu/SUSTech/YeCanming/Algs/Zip/Lz77Test.cpp cn/edu/SUSTech/YeCanming/Algs/Zip/RingQueueTest.cpp
        cn/edu/SUSTech/YeCanming/Algs/Zip/BitOutputStreamTest.cpp)
target_link_libraries(ZipAlgorithmTest ${GTEST_LIBRARIES})
target_link_libraries(ZipAlgorithmTest ZLIB::ZLIB)

add_executable(gen_lit_value_table cn/edu/SUSTech/YeCanming/Algs/Zip/gen_lit_value_table.cpp)


add_executable(ZipAlgorithmTest2 cn/edu/SUSTech/YeCanming/Algs/Zip/DeflateBlockTest.cpp)
target_link_libraries(ZipAlgorithmTest2 ${GTEST_LIBRARIES})
target_link_libraries(ZipAlgorithmTest2 ZLIB::ZLIB)

add_executable(TestLab8 cn/edu/SUSTech/YeCanming/Algs/lab8/TestLab8.cpp)
target_link_libraries(TestLab8 ${GTEST_LIBRARIES})

add_executable(TestLab12 cn/edu/SUSTech/YeCanming/Algs/lab12/TestLab12.cpp)
target_link_libraries(TestLab12 ${GTEST_LIBRARIES})

