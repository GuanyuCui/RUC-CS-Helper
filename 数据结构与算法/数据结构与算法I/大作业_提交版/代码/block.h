#ifndef BLOCK_H
#define BLOCK_H

#include "util.h"
#include "tx.h"

typedef int BlockID;
typedef long int BlockTimeStamp;
typedef struct BlockInfo
{
    BlockInfo(BlockTimeStamp time) : timeStamp(time), txCount(0){}
    ~BlockInfo()
    {
        for(auto i : Txs)
        {
            delete i.second;
        }
    }
    //添加交易
    Tx * addTx(long int txID, int blockID, double amount, long int time)
    {
        txCount++;
        auto retVal = Txs.emplace(std::make_pair(txCount, new Tx(txID, blockID, amount, time)));
        return retVal.first -> second;
    }
    BlockTimeStamp timeStamp;
    std::unordered_map<int, Tx *> Txs;
    int txCount;
}BlockInfo;

typedef std::map<BlockID, BlockInfo *> BlockTree;
#endif