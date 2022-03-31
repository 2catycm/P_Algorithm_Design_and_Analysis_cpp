//
// Created by 叶璨铭 on 2022/3/31.
//

#pragma once
#include <vector>
#include <array>
namespace cn::edu::SUSTech::YeCanming::Algs {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs;
    class ClosestPoint {
        template<typename T>
        std::tuple<std::array<size_t, 2>, T> ClosestPoint2DImpl(decltype(std::vector<std::array<T, 2>>().cbegin()) cbegin, decltype(std::vector<std::array<T, 2>>().cend()) cend) const;
//        template<class Iterator, typename T/*typename std::vector<T>::const_iterator*/>
//        std::tuple<std::array<size_t, 2>, T> ClosestPoint2DImpl(Iterator cbegin, Iterator cend) const;
    public:
        template<typename T>
        std::tuple<int, int> ClosestPoint1D(const std::vector<T> &vec) const;
        template<typename T>
        std::tuple<std::array<size_t, 2>, T> ClosestPoint2D(const std::vector<std::array<T, 2>> &vec2d) const;

        template<typename T, size_t N>
        std::array<int, 2> ClosestPointND(const std::vector<std::array<T, N>> &vecnd) const;

        template<typename T, size_t N>
        T euclideanDistance(const std::array<T, N>& a, const std::array<T, N>& b) const;
    };

}// namespace cn::edu::SUSTech::YeCanming::Algs

