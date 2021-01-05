#ifndef SOLUTION_H
#define SOLUTION_H

#include "util.h"
#include "loader.h"
#include "queryer.h"
#include "analyser.h"
#include "updater.h"

class Solution
{
    public:
        Solution(){}
        ~Solution()
        {
            for(auto &i : blocks)
            {
                delete i.second;
            }
        }
        //打印Logo
        void printLogo();
        //加载
        bool loadData();
        //打印用户界面
        void printUsage();
        //主过程
        void mainProc();
    private:
        //文件加载器
        Loader loader;
        //查询器
        Queryer queryer;
        //分析器
        Analyser analyser;
        //更新器
        Updater updater;
        //区块树
        BlockTree blocks;
        //交易图
        MarketGraph marketGraph;
};

void Solution::printLogo()
{
    std::cout << "--------------------------\"Grand Assignment\"--------------------------" << std::endl;
    std::cout << "|                  Written By G.Cui @ Info.RUC 2019                  |" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

bool Solution::loadData()
{
    std::string bfName = "";
    std::string txName = "";
#ifdef DEBUG
    bfName = "/Users/CuiGuanyu/Desktop/大作业/大作业数据集V2.1/block_part1.csv";
    txName = "/Users/CuiGuanyu/Desktop/大作业/大作业数据集V2.1/tx_data_part1_v2.csv";
#else
    std::cout << "Please enter block file name:";
    std::cin >> bfName;

    std::cout << "Please enter tx file name:";
    std::cin >> txName;
#endif
    return (loader.loadBlockFile(blocks, bfName) && loader.loadTxFile(marketGraph, blocks, txName));
}

void Solution::printUsage()
{
    std::cout << "-----------------------------------------------------------------------" << std::endl;
    std::cout << "Please choose the module(e.g. A):" << std::endl;
    std::cout << "Query:" << std::endl;
    std::cout << "\tA. Top k biggest Txs of an account between two timestamps." << std::endl;
    std::cout << "\tB. Total money of an account before a certain timestamp." << std::endl;
    std::cout << "\tC. Top k most valuable accounts before a certain timestamp." << std::endl;

    std::cout << "Analyse:" << std::endl;
    std::cout << "\tD. Market graph." << std::endl;
    std::cout << "\tE. Average in/out degree and top k in/out degree accounts." << std::endl;
    std::cout << "\tF. Are there circles in the market graph?" << std::endl;
    std::cout << "\tG. Shortest path from a given account. (Dijkstra)" << std::endl;

    std::cout << "Update:" << std::endl;
    std::cout << "\tH. Update Txs from file." << std::endl;

    std::cout << "Others:" << std::endl;
    std::cout << "\tQ. Quit." << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;
}

void Solution::mainProc()
{
    std::cout << ">>> ";
    std::string input = "";
    //选择功能的循环
    while(true)
    {
        std::cin >> input;
        if(input == "A")
        {
            queryer.functionA(marketGraph);
        }
        else if(input == "B")
        {
            queryer.functionB(marketGraph);
        }
        else if(input == "C")
        {
            queryer.functionC(marketGraph);
        }
        else if(input == "D")
        {
            analyser.functionD(marketGraph);
        }
        else if(input == "E")
        {
            analyser.functionE(marketGraph);
        }
        else if(input == "F")
        {
            analyser.functionF(marketGraph);
        }
        else if(input == "G")
        {
            analyser.functionG(marketGraph);
        }
        else if(input == "H")
        {
            updater.functionH(marketGraph, blocks);
        }
        else if(input == "Q")
        {
            std::cout << "Quitting..." << std::endl;
            break;
        }
        else
        {
            std::cout << "Unavailable!" << std::endl;
        }
        printUsage();
        std::cout << ">>> ";
    }
}

#endif