#ifndef GRAPH_H
#define GRAPH_H

#include "util.h"
#include "tx.h"

//边 = 连接的顶点 + 边上的信息
//单纯的出边或者入边
typedef struct Edge
{
    Edge() : sumAmount(0){}
    std::list<Tx *> txs;
    double sumAmount;
}Edge;

//出入边的总和
typedef struct Edges
{
    Edges(){};
    //注意: 因为出入度相对顶点数少得多(稀疏图), 如果边的集合用map存储的话, 
    //虽然效率略有降低(均摊O(1) -> 平均O(log n)), 却减少了每个节点两个hash-table所占用内存
    //可以在此处权衡一下 
    std::unordered_map<AccountName, Edge> InEdges;
    std::unordered_map<AccountName, Edge> OutEdges;
}Edges;

//交易图
class MarketGraph
{
    public:
        //预留1000000 hash
        MarketGraph(){vertices.reserve(1000000);};
        std::unordered_map<AccountName, Edges> & getVertices() {return vertices;}
        //添加新空节点, 如果存在, 什么也不做
        void addVertex(const AccountName & v);
        //增加v的入边, 另一账号为another, 没有则新建顶点
        void addInEdge(const AccountName & v, const AccountName & another, Tx * info);
        //增加v的出边, 另一账号为another, 没有则新建顶点
        void addOutEdge(const AccountName & v, const AccountName & another, Tx * info);
        //删除顶点v, 如果不存在, 什么也不做
        void deleteVertex(const AccountName & v);
    private:
        //顶点的容器, 保存顶点以及对应的入边和出边
        std::unordered_map<AccountName, Edges> vertices;
};

void MarketGraph::addVertex(const AccountName & v)
{
    //找不到就插入新顶点
    if(vertices.find(v) == vertices.end())
    {
        vertices.emplace(std::make_pair(v, Edges()));
    }
}

void MarketGraph::addInEdge(const AccountName & v, const AccountName & another, Tx * info)
{
    //找顶点
    auto vertexIter = vertices.find(v);
    //找不到就插入新顶点
    if(vertexIter == vertices.end())
    {
        vertexIter = vertices.emplace(std::make_pair(v, Edges())).first;
    }
    //找入边
    auto edgeIter = vertexIter -> second.InEdges.find(another);
    //找不到就插入新入边
    if(edgeIter == vertexIter -> second.InEdges.end())
    {
        edgeIter = vertexIter -> second.InEdges.emplace(std::make_pair(another, Edge())).first;
    }
    //插入新信息
    edgeIter -> second.txs.push_back(info);
    //增加转入总金额
    edgeIter -> second.sumAmount += info -> amount;
}

void MarketGraph::addOutEdge(const AccountName & v, const AccountName & another, Tx * info)
{
    //找顶点
    auto vertexIter = vertices.find(v);
    //找不到就插入新顶点
    if(vertexIter == vertices.end())
    {
        vertexIter = vertices.emplace(std::make_pair(v, Edges())).first;
    }
    //找出边
    auto edgeIter = vertexIter -> second.OutEdges.find(another);
    //找不到就插入新出边
    if(edgeIter == vertexIter -> second.OutEdges.end())
    {
        edgeIter = vertexIter -> second.OutEdges.emplace(std::make_pair(another, Edge())).first;
    }
    //插入新信息
    edgeIter -> second.txs.push_back(info);
    //增加转出总金额
    edgeIter -> second.sumAmount += info -> amount;
}

void MarketGraph::deleteVertex(const AccountName & v)
{
    auto vertexIter = vertices.find(v);
    //找不到顶点
    if(vertexIter == vertices.end())
    {
        return;
    }
    //根据出边表把对应顶点的入边删除
    for(auto i : vertexIter -> second.OutEdges)
    {
        vertices.at(i.first).InEdges.erase(v);
    }
    //根据入边表把对应顶点的出边删除
    for(auto i : vertexIter -> second.InEdges)
    {
        vertices.at(i.first).OutEdges.erase(v);
    }
    //删除自己
    vertices.erase(v);
}
#endif