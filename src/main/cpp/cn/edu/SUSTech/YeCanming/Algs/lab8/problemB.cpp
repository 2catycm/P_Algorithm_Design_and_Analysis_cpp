//
// Created by 叶璨铭 on 2022/5/3.
//
#pragma GCC optimize(3)
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
namespace cn::edu::SUSTech::YeCanming::Algs::lab8 {
#define DefineCost()                                                      \
    auto cost = [&](int i, int j) {                                       \
        auto &bugI = bugs[i];                                             \
        auto &bugJ = bugs[j];                                             \
        return std::abs(bugI[0] - bugJ[0]) + std::abs(bugI[1] - bugJ[1]); \
    };
    int64_t bruteForce2D(const std::vector<std::array<int, 2>> &bugs) {
        auto N = bugs.size() - 1;
        if (N <= 2)
            return 0;
        DefineCost();
        std::vector<int64_t> _map((N + 1) * N);
        std::fill(_map.begin(), _map.end(), std::numeric_limits<decltype(_map)::value_type>::max());
#define OPT(i, j) _map[(i) * (N) + (j)]
        OPT(1, 0) = OPT(2, 1) = 0;
        OPT(2, 0) = cost(1, 2);
        for (int i = 3; i <= N; ++i) {
            for (int j = 0; j <= i - 2; ++j) {
                OPT(i, j) = OPT(i - 1, j) + cost(i - 1, i);
            }
            for (int j = 0; j <= i - 2; ++j) {
                OPT(i, i - 1) = std::min(OPT(i, i - 1), OPT(i - 1, j) + cost(j, i));
            }
        }
        int64_t result = std::numeric_limits<decltype(result)>::max();
        for (int j = 0; j <= N - 1; ++j) {
            result = std::min(result, OPT(N, j));
        }
        return result;
#undef OPT
    }
    int64_t bruteForce1D(const std::vector<std::array<int, 2>>& bugs){
        auto N = bugs.size()-1;
        DefineCost();
        std::vector<int64_t> _prefix_sum(N+1);
        for (int i = 2; i <= N ; ++i) {
            _prefix_sum[i] = _prefix_sum[i-1]+cost(i-1, i);
        }
        std::vector<int64_t> _map(N);
        std::fill(_map.begin(), _map.end(), std::numeric_limits<decltype(_map)::value_type>::max());
    #define CostSum(i, j) _prefix_sum[(j)]-_prefix_sum[(i)]
    #define OPT1D(i) _map[i]
    #define OPT2D(i, j) _map[j]+CostSum((j)+1, i)
        OPT1D(0)=0; //OPT(1,0)=0
        OPT1D(1)=0; //OPT(2,1)=0
        for (int i = 2; i < N; ++i) {
            //正在算OPT(i+1, i),  比如 4, 3
            for (int j = 0; j <= i-1; ++j) {
                OPT1D(i) = std::min(OPT1D(i), OPT2D(i, j)+cost(j,i+1));
            }
        }
        int64_t result = std::numeric_limits<decltype(result)>::max();
        for (int j = 0; j <= N - 1; ++j) {
            result = std::min(result, OPT2D(N, j));
        }
        return result;
    #undef CostSum
    #undef OPT1D
    #undef OPT2D
    }
#undef DefineCost
}// namespace cn::edu::SUSTech::YeCanming::Algs::lab4
#ifndef TEST
#define TEST 0
#endif
#if !TEST
using namespace cn::edu::SUSTech::YeCanming::Algs::lab8;
int main() {
    std::ios::sync_with_stdio(false);
    int N;//number of bugs, <5000 or 50000
    std::cin >> N;
    std::vector<std::array<int, 2>> bugs(N + 1);
    for (int i = 1; i <= N; ++i) {
        std::cin >> bugs[i][0] >> bugs[i][1];
    }
    //    auto answer = N<=5000?bruteForce(bugs):solve(bugs);
//    auto answer = N <= 5000 ? bruteForce2D(bugs) : bruteForce2D(bugs);
    auto answer = N <= 5000 ? bruteForce1D(bugs) : bruteForce1D(bugs);
    std::cout << answer << std::endl;
    return 0;
}
#endif//!TEST