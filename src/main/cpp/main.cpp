#include <iostream>
#include "cn/edu/SUSTech/YeCanming/Algs/ClosestPoint.hpp"
using cn::edu::SUSTech::YeCanming::Algs::ClosestPoint;
int main() {
    ClosestPoint closestPoint;
    auto a = closestPoint.ClosestPoint1D<double>({1, 2, 3, 3.5, 3.75, 4.25});
    std::cout<<std::get<0>(a)<<std::endl;
    std::cout<<std::get<1>(a)<<std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
