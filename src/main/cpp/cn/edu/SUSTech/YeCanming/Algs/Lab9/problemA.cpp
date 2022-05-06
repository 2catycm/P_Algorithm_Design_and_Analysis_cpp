//
// Created by 叶璨铭 on 2022/5/5.
//
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include <array>
//using ll = int64_t;
constexpr int MAX_N = 105;
int arrayA[MAX_N];
std::array<int64_t, MAX_N> distance;
int N, M, K, S;
std::vector<std::array<int, 2>> edges[MAX_N];
void solve(){
    std::fill(distance.begin(), distance.end(), std::numeric_limits<decltype(distance)::value_type>::max());
    distance[S] = 0;
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N; ++j) {

        }
    }
}
int main() {
    std::cin >> N >> M >> K >> S;
    for (int i = 1; i <= N; ++i) {
        std::cin >> arrayA[i];
    }
    for (int i = 0; i < M; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        edges[x].push_back({y, w});
    }
    solve();
    return 0;
}