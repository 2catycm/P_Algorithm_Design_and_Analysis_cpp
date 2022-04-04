//
// Created by 叶璨铭 on 2022/4/3.
//
#define NTEST 0
#include "cn/edu/SUSTech/YeCanming/Algs/lab4/ProblemB_ManhattanServers.cpp"
#include "gtest/gtest.h"
#include <numeric>
#include <random>
#include <sstream>
namespace cn::edu::SUSTech::YeCanming::Algs::lab4 {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab4;
//#define TEST_maximumSpanningTreeDistance(Name, resultExpected, ...)\
//    TEST(GTestLab4B, maximumSpanningTreeDistance##Name){\
//        std::vector<int> chebyShevX = {__VA_ARGS__};\
//        const auto result = ThisPackage::maximumSpanningTreeDistance(chebyShevX.begin(), chebyShevX.end());\
//        EXPECT_EQ(resultExpected, result);\
//    }
//    TEST_maximumSpanningTreeDistance(1, 7, 0,2,7,10,11)
//    TEST_maximumSpanningTreeDistance(1_5, 7, 11, 7, 2, 10, 0)
//    TEST_maximumSpanningTreeDistance(2, 10, 0,10,11,12,13)
//    TEST_maximumSpanningTreeDistance(3, 10, -10,0,1,2,3)
//    TEST_maximumSpanningTreeDistance(4, 10, 3,-10, 2,0, 1)
//
//    TEST_maximumSpanningTreeDistance(5, 12, 0,2,12,17, 18)
//
//    TEST(GTestLab4B, Sample1){
//        std::vector<int> chebyShevX = {-5, -2, 1, 2, 3};
//        std::vector<int> chebyShevY = {1, -2, 3, 2, 3};
//        const auto result = std::max(ThisPackage::maximumSpanningTreeDistance(chebyShevX.begin(), chebyShevX.end()),
//                 ThisPackage::maximumSpanningTreeDistance(chebyShevY.begin(), chebyShevY.end()));
//        EXPECT_EQ(result, 5);
//    }
}
int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}