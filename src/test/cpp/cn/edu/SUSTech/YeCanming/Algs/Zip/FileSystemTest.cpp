//
// Created by 叶璨铭 on 2022/4/12.
//
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/utilities/filesystem.hpp"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;
    TEST(MyFileSystem, CanTest) {}
    TEST(MyFileSystem, PrintName) {
        auto r = ThisPackage::filesystem::preorderTraversal({CMAKE_PROJECT_DIR}, [](const std::filesystem::path &path) {});
        std::cout << "Totally " << r << " Files have been scanned." << std::endl;
        r = ThisPackage::filesystem::preorderTraversal({std::string(CMAKE_PROJECT_DIR) + "/bin"}, [](const std::filesystem::path &path) {
            std::cout << path << std::endl;
        });
        std::cout << "Totally " << r << " Files have been scanned." << std::endl;
    }
    using namespace std::chrono_literals;
    //https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t?msclkid=e4adf3faba6911ecb78dd1ec928b9478
    template<typename TP>
    std::time_t to_time_t(TP tp) {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
        //        auto sctp = time_point_cast<system_clock::duration>(tp+TP::clock()+ system_clock::from_time_t(std::time_t(0)));
        return system_clock::to_time_t(sctp);
    }
    // referenced from https://en.cppreference.com/w/cpp/filesystem/last_write_time?msclkid=2993e168ba6711ec8e7fdfa63e4a8d15
    TEST(StdFileSystem, last_write_time) {
        auto p = std::filesystem::temp_directory_path() / "example.bin";//operator / can append a pair of paths together
        std::ofstream(p.c_str()).put('a');                              // create file
        auto print_last_write_time = [](std::filesystem::file_time_type const &ftime) {
            //            std::time_t cftime = std::chrono::system_clock::to_time_t(
            //                    std::chrono::file_clock::to_sys(ftime));// since C++ 20, 17用不了
            //            std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime); // MSVC 用不了
            //            auto cftime = std::filesystem::file_time_type::clock::to_time_t(ftime);
            //            auto cftime = to_time_t(ftime);
            //            std::time_t cftime = ftime; //强制类型转换

            //下面我们宣布，允许C++20参赛。
            const auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(ftime);
            const auto time = std::chrono::system_clock::to_time_t(systemTime);
            std::cout << "File write time is " << std::asctime(std::localtime(&time));
        };

        auto ftime = std::filesystem::last_write_time(p);
        print_last_write_time(ftime);

        std::filesystem::last_write_time(p, ftime + 1h);// move file write time 1 hour to the future
        ftime = std::filesystem::last_write_time(p);    // read back from the filesystem
        print_last_write_time(ftime);

        std::filesystem::remove(p);
    }
    // 总结：
    // std::filesystem::file_time_type is std::chrono::time_point</*trivial-clock*/>;
    // and std::chrono::time_point represents a point in time.
    // trivial-clock is an implementation-defined type that satisfies TrivialClock
    // and is sufficient to represent the resolution and range of the file time values offered by the filesystem.

    //最基本的类型是std::time_t C语言时代就有了。
    //time_t time since epoch type
    //tm calendar time type
    TEST(StdFileSystem, time_t) {
        time_t a = time(NULL);
        printf("It is %s now.\n", ctime(&a));
        tm* b = localtime(&a);
        printf("It is %s now.\n", asctime(b));
    }

}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities