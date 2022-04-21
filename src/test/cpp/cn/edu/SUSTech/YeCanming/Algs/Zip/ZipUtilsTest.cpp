#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include "cn/edu/SUSTech/YeCanming/Judge/GTestExtensions.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/ZipUtils.hpp"
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    namespace stdfs = std::filesystem;
    TEST(ZipUtilsTest, CanTest){}
    TEST(ZipUtilsTest, CanCompressSimple){
        const auto testDataPath = stdfs::path(CMAKE_PROJECT_DIR)/"testData"/ "Zip";
        ZipUtils::compress(testDataPath/"sampleDirectory", testDataPath/"sampleActually.zip");
    }
    TEST(ZipUtilsTest, CanCompressChinese){
        const auto testDataPath = stdfs::path(CMAKE_PROJECT_DIR)/"testData"/ "Zip";
        ZipUtils::compress(testDataPath/L"家", testDataPath/L"实际生成-家.zip");
    }
}