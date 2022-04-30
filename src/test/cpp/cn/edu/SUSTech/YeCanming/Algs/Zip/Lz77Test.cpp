//
// Created by 叶璨铭 on 2022/4/30.
//
#include "cn/edu/SUSTech/YeCanming/Judge/GTestExtensions.hpp"
#include <cn/edu/SUSTech/YeCanming/Algs/Zip/utilities/LZ77.hpp>

#include <gtest/gtest.h>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    namespace utils = ThisPackage::utilities;
    TEST(ZipAlgorithm, CanTest) {}
    TEST(ZipAlgorithm, Simple) {
        char data[] = "Abcdabcdabcdabcd";//隐含了一个\0
        const auto sequence = utils::lz77_compress(data, sizeof(data));
        struct {
            void operator()(utils::Lz77Literal const &lit) {
                std::cout << "Lz77Literal{byte=" << lit.byte << "}" << std::endl;
            }
            void operator()(utils::Lz77Pointer const &ptr) {
                std::cout << "Lz77Pointer{distance=" << ptr.distance << ", length=" << ptr.length << "}" << std::endl;
            }
        } visitor;
        for (const auto &element : sequence) {
            std::visit(visitor, element);
        }
        std::vector<utils::Lz77Element> verification =
                {utils::Lz77Literal{'A'}, utils::Lz77Literal{'b'},
                 utils::Lz77Literal{'c'}, utils::Lz77Literal{'d'},
                 utils::Lz77Literal{'a'}, utils::Lz77Pointer{4,11},
                 utils::Lz77Literal{'\0'}};
        EXPECT_EQ(verification, sequence);
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}