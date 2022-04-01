//
// Created by 叶璨铭 on 2022/3/31.
//

#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <limits>
#include <vector>
namespace cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer;
    class ClosestPoint {
        template<typename T>
        std::tuple<std::array<size_t, 2>, T> findClosestPoint2DImpl(decltype(std::vector<std::array<T, 2>>().cbegin()) cbegin,
                                                                    decltype(std::vector<std::array<T, 2>>().cend()) cend,
                                                                    const std::vector<size_t> &yOrderedIndexes,
                                                                    const std::vector<std::array<T, 2>> &vec2d) const {
            //递归基情况
            size_t size = cend - cbegin;
            assert(size >= 2);
            if (size == 2)
                return {{0, 1}, euclideanDistance(cbegin[0], cbegin[1])};
            //递归求解左右
            size_t mid = size >> 1;
            auto [leftClosestPoint, leftClosestDist] = findClosestPoint2DImpl<T>(cbegin, cbegin + mid, yOrderedIndexes);
            auto [rightClosestPoint, rightClosestDist] = findClosestPoint2DImpl<T>(cbegin + mid, cbegin + size, yOrderedIndexes);
            rightClosestPoint[0] += mid;
            rightClosestPoint[1] += mid;//下标变换为本层下标
            std::array<size_t, 2> mergedClosestPoint{};
            T merged_min_dist{std::numeric_limits<T>::max()};
            //准备归并
            if (leftClosestDist < rightClosestDist) {
                merged_min_dist = leftClosestDist;
                mergedClosestPoint = leftClosestPoint;
            } else {
                merged_min_dist = rightClosestDist;
                mergedClosestPoint = rightClosestPoint;
            }
            T x_left = cbegin[mid][0] - merged_min_dist;
            T x_right = cbegin[mid][0] + merged_min_dist;
#define BoundCheckX(x) \
    if (!(x_left <= (x) && (x) <= x_right)) continue;
            //开始归并，寻找更近的点对
            //重建 中间的、按照y顺序排列的点集。 通过外面拍过的顺序记录来实现按照y顺序排列
            for (int i = 0; i < vec2d.size(); ++i) {

            }
            for (size_t i = 0; i < size; ++i) {
                BoundCheckX(cbegin[i][0])
                        //如果没有continue掉，就是在中间的，而且按照y顺序排好的一系列点。
                        for (size_t j = i + 1, validJ = 0; validJ < 6 && j < size; ++j) {
                    BoundCheckX(cbegin[j][0])
                            validJ++;
                    T dist = euclideanDistance(cbegin[i], cbegin[j]);
                    if (dist < merged_min_dist) {
                        merged_min_dist = dist;
                        mergedClosestPoint = {i, j};
                    }
                }
            }
            return std::make_tuple(mergedClosestPoint, merged_min_dist);
        }

    public:
        template<typename T>
        std::tuple<std::array<size_t, 2>, T> findClosestPoint2D(const std::vector<std::array<T, 2>> &vec2d) const {
            //vec2d 是这样的 {<1, 2>, <3, 4>, ..., <-2, 3>}
            //vec2DWithIndexes 是这样的 {{<1, 2>, 0}, {<3, 4>, 1}, ..., {<-2, 3>, n-1}}
            const auto n = vec2d.size();
            std::vector<std::tuple<std::array<T, 2>, size_t>> vec2DWithIndexes(n);
            for (size_t i = 0; i < n; i++) {
                vec2DWithIndexes[i] = {vec2d[i], i};
            }
            std::sort(std::begin(vec2DWithIndexes), std::end(vec2DWithIndexes),
                      [](std::tuple<std::array<T, 2>, size_t> a, std::tuple<std::array<T, 2>, size_t> b) {
                          return std::get<0>(a)[1] < std::get<0>(b)[1];
                      });// 按照y排序
            //yOrderedIndexes 是这样的 {3,1, ..., 9} 此时，vec2d[3], vec2d[1], ... 构成按y排序的点对。
            std::vector<size_t> yOrderedIndexes(n);
            for (size_t i = 0; i < n; i++) {
                yOrderedIndexes[i] = std::get<1>(vec2DWithIndexes[i]);
            }//记录按照y的顺序，方便算法内部“治”阶段重建点集
            //vec2DWithIndexes 现在是按照x排序的点对。
            std::sort(std::begin(vec2DWithIndexes), std::end(vec2DWithIndexes),
                      [](std::tuple<std::array<T, 2>, size_t> a, std::tuple<std::array<T, 2>, size_t> b) {
                          return std::get<0>(a)[0] < std::get<0>(b)[0];
                      });// 按照x排序
            //
            std::vector<std::array<T, 2>> vec2dSorted(n);
            for (size_t i = 0; i < n; i++) {
                vec2dSorted[i] = std::get<1>(vec2DWithIndexes[i]);
            }//取出点，不要index。
             //根据坐标index翻译答案。
            auto [pair, dist] = findClosestPoint2DImpl<T>(vec2dSorted.cbegin(), vec2dSorted.cend(), yOrderedIndexes, vec2d);
            pair[0] = std::get<1>(vec2DWithIndexes[pair[0]]);
            pair[1] = std::get<1>(vec2DWithIndexes[pair[1]]);
            return std::make_tuple(pair, dist);
        }

        template<typename T>
        std::tuple<int, int> ClosestPoint1D(const std::vector<T> &vec) const {
            assert(vec.size() >= 2);
            std::vector<std::tuple<T, int>> v(vec.size());
            for (int i = 0; i < vec.size(); ++i) {
                v[i] = std::make_tuple(vec[i], i);
            }
            std::sort(v.begin(), v.end(), [](std::tuple<T, int> a, std::tuple<T, int> b) {
                return std::get<0>(a) < std::get<0>(b);
            });
            int min_sorted_index = 0;
            T min_diff = std::get<0>(v[1]) - std::get<0>(v[0]);
            for (int i = 1; i < v.size() - 1; ++i) {
                T diff = std::get<0>(v[i + 1]) - std::get<0>(v[i]);
                if (diff < min_diff) {
                    min_sorted_index = i;
                    min_diff = diff;
                }
            }
            return std::tuple<int, int>{std::get<1>(v[min_sorted_index]), std::get<1>(v[min_sorted_index + 1])};
        }


        template<typename T, size_t N>
        std::array<int, 2> ClosestPointND(const std::vector<std::array<T, N>> &vec_nd) const {
            assert(vec_nd.size() >= 2);
            T min_dist = std::numeric_limits<T>::max();
            std::array<int, 2> min_index{0, 1};
            for (int i = 0; i < vec_nd.size(); i++) {
                for (int j = i + 1; j < vec_nd.size(); j++) {
                    //                min_diff = std::min(min_diff,  this->euclideanDistance(vec_nd[i], vec_nd[j])); 这样就无法获得ij
                    T dist = this->euclideanDistance(vec_nd[i], vec_nd[j]);
                    if (min_dist > dist) {
                        min_dist = dist;
                        min_index[0] = i;
                        min_index[1] = j;
                    }
                }
            }
            return min_index;
        }

        template<typename T, size_t N>
        T euclideanDistance(const std::array<T, N> &a, const std::array<T, N> &b) const {
            T sum = 0;
            for (int i = 0; i < N; ++i) {
                T diff = a[i] - b[i];
                sum += diff * diff;
            }
            return std::sqrt(sum);
        }
    };

}// namespace cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer
