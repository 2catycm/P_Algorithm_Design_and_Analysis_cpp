//
// Created by 叶璨铭 on 2022/5/5.
//
#include "includer.hpp"
#include <fstream>
#include <filesystem>
#include <gtest/gtest.h>
TEST(DivideAndConquer, BIT2){
    const auto root = std::filesystem::path(CMAKE_PROJECT_DIR);
    auto CppSourceFilePath = root/"src/main/cpp/cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/Structure/BIT2.cpp";
    auto IncludeDirectory = root/"src/main/cpp/cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/Structure/";
    auto TargetPath = root/"oj-submission/BIT2.cpp.i";
    auto lines = getFileContent(CppSourceFilePath.generic_string());
    std::fstream file(TargetPath.generic_string(), std::ios::out | std::ios::trunc);
    ASSERT_TRUE(file.is_open());
    for (const auto& line:lines){
        file<<line<<std::endl;
        ASSERT_TRUE(file.good());
    }
    file.close();
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}