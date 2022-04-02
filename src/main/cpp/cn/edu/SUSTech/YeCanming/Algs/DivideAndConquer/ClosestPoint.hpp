//
// Created by 叶璨铭 on 2022/3/31.
//

#pragma once
#include "BinarySearch.hpp"
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
        template<typename T, typename It = typename std::vector<std::array<T, 2>>::const_iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPair2D(const std::vector<std::array<T, 2>> &vec2d) const {
            return findClosestPointPair2D<T>(vec2d.cbegin(), vec2d.cend());
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
         * Known system defects：
         *      1. when the x coordinate of the inputs are the same, it degenerate to O(N^2).
         *      2. std::inplace_merge may be nlogn
         *      3. divide should always use mid point but not binary searched point to avoid n=1 problem.
         *
         */
        template<typename T, typename It = typename std::vector<std::array<T, 2>>::const_iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPair2D(const It first,
                                                                const It last) const {
            //for example, first-to-last-container is [<3,0>, <1,0>, <2,0>]
            const auto N = std::distance(first, last);
            //for example, size=3
            std::vector<It> vec2d_its(N);//rather than add an attribute to record the index, we use iterator instead.
            auto to = vec2d_its.begin();
            for (It from = first; from != last; std::advance(from, 1), std::advance(to, 1)) {
                *to = from;
            }//for example, vec2d_its=[0, 1, 2]. 0,1,2 are pointers or indexes or so-called iterator.
            std::sort(vec2d_its.begin(), vec2d_its.end(), [](It a, It b) {
                return (*a)[0] < (*b)[0];
            });//for example, vec2d_its=[1, 0, 2]. meaning that first-to-last-container c satisfies c[1].x < c[0].x < c[2].x .
            std::vector<bool> isLeft(N);
            std::vector<It> withoutXIllegal(N);
            return findClosestPointPair2DRecursively<T>(vec2d_its.begin(), vec2d_its.end(), isLeft, first, withoutXIllegal.begin());
        }

    private:
        template<typename T, typename It = typename std::vector<std::array<T, 2>>::const_iterator,
                 typename ItIt = typename std::vector<It>::iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPair2DRecursively(const ItIt first, const ItIt last,
                                                                           std::vector<bool> &isLeft, const It &firstIt,
                                                                           ItIt withoutXIllegalFirst) const {
            const auto n = std::distance(first, last);
#define Point2D(it) (*(it))
#define X_VALUE(it) (Point2D(it)[0])
#define Y_VALUE(it) (Point2D(it)[1])
            //for example, size=3
            //1.递归基情况
            assert(n >= 2);
            if (n == 2) {
                //先要按照y排好序
                if (Y_VALUE(first[0])>Y_VALUE(first[1]))
                    std::swap(first[0], first[1]); //交换了first作为迭代器数组的迭代器的那个数组中，数组第0个元素和第1个元素的值。（0,1是相对于first而言的坐标）
                return {{first[0], first[1]}, euclideanDistance(Point2D(first[0]), Point2D(first[1]))};
            }
            if (n <= 5) {
                //先要按照y排好序
                std::sort(first, last, [](It a, It b) {
                    return Y_VALUE(a) < Y_VALUE(b);
                });
                return __findClosestPointPairND<T, 2, typename std::vector<std::array<T, 2>>::const_iterator,
                                                typename std::vector<It>::iterator>(first, last);
            }
            //2.递归求解左右
            const auto midIt = first + (n >> 1);//左右的size可以相等或者差1，由于size=3和size=2都特殊处理，不会产生n=1的问题。
            const auto midX = X_VALUE(*midIt);  //不作为切分左右的依据。这是用来过滤点的。
                                                //2.1 处理左右问题的标记
                                                //firstIt是原本的点对数组的首位，每个迭代器It有唯一的序号。
#define OriginalIndex(it) std::distance(firstIt, (it))
#define SetLeft(it) isLeft[OriginalIndex(it)] = true
#define SetRight(it) isLeft[OriginalIndex(it)] = false
#define GetIsLeft(it) isLeft[OriginalIndex(it)]
            std::for_each(first, midIt, [&](It it) {
                SetLeft(it);
            });
            std::for_each(midIt, last, [&](It it) {
                SetRight(it);
            });
            //2.2 递归求解得到答案，同时左右变成了y有序。
            auto [leftClosestPair, leftClosestDist] = findClosestPointPair2DRecursively<T>(first, midIt, isLeft, firstIt, withoutXIllegalFirst);
            auto [rightClosestPair, rightClosestDist] = findClosestPointPair2DRecursively<T>(midIt, last, isLeft, firstIt, withoutXIllegalFirst);
            //3. 归并按照y排序。
            std::inplace_merge(first, midIt, last, [](It a, It b) {
                return Y_VALUE(a) < Y_VALUE(b);
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
            const auto withoutXIllegalLast = std::copy_if(first, last, withoutXIllegalFirst, [&](It it){
                return (x_left <= (X_VALUE(it)) && (X_VALUE(it)) <= x_right);
            });
            //4.2 开始归并，寻找更近的点对
            for (; withoutXIllegalFirst != withoutXIllegalLast; ++withoutXIllegalFirst) {
                int validJ = 0;
                for (ItIt another = withoutXIllegalFirst + 1; validJ < 6 && another != withoutXIllegalLast; ++another) {
                    if (GetIsLeft(*withoutXIllegalFirst) == GetIsLeft(*another))
                        continue;//找异边的点, 如果同边，就过滤掉
                    validJ++;
                    T dist = euclideanDistance(Point2D(*withoutXIllegalFirst), Point2D(*another));
                    if (dist < merged_min_dist) {
                        merged_min_dist = dist;
                        mergedClosestPoint = {*withoutXIllegalFirst, *another};
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


        template<typename T, size_t N, typename It = typename std::vector<std::array<T, N>>::const_iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPairND(const std::vector<std::array<T, N>> &vec_nd) const {
            return findClosestPointPairND<T, N, typename std::vector<std::array<T, N>>::const_iterator>(vec_nd.cbegin(), vec_nd.cend());
        }
        template<typename T, size_t N, typename It = typename std::vector<std::array<T, N>>::const_iterator>
        std::tuple<std::array<It, 2>, T> findClosestPointPairND(It first, const It last) const {
            const auto size = std::distance(first, last);
            assert(size >= 2);
            T min_dist = std::numeric_limits<T>::max();
            std::array<It, 2> min_index{first, first + 1};
            for (; first != last; ++first) {
                for (It another = first + 1; another != last; ++another) {
                    T dist = this->euclideanDistance(*first, *another);
                    if (min_dist > dist) {
                        min_dist = dist;
                        min_index[0] = first;
                        min_index[1] = another;
                    }
                }
            }
            return std::make_tuple(min_index, min_dist);
        }

    private:
        template<typename T, size_t N, typename It = typename std::vector<std::array<T, N>>::const_iterator,
                 typename ItIt = typename std::vector<It>::iterator>
        std::tuple<std::array<It, 2>, T> __findClosestPointPairND(ItIt first, const ItIt last) const {
            const auto size = std::distance(first, last);
            assert(size >= 2);
            T min_dist = std::numeric_limits<T>::max();
            std::array<It, 2> min_index{first[0], first[1]};
            for (; first != last; ++first) {
                for (ItIt another = first + 1; another != last; ++another) {
                    T dist = this->euclideanDistance(**first, **another);
                    if (min_dist > dist) {
                        min_dist = dist;
                        min_index[0] = *first;
                        min_index[1] = *another;
                    }
                }
            }
            return std::make_tuple(min_index, min_dist);
        }

    public:
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
