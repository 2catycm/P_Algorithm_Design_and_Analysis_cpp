//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include "LastWriteTime.hpp"
#include <cassert>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <zlib.h>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    namespace stdfs = std::filesystem;
    //已检查：1. byte 与 specification 一致。 2. 魔法数字没有抄错。
#pragma pack(1)
    struct LocalFileHeader {
        uint32_t signature{0x0403'4b50u};// LocalHeader 的魔法数字。旧版zip不要求魔法数字，所以读取程序为了兼容不利用这个信息。
        uint16_t version{0x0014u};       //2.0 版本的zip
        uint16_t flag{0};                //标志位，没有扩展则为0.
        uint16_t method{0x0000u};        //压缩方法
        LastWriteTime lastWriteTime;     // with time and date
        uint32_t crc32{0};               // 文件的CRC32值。
        uint32_t compressedSize{0};      //压缩后的byte数
        uint32_t uncompressedSize{0};    //压缩前的byte数
        uint16_t fileNameSize;
        uint16_t extraFieldSize{0};
        // 输出本结构体时，还要输出
        // 1. file name (variable size)
        // - 不带\0
        // - 长度为fileNameSize
        // 2. extra field (variable size)
        // - 没有扩展，就不用写。
        //由于长度未知，所以不能放在结构体内。
        std::string fileName;
        char *dataStream{nullptr};
        /**
         * 将本结构体Local Header，fileName和压缩之后的文件流DataStream写入二进制文件。
         * @param fs 目标文件流。
         * @return fs
         */
        friend std::ostream &operator<<(std::ostream &fs, const LocalFileHeader &header) {
            constexpr auto fixedSize = sizeof(header) - sizeof(header.fileName) - sizeof(header.dataStream);
            fs.write(reinterpret_cast<const char *>(&header), fixedSize);
            // fs.write(reinterpret_cast<const char *>(header.fileName.c_str()), header.fileNameSize);
            fs << header.fileName;//直接打印string即可，不会有\0。
            if (header.dataStream != nullptr)
                fs.write(header.dataStream, header.compressedSize);
            return fs;
        }
        LocalFileHeader(stdfs::path const &current_path, stdfs::path const &relativePath)
            : lastWriteTime{stdfs::last_write_time(current_path)},
              fileName{relativePath.generic_string()}, fileNameSize{uint16_t(relativePath.generic_string().size())} {
            if (stdfs::is_regular_file(current_path) && stdfs::file_size(current_path) != 0) {
                // 非空一般文件。
                std::ifstream fileIn{current_path.string(), std::ios::binary | std::ios::in};
                assert(fileIn.is_open());
                constexpr size_t chunk = 1024;
                // 先算crc32，uncompressedSize
                this->uncompressedSize = stdfs::file_size(current_path);
                uint32_t crc = crc32_z(0L, Z_NULL, 0);
                for (char buffer[chunk]; !fileIn.eof();) {
                    fileIn.read(buffer, sizeof(buffer));
                    crc = crc32_z(crc, reinterpret_cast<const Bytef *>(buffer), fileIn.gcount());
                }
                this->crc32 = crc;
                // 然后修改method，根据method压缩，进而更新compressedSize。
                storeFile(fileIn);
            } else {
                assert(stdfs::is_directory(current_path) || stdfs::file_size(current_path) == 0);//其他类型，比如symbolic link暂不处理。
                //文件夹或者空文件，不必处理，构造已经完成。
            }
        }

    private:
        void storeFile(std::ifstream &fileIn) {
            //注意传参细节，传递可修改的引用。
            fileIn.clear();//这一句不能没有。
            fileIn.seekg(0L, std::ios::beg);
            this->method = 0;
            this->compressedSize = uncompressedSize;
            dataStream = new char[compressedSize];
            constexpr size_t chunk = 1024;
            for (char buffer[chunk]; !fileIn.eof();) {
                const auto &readCnt = fileIn.tellg();
                fileIn.read(buffer, sizeof(buffer));
                std::memcpy(dataStream + readCnt, buffer, fileIn.gcount());
            }
        }
    };
#pragma pack()
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities