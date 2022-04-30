//
// Created by 叶璨铭 on 2022/4/30.
//
#include "cn/edu/SUSTech/YeCanming/Judge/GTestExtensions.hpp"
//#include "cn/edu/SUSTech/YeCanming/Algs/Zip/utilities/LZ77.hpp"
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/utilities/BitOutputStream.hpp"
#include <sstream>
#include <gtest/gtest.h>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    namespace utils = ThisPackage::utilities;
    TEST(BitOutputStreamTest, CanTest){}
    TEST(BitOutputStreamTest, CanWrite){
        std::stringstream ss;
        utils::BitOutputStream bs{&ss};
        bs.writeBit(1);bs.writeBit(0);
        bs.writeBit(0);bs.writeBit(0);
        bs.writeBit(0);bs.writeBit(1);
        bs.writeBit(1);bs.writeBit(0);
        bs.flush();
        EXPECT_EQ('a', ss.str()[0]);
    }
    TEST(BitOutputStreamTest, IsInLittleEndian){
        std::stringstream ss;
        utils::BitOutputStream bs{&ss};
        bs.writeBit(1);
        bs.writeByte('a');
        bs.writeBit(1);
        bs.writeBit(1);bs.writeBit(0);
        bs.writeBit(0);bs.writeBit(1);
        bs.writeBit(1);bs.writeBit(0);
        bs.flush();
        EXPECT_EQ(char(0b11000011u), ss.str()[0]); //测试时注意如果不转int为char，认为是负数。
        EXPECT_EQ(char(0b01100110u), ss.str()[1]);
    }
}