//
// Created by 叶璨铭 on 2022/4/12.
//
#include <gtest/gtest.h>
#include <cstdint>
#include <zlib.h>
constexpr uint8_t src_str[] = "Hello world! 大家好！ 中文是编译器换成UTF-8放到内存里的。aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
TEST(ZlibTest, CanCompressAndUnCompress){
    //compress
    uint8_t buf[1024]{};
    unsigned long read_cnt, write_cnt;
    EXPECT_EQ(sizeof(read_cnt), sizeof(uint32_t)); //但是你要用 uint32_t 吧，与zlib库的类型定义又不兼容。
    compress(buf, &read_cnt, src_str, sizeof(src_str));
    printf("length after compress is %lu, before it was %llu\n", read_cnt, sizeof src_str);
    //uncompress
    uint8_t dst_str[1024]{};
    uncompress(dst_str, &write_cnt, buf, read_cnt);
    printf("length after uncompress is %lu, before it was %lu\n", write_cnt, read_cnt);
    EXPECT_EQ(0, strncmp(reinterpret_cast<const char *>(dst_str),
                         reinterpret_cast<const char *>(src_str), sizeof(src_str)));
    //所以说不要用uint8_t.C语言库本来用了很多char来代替这个概念，约定俗成了，强改的语言不好看。
}