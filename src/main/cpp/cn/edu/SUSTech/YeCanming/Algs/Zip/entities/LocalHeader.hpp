//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include <cstdint>
#include "LastWriteTime.hpp"
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    struct LocalHeader {
        uint32_t magicNumber{0x0403'4b50u};// LocalHeader 的身份数字
        uint16_t version{0x0014u};        //2.0 版本的zip
        uint16_t flag{0};                //标志位，没有扩展则为0.
        uint16_t method{0x0008u};         //压缩方法
        LastWriteTime last_write_time; // with time and date
        uint32_t crc32{0};                  // 文件的CRC32值。
        uint32_t compressedSize{0};  //压缩后的byte数
        uint32_t uncompressedSize{0}; //压缩前的byte数
        uint16_t fileNameSize{0};
        uint16_t extraField{0};
        // 输出本结构体时，还要输出
        // - 不带\0的
        // - 长度为fileNameSize的
        // fileName。 由于长度未知，所以不能放在结构体内。
    };
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities