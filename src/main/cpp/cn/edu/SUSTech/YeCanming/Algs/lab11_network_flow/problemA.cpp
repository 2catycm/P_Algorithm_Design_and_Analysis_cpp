//
// Created by 叶璨铭 on 2022/5/20.
//
#include <iostream>
#include <list>
#include <forward_list>
#include <cassert>
#include <tuple>
#include <queue>
#include <vector>
#include <limits>
#define DEBUG true
#define MyLog if(DEBUG)\
                std::clog
template<class Capacity = size_t>
class FlowNetwork {
    static constexpr Capacity CapacityInf = std::numeric_limits<Capacity>::max();
    struct Edge{
        size_t from, to;
        Capacity cap, flow;
    };
    std::vector<Edge> mEdges; // from, to, weight
    std::vector<std::forward_list<typename decltype(mEdges)::iterator>> mAdjacencyList;
public:
    const size_t vertexCnt, edgeCnt;
    size_t source, sink;
    explicit FlowNetwork(size_t vertexCnt, size_t edgeCnt, size_t source=0, size_t sink=0)
        : vertexCnt(vertexCnt), edgeCnt(edgeCnt), source(source), sink(sink), mAdjacencyList(vertexCnt + 1) {
        mEdges.reserve(edgeCnt);
    }
    void addEdge(size_t vertexU, size_t vertexV, Capacity capacity){
        mEdges.push_back({vertexU, vertexV, capacity, 0});
        mAdjacencyList[vertexU].emplace_front(mEdges.end()-1);
        mEdges.push_back({vertexV, vertexU, 0, 0});
        mAdjacencyList[vertexV].emplace_front(mEdges.end()-1);
    }
    Capacity getMaximumFlow(){
        MyLog<<"Calculating maximum flow. "<<std::endl;
        Capacity maximumFlow{0};
        auto residualGraph = mAdjacencyList;
        auto allowCapacity = std::numeric_limits<Capacity>::max()>>31;
        for (; allowCapacity>0; ){
            MyLog<<"\tTrying to find an augmenting path with at least "<<allowCapacity<<std::endl;
            //对 residualGraph 做一次bfs，找到src到sink路径的同时
            // 1. 确保路径流量大于等于 allowCapacity
            // 2. 修改 residualGraph
            // 3. 增加总流量
            std::queue<size_t> toBeVisited;
            std::vector<Capacity> bottlenecks(vertexCnt+1);
            std::vector<typename decltype(mEdges)::iterator> parent(vertexCnt+1); //放得是edge类型的，表示一条边
            toBeVisited.emplace(source);
            bottlenecks[source] = CapacityInf;
            while (!toBeVisited.empty()){ //如果是从while的条件break的，就是没找到合适的路径，但是找到了所有source可达点的最短路径。
                auto top = toBeVisited.front();
                toBeVisited.pop();
                MyLog<<"\t\tbfs finds vertex "<<top<<std::endl;
                for (const auto& edge:mAdjacencyList[top]) { //遍历连接的所有边。
                    MyLog<<"\t\t\tit has neighbour vertex "<<edge->to<<std::endl;
                    auto residualCap = edge->cap-edge->flow;
                    if (bottlenecks[edge->to]==0 && residualCap>=allowCapacity){
                        parent[edge->to] = edge;
                        bottlenecks[edge->to] = std::min(bottlenecks[top], residualCap);
                        MyLog<<"\t\t\tbottleneck becomes "<<bottlenecks[edge->to]<<std::endl;
                        toBeVisited.emplace(edge->to);
                    }
                }
                if (bottlenecks[sink]!=0)
                    break;
            }
            if (bottlenecks[sink]!=0){
                MyLog<<"\t\tbfs finds a path. "<<std::endl;
                auto bottleNeck = bottlenecks[sink];
                MyLog<<"\t\tthe bottleneck of this path is "<<bottleNeck<<std::endl;
                for (size_t it=sink; it!=source; it = parent[it]->from){
                    assert(it!=0);
                    size_t num = std::distance(mEdges.begin(), parent[it]);
                    MyLog<<"\t\t\t"<<it<<" is on the path. "<<std::endl;
                    mEdges[num].flow += bottleNeck;
                    mEdges[num^1].flow -= bottleNeck;
                }
                maximumFlow+=bottleNeck;
            }else{
                MyLog<<"\t\tbfs finds no path. "<<std::endl;
                allowCapacity>>=1; //如果找不到路径，就降低要求。比如如果要求是1，一直找得到，就不会降，最后找不到了变成0，算法结束。
            }
        }
        return maximumFlow;
    }
};
int main() {
    size_t N, M, S, T;
    std::cin >> N >> M >> S >> T;
    FlowNetwork flowNetwork{N, M, S, T};
    for (int i = 0; i < M; ++i) {
        int u, v, c;
        std::cin>>u>>v>>c;
        flowNetwork.addEdge(u, v, c);
    }
    std::cout<<flowNetwork.getMaximumFlow()<<std::endl;
    return 0;
}