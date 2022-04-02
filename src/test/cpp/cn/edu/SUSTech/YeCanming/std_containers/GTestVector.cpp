//
// Created by 叶璨铭 on 2022/4/1.
//
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>
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
    TEST(VectorAlgorithms, merge){
        //ref: https://zh.cppreference.com/w/cpp/algorithm/merge
        // 以随机数填充 vector
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dis(0, 9);

        std::vector<int> v1(10), v2(10);
        std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
        std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));

        // 排序
        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());

        // 输出 v1
        std::cout << "v1 : ";
        std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';

        // 输出 v2
        std::cout << "v2 : ";
        std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';

        // 归并
        std::vector<int> dst;
        std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));

        // 输出
        std::cout << "dst: ";
        std::copy(dst.begin(), dst.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';

        ASSERT_TRUE(std::is_sorted(dst.begin(), dst.end()));
    }
    TEST(VectorAlgorithms, find){
        //ref: https://zh.cppreference.com/w/cpp/algorithm/find
        std::vector<int> v{1, 2, 3, 4};
        int n1 = 3;
        int n2 = 5;
        auto is_even = [](int i){ return i%2 == 0; };
        auto result1 = std::find(begin(v), end(v), n1);
        auto result2 = std::find(begin(v), end(v), n2);
        auto result3 = std::find_if(begin(v), end(v), is_even);
        (result1 != std::end(v))
                ? std::cout << "v contains " << n1 << '\n'
                : std::cout << "v does not contain " << n1 << '\n';
        EXPECT_NE(result1, std::end(v));
        (result2 != std::end(v))
                ? std::cout << "v contains " << n2 << '\n'
                : std::cout << "v does not contain " << n2 << '\n';
        EXPECT_EQ(result1, std::end(v));
        (result3 != std::end(v))
                ? std::cout << "v contains an even number: " << *result3 << '\n'
                : std::cout << "v does not contain even numbers\n";
        EXPECT_EQ(result3, std::end(v));
    }
}

int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}