//
// Created by 叶璨铭 on 2022/5/26.
//
#pragma GCC optimize(3)
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <tuple>
#include <unordered_map>
#include <map>
#include <vector>

#include <string>
//#include <omp.h>
#define DEBUG true
#define MyLog if(DEBUG)\
                std::clog
#define MapContains(map, key) ((map).count(key) > 0)
int crashCnt{0};
int64_t crashCost{0};
struct XiaoYeZi {
    static constexpr int pigeons = 5e5;   // 有5e5个数。
    static constexpr int states = 1e9 + 1;// 每个数的取值是1e9
    static constexpr int holeNumber = states / pigeons;
    template<typename T>
    size_t operator()(T const &a) const {
//        return a[0] + a[1] * states + a[2] * states * states;//14s  //18.8035秒
        return (a[0] + a[1] * states + a[2] * states * states)%(pigeons); //12s
//        return (a[0] + a[1] * states + a[2] * states * states)%(pigeons+23);

//        return std::hash<std::string_view>{}(std::to_string(a[0])+std::to_string(a[1])+std::to_string(a[2]));
//                 return a[0] + a[1] * pigeons + a[2] * pigeons* pigeons;  //18s
         //        return a[0]%pigeons + a[1]%pigeons * pigeons + a[2]%pigeons * pigeons * pigeons; //20s
         //        return a[0] + a[1] * 2e3 + a[2] * 4e6; //18s
         //        return (a[0]/holeNumber + a[1]/holeNumber * holeNumber + a[2]/holeNumber * holeNumber * holeNumber); // 永远跑不出来
    }
    template<typename T>
    bool operator()(T const &a, T const &b) const {
        if (a[0]==b[0]){
            if (a[1]==b[1])
                return a[2]<b[2];
            return a[1]<b[1];
        }
        return a[0]<b[0];
    }
};

template<typename T, size_t K>
T euclideanDistance(const std::array<T, K> &a, const std::array<T, K> &b) {
    T sum = 0;
    for (int i = 0; i < K; ++i) {
        T diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sum;
}
template<class T>
std::array<int64_t, 3> getCubeOf(const std::array<T, 3> &point, const T &currentMinDistance) {
    return {int64_t(2 * double(point[0]) / std::sqrt(currentMinDistance)),
            int64_t(2 * double(point[1]) / std::sqrt(currentMinDistance)),
            int64_t(2 * double(point[2]) / std::sqrt(currentMinDistance))};
}
template<typename T, size_t N, typename It = typename std::vector<std::array<T, N>>::iterator>
T findClosestPointPairND(It first, const It last) {
    crashCnt = 0, crashCost = 0;
    const auto size = std::distance(first, last);
    assert(size >= 2);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(first, last, g);
    T minDistance = euclideanDistance(first[0], first[1]);
    std::unordered_map<std::array<int64_t, 3>, size_t, XiaoYeZi> dict;
//    std::map<std::array<int64_t, 3>, size_t, XiaoYeZi> dict;
    dict[getCubeOf(first[0], minDistance)] = 0;
    dict[getCubeOf(first[0], minDistance)] = 1;
    for (int i = 2; i < size; ++i) {
        const auto &newPoint = first[i];
        const auto newCube = getCubeOf(newPoint, minDistance);
        bool noSmallerDistance = true;
        constexpr int bound = 2;//2
//#pragma omp parallel for
        for (int j = -bound; j <= bound; ++j) {
            for (int k = -bound; k <= bound; ++k) {
                for (int l = -bound; l <= bound; ++l) {
                    std::array<int64_t, 3> pairedCube = {newCube[0] + j, newCube[1] + k, newCube[2] + l};
                    if (!MapContains(dict, pairedCube))
                        continue;
                    auto newDistance = euclideanDistance(newPoint, first[dict[pairedCube]]);
                    if (newDistance < minDistance) {
                        noSmallerDistance = false;
                        minDistance = newDistance;
//                        goto out;
                    }
                }
            }
        }
//        out:
        if (noSmallerDistance) {
            dict[newCube] = i;
        } else {
            crashCnt++;
            dict.clear();
            for (int j = 0; j <= i; ++j) {
                dict[getCubeOf(first[j], minDistance)] = j;
            }
            crashCost+=i+1;
            MyLog<<"本次重建消耗"<<i+1<<"次操作"<<std::endl;
        }
    }
    return minDistance;
}

#if !OJTEST
int main() {
    size_t N;
    std::cin >> N;
    std::vector<std::array<int64_t, 3>> points(N);
    for (auto &&p : points) {
        std::cin >> p[0] >> p[1] >> p[2];
    }
    std::cout << findClosestPointPairND<int64_t, 3>(points.begin(), points.end()) << std::endl;
    return 0;
}
#endif