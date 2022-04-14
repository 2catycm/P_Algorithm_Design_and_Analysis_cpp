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
    //已检查：1. byte 与 specification 一致。 2. 魔法数字没有抄错。
#pragma pack(1)
    struct CentralDirectoryHeader {
        uint32_t signature{0x02014'b50u}; //central file header 的魔法数字
        uint16_t versionMadeBy{VERSION_MADE_BY};
        uint16_t version {0x0014}; // zip 2.0 version
        uint16_t flag {0}; //无扩展
        uint16_t method {0x0008};
        LastWriteTime last_write_time; // with time and date
        uint32_t crc32 {0}; //源文件的 CRC32 值
        uint32_t compressSize {0}; // 压缩后的字节大小
        uint32_t uncompressedSize {0}; // 压缩前的字节大小
        uint16_t fileNameSize {0}; // 文件名大小
        uint16_t extraFieldSize {0}; //没有扩展字段
        uint16_t fileCommentSize {0}; //没有注释
        uint16_t diskNumberStart  {0}; //
        uint16_t internalFileAttributes  {0}; //
        uint32_t externalFileAttributes {0}; //
        uint32_t relativeOffsetOfLocalHeader{0}; //local header相对于整个zip文件起始位置的字节数。
//        file name (variable size)
//        extra field (variable size)
//        file comment (variable size)
    };
#pragma pack()
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities
