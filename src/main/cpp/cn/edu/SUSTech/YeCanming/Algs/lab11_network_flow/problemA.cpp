//
// Created by 叶璨铭 on 2022/5/20.
//
#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <queue>
#include <cstdint>
#include <limits>
#define Square(X) ((X)*(X))

template<class Capacity = size_t>
class FlowNetwork {
    std::vector<Capacity> mAdjacencyMatrix; //如果N是100， 矩阵可能有10000那么大。
    size_t mEdgeCnt{0};
public:
    const size_t vertexCnt;
#define CapacityFromIToJ(adjMat, i, j) adjMat[vertexCnt*(i)+(j)]
    size_t source, sink;
    explicit FlowNetwork(size_t vertexCnt, size_t source=0, size_t sink=0)
        : vertexCnt(vertexCnt), source(source), sink(sink), mAdjacencyMatrix(Square(vertexCnt + 1)) {
    }
    void addEdge(size_t vertexU, size_t vertexV, Capacity capacity){
        CapacityFromIToJ(mAdjacencyMatrix, vertexU, vertexV)+=capacity;
        ++mEdgeCnt;
    }
    [[nodiscard]] size_t getEdgeCnt() const {
        return mEdgeCnt;
    }
    Capacity getMaximumFlow(){
        Capacity maximumFlow{0};
//        Capacity maximumFlow{std::numeric_limits<Capacity>::min()};
        auto residualGraph = mAdjacencyMatrix;
        auto allowCapacity = std::numeric_limits<Capacity>::max()>>31;
        for (bool cannotFindPath = true; allowCapacity>0; allowCapacity>>=cannotFindPath){ //如果找不到路径，就降低要求。比如如果要求是1，一直找得到，就不会降，最后找不到了变成0，算法结束。
            //对 residualGraph 做一次bfs，找到src到sink路径的同时
            // 1. 确保路径流量大于等于 allowCapacity
            // 2. 修改 residualGraph
            // 3. 增加总流量
            std::queue<size_t> toBeVisit;
            std::vector<bool> isVisited(vertexCnt+1);
            std::vector<size_t> parent(vertexCnt+1);
            toBeVisit.push(source);
            while (!toBeVisit.empty()){
                auto top = toBeVisit.front(); toBeVisit.pop(); isVisited[top] = true;
                if (top==sink){
                    cannotFindPath = false;
                    break;
                }
                for (int j = 1; j <= vertexCnt; ++j) { //遍历连接的所有边。
                    if (!isVisited[j] && CapacityFromIToJ(residualGraph, top, j)>=allowCapacity){
                        toBeVisit.push(j);
                        parent[j] = top;
                    }
                }
            }
        }
        return maximumFlow;
    }
};
int main() {
    size_t N, M, S, T;
    std::cin >> N >> M >> S >> T;
    FlowNetwork<uint64_t> flowNetwork{N, S, T};
    for (int i = 0; i < M; ++i) {
        size_t u, v; uint64_t c;
        std::cin>>u>>v>>c;
        flowNetwork.addEdge(u, v, c);
    }
    std::cout<<flowNetwork.getMaximumFlow()<<std::endl;
    return 0;
}