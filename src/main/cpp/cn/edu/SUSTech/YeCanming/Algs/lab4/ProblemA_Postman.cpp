//
// Created by 叶璨铭 on 2022/4/3.
//

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
namespace cn::edu::SUSTech::YeCanming::Algs::lab4 {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab4;
    struct Letter {
        int from, to, appearTime;
    }
    int64_t solvePostman(int N, int M, int K,
                 std::vector<int>& distances,
                 const std::vector<Letter>& letters) {

    }
}}// namespace cn::edu::SUSTech::YeCanming::Algs::lab4
#ifndef NTEST
#define NTEST 1
#endif
#if NTEST
namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab4;
int main() {
    int N, M, K; std::cin>>N>>M>>K; //1:1e4, 1:5e5, 1:100
    std::vector<int> distances(N-1);
    for (int i = 0; i < N; ++i) {
        std::cin>>distances[i]; //0:1e9
    }
    std::vector<ThisPackage::Letter>& letters(M);
    for (int i = 0; i < M; ++i) {
        ThisPackage::Letter newLetter;
        std::cin>>newLetter.from>>newLetter.to>>newLetter.appearTime;
        letters[i] = newLetter; //复制进去
    }
    std::cout<<ThisPackage::solvePostman(N, M, K, distances, letters)<<std::endl;
    return 0;
}
#endif //NTEST