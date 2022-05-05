//
// Created by 叶璨铭 on 2022/5/5.
//
#include "BinaryIndexedTree.hpp"
auto differ(std::vector<int64_t> const& arrayA){
    std::vector<int64_t> diff(arrayA);
    for(int i = 1; i <= diff.size()-1; ++i){
        diff[i] = arrayA[i]-arrayA[i-1];
    }
    return diff;
}
int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int64_t> arrayA(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> arrayA[i];
    }
    auto diff = differ(arrayA);
    auto bit = BinaryIndexedTree(diff);
    for (int i = 0; i < m; ++i) {
        int op, x;
        std::cin>>op;
        if (op == 1) {
            int y, k;
            std::cin >> x >> y >> k;
            bit.add(x, k);
            bit.add(y+1, -k);
        } else {
            assert(op == 2);
            std::cin>>x;
            std::cout<<bit.sumTo(x)<<std::endl;
        }
    }
    return 0;
}