#pragma once
#include <cstdint>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    //已检查：1. byte 与 specification 一致。 2. 魔法数字没有抄错。
#pragma pack(1)
    struct EndOfCentralDirectoryHeader {
        uint32_t signature{0x0606'4b50u};//end of central file header 的魔法数字
        uint16_t numberOfThisDisk{0};
        uint16_t numberOfTheDiskWithTheStartOfTheCentralDirectory{0};
        uint16_t totalNumberOfEntriesOnThisDisk{0}; // zip 中包含的目录数
        uint16_t totalNumberOfEntries{0};   // zip 中包含的文件数
        uint32_t sizeOfTheCentralDirectory{0}; // 上面有很多个 CentralDirectoryHeader，他们一共占用多少字节
        uint32_t startOfCentralDirectory{0}; // CentralDirectoryHeader 们从哪里开始。
    };
#pragma pack()
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities