#pragma once
#include <fstream>
#include <vector>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;
    struct BitOutputStream {
        using byte = unsigned char;
        std::ostream *super;
        explicit BitOutputStream(std::ostream *super) : super(super) {}
        byte buffer{0};
        byte usedInBuffer{0};
        friend BitOutputStream &operator<<(BitOutputStream &fs, const std::vector<bool> &bits) {
            for (const auto &bit : bits) {
                fs.writeBit(bit);//vector bool 只读遍历是没有问题的。
            }
            return fs;
        }
        void writeBit(bool x) {
            // add bit to buffer in small endian
            buffer |= x<<(usedInBuffer++);
            // if buffer is full (8 bits), write out as a single byte
            if (usedInBuffer == 8) flushBuffer();
        }

        void writeByte(byte x) {
            // optimized if byte-aligned
            if (usedInBuffer == 0) {
                super->write(reinterpret_cast<const char *>(&x), 1);
                return;
            }

            // otherwise write one bit at a time
            for (int i = 0; i < 8; i++) {
                bool bit = ((x >> i) & 1) == 1;
                writeBit(bit);
            }
        }
        // write out any remaining bits in buffer to the binary output stream, padding with 0s
        void flushBuffer() {
            if (usedInBuffer == 0) return;
//            if (usedInBuffer > 0) buffer <<= (8 - usedInBuffer);
            super->write(reinterpret_cast<const char *>(&buffer), 1);
            usedInBuffer = 0;
            buffer = 0;
        }
        void flush() {
            flushBuffer();
            super->flush();
        }
    };
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities