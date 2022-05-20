//
// Created by 叶璨铭 on 2022/5/20.
//
#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <limits>
template<class Capacity = size_t>
class FlowNetwork {
    std::vector<std::list<std::tuple<size_t, Capacity>>> mAdjacencyList;
    size_t mEdgeCnt{0};
public:
    const size_t vertexCnt;
    size_t source, sink;
    explicit FlowNetwork(size_t vertexCnt, size_t source=0, size_t sink=0)
        : vertexCnt(vertexCnt), source(source), sink(sink), mAdjacencyList(vertexCnt + 1) {
    }
    void addEdge(size_t vertexU, size_t vertexV, Capacity capacity){
        mAdjacencyList[vertexU].emplace_back(vertexV, capacity);
        ++mEdgeCnt;
    }
    [[nodiscard]] size_t getEdgeCnt() const {
        return mEdgeCnt;
    }
    Capacity getMaximumFlow(){
        Capacity maximumFlow{0};
//        Capacity maximumFlow{std::numeric_limits<Capacity>::min()};
        auto residualGraph = mAdjacencyList;

    }
};
int main() {
    size_t N, M, S, T;
    std::cin >> N >> M >> S >> T;
    FlowNetwork flowNetwork{N, S, T};
    for (int i = 0; i < M; ++i) {
        int u, v, c;
        std::cin>>u>>v>>c;
        flowNetwork.addEdge(u, v, c);
    }
    std::cout<<flowNetwork.getMaximumFlow()<<std::endl;
    return 0;
}