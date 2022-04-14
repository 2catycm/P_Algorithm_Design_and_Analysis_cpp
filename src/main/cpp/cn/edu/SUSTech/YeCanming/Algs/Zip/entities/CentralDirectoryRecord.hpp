//
// Created by 叶璨铭 on 2022/4/14.
//
#pragma once
#include <cstdint>
#include "LastWriteTime.hpp"
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
#ifdef _WIN32
#define VERSION_MADE_BY 10
#elif linux
#define VERSION_MADE_BY 3
#elif __APPLE__
#define VERSION_MADE_BY 7
#else
#warning "Unsupported Platform, field VERSION_MADE_BY in " __FILE__  "will be treated as zero"
#define VERSION_MADE_BY 0
#endif
    struct CentralDirectoryRecord {
        uint32_t magicNumber{0x02014'b50u};
        uint16_t versionMadeBy{VERSION_MADE_BY};
        uint16_t version {0x0014}; // zip 2.0 version
        uint16_t flag {0}; //无扩展
        uint16_t method {0x0008};
        LastWriteTime last_write_time; // with time and date
    };
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities
