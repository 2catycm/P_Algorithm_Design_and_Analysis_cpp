//
// Created by 叶璨铭 on 2022/3/31.
//
#include "gtest/gtest.h"
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
    };
    TEST_F(GTestClosestPoint, CanRun){
        ASSERT_EQ(1, 1);
    }
}
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}