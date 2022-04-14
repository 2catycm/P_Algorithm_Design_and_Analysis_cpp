//
// Created by 叶璨铭 on 2022/4/14.
//
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/entities/LastWriteTime.hpp"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    TEST(TestLastWriteTime, construct) {
        auto p = std::filesystem::temp_directory_path() / "example.bin";//operator / can append a pair of paths together
        std::ofstream(p.c_str()).put('a');
        auto ftime = std::filesystem::last_write_time(p);
        LastWriteTime last_write_time{ftime};
        std::cout << std::hex << std::setfill('0') << std::setw(2);
        std::cout << last_write_time.mTime << std::endl;
        std::cout << last_write_time.mDate << std::endl;
        std::time_t t{last_write_time};
        std::cout << std::ctime(&t) << std::endl;
        std::cout << std::asctime(std::localtime(&t)) << std::endl;
    }
    // 问题：1.本地时间问题，360压缩的结果和jszip的讨论不一样。
    // 2. 本地时间函数的原理，为什么恢复后
    //    std::cout<<std::ctime(&t)<<std::endl;
    //    std::cout<<std::asctime(std::localtime(&t))<<std::endl;
    // 居然是一样的。
    TEST(TestLastWriteTime, testBZip) {
        auto p = std::filesystem::path(CMAKE_PROJECT_DIR) / "testData" / "Zip"/"test.binary";
        auto ftime = std::filesystem::last_write_time(p);
        LastWriteTime last_write_time{ftime};
        std::cout << std::hex << std::setfill('0') << std::setw(2);
        std::cout << last_write_time.mTime << std::endl;
        std::cout << last_write_time.mDate << std::endl;
        uint16_t validate[] = {0xA8C8, 0x548E};
        EXPECT_EQ(0, memcmp(validate, &last_write_time, sizeof(validate)));
        std::time_t t{last_write_time};
        std::cout << std::ctime(&t) << std::endl;
        std::cout << std::asctime(std::localtime(&t)) << std::endl;
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities