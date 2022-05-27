//
// Created by 叶璨铭 on 2022/5/27.
//
/**
    Auf Wiedersehen
    I got a lot of nasty things blowing up in my head
    But none of them are worth my time
    You ain't even worth this rhyme
    And I don't I don't give a flying
*/
#include <array>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>
namespace cn::edu::SUSTech::YeCanming::Algs::lab12 {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab12;
    template<class InputIt, class T, class BinaryOperation>
    constexpr // since C++20
    T accumulate(InputIt first, InputIt last, T init, BinaryOperation op){
        for (; first != last; ++first) {
            init = op(std::move(init), *first); // std::move since C++20
        }
        return init;
    }

    struct Word{
        size_t length{0}; //[1, 1000]
        int elegance{0}; // same range as int
    };
    /**
     * 输入一个word的集合，给定容量限制。
     * 输出这个集合的最大优雅程度。
     */
    template <class It>
    int64_t knapsack01(It first, It last, uint64_t capacity){
        const auto size = std::distance(first, last);
        std::vector<int64_t> opt(capacity+1);
        std::fill(opt.begin(),  opt.end(), std::numeric_limits<decltype(opt)::value_type>::min());
        opt[0] = 0; // 容量为0的时候，目前已知最大优雅度是0.
        for (;first!=last; ++first) {
            auto& word = first[0];
            for (int64_t j = int64_t(opt.size())-1; j >=0 ; --j) { //倒过来求，就可以避免读取了修改过的值。
                if (word.length > j)
                    continue;
                //可以选择加上这个word，或者不加。
                opt[j] = std::max(opt[j], opt[j -word.length]+word.elegance);
            }
        }
        return opt[capacity];
    }
    template <class It>
    int64_t bruteForceSolve(It seaFloweryFirst, It fluffyBunnyFirst, It fluffyBunnyLast) {
        auto adder = [](const uint64_t& a, const Word& b){return a+b.length;};
        uint64_t lengthSum1 = ThisPackage::accumulate(seaFloweryFirst, fluffyBunnyFirst, uint64_t(0), adder);
        uint64_t lengthSum2 = ThisPackage::accumulate(fluffyBunnyFirst, fluffyBunnyLast, uint64_t(0), adder);
        auto maximumLength = std::max(lengthSum1, lengthSum2);
        auto bestResult = std::numeric_limits<int64_t>::min();
        for (int i = 0; i < maximumLength; ++i) {
            bestResult = std::max(bestResult,
                knapsack01(seaFloweryFirst, fluffyBunnyFirst, i)+
                knapsack01(fluffyBunnyFirst, fluffyBunnyLast, i));
        }
        return bestResult;
    }
}
using namespace cn::edu::SUSTech::YeCanming::Algs::lab12;
int main(){
    size_t T; //[1, 10]
    std::cin>>T;
    for (size_t i = 0; i < T; ++i) {
        size_t N, M; //[1, 1000]  而且 T个case加起来不超过5000.
        std::cin>>N>>M;
        std::vector<Word> words(N+M);
        for (auto&& w:words)
            std::cin>>w.length>>w.elegance;
        std::cout<< bruteForceSolve(words.begin(), words.begin()+N, words.end())<<std::endl;
    }
    return 0;
}