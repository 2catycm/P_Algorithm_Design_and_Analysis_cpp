//
// Created by 叶璨铭 on 2022/5/20.
//
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>
#include <unordered_set>
#include <queue>
#include <cstdint>
#include <limits>
#include <cassert>
#define Square(X) ((X)*(X))

template<class Capacity = size_t>
class FlowNetwork {
    std::vector<Capacity> mAdjacencyMatrix; //如果N是100， 矩阵可能有10000那么大。
    std::vector<std::unordered_set<size_t>> mAdjacencyList; //用于加速bfs。
    size_t mEdgeCnt{0};
public:
    const size_t vertexCnt;
#define CapacityFromIToJ(adjMat, i, j) adjMat[vertexCnt*(i)+(j)]
    size_t source, sink;
    explicit FlowNetwork(size_t vertexCnt, size_t source=0, size_t sink=0)
        : vertexCnt(vertexCnt), source(source), sink(sink), mAdjacencyMatrix(Square(vertexCnt + 1)), mAdjacencyList(vertexCnt+1) {
    }
    void addEdge(size_t vertexU, size_t vertexV, Capacity capacity){
        CapacityFromIToJ(mAdjacencyMatrix, vertexU, vertexV)+=capacity;
        mAdjacencyList[vertexU].emplace(vertexV);
        ++mEdgeCnt;
    }
    [[nodiscard]] size_t getEdgeCnt() const {
        return mEdgeCnt;
    }
    Capacity getMaximumFlow(){
        Capacity maximumFlow{0};
        auto residualGraphMat = mAdjacencyMatrix;
        auto residualGraphList = mAdjacencyList;
        auto allowCapacity = std::numeric_limits<Capacity>::max()>>31;
        for (; allowCapacity>0; ){
            bool cannotFindPath = true;
            //对 residualGraph 做一次bfs，找到src到sink路径的同时
            // 1. 确保路径流量大于等于 allowCapacity
            // 2. 修改 residualGraph
            // 3. 增加总流量
            std::stack<size_t> toBeVisit;
            std::vector<bool> isVisited(vertexCnt+1);
            std::vector<size_t> parent(vertexCnt+1);
            toBeVisit.push(source);
            isVisited[source] = true;
            while (!toBeVisit.empty()){ //如果是从while的条件break的，就是没找到合适的路径，但是找到了所有source可达点的最短路径。
                auto top = toBeVisit.top(); toBeVisit.pop();
                if (top==sink){
                    cannotFindPath = false;
                    break; //代表找到了最短路径。
                }
//                for (int j = 1; j <= vertexCnt; ++j) { //遍历连接的所有边。
                for (const auto& relative:mAdjacencyList[top]) { //遍历连接的所有边。
                    if (!isVisited[relative] && CapacityFromIToJ(residualGraphMat, top, relative)>=allowCapacity){
                        isVisited[top] = true;//写在这里而不是pop后面，这样就可以防止后面队列太大。
                        parent[relative] = top; //上面那个isVisited很重要，保证了parent不会被人乱改。parent始终是记录最短路径的。
                        toBeVisit.push(relative);
                    }
                }
            }
            if (!cannotFindPath){
                Capacity bottleNeck{std::numeric_limits<Capacity>::max()};
                for (size_t it=sink; it!=source; it = parent[it]){
                    assert(it!=0);
                    bottleNeck = std::min(bottleNeck, CapacityFromIToJ(residualGraphMat, parent[it], it));
                }
                assert(bottleNeck!=0);
                for (size_t it=sink; it!=source; it = parent[it]){
                    assert(it!=0);
                    auto& edge = CapacityFromIToJ(residualGraphMat, parent[it], it);
                    auto& reverseEdge = CapacityFromIToJ(residualGraphMat, it, parent[it]);
                    if (reverseEdge==0)
                        residualGraphList[it].emplace(parent[it]);
                    reverseEdge+=bottleNeck;
                    edge-=bottleNeck;
//                    if (edge==0)
//                        residualGraphList[parent[it]].erase(it);
                }
                maximumFlow+=bottleNeck;
            }else{
                allowCapacity>>=cannotFindPath; //如果找不到路径，就降低要求。比如如果要求是1，一直找得到，就不会降，最后找不到了变成0，算法结束。
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