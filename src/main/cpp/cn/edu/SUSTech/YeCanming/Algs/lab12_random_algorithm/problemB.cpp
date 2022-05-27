//
// Created by 叶璨铭 on 2022/5/26.
//
#include <array>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>
#define MapContains(map, key) ((map).count(key) > 0)
struct XiaoYeZi {
    template<typename T>
    size_t operator() (T const &a) const {
        return a[0] + a[1] * 5e5 + a[2] * 25e10;
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
std::array<int64_t, 3> getCubeOf(const std::array<T, 3>& point, const T& currentMinDistance){
    return {int64_t(double(point[0])/currentMinDistance),
            int64_t(double(point[1])/currentMinDistance),
            int64_t(double(point[2])/currentMinDistance)};
}
template<typename T, size_t N, typename It = typename std::vector<std::array<T, N>>::iterator>
T findClosestPointPairND(It first, const It last) {
    const auto size = std::distance(first, last);
    assert(size>=2);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(first, last, g);
    T minDistance = euclideanDistance(first[0], first[1]);
    std::unordered_map<std::array<int64_t, 3>, size_t, XiaoYeZi> dict;
    dict[getCubeOf(first[0], minDistance)] = 0;
    dict[getCubeOf(first[0], minDistance)] = 1;
    for (int i = 2; i < size; ++i) {
        const auto& newPoint = first[i];
        const auto newCube = getCubeOf(newPoint, minDistance);
        bool noSmallerDistance = true;
        constexpr int bound = 7; //2
        for (int j = -bound; j <= bound; ++j) {
            for (int k = -bound; k <= bound; ++k) {
                for (int l = -bound; l <= bound; ++l) {
                    std::array<int64_t, 3> pairedCube = {newCube[0]+j, newCube[1]+k, newCube[2]+l};
                    if(!MapContains(dict, pairedCube))
                        continue;
                    auto newDistance = euclideanDistance(newPoint, first[dict[pairedCube]]);
                    if (newDistance<minDistance){
                        noSmallerDistance = false;
                        minDistance = newDistance;
                    }
                }
            }
        }
        if (noSmallerDistance){
            dict[newCube] = i;
        }else{
            dict.clear();
            for (int j = 0; j <= i; ++j) {
                dict[getCubeOf(first[j], minDistance)] = j;
            }
        }
    }
    return minDistance;
}

int main(){
    size_t N;
    std::cin>>N;
    std::vector<std::array<int64_t, 3>> points(N);
    for(auto&& p:points){
        std::cin>>p[0]>>p[1]>>p[2];
    }
    std::cout<<findClosestPointPairND<int64_t, 3>(points.begin(), points.end())<<std::endl;
    return 0;
}