//
// Created by 叶璨铭 on 2022/3/31.
//

#include "ClosestPoint.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs;
namespace cn::edu::SUSTech::YeCanming::Algs {
    template<typename T>
    std::tuple<std::array<size_t, 2>, T> ClosestPoint::ClosestPoint2D(const std::vector<std::array<T, 2>> &vec2d) const {
        auto v = vec2d;
        std::sort(std::begin(vec2d), std::end(vec2d), [](std::array<T, 2> a, std::array<T, 2> b) {
            return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
        });//y then x 的字典序
        return ClosestPoint2DImpl(v.cbegin(), v.cend());
    }
    template<typename T>
    std::tuple<std::array<size_t, 2>, T> ClosestPoint::ClosestPoint2DImpl(const T *cbegin, const T *cend) const {
        //递归基情况
        size_t size = cend - cbegin;
        assert(size >= 2);
        if (size == 2)
            return {0, 1};
        //递归求解左右
        size_t mid = size >> 1;
        auto [leftClosestPoint, leftClosestDist] = ClosestPoint2DImpl(cbegin, cbegin + mid);
        auto [rightClosestPoint, rightClosestDist] = ClosestPoint2ClosestPoint2DImpl(cbegin + mid, cbegin + size);
        std::get<std::array<size_t, 2>>(rightClosestPoint)[0]+=mid;
        std::get<std::array<size_t, 2>>(rightClosestPoint)[1]+=mid; //下标变换为本层下标
        std::array<size_t, 2> mergedClosestPoint{}; T merged_min_dist{std::numeric_limits<T>::max()};
        //准备归并
        if (leftClosestDist<rightClosestDist) {
            merged_min_dist = leftClosestDist;
            mergedClosestPoint = leftClosestPoint;
        } else {
            merged_min_dist = rightClosestDist;
            mergedClosestPoint = rightClosestPoint;
        }
        T half_lr_min_dist = static_cast<T>(std::ceil(merged_min_dist) / 2);
        T x_left = cbegin[mid] - half_lr_min_dist;
        T x_right = cbegin[mid] + half_lr_min_dist;
#define BoundCheckX(x) if (!(x_left <= (x) && (x) <= x_right)) continue;
        //开始归并，寻找更近的点对
        for (size_t i = 0; i < size; ++i) {
            BoundCheckX(cbegin[i][0])
            //如果没有continue掉，就是在中间的，而且按照y顺序排好的一系列点。
            for (size_t j = i + 1, validJ = 0; validJ < 6 && j < size; ++j) {
                BoundCheckX(cbegin[j][0])
                validJ++;
                T dist = euclideanDistance(cbegin[i], cbegin[j]);
                if (dist<merged_min_dist){
                    merged_min_dist = dist;
                    mergedClosestPoint = {i, j};
                }
            }
        }
        return std::make_tuple(mergedClosestPoint, merged_min_dist);
    }

    template<typename T>
    std::tuple<int, int> ClosestPoint::ClosestPoint1D(const std::vector<T> &vec) const {
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
    std::array<int, 2> ClosestPoint::ClosestPointND(const std::vector<std::array<T, N>> &vec_nd) const {
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
    T ClosestPoint::euclideanDistance(const std::array<T, N> &a, const std::array<T, N> &b) const {
        T sum = 0;
        for (int i = 0; i < N; ++i) {
            T diff = a[i] - b[i];
            sum += diff * diff;
        }
        return std::sqrt(sum);
    }


    template std::tuple<int, int> ClosestPoint::ClosestPoint1D(const std::vector<int> &vec) const;
    template std::tuple<int, int> ClosestPoint::ClosestPoint1D(const std::vector<double> &vec) const;
    template std::array<int, 2> ClosestPoint::ClosestPointND(const std::vector<std::array<int, 2>> &vec_nd) const;
    template std::array<int, 2> ClosestPoint::ClosestPointND(const std::vector<std::array<double, 2>> &vec_nd) const;
}// namespace cn::edu::SUSTech::YeCanming::Algs
