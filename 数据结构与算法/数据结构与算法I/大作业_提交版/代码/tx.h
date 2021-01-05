#ifndef TX_H
#define TX_H

#include "util.h"
#include "account.h"

typedef long int TxTimeStamp;
//转账只包含金额, 账号由交易图存储
typedef struct Tx
{
    Tx(long int _txID, int _blockID, double _amount, long int _timeStamp)
        :txID(_txID), blockID(_blockID), amount(_amount), timeStamp(_timeStamp){}
    long int txID;
    int blockID;
    //Bit Coin金额
    double amount;
    //时间戳
    TxTimeStamp timeStamp;
}Tx;

//扩展的转账记录
typedef struct TxRecord
{
    TxRecord(long int _txID, int _blockID, AccountName _another, double _amount, bool _isOut)
        : txID(_txID), blockID(_blockID), another(_another), amount(_amount), isOut(_isOut){}
    long int txID;
    int blockID;
    AccountName another;
    double amount;
    //是否转出
    bool isOut;
}TxRecord;

#endif