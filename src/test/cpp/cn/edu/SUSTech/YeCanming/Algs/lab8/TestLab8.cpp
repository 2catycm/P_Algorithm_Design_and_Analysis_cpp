//
// Created by 叶璨铭 on 2022/5/3.
//
#define TEST 1
#include "cn/edu/SUSTech/YeCanming/Algs/lab8/problemB.cpp"
#include "gtest/gtest.h"
#include <numeric>
#include <random>
#include <sstream>
namespace cn::edu::SUSTech::YeCanming::Algs::lab8 {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab8;
    TEST(Lab8ProblemB_BruteForce2D, sample) {
        auto re = bruteForce2D({{}, {0, 1}, {1, 0}, {1, 1}});
        EXPECT_EQ(1, re);
        re = bruteForce2D({{}, {1, 0}, {9, 8}, {3, 2}, {5, 9}});
        EXPECT_EQ(9, re);
    }
    TEST(Lab8ProblemB_BruteForce1D, sample) {
        auto re = bruteForce1D({{}, {0, 1}, {1, 0}, {1, 1}});
        EXPECT_EQ(1, re);
        re = bruteForce1D({{}, {1, 0}, {9, 8}, {3, 2}, {5, 9}});
        EXPECT_EQ(9, re);
    }
    std::random_device rd;

    TEST(Lab8ProblemB_Crashes, middle) {
        auto N = 5000;
        std::vector<std::array<int, 2>> bugs(N + 1);
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dis(0, 1e9);
        for (int i = 0; i < 10; ++i) {
            for (int j = 1; j <= N; ++j) {
                bugs[j] = {dis(mt), dis(mt)};
            }
            auto reB1D = bruteForce1D(bugs);
            auto reB2D = bruteForce2D(bugs);
            if (reB1D!=reB2D) {
                std::stringstream ss("At vector: \n{");
                for (int j = 1; j <= N; ++j) {
                    ss << "(" << bugs[j][0] << "," << bugs[j][1] << "), ";
                }
                EXPECT_EQ(reB1D, reB2D) << ss.str();
            }
        }
    }
    TEST(Lab8ProblemB_BruteForce1D, middle) {
        auto N = 5000;
        std::vector<std::array<int, 2>> bugs(N + 1);
        auto re = bruteForce1D(bugs);
        EXPECT_EQ(0, re)<<re;
    }
    TEST(Lab8ProblemB_BruteForce1D, large) {
        auto N = 50000;
        std::vector<std::array<int, 2>> bugs(N + 1);
        auto re = bruteForce1D(bugs);
        EXPECT_EQ(0, re)<<re;
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::lab8
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}