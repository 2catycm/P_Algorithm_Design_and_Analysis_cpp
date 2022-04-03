//
// Created by 叶璨铭 on 2022/4/3.
//
#ifndef NTEST
#define NTEST 1
#endif
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
namespace cn::edu::SUSTech::YeCanming::Algs::lab4 {
    namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab4;
    template<class It>
    int solveServers(const It xFirst, const It xLast, const It yFirst, const It yLast) {
        const auto N = std::distance(xFirst, xLast);
        assert(std::distance(yFirst, yLast)==N);
        std::sort(xFirst, xLast);
        std::sort(yFirst, yLast);
        assert(std::distance(xFirst, xLast) == N && std::distance(yFirst, yLast)==N);//排序后指针指向仍然为首位。但是首位的值已发生变化、
        assert(N >= 2);
        int minMaxDist = std::max(xLast[-1] - xFirst[0], yLast[-1] - yFirst[0]);
        for (It xLeft = xFirst + 1, xRight = xLast - 1, yLeft = yFirst + 1, yRight = yLast - 1; std::distance(xLeft, xRight) >= 0;) {
            //维护使得距离最大的且不成环的永远为 first:(right-1) left:(last-1)
            const auto firstDist = std::max(xRight[-1] - xFirst[0], yRight[-1] - yFirst[0]);
            const auto lastDist = std::max(xLast[-1] - xLeft[0], yLast[-1] - yLeft[0]);
            if (firstDist > lastDist) {
                minMaxDist = firstDist;
                --xRight;
                --yRight;
            } else {
                minMaxDist = lastDist;
                ++xLeft;
                ++yLeft;
            }
        }
        return minMaxDist;
    }
}// namespace cn::edu::SUSTech::YeCanming::Algs::lab4
#if NTEST
namespace ThisPackage = cn::edu::SUSTech::YeCanming::Algs::lab4;
int main() {
    int N;
    std::cin >> N;
    if (N == 1) {
        std::cout << std::numeric_limits<int>::max() << std::endl;
        return 0;
    }
    std::vector<int> chebyShevX(N);
    std::vector<int> chebyShevY(N);
    for (int i = 0; i < N; ++i) {
        int manhattanX, manhattanY;
        std::cin >> manhattanX >> manhattanY;
        chebyShevX[i] = manhattanX + manhattanY;
        chebyShevY[i] = manhattanX - manhattanY;
    }
    std::cout << ThisPackage::solveServers(chebyShevX.begin(), chebyShevX.end(), chebyShevY.begin(), chebyShevY.end())
              << std::endl;
    return 0;
}
#endif