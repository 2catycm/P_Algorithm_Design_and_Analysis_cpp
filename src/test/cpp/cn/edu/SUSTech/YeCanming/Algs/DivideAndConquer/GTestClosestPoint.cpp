//
// Created by 叶璨铭 on 2022/3/31.
//
#include "cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/ClosestPoint.hpp"
#include "gtest/gtest.h"
//#include <boost/log/trivial.hpp>
#include <numeric>
#include <random>
#include <sstream>
namespace cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer{
    class GTestClosestPoint : public ::testing::Test {
    protected:
        ClosestPoint closestPoint;
        std::vector<std::array<double, 2>> vec2d1 = {{1, 2},{3, 4}, {2.5, 10}, {10, 2.5}};

        //random
        std::random_device rd;
    };
    TEST_F(GTestClosestPoint, TestClosestPoint2DRandomlyWithND){
        auto m = int(1e7);
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dis(-m, m);

    }
#define TEST_TestClosestPoint2DWhenXAreEqual_single(Name, ...) \
  TEST_F(GTestClosestPoint, TestClosestPoint2DWhenXAreEqualSingle##Name) { \
            std::vector<double> vec1d = { __VA_ARGS__ };                  \
           ASSERT_NE(vec1d.size(), 0);                                                        \
            std::vector<std::array<double, 2>> data(vec1d.size());                   \
            for (int j = 0; j < vec1d.size(); ++j) {\
                data[j] = {20.0, vec1d[j]};\
            }\
            std::stringstream ss;\
            std::copy(vec1d.begin(), vec1d.end(), std::ostream_iterator<double>(ss, ", "));\
            ss<<std::endl;\
            auto resultExpected = closestPoint.findClosestPointPairND<double, 2>(data);\
            auto resultActually = closestPoint.findClosestPointPair2D<double>(data);\
            EXPECT_EQ(std::get<1>(resultExpected),std::get<1>(resultActually))<<ss.str();\
    }
#define TEST_TestClosestPoint2DWhenXAreEqual(Name, m, n, times)\
    TEST_F(GTestClosestPoint, TestClosestPoint2DWhenXAreEqual##Name){\
        std::mt19937 mt(rd());\
        std::uniform_int_distribution<> dis(-(m), m);\
        auto N = n;\
        std::vector<double> vec1d(N);\
        for (int i = 0; i < (times); ++i) {\
            std::generate(vec1d.begin(), vec1d.end(), std::bind(dis, std::ref(mt)));\
            std::vector<std::array<double, 2>> data(N);\
            for (int j = 0; j < N; ++j) {\
                data[j] = {20.0, vec1d[j]};\
            }\
            std::stringstream ss;\
            std::copy(vec1d.begin(), vec1d.end(), std::ostream_iterator<double>(ss, ", "));\
            ss<<std::endl;\
            auto resultExpected = closestPoint.findClosestPointPair1D<double>(vec1d);\
            auto resultActually = closestPoint.findClosestPointPair2D<double>(data);\
            EXPECT_EQ(std::get<1>(resultExpected),std::get<1>(resultActually))<<ss.str();\
        }\
    }
    TEST_TestClosestPoint2DWhenXAreEqual(1, 100, 10, 100)
    TEST_TestClosestPoint2DWhenXAreEqual(2, 1000, 20, 100)
    TEST_TestClosestPoint2DWhenXAreEqual(3, 1000, 100, 100)
    TEST_TestClosestPoint2DWhenXAreEqual(4, 1e7, 1e3, 50)
    TEST_TestClosestPoint2DWhenXAreEqual(5, 1e7, 1e4, 5)

    //为什么过不了，因为原理错了。当x相等时候，不可能只看6个。也不能只看15个。 除非一开始排序的时候，进行先x后y的同比排序，关系才成立。
    TEST_TestClosestPoint2DWhenXAreEqual_single(1, 32, 123, 827, 224, 686, 351, 171, 154, 678, 941, 574, 421, 769, 374, 905, 357, 215, 386, 885, 233)

    TEST_F(GTestClosestPoint, TestClosestPoint2D){
#define Index(it) std::distance(vec2d1.cbegin(),it)
        auto [cl, d] = closestPoint.findClosestPointPair2D<double>(vec2d1);
        EXPECT_EQ(d, 2*sqrt(2));
        EXPECT_EQ(Index(cl[0])+Index(cl[1]), 1);
        EXPECT_EQ(std::max(Index(cl[0]),Index(cl[1]))-std::min(Index(cl[0]),Index(cl[1])), 1);
    }
//    TEST_F(GTestClosestPoint, CanLog){
//        BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
//        BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
//        BOOST_LOG_TRIVIAL(info) << "An informational severity message";
//        BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
//        BOOST_LOG_TRIVIAL(error) << "An error severity message";
//        BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
//    }
}
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}