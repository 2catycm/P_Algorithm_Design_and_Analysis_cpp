//
// Created by 叶璨铭 on 2022/5/5.
//
#include "includer.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#define Submit(PackageId, PackageString, FileName)                                                                        \
    TEST(##PackageId##FileName, BIT2) {                                                                                   \
        const auto root = std::filesystem::path(CMAKE_PROJECT_DIR);                                                       \
        const auto src_root = root / "src/main/cpp";                                                                      \
        auto IncludeDirectory = src_root / (PackageString);                                                               \
        auto CppSourceFilePath = IncludeDirectory / #FileName ".cpp";                                                     \
        auto TargetPath = root / "oj-submission" / #FileName ".cpp.i";                                                \
        ASSERT_TRUE(std::filesystem::exists(IncludeDirectory)) << "Include directory(" << std::endl                       \
                                                               << IncludeDirectory.generic_string() << ")" << std::endl   \
                                                               << "doesn't exist." << std::endl;                          \
        ASSERT_TRUE(std::filesystem::exists(CppSourceFilePath)) << "CppSource FilePath(" << std::endl                     \
                                                                << CppSourceFilePath.generic_string() << ")" << std::endl \
                                                                << "doesn't exist." << std::endl;                         \
        auto lines = getFileContent(CppSourceFilePath.generic_string());                                                  \
        std::fstream file(TargetPath.generic_string(), std::ios::out | std::ios::trunc);                                  \
        ASSERT_TRUE(file.is_open()) << "TargetPath (" << std::endl                                                        \
                                    << TargetPath.generic_string() << ")" << std::endl                                    \
                                    << "can't be opened." << std::endl;                                                   \
        for (const auto &line : lines) {                                                                                  \
            file << line << std::endl;                                                                                    \
            ASSERT_TRUE(file.good());                                                                                     \
        }                                                                                                                 \
        std::cout << "Totally " << lines.size() << " lines of codes have been generated. " << std::endl;                  \
        file.close();                                                                                                     \
    }
Submit(DivideAndConquer, "cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/Structure", BIT1);
Submit(DivideAndConquer, "cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/Structure", BIT2);


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}