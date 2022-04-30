//
// Created by 叶璨铭 on 2022/4/30.
//
#include <gtest/gtest.h>
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/utilities/DeflateBlock.hpp"
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    namespace utils = ThisPackage::utilities;
    TEST(DeflateBlockTest, CanTest){}
    TEST(DeflateBlockTest, Simple){
        std::stringstream ss;
        utils::BitOutputStream bitstream{&ss};
        char buffer[] = "Abcdabcdabcdabcd";
        utils::DeflateBlock block{buffer, static_cast<size_t>(sizeof(buffer)), true};
        bitstream<<block;
        bitstream.flush();
        std::cout<<ss.str()<<std::endl;
    }
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}