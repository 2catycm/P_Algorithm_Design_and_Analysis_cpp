//
// Created by 叶璨铭 on 2022/4/1.
//
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
namespace cn::edu::SUSTech::YeCanming::std_containers {
    TEST(VectorAsDynamicArray, CanTest){
        std::cout<<"hello"<<std::endl;
    }
    TEST(VectorAsDynamicArray, PredefinedSize){
        std::vector<std::tuple<int,int>> vec1(10);
        vec1.emplace_back(2,2);
        vec1.push_back({4,3});
        vec1[2] = {9,10};
        EXPECT_EQ(12, vec1.size());
        for (int i = 0; i < vec1.size(); i++) {
            std::cout << std::get<0>(vec1[i]) <<", "<< std::get<1>(vec1[i])<<std::endl;
        }
    }
}

int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
