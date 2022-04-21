//
// Created by 叶璨铭 on 2022/4/14.
//
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/entities/LastWriteTime.hpp"
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/entities/LocalFileHeader.hpp"
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/entities/CentralDirectoryHeader.hpp"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include "cn/edu/SUSTech/YeCanming/Judge/GTestExtensions.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    namespace stdfs = std::filesystem;
    TEST(TestCentralDirectoryHeader, constructAndWrite){
        const auto root = stdfs::path(CMAKE_PROJECT_DIR)/"testData"/"Zip";
        const auto filepath = root/"test.binary";
        const auto relativePath = stdfs::path("test.binary");
        LocalFileHeader _header{filepath, relativePath};
        std::fstream fileOut{(root/"test.binary.centralDirectoryHeader.binary").generic_string(),
                             std::ios::binary | std::ios::out | std::ios::trunc};
        fileOut<<_header;
        CentralDirectoryHeader header{_header, uint32_t(fileOut.tellp())};
        fileOut<<header;
        const auto writtenCnt = fileOut.tellp();
        ASSERT_LE(writtenCnt, 1024)<<"The size of the local file header with CentralDirectoryHeader exceeds 1024, so you should rewrite the test.";
        fileOut.close();
        std::fstream fileIn{(root/"test.binary.centralDirectoryHeader.binary").generic_string(),
                            std::ios::binary | std::ios::in};
        std::fstream fileInVerify{(root/"test.zip").generic_string(),
                            std::ios::binary | std::ios::in};
        char buffer1[1024], buffer2[1024];
        fileIn.read(buffer1, 1024);
        fileInVerify.read(buffer2, 1024);
        EXPECT_MEMEQ(buffer1, buffer2, fileIn.gcount());
        // ASSERT_EQ(0, memcmp(buffer1, buffer2, fileIn.gcount()));
    }
    TEST(TestLocalHeader, constructAndWrite){
        const auto root = stdfs::path(CMAKE_PROJECT_DIR)/"testData"/"Zip";
        const auto filepath = root/"test.binary";
        const auto relativePath = stdfs::path("test.binary");
        // note: 假如我们对Zip这个文件夹做压缩，我们可以认为这个文件夹的上级目录为Zip文件内的根目录
        //也可以认为这个文件夹就是根目录，都可以。
        LocalFileHeader header{filepath, relativePath};
        std::fstream fileOut{(root/"test.binary.localHeader.binary").generic_string(),
                             std::ios::binary | std::ios::out | std::ios::trunc};
        fileOut<<header;
        const auto writtenCnt = fileOut.tellp();
        ASSERT_LE(writtenCnt, 1024)<<"The size of the local file header exceeds 1024, so you should rewrite the test.";
        fileOut.close();
        std::fstream fileIn{(root/"test.binary.localHeader.binary").generic_string(),
                            std::ios::binary | std::ios::in};
        std::fstream fileInVerify{(root/"test.zip").generic_string(),
                            std::ios::binary | std::ios::in};
        char buffer1[1024], buffer2[1024];
        fileIn.read(buffer1, 1024);
        fileInVerify.read(buffer2, 1024);
        ASSERT_EQ(0, memcmp(buffer1, buffer2, fileIn.gcount()));
    }
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