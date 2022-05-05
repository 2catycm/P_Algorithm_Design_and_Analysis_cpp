//
// Created by 叶璨铭 on 2022/5/5.
//
#include "BinaryIndexedTree.hpp"
int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int64_t> arrayA(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> arrayA[i];
    }
    auto bit = BinaryIndexedTree(arrayA);
    for (int i = 0; i < m; ++i) {
        int op, x, y;
        std::cin >> op >> x >> y;
        if (op == 1) {
            bit.add(x, y);
        } else {
            assert(op == 2);
            std::cout<<bit.sumAmong(x,y)<<std::endl;
        }
    }
    return 0;
}