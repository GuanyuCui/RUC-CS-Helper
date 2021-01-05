#ifndef ANALYSER_H
#define ANALYSER_H

#include "util.h"
#include "account.h"
#include "graph.h"

class Analyser
{
    public:
        Analyser(){}
        //输出交易图
        void functionD(MarketGraph & G);
        //输出平均出入度以及出入度最高的前k个账号
        void functionE(MarketGraph & G);
        //输出图中的是否存在环
        void functionF(MarketGraph & G);
        //输出给定账号与其他账号之间的最短交易路径
        void functionG(MarketGraph & G);
    private:
        unsigned long long Dijkstra(MarketGraph & G, const AccountName & accName, std::vector<std::stack<AccountName>> & paths);
};

void Analyser::functionD(MarketGraph & G)
{
    std::cout << "Market Graph." << std::endl;
    unsigned long long txCount = 0;
    std::clock_t sTime = std::clock();
    for(auto i : G.getVertices())
    {
        //输出每一个向外转帐金额
        for(auto j : i.second.OutEdges)
        {
            txCount++;
            std::cout << txCount << ": " << i.first << " -> " << j.first << " Sum: " << j.second.sumAmount << std::endl;
        }
    }
    std::clock_t eTime = std::clock();
    std::cout << "Total: " << txCount << " Txs." << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);
}

void Analyser::functionE(MarketGraph & G)
{
    //std::cout << "Average in/out degree and top k in/out degree accounts." << std::endl;
    //std::cout << "Please enter k(>0):";

    int k;
    std::cin >> k;

    if(k <= 0)
    {
        std::cout << "Too small k!" << std::endl;
        return;
    }

    //按出/入度降序排列
    typedef std::pair<AccountName, size_t> AccDegPair;
    class MyCompare
    {
        public:
            bool operator()(const AccDegPair & A, const AccDegPair & B)
            {
                return A.second < B.second;
            }
    };

    //入度优先队列
    std::priority_queue<AccDegPair, std::vector<AccDegPair>, MyCompare> inDegQ;
    //出度优先队列
    std::priority_queue<AccDegPair, std::vector<AccDegPair>, MyCompare> outDegQ;

    //出度=入度, 所以只用统计一个的和
    unsigned long long sumInDeg = 0ull;
    //unsigned long long sumOutDeg = 0ull;
    unsigned long long sumAccount = 0ull;

    std::clock_t sTime = std::clock();
    //遍历每一个节点, 获得相应度数, 并放到优先队列中
    for(auto i : G.getVertices())
    {
        outDegQ.emplace(std::make_pair(i.first, i.second.OutEdges.size()));
        //sumAccount++;
    }
    //std::cout << "Total: " << sumAccount << " accounts, " << sumInDeg << " degree(s)." << std::endl;
    //std::cout << "Average degree: " << double(sumInDeg) / sumAccount << std::endl;
    
    //std::cout << std::endl;


    //std::cout << "Top " << k << " outdegree accounts:" << std::endl;
    for(int i = 0; i < k && !outDegQ.empty(); i++)
    {
        //std::cout << (i + 1) << ": " << outDegQ.top().first << ", Outdegree: " << outDegQ.top().second << std::endl;
        std::cout << (i + 1) << "\t" << outDegQ.top().first << "\t" << outDegQ.top().second << std::endl;
        outDegQ.pop();
    }

    std::clock_t eTime = std::clock();
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);

    sTime = std::clock();

    //遍历每一个节点, 获得相应度数, 并放到优先队列中
    for(auto i : G.getVertices())
    {
        inDegQ.emplace(std::make_pair(i.first, i.second.InEdges.size()));
        //sumInDeg += i.second.InEdges.size();
        //sumAccount++;
    }
    //std::cout << "Top " << k << " indegree accounts:" << std::endl;
    for(int i = 0; i < k && !inDegQ.empty(); i++)
    {
        //std::cout << (i + 1) << ": " << inDegQ.top().first << ", Indegree: " << inDegQ.top().second << std::endl;
        std::cout << (i + 1) << "\t" << inDegQ.top().first << "\t" << inDegQ.top().second << std::endl;
        inDegQ.pop();
    }

    eTime = std::clock();
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);
}

void Analyser::functionF(MarketGraph & G)
{
    std::cout << "Are there circles in the market graph?" << std::endl;
    std::cout << "Result: ";
    std::clock_t sTime = std::clock();

    //账号-入度对
    std::unordered_map<AccountName, size_t> accDegMap;
    //零入度栈
    std::stack<AccountName> zeroDegStack;
    //复制数据, 求入度
    //O(V)
    for(auto i : G.getVertices())
    {
        size_t inDeg = i.second.InEdges.size();
        accDegMap.emplace(std::make_pair(i.first, inDeg));
        if(inDeg == 0)
        {
            zeroDegStack.emplace(i.first);
        }
    }
    unsigned long long zeroDegCount = 0;
    while(!zeroDegStack.empty())
    {
        zeroDegCount++;
        AccountName top = zeroDegStack.top();
        zeroDegStack.pop();
        for(auto j : G.getVertices().at(top).OutEdges)
        {
            --accDegMap.at(j.first);
            if(accDegMap.at(j.first) == 0)
            {
                zeroDegStack.emplace(j.first);
            }
        }
        
    }
    if(zeroDegCount < G.getVertices().size())
    {
        std::cout << "Yes." << std::endl;
    }
    else
    {
        std::cout << "No." << std::endl;
    }

    std::clock_t eTime = std::clock();
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);
}

