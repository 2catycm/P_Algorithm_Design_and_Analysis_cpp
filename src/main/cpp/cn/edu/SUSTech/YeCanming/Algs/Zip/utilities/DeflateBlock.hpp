#pragma once
#include "BitOutputStream.hpp"
#include "LZ77.hpp"
#include <vector>

namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;

    struct DeflateBlock{
        std::vector<bool> bits;
        friend ThisPackage::BitOutputStream &operator<<(ThisPackage::BitOutputStream &fs, const DeflateBlock &deflateBlock) {
            fs<<deflateBlock.bits;
//            deflateBlock.bits.clear();
            return fs;
        }
        DeflateBlock(const char* buffer, size_t bufferLen, bool isLastBlock){
            // header
            bits.push_back(isLastBlock);
            bits.push_back(false);
            bits.push_back(true); // fixed Huffman method: 01
            const auto lz77_sequence = lz77_compress(buffer, bufferLen);
            
        }
    };
}