//
// Created by 叶璨铭 on 2022/5/3.
//
#pragma GCC optimize(3)
#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>
#include <array>
#include <limits>

int64_t bruteForce(const std::vector<std::array<int, 2>>& bugs){
    auto N = bugs.size()-1;
    if (N<=2)
        return 0;
    std::vector<int64_t> _map((N+1)*N);
    std::fill(_map.begin(), _map.end(), std::numeric_limits<decltype(_map)::value_type>::max());
#define OPT(i, j) _map[(i)*(N)+(j)]
    auto cost = [&](int i, int j){
        auto& bugI = bugs[i];
        auto& bugJ = bugs[j];
        return std::abs(bugI[0]-bugJ[0])+std::abs(bugI[1]-bugJ[1]);
    };
    OPT(1,0) = OPT(2,1) = 0;
    OPT(2,0) = cost(1,2);
    for (int i = 3; i <= N; ++i) {
        for (int j = 0; j <= i-2; ++j) {
            OPT(i, j) = OPT(i-1, j)+cost(i-1, i);
        }
        for (int j = 0; j <= i-2; ++j) {
            OPT(i, i-1) = std::min(OPT(i, i-1), OPT(i-1, j)+cost(j, i));
        }
    }
    int64_t result = std::numeric_limits<decltype(result)>::max();
    for (int j = 0; j <= N-1; ++j) {
        result = std::min(result, OPT(N, j));
    }
    return result;
#undef OPT
}
int64_t solve(const std::vector<std::array<int, 2>>& bugs){
    auto N = bugs.size()-1;
    std::vector<int64_t> _prefix_sum(N+1);
    for (int i = 0; i < N + 1; ++i) {

    }
}
int main(){
    std::ios::sync_with_stdio(false);
    int N; //number of bugs, <5000 or 50000
    std::cin>>N;
    std::vector<std::array<int, 2>> bugs(N+1);
    for (int i = 1; i <= N; ++i) {
        std::cin>>bugs[i][0]>>bugs[i][1];
    }
    auto answer = N<=5000?bruteForce(bugs):solve(bugs);
    std::cout<<answer<<std::endl;
    return 0;
}