//
// Created by 叶璨铭 on 2022/4/14.
//
#include <gtest/gtest.h>
#include <cstring>

TEST(GTestCMemory, reinterpret){
    //        auto chars = reinterpret_cast<char[4]>(uint32_t(0x12345678'12345678));
    //        auto integer = reinterpret_cast<uint32_t>("123"); //not this one

    //这是个好的思路，C语言就很厉害了, 恰恰是因为C语言不在意类型.
    // C++在这个问题上没什么用。（不要std copy， 你以为的类型安全，其实我要的效果是洞悉内存）
    //1. 复制 uint32_t 为 char[4]
    uint32_t ui = 0x1234'5678u; //小端顺序
    char cs[4];
    memcpy(&cs, &ui, sizeof(cs));
    //        char validate[] = {12, 34, 56, 78};// 数字转换为字符数字，没有毛病
    char validate[] = {0x78, 0x56, 0x34, 0x12}; //注意小端序，注意十六进制。
    EXPECT_EQ(0, strncmp(cs, validate, sizeof(cs)));
    //2. 复制 char[4] 为 uint32_t
    char cs2[] = {0x78, 0x56, 0x34, 0x12};
    uint32_t ui2;
    memcpy(&ui2, &cs2, sizeof(ui2));
    uint32_t validate2 = 0x1234'5678u;
    EXPECT_EQ(ui2, validate2);

    //3. 不想复制，想要编译期; 想要共享。
    uint32_t ui3 = 0x1234'5678u;
    char* cs3 = (char*)(&ui3); //这就是共享，你的指针就是我的指针。编译期我们就是一样的。
    char validate3[] = {0x78, 0x56, 0x34, 0x12};
    EXPECT_EQ(0, strncmp(cs3, validate3, sizeof(ui3)));

    char cs4[] = {0x78, 0x56, 0x34, 0x12};
    uint32_t& ui4 = *((uint32_t*)cs4);
    uint32_t validate4 = 0x1234'5678u;
    EXPECT_EQ(ui4, validate4);
}
TEST(GTestCMemory, reinterpret_with_align_struct){
    struct aligned{
        char a;
        int b;
        short c;
        int d;
    };
    EXPECT_EQ(4*sizeof (int), sizeof(aligned)); //对齐法则参考：https://blog.csdn.net/keyearth/article/details/6129882
    aligned a {0x12, 0x23, 0x34, 0x45};
    char* cs1 = (char*)(&a);
    char validate1[] = {0x45, 0x00, 0x00, 0x00,
                        0x34, 0x00, 0x00, 0x00,
                        0x23, 0x00, 0x00, 0x00,
                        0x12, 0x00, 0x00, 0x00};
    EXPECT_NE(0, memcmp(cs1, validate1, sizeof(a)))<<cs1; //错在结构体不是大端序；结构体对齐不只是补零
    unsigned char validate2[] = {0x12, 0xcc, 0xcc, 0xcc,
                                 0x23, 0x00, 0x00, 0x00,
                                 0x34, 0x00, 0xcc, 0xcc,
                                 0x45, 0x00, 0x00, 0x00};
    EXPECT_EQ(0, memcmp(cs1, validate2, sizeof(a)))<<cs1;
}
TEST(GTestCMemory, reinterpret_with_unalign_struct){
#pragma pack(1)
    struct unaligned {
        char a;
        int b;
        short c;
        int d;
    };
#pragma pack()
    EXPECT_EQ(sizeof (int)*2+sizeof(char)+sizeof(short), sizeof(unaligned));
    unaligned a {0x12, 0x23, 0x34, 0x45};
    char* cs1 = (char*)(&a);
    char validate1[] = {0x12, 0x23, 0x00, 0x00, 0x00, 0x34, 0x00, 0x45, 0x00, 0x00, 0x00};
    EXPECT_EQ(0, memcmp(cs1, validate1, sizeof(a)))<<cs1;
}