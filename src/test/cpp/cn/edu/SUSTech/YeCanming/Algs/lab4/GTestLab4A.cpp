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
    TEST(TestLab4, Sample1){
        EXPECT_EQ(30, ThisPackage::solvePostman(5,4,2,{0, 3,2,1,6}, {{1,3,2}, {4,5,6}, {2,5,10}, {2,3,6}}));
    }
}
