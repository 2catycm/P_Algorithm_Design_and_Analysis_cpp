//
// Created by 叶璨铭 on 2022/3/31.
//
#include "cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/ClosestPoint.hpp"
#include "gtest/gtest.h"
#include <boost/log/trivial.hpp>
#include <numeric>
#include <random>
#include <sstream>
namespace cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer{
    class GTestClosestPoint : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if their bodies would
        // be empty.
        GTestClosestPoint() {
            // You can do set-up work for each test here.
        }
        ~GTestClosestPoint() override {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        void SetUp() override {
            // Code here will be called immediately after the constructor (right
            // before each test).
        }

        void TearDown() override {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }
        // Class members declared here can be used by all tests in the test suite
        // for Foo.
        ClosestPoint closestPoint;
        std::vector<std::array<double, 2>> vec2d1 = {{1, 2},{3, 4}, {2.5, 10}, {10, 2.5}};

        //random
        std::random_device rd;
    };
    TEST_F(GTestClosestPoint, TestClosestPoint2DWhenXAreEqual){
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dis(0, 9);
        auto N = 100;
        std::vector<double> vec1d(N);
        for (int i = 0; i < 100; ++i) {
            std::generate(vec1d.begin(), vec1d.end(), std::bind(dis, std::ref(mt)));
            std::vector<std::array<double, 2>> data(N);
            for (int j = 0; j < N; ++j) {
                data[j] = {20.0, vec1d[j]};
            }
            std::stringstream ss;
            std::copy(vec1d.begin(), vec1d.end(), std::ostream_iterator<double>(ss, " "));
            ss<<std::endl;
            auto resultExpected = closestPoint.findClosestPointPairND<double, 2>(data);
            auto resultActually = closestPoint.findClosestPointPair2D<double>(data);
            EXPECT_EQ(std::get<1>(resultExpected),std::get<1>(resultActually))<<ss.str();
        }
    }
    TEST_F(GTestClosestPoint, TestClosestPoint2D){
#define Index(it) std::distance(vec2d1.cbegin(),it)
        auto [cl, d] = closestPoint.findClosestPointPair2D<double>(vec2d1);
        EXPECT_EQ(d, 2*sqrt(2));
        EXPECT_EQ(Index(cl[0])+Index(cl[1]), 1);
        EXPECT_EQ(std::max(Index(cl[0]),Index(cl[1]))-std::min(Index(cl[0]),Index(cl[1])), 1);
    }
    TEST_F(GTestClosestPoint, CanLog){
        BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
        BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
        BOOST_LOG_TRIVIAL(info) << "An informational severity message";
        BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
        BOOST_LOG_TRIVIAL(error) << "An error severity message";
        BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
    }
}
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}