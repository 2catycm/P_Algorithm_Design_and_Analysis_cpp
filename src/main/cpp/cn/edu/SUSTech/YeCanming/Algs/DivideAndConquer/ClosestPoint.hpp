//
// Created by 叶璨铭 on 2022/3/31.
//

#pragma once
#include "BinarySearch.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <limits>
#include <vector>
namespace cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::DivideAndConquer;
    class ClosestPoint {
    public:
        template<typename T>
        std::tuple<std::array<size_t, 2>, T> findClosestPointPair2D(const std::vector<std::array<T, 2>> &vec2d) const {
            return findClosestPointPair2D(vec2d.cbegin(), vec2d.cend());
        }
        /**
         * Efficient algorithm implementation for finding closest 2d point pair among a set of points.
         * @tparam T the number type of 2d points. For example, <1,-2> is a int point and <2.0, -10> is a double point.
         * the type of the point is assumed to be std::array<T, 2>.
         * @param first the inclusive start of the range where you want to  find the closest 2d point pair.
         * @param last the exclusive end of the range where you want to find the closest 2d point pair.
         * first and last should be const_iterator of std::vector<std::array<T, 2>>.
         * @return a tuple [pair, dist] where pair is the two iterators whose points are closest and dist is the smallest distance.
         * Time complexity: if N = std::distance(first, last), then the time complexity is θ(NlogN) .
         * System workflow:
         *      Firstly, this method sorts the iterators according to x, which allows us to
         *      use "divide" algorithm according to x.
         *      Then, we will call another recursive method, who will not only compute closest pair and distance,
         *      but also sorts the iterators in the order of y.
         *      After getting the answer for sub-problems, it conquers by computing new closest pair and distance,
         *      while also merges the sorted iterators in the order of y.
         * Known system defects： when the x coordinate of the inputs are the same, it degenerate to O(N^2).
         */
        template<typename T, typename It=typename std::vector<std::array<T, 2>>::const_iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPair2D(const It first,
                                                                const It last) {
            //for example, first-to-last-container is [<3,0>, <1,0>, <2,0>]
            const auto N = std::distance(first, last);
            //for example, size=3
            std::vector<It> vec2d_its(N); //rather than add an attribute to record the index, we use iterator instead.
            for (It from = first, to = vec2d_its.begin(); from!=last; std::advance(from, 1), std::advance(to, 1)){
                *to = from;
            }//for example, vec2d_its=[0, 1, 2]. 0,1,2 are pointers or indexes or so-called iterator.
            std::sort(vec2d_its.begin(), vec2d_its.end(), [](It a, It b){
                return (*a)[0]<(*b)[0];
            });//for example, vec2d_its=[1, 0, 2]. meaning that first-to-last-container c satisfies c[1].x < c[0].x < c[2].x .
            return findClosestPointPair2DRecursively(vec2d_its.begin(), vec2d_its.end());
        }
    private:
        template<typename T, typename It = typename std::vector<std::array<T, 2>>::const_iterator,
                typename ItIt=typename std::vector<It>::iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPair2DRecursively(const ItIt first, const ItIt last) const {
            const auto n = std::distance(first, last);
#define Point2D(it) (*(it))
#define X_VALUE(it) (Point2D(it)[0])
#define Y_VALUE(it) (Point2D(it)[1])
            //for example, size=3
            //1.递归基情况
            assert(n >= 2);
            if (n == 2)
                return {{first[0], first[1]}, euclideanDistance(Point2D(first[0]), Point2D(first[1]))};
            //2.递归求解左右
            const auto midIndex = n >>1;
            //2.1 趁着现在是x有序的，先把中间的x的值找出来
            const auto midX = X_VALUE(first[midIndex]);  // <=midX的都是左边，>midX的是右边。
            //2.1 不要低估这一步的重要性：根据midX重新分配minIndex。 这能把O(n)的情况节省为O(logn)
            ItIt midIt = ThisPackage::binary_search_for_last_satisfies(first+midIndex, last, [](It it){
                return X_VALUE(it)<=midX;
            })+1; //midIt是右边x的第一个。
            //2.2 递归求解得到答案，同时左右变成了y有序。
            auto [leftClosestPair, leftClosestDist] = findClosestPointPair2DRecursively<T>(first, midIt);
            auto [rightClosestPair, rightClosestDist] = findClosestPointPair2DRecursively<T>(midIt, last);
            //3. 归并按照y排序。
            std::inplace_merge(first, midIt, last, [](It a, It b){
                return Y_VALUE(a)<Y_VALUE(b);
            });
            //4. 归并求最近点对
            //4.1 左右中 更小的那个，记为 mergedClosestPoint 。
            std::array<It, 2> mergedClosestPoint{};
            T merged_min_dist{std::numeric_limits<T>::max()};
            if (leftClosestDist < rightClosestDist) {
                merged_min_dist = leftClosestDist;
                mergedClosestPoint = leftClosestPair;
            } else {
                merged_min_dist = rightClosestDist;
                mergedClosestPoint = rightClosestPair;
            }
            //4.2 准备归并范围
            T x_left = midX - merged_min_dist;
            T x_right = midX + merged_min_dist;
#define BoundCheckX(x) \
    if (!(x_left <= (x) && (x) <= x_right)) continue
            //4.2 开始归并，寻找更近的点对
            for (size_t i = 0; i < n; ++i) {
                BoundCheckX(X_VALUE(first[i]));
                //如果没有continue掉，就是在中间的，而且按照y顺序排好的一系列点。
                for (size_t j = i + 1, validJ = 0; validJ < 6 && j < n; ++j) {
                    BoundCheckX(X_VALUE(first[j]));
                    if ((X_VALUE(first[i])<=midX)==(X_VALUE(first[j])<=midX))
                        continue; //找异边的点, 如果同边，就过滤掉
                    validJ++;
                    T dist = euclideanDistance(Point2D(first[i]), Point2D(first[j]));
                    if (dist < merged_min_dist) {
                        merged_min_dist = dist;
                        mergedClosestPoint = {first[i], first[j]};
                    }
                }
            }
            return std::make_tuple(mergedClosestPoint, merged_min_dist);
        }
    public:

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
