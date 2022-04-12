//
// Created by 叶璨铭 on 2022/4/1.
//
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
namespace cn::edu::SUSTech::YeCanming::cpplang {
    TEST(VectorAsDynamicArray, CanTest){
        std::cout<<"hello"<<std::endl;
    }
    TEST(VectorAsDynamicArray, PredefinedSize_AutoInitialization){
        // std::vector<int>
        std::vector<int> vec(10);
        EXPECT_TRUE(std::all_of(vec.begin(), vec.end(), [](int a){
            return a==0;
        }));
        // 单个 A
        struct A {int a; int b;};
        A a;
        EXPECT_NE(a.a, 0);
        EXPECT_NE(a.b, 0);
        // std::vector<A>
        std::vector<A> vec2(10);
        EXPECT_TRUE(std::all_of(vec2.begin(), vec2.end(), [](A a){
            return a.a == 0 && a.b==0;
        }));
    }
    TEST(VectorAsDynamicArray, PredefinedSize1){
        std::vector<std::tuple<int,int>> vec1(10);
        vec1.emplace_back(2,2);
        vec1.push_back({4,3});
        vec1[2] = {9,10};
        EXPECT_EQ(12, vec1.size());
        for (int i = 0; i < vec1.size(); i++) {
            std::cout << std::get<0>(vec1[i]) <<", "<< std::get<1>(vec1[i])<<std::endl;
        }
    }
    TEST(VectorAlgorithms, swap){
        std::vector<double> a{2,3,4};
        std::swap(a[0], a[2]);
        std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
        EXPECT_EQ(a[0], 4);
        EXPECT_EQ(a[2], 2);
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
