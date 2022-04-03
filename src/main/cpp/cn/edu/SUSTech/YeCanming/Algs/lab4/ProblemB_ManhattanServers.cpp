//
// Created by 叶璨铭 on 2022/4/3.
//
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <functional>
#include <numeric>
template <class It>
int maximumSpanningTreeDistance(const It first, const It last) {

    const auto N = std::distance(first, last);
    std::sort(first, last);
    // get Parent 判断连通性
    std::vector<int> parent(N);
    std::iota(parent.begin(), parent.end(), 0);
    const std::function<int(const int&)> getParent = [&](const int& node){
        return parent[node]==node?node:getParent(node);
    };
#define GetParent(it) getParent(std::distance(first,(it)))
    int maxDist = std::numeric_limits<int>::min();
    int successEdgeCnt = 0;
    for (It left = first, right = last-1; std::distance(left, right)>=1;){
        //维护使得距离最大的且不成环的永远为 first-(right-1) left-(last-1)
        const auto firstDist = right[-1]-first[0];
        const auto lastDist = last[-1]-left[0];
        if (firstDist > lastDist){

        }
        int t1 = GetParent(left); int t2 = GetParent(right);
        if (t1!=t2){ //不会构成环路
            maxDist = *right - *left; //更新最大生成树的最小边
            parent[t2] = t1; //把父节点合并
            if (++successEdgeCnt==N)
                break;
            if ((left[1]-left[0])>(right[0]-right[-1]))

        }
    }
    return maxDist;
}
int main() {
    int N;
    std::cin >> N;
    std::vector<int> chebyShevX(N);
    std::vector<int> chebyShevY(N);
    for (int i = 0; i < N; ++i) {
        int manhattanX, manhattanY;
        std::cin >> manhattanX >> manhattanY;
        chebyShevX[i] = manhattanX + manhattanY;
        chebyShevX[i] = manhattanX - manhattanY;
    }
    std::cout << std::max(maximumSpanningTreeDistance(chebyShevX.begin(), chebyShevX.end()),
                          maximumSpanningTreeDistance(chebyShevX.begin(), chebyShevX.end()))
              << std::endl;
    return 0;
}