//
// Created by 叶璨铭 on 2022/4/12.
//
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <iostream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    /**
     * 文件系统库。
     */
    TEST(BinaryIO, CanTest) {
        auto a = std::filesystem::current_path();
        std::cout<<a<<std::endl;
        std::string b = CMAKE_PROJECT_DIR;
        EXPECT_EQ(a, b+"/bin");
    }

    /**
     * 文本流和二进制流都是有序字符序列，一个字符是一个8位1字节的整数。
     * 文本流能够组合成行，且按照编码解释。文本流写出和读入可能因为平台原因有差异。
     * 二进制流能“通透地记录内部数据”，读入和写出的一定相等。
     * "wb"	binary|out, binary|out|trunc	销毁内容	创建新文件
     */
    TEST(BinaryIO, CanWrite){
        std::fstream file{"./test.binary"
        , std::ios::binary| std::ios::out|std::ios::trunc};
        ASSERT_TRUE(file.is_open());
//        file<<21<<0<<'a';
        file.put(21).put(0).put('a');
        file.write("123", 4);
    }
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}