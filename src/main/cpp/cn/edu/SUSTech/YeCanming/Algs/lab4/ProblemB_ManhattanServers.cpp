//
// Created by 叶璨铭 on 2022/4/3.
//
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
#include <cstdint>
template <class It>
int maximumSpanningTreeDistance(const It first, const It last) {
    const auto N = std::distance(first, last);
    std::sort(first, last);
    assert(std::distance(first, last)==N); //排序后指针指向仍然为首位。但是首位的值已发生变化、
    assert(N >= 2);
    int minMaxDist = last[-1]-first[0];
    for (It left = first+1, right = last-2; std::distance(left, right)>=0;){
        //维护使得距离最大的且不成环的永远为 first-(right-1) left-(last-1)
        const auto firstDist = right[0]-first[0];
        const auto lastDist = last[-1]-left[0];
        if (firstDist > lastDist){
            minMaxDist = firstDist;
            --right;
        }else{
            minMaxDist = lastDist;
            ++left;
        }
    }
    return minMaxDist;
}
int main() {
    int N;
    std::cin >> N;
    if (N==1){
        std::cout<<std::numeric_limits<int>::max()<<std::endl;
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
//    std::sort(chebyShevX.begin(), chebyShevX.end());
//    std::sort(chebyShevY.begin(), chebyShevY.end());
    std::cout << std::max(maximumSpanningTreeDistance(chebyShevX.begin(), chebyShevX.end()),
                          maximumSpanningTreeDistance(chebyShevY.begin(), chebyShevY.end()))
              << std::endl;
    return 0;
}