//
// Created by 叶璨铭 on 2022/4/12.
//
#include <cstring>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    /**
     * 文件系统库。
     */
    TEST(BinaryIO, CanTest) {
        auto a = std::filesystem::current_path();
        std::cout << a << std::endl;
        std::string b = CMAKE_PROJECT_DIR;
        EXPECT_EQ(a, b + "/bin");
    }

    /**
     * 文本流和二进制流都是有序字符序列，一个字符是一个8位1字节的整数。
     * 文本流能够组合成行，且按照编码解释。文本流写出和读入可能因为平台原因有差异。
     * 二进制流能“通透地记录内部数据”，读入和写出的一定相等。
     * "wb"	binary|out, binary|out|trunc	销毁内容	创建新文件
     */
    TEST(BinaryIO, CanWrite) {
        std::fstream file{"./test.binary", std::ios::binary | std::ios::out | std::ios::trunc};
        ASSERT_TRUE(file.is_open());
        //        file<<21<<0<<'a'; 格式输出
        file.put(21).put(0).put('a');
        EXPECT_EQ(3, file.tellp());
        file.write("123", 4);
        EXPECT_EQ(7, file.tellp());
    }
    TEST(BinaryIO, CanRead) {
        std::fstream file{"./test.binary",
                          std::ios::binary | std::ios::in};
        ASSERT_TRUE(file.is_open());
        char buffer[100];
        //        file>>a; 格式输入
        //        file.get(buffer[0]).get(buffer[1]).get(buffer[2]);
        //        file.read(buffer, 4);
        file.read(buffer, 7);
        EXPECT_EQ(buffer[0], 21);
        EXPECT_EQ(buffer[1], 0);
        EXPECT_EQ(buffer[2], 'a');
        EXPECT_TRUE(std::strncmp(buffer + 3, "123", 4) == 0);
    }
    TEST(BinaryIO, CanReadWithLoop) {
        std::ifstream fileIn{"./test.binary",
                          std::ios::binary | std::ios::in};
        ASSERT_TRUE(fileIn.is_open());
        // constexpr size_t chunk = 1024;
        // constexpr size_t chunk = 1;
        constexpr size_t chunk = 2;
        uint32_t cnt = 0;
        for (char buffer[chunk]; !fileIn.eof();) {
            std::cout<<fileIn.tellg()<<std::endl;
            fileIn.read(buffer, sizeof(buffer));
            std::cout<<fileIn.gcount()<<std::endl;
            cnt += fileIn.gcount();
        }
        EXPECT_EQ(cnt, 7);
    }
    TEST(BinaryIO, CanMoveFromOneStreamToAnother){
        char a[] = {'a', 0x0C, 0x7F};
        std::stringstream ss;
        ss.write(a, sizeof(a));
        std::fstream fileOut{"./testFromStringStream.binary",
                             std::ios::binary | std::ios::out | std::ios::trunc};
        ASSERT_TRUE(fileOut.is_open());
        EXPECT_EQ(ss.tellg(), 0); 
        ss.seekg(0);//既然是0，其实也不必seek
        fileOut<<ss.rdbuf();
        // fileOut.write(ss.str().data(), ss.str().size());
        EXPECT_EQ(fileOut.tellp(), sizeof(a));
        fileOut.flush(); //不flush什么都没有
        std::fstream fileIn{"./testFromStringStream.binary",
                            std::ios::binary | std::ios::in};
        ASSERT_TRUE(fileIn.is_open());
        char buffer[sizeof(a)];
        fileIn.read(buffer, sizeof(a));
        EXPECT_EQ(0, memcmp(buffer, a, sizeof(a)))/* <<"buffer: "<<buffer */;
    }
    TEST(BinaryIO, CanWriteString){
        std::string s = "abc"; // with a \0 at the end
        EXPECT_EQ(s.size(), 3); //而不是4.
        std::fstream fileOut{"./testCanWriteString.binary",
                             std::ios::binary | std::ios::out | std::ios::trunc};
        fileOut.write(reinterpret_cast<const char *>(s.c_str()), s.size());
        fileOut<<s; //亦不会写出\0
        EXPECT_EQ(fileOut.tellp(), s.size()*2);
        fileOut.flush();
        std::fstream fileIn{"./testCanWriteString.binary",
                            std::ios::binary | std::ios::in};
        char buffer[10];
        fileIn.read(buffer, 10);
        EXPECT_EQ(0, memcmp(buffer, (s+s).c_str(), 6));
        EXPECT_NE(0, memcmp(buffer, (s+s).c_str(), 7));
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}