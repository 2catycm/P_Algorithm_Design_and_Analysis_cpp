//
// Created by 叶璨铭 on 2022/4/14.
//
#pragma once
#include "LastWriteTime.hpp"
#include "LocalFileHeader.hpp"
#include <cstdint>
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
        uint32_t signature{0x02014'b50u};//central file header 的魔法数字
        uint16_t versionMadeBy{VERSION_MADE_BY};
        uint16_t version{0x0014u};              // zip 2.0 version
        uint16_t flag{0};                       //无扩展
        uint16_t method{0x0000u};               //压缩方法。
        LastWriteTime lastWriteTime;            // with time and date
        uint32_t crc32{0};                      //源文件的 CRC32 值
        uint32_t compressedSize{0};               // 压缩后的字节大小
        uint32_t uncompressedSize{0};           // 压缩前的字节大小
        uint16_t fileNameSize;                  // 文件名大小
        uint16_t extraFieldSize{0};             //没有扩展字段
        uint16_t fileCommentSize{0};            //没有注释
        uint16_t diskNumberStart{0};            //
        uint16_t internalFileAttributes{0};     //
        uint32_t externalFileAttributes{0};     //
        uint32_t relativeOffsetOfLocalHeader{0};//local header相对于整个zip文件起始位置的字节数。
                                                //        file name (variable size)
                                                //        extra field (variable size)
                                                //        file comment (variable size)
        std::string fileName;
        /**
         * 将本结构体CentralDirectoryHeader与fileName写入二进制文件。
         * @param fs 目标文件流。
         * @return fs
         */
        friend std::ostream &operator<<(std::ostream &fs, const CentralDirectoryHeader &header) {
            constexpr auto fixedSize = sizeof(header) - sizeof(header.fileName);
            fs.write(reinterpret_cast<const char *>(&header), fixedSize);
            // fs.write(reinterpret_cast<const char *>(header.fileName.c_str()), header.fileNameSize);
            fs<<header.fileName; //直接打印string即可，不会有\0。
            return fs;
        }
        CentralDirectoryHeader(LocalFileHeader const & localHeader, uint32_t offset)
            : lastWriteTime{localHeader.lastWriteTime},
              fileName{localHeader.fileName}, fileNameSize{localHeader.fileNameSize},
              crc32{localHeader.crc32}, compressedSize{localHeader.compressedSize},
              uncompressedSize{localHeader.uncompressedSize}, 
              relativeOffsetOfLocalHeader(offset) {
            
        }
    };
#pragma pack()
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities
