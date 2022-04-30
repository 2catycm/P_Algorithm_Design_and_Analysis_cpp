//
// Created by 叶璨铭 on 2022/4/30.
//
#include "cn/edu/SUSTech/YeCanming/Algs/Zip/structures/RingQueue.hpp"
#include "cn/edu/SUSTech/YeCanming/Judge/GTestExtensions.hpp"
#include <gtest/gtest.h>
namespace cn::edu::SUSTech::YeCanming::Algs::Zip {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::Zip;
    using ThisPackage::utilities::RingQueue;
    TEST(TestRingQueue, WhenFull) {
        RingQueue<int, 3> a;
        EXPECT_TRUE(a.isEmpty());
        EXPECT_FALSE(a.isFull());
        a.push(20);
        a.push(20);
        EXPECT_FALSE(a.isFull());
        EXPECT_FALSE(a.isEmpty());
        a.push(20);
        EXPECT_TRUE(a.isFull());
        EXPECT_FALSE(a.isEmpty());
        a.pop();
        EXPECT_FALSE(a.isFull());
        EXPECT_FALSE(a.isEmpty());
        a.push(20);
        EXPECT_TRUE(a.isFull());
        EXPECT_FALSE(a.isEmpty());
    }
    TEST(TestRingQueue, Simple) {
        RingQueue<int, 10> a;
        a.push(10);
        a.push(9);
        a.push(8);
        a.push(7);
        a.push(6);
        int sum = 0;
        a.rear2frontTraversal([&](const int &i) {
            sum += i;
            return i == 7;
        });
        EXPECT_EQ(6 + 7, sum);
        EXPECT_EQ(6, a.back());
        EXPECT_EQ(10, a.front());
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::Zip