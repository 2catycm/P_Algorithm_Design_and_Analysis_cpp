//
// Created by 叶璨铭 on 2022/4/12.
//
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/utilities/filesystem.hpp"
#include <chrono>
#include <cstddef>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <span>
#include <string_view>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;
    TEST(MyFileSystem, CanTest) {}
    TEST(MyFileSystem, PrintName) {
        size_t cnt = 0;
        auto r = ThisPackage::filesystem::preorderTraversal(std::filesystem::path{CMAKE_PROJECT_DIR} / "testData" / "Zip" / "filecnt" / "five", [&](const std::filesystem::path &path) {
            ++cnt;
            std::cout << path << std::endl;
            return true;
        });
        EXPECT_TRUE(r);
        std::cout << "Totally " << cnt << " Files have been scanned." << std::endl;
        EXPECT_EQ(5 + 1, cnt);//还包括directory，所以+1
        cnt = 0;
        r = ThisPackage::filesystem::preorderTraversal({std::filesystem::path{CMAKE_PROJECT_DIR} / "testData" / "Zip" / "filecnt" / "zero"}, [&](const std::filesystem::path &path) {
            ++cnt;
            std::cout << path << std::endl;
            return true;
        });
        EXPECT_TRUE(r);
        std::cout << "Totally " << cnt << " Files have been scanned." << std::endl;
        EXPECT_EQ(0 + 1, cnt);//还包括directory，所以+1
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
        tm *b = localtime(&a);
        printf("It is %s now.\n", asctime(b));
    }

    TEST(StdFileSystem, relativePath) {
        auto base = stdfs::path{CMAKE_PROJECT_DIR};
        auto current_path = base / "testData" / "Zip" / "filecnt" / "five";
        auto relative = stdfs::relative(current_path, base);
        EXPECT_EQ(relative.generic_string(), "testData/Zip/filecnt/five");
    }

    TEST(StdFileSystem, SeperatorTest) {
        auto separator = stdfs::path::preferred_separator;//wchar_t
        static_assert(std::is_same_v<decltype(separator), wchar_t>);
        std::wcout << separator << std::endl;
        EXPECT_NE('/', separator);
        EXPECT_EQ('\\', separator);
        //宽字符字面量，例如 L'β' 或 L'猫'。
        // 这种字面量具有 wchar_t 类型，且其值等于c字符 在执行宽字符集中的值
        stdfs::path a = "a/b/c";
        a /= "d";
        EXPECT_EQ(a, "a/b/c/d");
        a.make_preferred();
        EXPECT_EQ(a, "a\\b\\c\\d");
        a /= "e";
        EXPECT_EQ(a, "a\\b\\c\\d\\e");
    }
    // https://zh.cppreference.com/w/cpp/filesystem/path/generic_string
    TEST(StdFileSystem, GenericPathString) {
        auto print = [](std::string_view rem, auto const &str) {
            std::cout << rem << std::hex << std::uppercase << std::setfill('0');
            for (const auto b : std::as_bytes(std::span{str})) {
                std::cout << std::setw(2) << std::to_integer<unsigned>(b) << ' ';
            }
            std::cout << '\n';
        };
            //    std::filesystem::path p{CMAKE_PROJECT_DIR "/testData"};
        //        std::filesystem::path p{L##CMAKE_PROJECT_DIR L"/testData/家/屋\\我的电脑"};
            //    std::filesystem::path p{"/家/屋"};
        auto p = stdfs::path{CMAKE_PROJECT_DIR} / L"/testData/家/屋\\我的电脑";
        std::cout << p.string() << '\n';
        std::cout << p.generic_string() << '\n';//这里我们说的重点不是中文路径问题，而是说windows平台分隔符换成了通用分隔符。
        print("string    : ", p.generic_string());
        print("u8string  : ", p.generic_u8string());
        print("u16string : ", p.generic_u16string());
        print("u32string : ", p.generic_u32string());
        //  print("wstring   : ", p.generic_wstring  ());
        //  gcc-11.0.0 2020.12.30 仍然失败， clang-10 - ok
    }
    TEST(StdFileSystem, 中文测试) {
        char16_t 中文变量 = L'简';// 用UTF-16表示

    }
    TEST(StdFileSystem, 中文路径问题) {

    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities