//
// Created by 叶璨铭 on 2022/5/22.
//
#pragma once
#include <list>
#include <forward_list>
#include <cassert>
#include <tuple>
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#define DEBUG true
#define MyLog if(DEBUG)\
                std::clog
template<class Capacity = uint64_t>
class FlowNetwork {
    static constexpr Capacity CapacityInf = std::numeric_limits<Capacity>::max();
    struct Edge {
        size_t from, to;
        Capacity cap, flow;
    };
    std::vector<Edge> mEdges; // from, to, weight
    std::vector<std::vector<size_t>> mAdjacencyList; //size_t的值表示边在mEdges中的索引。使用vector可以利用随机访问来进行断点续传（当前弧优化）
public:
    const size_t vertexCnt, edgeCnt;
    size_t source, sink;
    std::vector<size_t> depth; //表示bfs的层级
    explicit FlowNetwork(size_t vertexCnt, size_t edgeCnt=0, size_t source=0, size_t sink=0)
        : vertexCnt(vertexCnt), edgeCnt(edgeCnt), source(source), sink(sink), mAdjacencyList(vertexCnt + 1), depth(vertexCnt+1), mIsVisited(vertexCnt+1) {
        mEdges.reserve(edgeCnt);
    }
    void addEdge(size_t vertexU, size_t vertexV, Capacity capacity){
        mEdges.push_back({vertexU, vertexV, capacity, 0});
        mAdjacencyList[vertexU].emplace_back(mEdges.size()-1);
        mEdges.push_back({vertexV, vertexU, 0, 0});
        mAdjacencyList[vertexV].emplace_back(mEdges.size()-1);
    }
    Capacity getMaximumFlow() {
        MyLog << "Calculating maximum flow. " << std::endl;
        Capacity maximumFlow{0};
        while (bfs()){
            MyLog<<"\tThere is an augmenting route."<<std::endl;
            std::fill(mIsVisited.begin(), mIsVisited.end(), false);
            MyLog<<"\tDoing dfs."<<std::endl;
            maximumFlow += dfs(source, CapacityInf);
        }
        return maximumFlow;
    }

private:
    std::vector<bool> mIsVisited; // 表示"当前弧优化" 的边的索引。
    /**
     * build or rebuild the depth array.
     * @return whether there is an augmenting path.
     */
    bool bfs(Capacity allowCapacity = 0){
        MyLog<<"\tDoing bfs on the residual graph(denoted by flow on edge)."<<std::endl;
        std::queue<size_t> toBeVisited;
        toBeVisited.emplace(source);
        mIsVisited[source] = true;
        while (!toBeVisited.empty()){
            auto top = toBeVisited.front();
            toBeVisited.pop();
            for (const auto& _edge:mAdjacencyList[top]){
                auto& edge = mEdges[_edge];
                if (!mIsVisited[edge.to] && edge.cap-edge.flow>allowCapacity){
                    mIsVisited[edge.to] = true;
                    depth[edge.to] = depth[top]+1;
                    toBeVisited.emplace(edge.to);
                }
            }
            if (mIsVisited[sink])
                return true;
        }
        return false;
    }
    /**
     *
     * @param currentNode
     * @param allowCapacity before reaching currentNode, the capacity has been restricted to this value.
     * @return maximumFlowFromCurrentNode: the final flow integration which starts from currentNode
     */
    Capacity dfs(size_t currentNode, Capacity allowCapacity){
        MyLog<<"\t\tdfs on "<<currentNode<<"with allowCapacity="<<allowCapacity<<std::endl;
        if (currentNode ==sink || allowCapacity==0)
            return allowCapacity; //如果要递归访问sink，那么保持原有capacity不变；如果原来没有可行capacity，返回0.
        Capacity maximumFlowFromCurrentNode = 0;
        auto& relatives = mAdjacencyList[currentNode];
//        for (size_t& i = mValidRoute[currentNode]; i < relatives.size(); ++i){
//            size_t edgeIndex = relatives[i];
        for (const auto& edgeIndex:relatives){
            Edge& edge = mEdges[edgeIndex]; // 这是我们将要走过的边。
            if (depth[currentNode]+1==depth[edge.to] && !mIsVisited[edge.to]){
                //按照bfs的指导，确定我们要遍历的边。
                // 由于每次都要访问新的一层，所以一定不会访问到访问过的。
                auto bottleNeck = dfs(edge.to, std::min(allowCapacity, edge.cap-edge.flow)); // 我们要走的边能达到的最大流是多少？被前面的allowCapacity限制，也被这条边限制，其他的问题递归决定。
                if (bottleNeck>0){
                   //前面的来路已经有流了，作为current Node，我们的历史使命是为edge注入它需要的流。
                   edge.flow += bottleNeck;
                   mEdges[edgeIndex^1].flow-=bottleNeck; // 当然允许通过反向边未来反悔。
                   maximumFlowFromCurrentNode+=bottleNeck;
                   allowCapacity-=bottleNeck; //我们从前面转接了allowCapacity，如今用去了bottleNeck在这条边上。
//                   mValidRoute+=
                   if (allowCapacity<=0){
                       assert(allowCapacity==0);
                       break;
                   }
                }
            }
        }
        mIsVisited[currentNode] = true; //退栈。
        MyLog<<"\t\tThe maximumFlowFrom "<<currentNode<<" is "<<maximumFlowFromCurrentNode<<std::endl;
        return maximumFlowFromCurrentNode;
    }
};