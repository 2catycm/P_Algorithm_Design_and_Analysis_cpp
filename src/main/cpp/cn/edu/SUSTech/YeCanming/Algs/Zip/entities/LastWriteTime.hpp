//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include <chrono>
#include <cstdint>
#include <ctime>
#include <filesystem>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    struct LastWriteTime {
        uint16_t mTime{0};// 文件最后写入时间。
        uint16_t mDate{0};// 文件最后写入时间。
        LastWriteTime() = default;
        explicit LastWriteTime(std::time_t const &time) {
            //chrono的用处是精度中立、跨平台，
            // 但是对日期、时间的处理还是得靠C语言的time库。
            // https://blog.csdn.net/qq_41453285/article/details/105464872?msclkid=f52643a1bbc611ec96013dc67bb23ae7
//            std::tm *tm_time = std::gmtime(&time);
            std::tm *tm_time = std::localtime(&time); //360 压缩 的结果是这个。
            // zip 对 LastWriteTime的格式要求 https://github.com/Stuk/jszip/issues/369
            // 1. 读取到的文件最后修改时间是 UTC时间，经过操作系统翻译后为本地时间
            //   > NTFS 文件系统以 UTC 格式存储时间值，因此它们不会受到时区或夏令时的更改的影响。
            //   > https://docs.microsoft.com/zh-cn/windows/win32/sysinfo/file-times
            // 2. UTC 是更加精确的 GMT 。 都是定义了一个标准时区。
            // 3. 注意区分
            //      int tm_mday;  // day of the month - [1, 31]
            //      int tm_wday;  // days since Sunday - [0, 6]
            //      int tm_yday;  // days since January 1 - [0, 365]
            // 4. 1900 是 C语言tm结构体的要求；1980是zip格式的要求。
//            mTime = (tm_time->tm_hour) << 11 | (tm_time->tm_min) << 5 | (tm_time->tm_sec >> 1);
            mTime = (tm_time->tm_hour) << 11 | (tm_time->tm_min) << 5 | ((tm_time->tm_sec >> 1)+1); //360 压缩这里有+1
            mDate = (tm_time->tm_year - 1980 + 1900) << 9 | (tm_time->tm_mon + 1) << 5 | (tm_time->tm_mday);
        }
        explicit LastWriteTime(std::filesystem::file_time_type const &ftime) : LastWriteTime(std::chrono::system_clock::to_time_t(
                                                                                       std::chrono::clock_cast<std::chrono::system_clock>(ftime))) {}
        explicit operator std::time_t() {
            auto const *thisIP = reinterpret_cast<int32_t const *>(this);
            std::tm tm_time{
//                    (*thisIP & 0x1f) << 1,                 // second
                    ((*thisIP & 0x1f)-1) << 1,                 // second 360 压缩这里有-1
                    (*thisIP >> 5) & 0x3f,                 // minute
                    (*thisIP >> 11) & 0x1f,                // hour
                    (*thisIP >> 16) & 0x1f,                // day
                    ((*thisIP >> 21) & 0x0f) - 1,          // month
                    ((*thisIP >> 25) & 0x7f) + 1980 - 1900,// year
                    0, 0, -1};
            return std::mktime(&tm_time);
        }
    };
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities