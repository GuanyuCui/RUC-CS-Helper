#ifndef LOADER_H
#define LOADER_H

#include "util.h"
#include "block.h"
#include "graph.h"

//加载器
class Loader
{
    public:
        //加载区块文件 目标为dest区块树, 文件名fName, 是否过滤第一行
        bool loadBlockFile(BlockTree & dest, const std::string & fName, bool trimTitle = true);
        //加载交易文件 目标为accDest交易图, 以交易树为辅助, 文件名fName, 是否过滤第一行
        bool loadTxFile(MarketGraph & accDest, BlockTree & dest, const std::string & fName, bool trimTitle = true);
};

bool Loader::loadBlockFile(BlockTree & dest, const std::string & fName, bool trimTitle)
{
    //先打开文件
    std::fstream blockFile(fName, std::fstream::in);
    //加载失败
    if(!blockFile.is_open())
    {
        std::cout << "Unable to open file!" << std::endl;
        return false;
    }
    std::cout << "Loading block file...Please Wait..." << std::endl;
    std::clock_t sTime = std::clock();

    if(trimTitle)
    {
        //跳过第一行
        blockFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    char tmpLine[1024] = {0};
    //一行行处理
    while(!blockFile.eof())
    {
        blockFile.getline(tmpLine, 1024);
        int ID = 0;
        long int timeStamp = 0;
        //blockID,hash,block_timestamp
        std::sscanf(tmpLine, "%d,%*[^,],%ld", &ID, &timeStamp);
        dest.emplace(std::make_pair(ID, new BlockInfo(timeStamp)));
    }
    std::clock_t eTime = std::clock();
    std::cout << "Successfully loaded block file!" << std::endl;
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    blockFile.close();
    return true;
}

bool Loader::loadTxFile(MarketGraph & accDest, BlockTree & dest, const std::string & fName, bool trimTitle)
{
    std::fstream txFile(fName, std::fstream::in);
    //加载失败
    if(!txFile.is_open())
    {
        std::cout << "Unable to open file!" << std::endl;
        return false;
    }
    std::cout << "Loading tx file...Please Wait..." << std::endl;
    std::clock_t sTime = std::clock();
    if(trimTitle)
    {
        //跳过第一行
        txFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    char tmpLine[1024] = {0};
    char from[35] = {0};
    char to[35] = {0};
    while(!txFile.eof())
    {
        long int txID = 0;
        int blockID = 0;
        double amount = 0;
        txFile.getline(tmpLine, 1024);
        //tx_id,blockID,from,amount,to
        std::sscanf(tmpLine, "%ld,%d,%[^,],%lf,%[^,\r\n]", &txID, &blockID, from, &amount, to);
        //找到对应区块, 添加交易记录, 同时修改账号交易记录内容
        try
        {
            auto iter = dest.at(blockID);
            long int timeStamp = iter -> timeStamp;
            //添加交易, 获得交易在交易树的存储地址
            Tx * addr = iter -> addTx(txID, blockID, amount, timeStamp);
            //添加出入边, 边上有指针数组指向交易
            accDest.addInEdge(to, from, addr);
            accDest.addOutEdge(from, to, addr);
        }
        catch(const std::out_of_range &)
        {
            std::cout << "Lack blockID!" << std::endl;
            return false;
        }
    }
    std::clock_t eTime = std::clock();
    std::cout << "Successfully loaded tx file!" << std::endl;
    std::cout << "Time: " << double(eTime - sTime) / CLOCKS_PER_SEC << " seconds.\n" << std::endl;
    txFile.close();
    return true;
}
#endif