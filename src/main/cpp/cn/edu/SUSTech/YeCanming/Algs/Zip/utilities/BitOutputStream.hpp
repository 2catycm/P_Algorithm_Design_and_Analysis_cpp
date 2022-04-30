#include <fstream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip::utilities;
    struct BitOutputStream {
        using byte = unsigned char;
        std::ostream *super;
        BitOutputStream(std::ostream *super) : super(super) {}
        byte lastByte{0};
        byte remaining{0};
        writeBits(const byte *a, size_t bitsCnt) {

        }
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip::utilities