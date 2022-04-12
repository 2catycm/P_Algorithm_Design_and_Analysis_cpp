//
// Created by 叶璨铭 on 2022/4/12.
//
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/Utilities/filesystem.hpp"
#include <filesystem>
#include <gtest/gtest.h>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::Utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::Utilities;
    TEST(FileSystem, CanTest) {}
    TEST(FileSystem, PrintName) {
        auto r = ThisPackage::filesystem::preorderTraversal({CMAKE_PROJECT_DIR}, [](const std::filesystem::path &path) {});
        std::cout<<"Totally "<<r<<" Files have been scanned."<<std::endl;
        r = ThisPackage::filesystem::preorderTraversal({std::string(CMAKE_PROJECT_DIR)+"/bin"}, [](const std::filesystem::path &path) {
            std::cout << path << std::endl;
        });
        std::cout<<"Totally "<<r<<" Files have been scanned."<<std::endl;
    }

}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::Utilities