void Analyser::functionG(MarketGraph & G)
{
    //std::cout << "Shortest path from a given account. (Dijkstra)" << std::endl;
    //std::cout << "Please enter an account:";

    std::string accName;
    std::cin >> accName;

    std::cout << std::endl;
    
    //找不到账号
    if(G.getVertices().find(accName) == G.getVertices().end())
    {
        std::cout << "Can't find account." << std::endl;
        return;
    }
    std::vector<std::stack<AccountName>> paths;
    std::clock_t sTime = std::clock();

    Analyser::Dijkstra(G, accName, paths);
    std::cout << std::endl;

    unsigned long long pathCount = 0;
    for(auto i : paths)
    {
        pathCount++;
        std::cout << "Path: " << pathCount << std::endl;
        std::cout << i.top() << std::endl;
        i.pop();
        while(!i.empty())
        {
            std::cout << " -> " << i.top() << std::endl;
            i.pop(); 
        }
        std::cout << std::endl;
    }

    std::clock_t eTime = std::clock();
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);
}

unsigned long long Analyser::Dijkstra(MarketGraph & G, const AccountName & accName, std::vector<std::stack<AccountName>> & paths)
{
    //工具
    //(weight, prevVertex) 对, 保存路径至此权重与上一个顶点(输出路径方便)
    typedef std::pair<double, AccountName> WVPair;
    //存放 string -> (weight, prevVertex)对的树 prevVertex == 本身表示已经到头了
    //每轮遍历松弛, 从中取出最小的
    typedef std::unordered_map<AccountName, WVPair> DisMaxTree;
    //动态树
    DisMaxTree disMax;
    //已经找到最短路径的集合
    std::unordered_map<AccountName, WVPair> foundMin;

    //树上挑出一组最小的边的函数, 返回tree.end()表示树空了
    auto findMin = [](DisMaxTree & tree) -> DisMaxTree::iterator
    {
        DisMaxTree::iterator minIndex = tree.begin();
        for(DisMaxTree::iterator i = tree.begin(); i != tree.end(); i++)
        {
            if(minIndex -> second.first > i -> second.first)
            {
                minIndex = i;
            }
        }
        return minIndex;
    };

    unsigned long long pathCount = 0;
    //保存以dest为终点的路径
    auto savePath = [&](AccountName & dest, std::vector<std::stack<AccountName>> & paths) -> void
    {
        pathCount++;
        //std::cout << "Path " << pathCount << " : " << std::endl;
        std::stack<AccountName> toolStack;
        AccountName nowStr = dest;
        while(foundMin.at(nowStr).second != nowStr)
        {
            toolStack.emplace(nowStr);
            nowStr = foundMin.at(nowStr).second;
        }
        toolStack.emplace(foundMin.at(nowStr).second);
        paths.emplace_back(toolStack);
    };

    //每一轮的源头点, 第一轮自然是源头
    AccountName nowSource = accName;
    //初始节点为找到最短路径的
    foundMin.emplace(std::make_pair(accName, std::make_pair(0, accName)));

    //首先把所有相邻顶点的信息存进去
    for(auto i : G.getVertices().find(accName) -> second.OutEdges)
    {
        disMax.emplace(std::make_pair(i.first, std::make_pair(i.second.sumAmount, accName)));
    }

    //找一个最小的
    DisMaxTree::iterator min = findMin(disMax);
    //树是空的, 孤立点
    if(min == disMax.end())
    {
        std::cout << "No paths." << std::endl;
        return 0;
    }

    while(min != disMax.end())
    {
        //加入已经找到最小值的
        foundMin.emplace(*min);
        //从刚找到的最小值出发
        nowSource = min -> first;
        //打印一下路径(以nowSource为终点)
        std::cout << accName << "\t" << nowSource << "\t" << min -> second.first << std::endl;
        //保存路径
        savePath(nowSource, paths);
        //弹出最小顶点不再考虑
        disMax.erase(min);
        //从这个点出发, 遍历一下有没有更优的
        for(auto i : G.getVertices().find(nowSource) -> second.OutEdges)
        {
            //树上没出现——>加入新遇到的顶点
            if(disMax.find(i.first) == disMax.end())
            {
                disMax.emplace(std::make_pair(i.first, 
                    std::make_pair(foundMin.at(nowSource).first + i.second.sumAmount, nowSource)
                    ));
            }
            //原来路径长——>松弛一下
            else if(disMax.at(i.first).first > foundMin.at(nowSource).first + i.second.sumAmount)
            {
                disMax.emplace(std::make_pair(i.first, 
                    std::make_pair(foundMin.at(nowSource).first + i.second.sumAmount, nowSource)
                    ));
            }
        }
        min = findMin(disMax);
    }
    return pathCount;
}
#endif