//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include "entities/CentralDirectoryHeader.hpp"
#include "entities/LocalFileHeader.hpp"
#include "entities/EndOfCentralDirectoryHeader.hpp"
#include "utilities/filesystem.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    namespace stdfs = std::filesystem;
    namespace ZipUtils {
        /**
         * compress src folder and all its contents into a zip file dst.
         * @param src
         * @param dst
         * @param limit in case the compressed directory is too large, a limit is required.
         * @return whether the compression was successful.
         */
        bool compress(stdfs::path const &src, stdfs::path const &dst, size_t limit) {
            std::fstream dst_file{dst.c_str(), std::ios::binary | std::ios::out | std::ios::trunc};
            if (!dst_file.is_open())
                return false;
            std::stringstream centralDirectoryHeaders;
            uint16_t fileCnt{0}, directoryCnt{0};
            if (!utilities::filesystem::preorderTraversal(src, [&](const stdfs::path &current_path) {
                    if (--limit < 0)
                        return false;
                    if(stdfs::is_regular_file(current_path))
                        ++fileCnt;
                    else{
                        assert(stdfs::is_directory(current_path)); //symbolic link is not supported yet.
                        ++directoryCnt;
                    }
                    const auto relativePath = stdfs::relative(current_path, src/"..");
                    const uint32_t offset = dst_file.tellp();
                    entities::LocalFileHeader header{current_path, relativePath};
                    dst_file << header;
                    entities::CentralDirectoryHeader cdheader{header, offset};
                    centralDirectoryHeaders << cdheader;
                    return true;
                }))
                return false;
            uint32_t centralHeaderBegin = dst_file.tellp();
            uint32_t centralHeaderBytes = centralDirectoryHeaders.tellp();
            dst_file << centralDirectoryHeaders.rdbuf();
            entities::EndOfCentralDirectoryHeader endHeader{directoryCnt, fileCnt, centralHeaderBytes,centralHeaderBegin};
            dst_file << endHeader;
            return true;
        }
        bool compress(const std::string &src, const std::string &dst) {
            return compress(stdfs::path(src), stdfs::path(dst), size_t(-1));
        }
        bool compress(const std::string &src, const std::string &dst, size_t limit) {
            return compress(stdfs::path(src), stdfs::path(dst), limit);
        }
        bool compress(stdfs::path const &src, stdfs::path const &dst) {
            return compress(src, dst, size_t(-1));//最大值
        }
    };// namespace ZipUtils
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip