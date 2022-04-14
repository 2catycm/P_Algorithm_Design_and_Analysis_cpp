//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include <cstdint>
#include "LastWriteTime.hpp"
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    namespace stdfs = std::filesystem;
    //已检查：1. byte 与 specification 一致。 2. 魔法数字没有抄错。
#pragma pack(1)
    struct LocalFileHeader {
        uint32_t signature{0x0403'4b50u};// LocalHeader 的魔法数字。旧版zip不要求魔法数字，所以读取程序为了兼容不利用这个信息。
        uint16_t version{0x0014u};        //2.0 版本的zip
        uint16_t flag{0};                //标志位，没有扩展则为0.
        uint16_t method{0x0008u};         //压缩方法
        LastWriteTime lastWriteTime; // with time and date
        uint32_t crc32{0};                  // 文件的CRC32值。
        uint32_t compressedSize{0};  //压缩后的byte数
        uint32_t uncompressedSize{0}; //压缩前的byte数
        uint16_t fileNameSize{0};
        uint16_t extraFieldSize{0};
        // 输出本结构体时，还要输出
        // 1. file name (variable size)
        // - 不带\0
        // - 长度为fileNameSize
        // 2. extra field (variable size)
        // - 没有扩展，就不用写。
        //由于长度未知，所以不能放在结构体内。
        LocalFileHeader(stdfs::path const &relativePath):fileNameSize(relativePath.string().size()){
        }
    };
#pragma pack()
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities