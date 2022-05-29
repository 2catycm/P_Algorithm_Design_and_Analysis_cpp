//
// Created by 叶璨铭 on 2022/5/27.
//
#define OJTEST 1
#include "cn/edu/SUSTech/YeCanming/Algs/lab12_random_algorithm/problemB.cpp"
#include "gtest/gtest.h"
#include <numeric>
#include <random>
#include <sstream>
#include <chrono>
using namespace std::chrono;
std::random_device rd;
#define TEST_Speed_When_N_Is_(N, Name)\
TEST(Lab12BSpeed, Name) {\
    std::vector<std::array<int64_t, 3>> points(N);\
    std::mt19937 mt(rd());\
    std::uniform_int_distribution<> dis(0, 1e9);\
    for (auto&& point:points){\
        point = {dis(mt), dis(mt), dis(mt)};\
    }\
    auto start = system_clock::now();\
    findClosestPointPairND<int64_t, 3>(points.begin(), points.end());\
    auto end   = system_clock::now();\
    auto duration = duration_cast<microseconds>(end - start);\
    std::cout <<  "花费了"\
         << double(duration.count()) * microseconds::period::num / microseconds::period::den\
         << "秒" << std::endl;         \
    std::cout<<"重建字典"<<crashCnt<<"次。"<<std::endl;\
    std::cout<<"重建使用了"<<crashCost<<"次操作"<<std::endl;\
}
TEST_Speed_When_N_Is_(5e5, VeryBig); // 76万
TEST_Speed_When_N_Is_(100000, Middle2); //22万
TEST_Speed_When_N_Is_(10000, Middle); // 3万
TEST_Speed_When_N_Is_(1000, Small); // 2000


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}