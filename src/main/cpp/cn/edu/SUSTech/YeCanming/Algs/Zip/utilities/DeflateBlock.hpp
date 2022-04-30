#pragma once
#include "BitOutputStream.hpp"
#include "FixedHuffmanCode.hpp"
#include "LZ77.hpp"
#include <vector>

namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;

    struct DeflateBlock {
        std::vector<bool> bits;
        friend ThisPackage::BitOutputStream &operator<<(ThisPackage::BitOutputStream &fs, const DeflateBlock &deflateBlock) {
            fs << deflateBlock.bits;
            //            deflateBlock.bits.clear();
            return fs;
        }
        DeflateBlock(const char *buffer, size_t bufferLen, bool isLastBlock) {
            // header
            bits.push_back(isLastBlock);
            bits.push_back(true);
            bits.push_back(false);// fixed Huffman method: 01. Note that it is in big endian.
            const auto lz77_sequence = lz77_compress(buffer, bufferLen);
            struct {
                void outputBinaryLittleEndian(uint32_t data, uint32_t lenInBits) const {
                    for (int i = 0; i < lenInBits; ++i) {
                        bits_ptr->push_back(data & 1);
                        data >>= 1;
                    }
                }
                void outputBinaryBigEndian(uint32_t data, uint32_t lenInBits) const {
                    int mask = 1<<(lenInBits-1);
                    for (int i = 0; i < lenInBits; ++i) {
                        bits_ptr->push_back(data & mask);
                        data <<= 1;
                    }
                }
                void outputLitCode(uint16_t lit_code) const {
                    auto lit_slot = slot_for_lit[lit_code];
                    auto position_in_slot = lit_code - base_value_of_lit_slot[lit_slot];
                    uint32_t final_code = base_code_of_lit_slot[lit_slot] + position_in_slot;
                    outputBinaryLittleEndian(final_code, bits_for_lit_slot[lit_slot]);
                }
                void operator()(Lz77Literal const &lit) const {
                    outputLitCode(lit.byte);
                }
                void operator()(Lz77Pointer const &ptr) const {
                    uint16_t length = ptr.length;
                    uint16_t distance = ptr.distance;
                    //先做length
                    auto length_slot = deflate_length_slot[length];
                    auto length_code = 257 + length_slot;
                    outputLitCode(length_code);
                    auto length_extra_len = deflate_extra_length_bits[length_slot];
                    auto length_extra = length - deflate_length_slot_base[length_slot];
                    outputBinaryBigEndian(length_extra, length_extra_len);
                    //再做distance
                    auto distance_slot = distance <= 256 ? deflate_offset_slot[distance] : deflate_offset_slot[256 + ((distance - 1) >> 7)];
                    auto& distance_code = distance_slot; //一样的
                    outputBinaryLittleEndian(distance_code, 5);
                    auto distance_extra_len = deflate_extra_offset_bits[distance_slot];
                    auto distance_extra = distance - deflate_offset_slot_base[distance_slot];
                    outputBinaryBigEndian(distance_extra, distance_extra_len);
                }
                std::vector<bool> *const bits_ptr;
            } visitor{&bits};
            for (const auto &element : lz77_sequence) {
                std::visit(visitor, element);
            }
            for (int i = 0; i < 7; ++i) {
                bits.push_back(false); //表示256
            }
        }
    };
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities