//
// Created by 叶璨铭 on 2022/3/31.
//
#include <algorithm>
#include <memory>
#include <random>
#include <cassert>
#include <memory>
#include "cn/edu/SUSTech/YeCanming/Algs/ClosestPoint.h"
#include "cn/edu/SUSTech/YeCanming/Judge/JudgeUnit1.hpp"
using cn::edu::SUSTech::YeCanming::Algs::ClosestPoint;
std::unique_ptr<ClosestPoint> closestPointPtr;
BeforeEach
void setUp(){
    closestPointPtr = std::make_unique<ClosestPoint>();
}
Test
void testClosestPoint2D(){
    auto& closestPoint = *closestPointPtr;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::vector<double> v = {1, 2, 3, 3.5, 3.75, 4.25};
    std::shuffle(v.begin(), v.end(), rng);
    auto a = closestPoint.ClosestPoint1D<double>(v);
    assert(v[std::get<0>(a)]+v[std::get<1>(a)] == 7.25);
    assert(std::abs(v[std::get<0>(a)]-v[std::get<1>(a)]) == 0.25);
    assert(std::abs(v[std::get<0>(a)]-v[std::get<1>(a)]) != 0.3);
}
Test
void testClosestPointND(){
    auto& closestPoint = *closestPointPtr;
    std::vector<std::array<double, 2>> v = {{1, 2},{3, 4}, {2.5, 10}, {10, 2.5}};
    auto a = closestPoint.ClosestPointND(v);
    assert(a[0]+a[1]==1);
    assert(std::abs(a[0]-a[1])==1);
}

int main(){
    setUp();
    testClosestPoint2D();
    setUp();
    testClosestPointND();
}