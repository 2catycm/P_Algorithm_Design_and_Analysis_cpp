//
// Created by 叶璨铭 on 2022/4/2.
//
#include "gtest/gtest.h"
#include <boost/log/trivial.hpp>
#include <numeric>
#include <algorithm>
#include <vector>
#include "cn/edu/SUSTech/YeCanming/Algs/DivideAndConquer/BinarySearch.h"
namespace cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer;
    TEST(GTestBinarySearch, UsedToFindElement){
        std::vector<int> a(10);
        std::iota(a.begin(), a.end(), 0); //0,1,2,...,9
        auto result = ThisPackage::binary_search_for_last_satisfies(a.begin(), a.end(), [](const int& a){
            return a<=5;
        });
        EXPECT_EQ(*result, 5);
        auto resultC = ThisPackage::binary_search_for_last_satisfies(a.cbegin(), a.cend(), [](const int& a){
            return a<=5;
        });
        EXPECT_EQ(*resultC, 5);
    }
    TEST(GTestBinarySearch, WhenSatifactionSequenceAreAllZero){
        std::vector<int> a(10);
        std::fill(a.begin(), a.end(), 10);
        auto result = ThisPackage::binary_search_for_last_satisfies(a.begin(), a.end(), [](const int& a){
            return a>11;
        });
        EXPECT_EQ(result, a.end());
        auto resultC = ThisPackage::binary_search_for_last_satisfies(a.cbegin(), a.cend(), [](const int& a){
            return a>11;
        });
        EXPECT_EQ(result, a.cend());
    }
}
int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}