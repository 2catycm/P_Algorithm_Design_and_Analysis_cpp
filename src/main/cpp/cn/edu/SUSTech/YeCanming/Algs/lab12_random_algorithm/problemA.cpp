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
    constexpr auto negativeInf = std::numeric_limits<int64_t>::min();
    constexpr int64_t safeAdd(const int64_t& a, const int64_t& b){
        if (a==negativeInf || b==negativeInf)
            return negativeInf;
        else
            return a+b;
    }
    template<class InputIt, class T, class BinaryOperation>
    constexpr // since C++20
    T accumulate(InputIt first, InputIt last, T init, BinaryOperation op){
        for (; first != last; ++first) {
            init = op(std::move(init), *first); // std::move since C++20
        }
        return init;
    }

    struct Word{
        int length{0}; //[1, 1000]
        int elegance{0}; // same range as int
    };
    /**
     * 输入一个word的集合，给定容量限制。
     * 输出这个集合的最大优雅程度。
     * 其中，允许了 -capacity 到 +capacity 的容量限制，允许负的权重
     */
    template <class It>
    auto _knapsack01(It first, It last, uint64_t capacity){
        const auto size = std::distance(first, last);
        std::vector<int64_t> opt(2*capacity+1);
        std::fill(opt.begin(),  opt.end(), negativeInf);

        opt[capacity] = 0; // 容量为0的时候，目前已知最大优雅度是0.
        for (;first!=last; ++first) {
            auto& word = first[0];
            auto& wordLength = word.length;
            if (wordLength > 0){
                for (int64_t j = int64_t(opt.size())-1; j >=wordLength; --j) { //倒过来求，就可以避免读取了修改过的值。 否则是错的，多次使用了同一个物品。
                    //可以选择加上这个word，或者不加。
                    opt[j] = std::max(opt[j], safeAdd(opt[j -word.length], word.elegance));
                }
            }else if (wordLength<0){
                for (int64_t j = 0; j < opt.size()+wordLength; ++j) {
                    //可以选择加上这个word，或者不加。
                    opt[j] = std::max(opt[j], safeAdd(opt[j -word.length], word.elegance));
                }
            }
        }
        return opt;
    }
    template <class It>
    int64_t goodSolve(It seaFloweryFirst, It fluffyBunnyFirst, It fluffyBunnyLast){
        auto maxer = [](const int& a, const Word& b){return std::max(a, b.length);};
        int lengthSum1 = ThisPackage::accumulate(seaFloweryFirst, fluffyBunnyFirst, uint64_t(0), maxer);
        int lengthSum2 = ThisPackage::accumulate(fluffyBunnyFirst, fluffyBunnyLast, uint64_t(0), maxer);
        auto maximumLength = std::max(lengthSum1, -lengthSum2);
        int threeSigma = 3* 2*maximumLength * 2*std::sqrt(std::distance(seaFloweryFirst, fluffyBunnyLast) / 12);
        threeSigma/=2;
        assert(threeSigma>=0);
        for (It it = fluffyBunnyFirst; it!=fluffyBunnyLast; ++it){
            it->length *=-1;
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(seaFloweryFirst, fluffyBunnyLast, g);
        auto opt = _knapsack01(seaFloweryFirst, fluffyBunnyLast, threeSigma);
        return opt[threeSigma];
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
        std::cout<< goodSolve(words.begin(), words.begin()+N, words.end())<<std::endl;

    }
    return 0;
}