#pragma once
#include <cstdint>
#include <fstream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    //已检查：1. byte 与 specification 一致。 2. 魔法数字没有抄错。
#pragma pack(1)
    struct EndOfCentralDirectoryHeader {
        uint32_t signature{0x0606'4b50u};//end of central file header 的魔法数字
        uint16_t numberOfThisDisk{0};
        uint16_t numberOfTheDiskWithTheStartOfTheCentralDirectory{0};
        uint16_t totalNumberOfEntriesOnThisDisk;// zip 中包含的目录数
        uint16_t totalNumberOfEntries;          // zip 中包含的文件数
        uint32_t sizeOfTheCentralDirectory;     // 上面有很多个 CentralDirectoryHeader，他们一共占用多少字节
        uint32_t startOfCentralDirectory;       // CentralDirectoryHeader 们从哪里开始。
        EndOfCentralDirectoryHeader(uint16_t directoryCnt, uint16_t fileCnt,
        uint32_t centralHeaderBytes, uint32_t centralHeaderBegin):
        totalNumberOfEntriesOnThisDisk{directoryCnt}, totalNumberOfEntries{fileCnt},
        sizeOfTheCentralDirectory{centralHeaderBytes}, startOfCentralDirectory{centralHeaderBegin}{

        }
        /**
         * 将本结构体 EndOfCentralDirectoryHeader 与fileName写入二进制文件。
         * @param fs 目标文件流。
         * @return fs
         */
        friend std::ostream &operator<<(std::ostream &fs, const EndOfCentralDirectoryHeader &header) {
            constexpr auto fixedSize = sizeof(header);
            fs.write(reinterpret_cast<const char *>(&header), fixedSize);
            assert(fs.good());
            return fs;
        }
    };
#pragma pack()
    }// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities