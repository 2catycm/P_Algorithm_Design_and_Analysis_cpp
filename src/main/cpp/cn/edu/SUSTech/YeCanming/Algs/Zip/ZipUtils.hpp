//
// Created by 叶璨铭 on 2022/4/12.
//
#pragma once
#include <filesystem>
#include "utilities/filesystem.hpp"
#include "entities/LocalFileHeader.hpp"
#include <fstream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    namespace stdfs = std::filesystem;
    namespace ZipUtils{
        bool compress(const std::string& src, const std::string& dst){
            return compress(stdfs::path(src), stdfs::path(dst), size_t(-1));
        }
        bool compress(const std::string& src, const std::string& dst, size_t limit){
            return compress(stdfs::path(src), stdfs::path(dst), limit);
        }
        bool compress(stdfs::path const& src, stdfs::path const& dst){
            return compress(src, dst, size_t(-1)); //最大值
        }
        /**
         * compress src folder and all its contents into a zip file dst.
         * @param src
         * @param dst
         * @param limit in case the compressed directory is too large, a limit is required.
         * @return whether the compression was successful.
         */
        bool compress(stdfs::path const& src, stdfs::path const& dst, size_t limit){
            std::fstream dst_file{dst.c_str(), std::ios::binary| std::ios::out|std::ios::trunc};
            if (!dst_file.is_open())
                return false;
            return utilities::filesystem::preorderTraversal(src, [&](const stdfs::path& current_path){
                if(--limit<0)
                    return false;
                const auto relativePath = relative(current_path, src);
                entities::LocalFileHeader header{relativePath};

            });
        }

    };
}