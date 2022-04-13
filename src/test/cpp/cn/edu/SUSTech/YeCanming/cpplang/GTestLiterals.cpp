//
// Created by 叶璨铭 on 2022/4/12.
//
#include <gtest/gtest.h>
#include <type_traits>
namespace cn::edu::SUSTech::YeCanming::cpplang {
    TEST(GTestLiterals, interger_separator) {
        int a = 123'345; //since C++14. 是单引号。不是逗号，也不是下划线.
        EXPECT_EQ(123345, a);
        uint32_t b = 0x0403'4b50;
        EXPECT_EQ(0x04034b50, b);
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