//
// Created by 叶璨铭 on 2022/4/4.
//
#define NTEST 0
#include "cn/edu/SUSTech/YeCanming/Algs/lab4/ProblemA_Postman.cpp"
#include "gtest/gtest.h"
#include <numeric>
#include <random>
#include <sstream>
namespace cn::edu::SUSTech::YeCanming::Algs::lab4 {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab4;
//    using ThisPackage::solvePostman;
    TEST(TestLab4, Sample1){
        EXPECT_EQ(30, solvePostman(5,4,2,{0, 3,2,1,6}, {{1,3,2}, {4,5,6}, {2,5,10}, {2,3,6}}));
        EXPECT_NE(34, solvePostman(5,4,2,{0, 3,2,1,6}, {{1,3,2}, {4,5,6}, {2,5,10}, {2,3,6}}));
    }
    TEST(TestLab4, Sample2){
        EXPECT_EQ(16, solvePostman(5,4,100,{0, 3,2,1,6}, {{1,3,2}, {4,5,6}, {2,5,10}, {2,3,6}}));
        EXPECT_EQ(16, solvePostman(5,4,std::numeric_limits<int>::max(),{0, 3,2,1,6}, {{1,3,2}, {4,5,6}, {2,5,10}, {2,3,6}}));
    }
    TEST(TestLab4, WhenHouseIs1){
        int N{1}, M{0}, K{100};
        EXPECT_EQ(0, solvePostman(N, M, K, {0}, {}));
    }

}
