//
// Created by 叶璨铭 on 2022/3/31.
//
#include "cn/edu/SUSTech/YeCanming/Algs/ClosestPoint.hpp"
#include "gtest/gtest.h"
#include <boost/log/trivial.hpp>
namespace cn::edu::SUSTech::YeCanming::Algs{
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
    };
    TEST_F(GTestClosestPoint, TestClosestPoint2D){
        auto [cl, d] = closestPoint.ClosestPoint2D(vec2d1);
        EXPECT_EQ(d, 2*sqrt(2));
        EXPECT_EQ(cl[0]+cl[1], 1);
        EXPECT_EQ(std::max(cl[0],cl[1])-std::min(cl[0],cl[1]), 1);
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