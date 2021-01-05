#ifndef QUERYER_H
#define QUERYER_H

#include "util.h"
#include "account.h"
#include "block.h"
#include "graph.h"

class Queryer
{
    public:
        Queryer(){}
        //指定账号某时间段内交易金额最大的k项记录
        void functionA(MarketGraph & marketGraph);
        //指定账号某时间前的总金额(假设初始为0)
        void functionB(MarketGraph & marketGraph);
        //某时刻福布斯排行榜top k
        void functionC(MarketGraph & marketGraph);
};

void Queryer::functionA(MarketGraph & marketGraph)
{
    std::getchar();
    int k = 0;
    long int startTime = 0l, endTime = 0l;
    char _accName[35] = {0};
    std::scanf("\"%[^\"]\",%ld,%ld,%d", _accName, &startTime, &endTime, &k);
    //输入k
    //std::cout << "Top k biggest Txs of an account between two timestamps." << std::endl;
    //std::cout << "Please enter k(>0):";
    //int k;
    //std::cin >> k;
    if(k <= 0)
    {
        std::cout << "Too small k!" << std::endl;
        return;
    }
    //输入起止时间戳
    //std::cout << "Please enter start and end timestamps:";
    //long int startTime = 0l, endTime = 0l;
    //std::cin >> startTime >> endTime;
    if(startTime > endTime)
    {
        std::cout << "Illegal time duration!" << std::endl;
        return;
    }

    //std::cout << "Please enter an account:";
    std::string accName(_accName);
    //std::cin >> accName;

    auto accIndex = marketGraph.getVertices().find(accName);
    if(accIndex == marketGraph.getVertices().end())
    {
        std::cout << "Can't find account!" << std::endl;
        return;
    }

    std::clock_t sTime = std::clock();

    //size_t outDeg = accIndex -> second.OutEdges.size();
    //size_t inDeg = accIndex -> second.InEdges.size();
    //size_t total = outDeg + inDeg;

    //std::cout << "Total: " << total << " record(s)." << std::endl;
    //std::cout << "Out: " << outDeg << " record(s)." << std::endl;
    //std::cout << "In: " << inDeg << " record(s)." << std::endl;

    //优先队列    
    class MyCompare
    {
        public:
            bool operator()(const TxRecord & A, const TxRecord & B)
            {
                return A.amount < B.amount;
            }
    };
    std::priority_queue<TxRecord, std::vector<TxRecord>, MyCompare> q;

    //遍历两个链表, 找出在时间戳范围内的
    //出边
    for(auto & i : accIndex -> second.OutEdges)
    {
        for(auto & j : i.second.txs)
        {
            if(j -> timeStamp >= startTime && j -> timeStamp <= endTime)
            {
                q.emplace(TxRecord(j -> txID, j -> blockID, i.first, j -> amount, true));
            }
        }
    }
    //入边
    for(auto & i : accIndex -> second.InEdges)
    {
        for(auto & j : i.second.txs)
        {
            if(j -> timeStamp >= startTime && j -> timeStamp <= endTime)
            {
                q.emplace(TxRecord(j -> txID, j -> blockID, i.first, j -> amount, false));
            }
        }
    }

    //std::cout << "Top " << k << " Txs:" << std::endl;
    for(int i = 0; i < k && !q.empty(); i++)
    {
        //std::cout << (i + 1) << ": ";
        std::cout << q.top().txID << "\t" << q.top().blockID << "\t";
        //出边
        if(q.top().isOut)
        {
            //std::cout << accName << " -> " << q.top().another;
            std::cout << accName << "\t" << q.top().amount << "\t" << q.top().another << std::endl;
        }
        else
        {
            //std::cout << q.top().another << " -> " << accName;
            std::cout << q.top().another << "\t" << q.top().amount << "\t" << accName << std::endl;
        }
        //std::cout << ", Amount: " << q.top().amount << std::endl;
        q.pop();
    }
    std::clock_t eTime = std::clock();
    
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);
}

void Queryer::functionB(MarketGraph & marketGraph)
{
    std::getchar();
    //std::cout << "Total money of an account before a certain timestamp." << std::endl;
    //std::cout << "Please enter an end timestamp:";
    //long int endTime = 0l;

    //std::cin >> endTime;

    //std::cout << "Please enter an account:";
    long int startTime = 0l, endTime = 0l;
    char _accName[35] = {0};
    std::scanf("\"%[^\"]\",%ld,%ld", _accName, &startTime, &endTime);

    std::string acc(_accName);
    //std::cin >> acc;
    auto accIndex = marketGraph.getVertices().find(acc);
    if(accIndex == marketGraph.getVertices().end())
    {
        std::cout << "Can't find account!" << std::endl;
        return;
    }

    std::clock_t sTime = std::clock();
    double sum = 0;
    //遍历两个链表, 找出在时间戳范围内的(可优化)
    for(auto & i : accIndex -> second.OutEdges)
    {
        for(auto & j : i.second.txs)
        {
            if(j -> timeStamp >= startTime && j -> timeStamp <= endTime)
            {
                sum -= j -> amount;
            }
        }
    }
    for(auto & i : accIndex -> second.InEdges)
    {
        for(auto & j : i.second.txs)
        {
            if(j -> timeStamp >= startTime && j -> timeStamp <= endTime)
            {
                sum += j -> amount;
            }
        }
    }

    //std::cout << "Account: " << acc << ". Sum before @" << endTime << " : " << sum << "." << std::endl;
    std::cout << acc << ":" << sum << std::endl;
    std::clock_t eTime = std::clock();

    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);
}

void Queryer::functionC(MarketGraph & marketGraph)
{
    std::getchar();
    //std::cout << "Top k most valuable accounts before a certain timestamp." << std::endl;
    //std::cout << "Please enter k(>0):";

    long int startTime = 0l, endTime = 0l;
    int k = 0;
    std::scanf("%ld,%ld,%*[^0-9]%d", &startTime, &endTime, &k);
    //std::cin >> k;
    if(k <= 0)
    {
        std::cout << "Too small k! Default 50." << std::endl;
        k = 50;
    }

    //std::cout << "Please enter an end timestamp:";
    //long int endTime = 0l;
    //std::cin >> endTime;

    std::clock_t sTime = std::clock();

    typedef std::pair<AccountName, double> AccountPair;

    class MyCompare
    {
        public:
            bool operator()(const AccountPair & A, const AccountPair & B)
            {
                return A.second < B.second;
            }
    };
    std::priority_queue<AccountPair, std::vector<AccountPair>, MyCompare> topKS;
    //捋交易网
    for(auto i : marketGraph.getVertices())
    {
        double sum = 0;
        //入边
        for(auto j : i.second.InEdges)
        {
            for(auto k : j.second.txs)
            {
                if(k -> timeStamp <= endTime)
                {
                    sum += k -> amount;
                }
            }
        }
        //出边
        for(auto j : i.second.OutEdges)
        {
            for(auto k : j.second.txs)
            {
                if(k -> timeStamp <= endTime)
                {
                    sum -= k -> amount;
                }
            }
        }
        topKS.emplace(std::make_pair(i.first, sum));
    }
    
    //std::cout << "Top " << k << " most valuable accounts:" << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout.precision(4);
    for(int i = 0; i < k && !topKS.empty(); i++)
    {
        //std::cout << (i + 1) << ": " << topKS.top().first << ", Sum: " << topKS.top().second << std::endl;
        std::cout << (i + 1) << "\t" << topKS.top().first << "\t" << topKS.top().second << std::endl;
        topKS.pop();
    }
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);

    std::clock_t eTime = std::clock();

    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);
}

#endif