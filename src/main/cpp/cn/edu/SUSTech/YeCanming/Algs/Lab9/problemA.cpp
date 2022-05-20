//
// Created by 叶璨铭 on 2022/5/5.
//
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
constexpr int MAX_N = 105;
int arrayA[MAX_N];
std::array<int64_t, MAX_N> distances[6];
int N, M, K, S;
std::vector<std::array<int, 2>> edges[MAX_N];
constexpr int64_t INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64_t NINF = std::numeric_limits<decltype(INF)>::min();
constexpr int64_t safeAdd(int64_t a, int64_t b) {
    if (a == INF || b == INF)
        return INF;
    else if (a == NINF || b == NINF)
        return NINF;
    else
        return a + b;
}
/**
 * 复杂度：NM
 * @param distance The distance to be dynamic programming.
 * @return if there is no negative ring, the result is valid, so return true, otherwise false.
 */
bool bellmanFord(std::array<int64_t, MAX_N> &distance) {
    for (int j = 0; j < N - 1; ++j) {
        for (int i = 1; i <= N; ++i) {
            for (const auto &neighbour : edges[i]) {
                auto newCost = safeAdd(distance[i], neighbour[1]);
                distance[neighbour[0]] = std::min(distance[neighbour[0]], newCost);
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (const auto &neighbour : edges[i]) {
            auto newCost = safeAdd(distance[i], neighbour[1]);
            if (newCost < distance[neighbour[0]])
                return false;
        }
    }
    return true;
}
int main() {
    std::cin >> N >> M >> K >> S;//100, 5000, 5, 100
    for (int i = 1; i <= N; ++i) {
        std::cin >> arrayA[i];//int
    }
    for (int i = 0; i < M; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;// 1编号，int
        edges[x].push_back({y, w});
    }
    std::fill(distances[0].begin(), distances[0].end(), INF);
    distances[0][S] = 0;
    auto b = bellmanFord(distances[0]);
    if (!b) {
        std::cout << "INVINCIBLE" << std::endl;
        return 0;
    }
    distances[1] = distances[0];
    for (int i = 0; i < K; ++i) {
        for (int j = 1; j <= N; ++j) {
            distances[1][j] = safeAdd(distances[1][j], arrayA[j]);
        }
        bellmanFord(distances[1]);
        for (int j = 1; j <= N; ++j) {
            distances[1][j] = safeAdd(distances[1][j], -arrayA[j]);
        }
        bellmanFord(distances[1]);
    }
    auto cost = INF;
    for (int i = 1; i <= N; ++i) {
        cost = std::min(cost, distances[1][i]);
    }
    std::cout << -cost << std::endl;
    return 0;
}