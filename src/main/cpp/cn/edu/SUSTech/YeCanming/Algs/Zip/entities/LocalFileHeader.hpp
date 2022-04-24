//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include "../utilities/filesystem.hpp"
#include "LastWriteTime.hpp"
#include <cassert>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <zlib.h>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::entities;
    namespace stdfs = std::filesystem;
    namespace zipfs = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities::filesystem;
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
        std::stringstream dataStream{"", std::ios::in | std::ios::out | std::ios::binary};
        /**
         * 将本结构体Local Header，fileName和压缩之后的文件流DataStream写入二进制文件。
         * @param fs 目标文件流。
         * @return fs
         */
        friend std::ostream &operator<<(std::ostream &fs, const LocalFileHeader &header) {
            constexpr auto fixedSize = sizeof(header) - sizeof(header.fileName) - sizeof(header.dataStream);
            fs.write(reinterpret_cast<const char *>(&header), fixedSize);
            assert(fs.good());
            // fs.write(reinterpret_cast<const char *>(header.fileName.c_str()), header.fileNameSize);
            fs << header.fileName;//直接打印string即可，不会有\0。
            assert(fs.good());
            // fs << header.dataStream.rdbuf();
            fs << header.dataStream.str();
            assert(fs.good());
            return fs;
        }
        LocalFileHeader(stdfs::path const &current_path, stdfs::path const &relativePath)
            : lastWriteTime{stdfs::last_write_time(current_path)},
              fileName{zipfs::normalized_string(relativePath, current_path)} {
            if (stdfs::is_regular_file(current_path) && stdfs::file_size(current_path) != 0) {
                fileNameSize = fileName.size();
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
                if (this->uncompressedSize <= 2048){
                    std::cout<<"[INFO]: file is too small to use DEFLATE, using STORE instead.  "<<std::endl;
                    storeFile(fileIn);
                }
                else if (deflateFile(fileIn, Z_DEFAULT_COMPRESSION) != Z_OK){
                    std::cerr<<"[WARN]: DEFLATE method failed."<<std::endl;
                    std::cout<<"[INFO]: using STORE method instead. "<<std::endl;
                    storeFile(fileIn);
                }
            } else {
                assert(stdfs::is_directory(current_path) || stdfs::file_size(current_path) == 0);//其他类型，比如symbolic link暂不处理。
                //文件夹或者空文件，不必处理，构造已经完成。
            }
        }

    private:
        int deflateFile(std::ifstream &fileIn, int level) {
            fileIn.clear();//这一句不能没有。
            fileIn.seekg(0L, std::ios::beg);
            dataStream.clear();
            dataStream.seekp(0L, std::ios::beg);
            assert(fileIn.good()&&dataStream.good());
            this->method = 0x0008u;
            // compress fileIn to dataStream using DEFLATE :

            //标志
            int ret, flush;//ret返回状态，
            // flush记录deflate()方法的刷新状态：不刷新或者等到文件结束一起刷新。
            unsigned have;//deflate()方法返回的数据量（单位为byte）
            // 初始化z_stream结构体。结构体的信息用于维护deflate()的状态。
            z_stream strm;
            // 输入输出缓冲。
            constexpr size_t chunk = 2048;
            unsigned char in[chunk];
            unsigned char out[chunk];
            // 初始化strm.
            strm.zalloc = Z_NULL;
            strm.zfree = Z_NULL;
            strm.opaque = Z_NULL;//默认内存申请方式。
            ret = deflateInit(&strm, level);
            if (ret != Z_OK){
                std::cerr<<"[ERROR]: deflateInit() failed with exit code "<<ret<<std::endl;
                return ret;
            }
            //外面的循环：确保读取整个文件，直到eof。确保压缩流输出到输出流。
            do {
                fileIn.read(reinterpret_cast<char *>(in), sizeof(in));
                strm.avail_in = fileIn.gcount();//刚才读了多少字节。
                if (fileIn.bad()) {
                    (void) deflateEnd(&strm);//防止内存泄露
                    std::cerr<<"[WARN]: DEFLATE method: fail to read bytes"<<std::endl;
                    return Z_ERRNO;
                }
                flush = fileIn.eof() ? Z_FINISH : Z_NO_FLUSH;//如果读完了，那么待会deflate的时候就知道这是最后一片区域。
                strm.next_in = in;                           //指向刚才读进来数据的指针。

                // 内循环：把外循环读取的一块数据进行压缩，直到没有数据要输出为止。
                // 不断增大out缓存区，以让in都被处理过。
                do {
                    strm.avail_out = chunk;//out缓冲区的大小
                    strm.next_out = out;   //缓冲区指针
                    ret = deflate(&strm, flush);
                    assert(ret != Z_STREAM_ERROR);
                    //deflate 尽可能把所有avail_in 处理完放到avail_out里面。
                    //现在我们要把 读取数和写出数重新统计。
                    // deflate方法把它读取了多少和写了多少放在strm结构体中了
                    // deflate分块处理，一定要被告知什么是后结束。
                    have = chunk - strm.avail_out;//计算多少压缩后数据被放出。
                    dataStream.write(reinterpret_cast<char *>(out), have);
                    if (dataStream.bad()) {
                        (void) deflateEnd(&strm);
                        std::cerr<<"[WARN]: DEFLATE method: fail to write bytes"<<std::endl;
                        return Z_ERRNO;
                    }
                } while (strm.avail_out == 0);// out空间不足，需要继续压缩。
                assert(strm.avail_in == 0);   // 所有数据都被处理完了。

                // 状态为FINISH退出循环
            } while (flush != Z_FINISH);
            assert(ret == Z_STREAM_END); /* stream will be complete */

            // 防止内存泄露
            (void) deflateEnd(&strm);
            this->compressedSize = dataStream.tellp();
            return Z_OK;
        }
        void storeFile(std::ifstream &fileIn) {
            //注意传参细节，传递可修改的引用。
            fileIn.clear();//这一句不能没有。
            fileIn.seekg(0L, std::ios::beg);
            dataStream.clear();
            dataStream.seekp(0L, std::ios::beg);
            assert(fileIn.good()&&dataStream.good());
            this->method = 0;
            this->compressedSize = uncompressedSize;
            dataStream << fileIn.rdbuf();
            dataStream.flush();
        }
    };
#pragma pack()
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::entities