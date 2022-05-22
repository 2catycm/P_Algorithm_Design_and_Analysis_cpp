//
// Created by 叶璨铭 on 2022/5/20.
//
#include <iostream>

//#include "EdmondsKarpFlowNetwork.h"
#include "DinicFlowNetwork.h"
int main() {
    size_t N, M, S, T;
    std::cin >> N >> M >> S >> T;
    FlowNetwork<uint64_t> flowNetwork{N, M, S, T};
    for (int i = 0; i < M; ++i) {
        int u, v, c;
        std::cin>>u>>v>>c;
        flowNetwork.addEdge(u, v, c);
    }
    std::cout<<flowNetwork.getMaximumFlow()<<std::endl;
    return 0;
}
