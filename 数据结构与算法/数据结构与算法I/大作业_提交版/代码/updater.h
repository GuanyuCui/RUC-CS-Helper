#ifndef UPDATER_H
#define UPDATER_H

#include "util.h"
#include "account.h"
#include "block.h"
#include "graph.h"
#include "loader.h"

class Updater
{
    public:
        Updater(){}
        //根据文件添加交易
        void functionH(MarketGraph & G, BlockTree & blocks);
};

void Updater::functionH(MarketGraph & G, BlockTree & blocks)
{
#ifdef DEBUG
    std::string fName = "/Users/CuiGuanyu/Desktop/大作业/大作业数据集V2.1/tx_data_part2.csv";
#else
    std::cout << "Please enter Tx file name:" << std::endl;
    std::string fName;
    std::cin >> fName;
#endif
    Loader loader;
    loader.loadTxFile(G, blocks, fName, false);
}
#endif