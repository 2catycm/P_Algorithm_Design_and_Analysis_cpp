//
// Created by 叶璨铭 on 2022/4/12.
//
#include <gtest/gtest.h>
#include <cstring>
#include <type_traits>
namespace cn::edu::SUSTech::YeCanming::cpplang {
    TEST(GTestLiterals, interger_separator) {
        int a = 123'345; //since C++14. 是单引号。不是逗号，也不是下划线.
        EXPECT_EQ(123345, a);
        uint32_t b = 0x0403'4b50;
        EXPECT_EQ(0x04034b50, b);
    }
    TEST(GTestLiterals, reinterpret){
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

    // https://zh.cppreference.com/w/cpp/language/integer_literal
    // 字面量的类型 规则
    // 无后缀非十进制，优先int，不能表示换unsigned, 再不行换long
    // 后缀u，只能往unsigned 类型上找。
    // 后缀l，至少有一个long
    TEST(GTestLiterals, LiteralType){
        //字面量的类型
        //整数字面量的类型，是依赖于所用数字基底和 整数后缀 的列表中，首个能适合其值的类型。
        uint32_t a = 0x0034'5678u;
        EXPECT_EQ(a, 0x0034'5678);//不加u是还是一样的。
        // 上面是因为运算符重载所以一样。其实内存也一样,因为表示正数的时候是兼容的。
        EXPECT_EQ(reinterpret_cast<void*>(a), reinterpret_cast<void*>(int32_t(0x0034'5678)));

        //下一个问题。
        int32_t b = 0xffff'ffff; //常量的类型是uint32_t, 因此用于构造int32_t发出警告。
        static_assert(std::is_same_v<decltype(0xffff'ffff), uint32_t>); //静态检查
        EXPECT_EQ(typeid(0xffff'ffff), typeid(uint32_t(0)));//动态检查
        uint32_t c = 0xffff'ffff; //没有警告
    }
}