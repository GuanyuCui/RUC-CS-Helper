#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include "bitree.h"


typedef std::pair<char, double> CWPair;

class HNodeGreater
{
    public:
        bool operator()(const BiTreeNode<CWPair> * A, const BiTreeNode<CWPair> * B)
        {
            return A -> getData().second > B -> getData().second;
        }
};

class HuffmanCode
{
    public:
        HuffmanCode(const std::vector<std::pair<char, double> > &);
        //打印字母表
        void printTable();
        //编码
        std::string getCode(const std::string &);
        //译码
        std::string getOriginal(const std::string &);

    private:
        //内部的二叉树
        BiTree<CWPair> tree;
        //编码出来的表
        std::map<char, std::string> codeTable;
        //遍历树获得字母编码表
        void parseTable(std::string & path, BiTreeNode<CWPair> * nowRoot);
};

HuffmanCode::HuffmanCode(const std::vector<std::pair<char, double> > & freq)
{
    //优先队列
    std::priority_queue<BiTreeNode<CWPair> *, std::vector<BiTreeNode<CWPair> *>, HNodeGreater> pQueue;
    //初始节点
    for(size_t i = 0; i < freq.size(); i++)
    {
        pQueue.push(new BiTreeNode<CWPair>(freq.at(i)));
    }
    BiTreeNode<CWPair> * newRoot = nullptr;
    //两个以上节点才有必要
    while(pQueue.size() >= 2)
    {
        //弹出两个权值最小的
        BiTreeNode<CWPair> * l = pQueue.top();
        pQueue.pop();
        BiTreeNode<CWPair> * r = pQueue.top();
        pQueue.pop();
        //组合成为一棵新树
        CWPair rootPair = {'\0', l -> getData().second + r -> getData().second};
        newRoot = new BiTreeNode<CWPair>(rootPair);
        newRoot -> setLChild(l);
        //l -> setParent(newRoot);
        newRoot -> setRChild(r);
        //r -> setParent(newRoot);
        //插回去
        pQueue.push(newRoot);
    }
    //处理完之后
    tree.setRoot(newRoot);
    std::string path;
    parseTable(path, newRoot);

    //输出编码表, 调试用
    /*
    for(auto i = codeTable.begin(); i != codeTable.end(); i++)
    {
        std::cout << i -> first << " " << i -> second << std::endl;
    }
    
    std::cout << tree.depth() << std::endl;
    */
}

void HuffmanCode::parseTable(std::string & path, BiTreeNode<CWPair> * nowRoot)
{
    //遍历来获得
    if(nowRoot -> isLeaf())
    {
        codeTable.insert(std::pair<char, std::string>(nowRoot -> getData().first, path));
        path.pop_back();
        return;
    }
    //递归
    //左边
    path += "0";
    parseTable(path, nowRoot -> getLChild());

    //右边
    path += "1";
    parseTable(path, nowRoot -> getRChild());

    //处理完左右向上一层
    path.pop_back();
}

void HuffmanCode::printTable()
{
    for(std::map<char, std::string>::iterator i = codeTable.begin(); i != codeTable.end(); i++)
    {
        std::cout << i -> first << " " << i -> second << std::endl;
    }
}

std::string HuffmanCode::getCode(const std::string & str)
{
    std::string retVal;
    for(size_t i = 0; i < str.size(); i++)
    {
        retVal += codeTable.at(str.at(i));
    }
    return retVal;
}

std::string HuffmanCode::getOriginal(const std::string & str)
{
    std::string retVal;
    BiTreeNode<CWPair> * nowNode = tree.getRoot();
    for(size_t i = 0; i < str.size(); i++)
    {
        if(nowNode -> isLeaf())
        {
            retVal.push_back(nowNode -> getData().first);
            nowNode = tree.getRoot();
        }
        if(str.at(i) == '0')
        {
            nowNode = nowNode -> getLChild();
        }
        else if(str.at(i) == '1')
        {
            nowNode = nowNode -> getRChild();
        }
    }
    //最后必然是叶子
    if(nowNode -> isLeaf())
    {
        retVal.push_back(nowNode -> getData().first);
        nowNode = tree.getRoot();
    }
    else
    {
        std::out_of_range e("编码意外终止");
        throw e;
    }
    return retVal;
}
#endif