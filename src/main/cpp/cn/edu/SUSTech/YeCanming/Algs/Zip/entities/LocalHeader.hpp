//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include <cstdint>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    struct LocalHeader {
        uint32_t magicNumber{0x0403'4b50};// LocalHeader 的魔法数字
        uint16_t version{0x0014};        //2.0 版本的zip
        uint16_t flag{0};                //标志位，没有扩展则为0.
        uint16_t method{0x0008};         //压缩方法
        uint16_t time{0};                // 文件最后写入时间。
        uint16_t date{0};                // 文件最后写入时间。
        uint32_t crc32{0};                  // 文件的CRC32值。
        uint32_t compressedSize{0};  //压缩后的byte数
        uint32_t uncompressedSize{0}; //压缩前的byte数
        uint16_t fileNameSize{0};
    };
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities