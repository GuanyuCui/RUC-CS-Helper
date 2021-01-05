#include <iostream>
#include <vector>
#include <utility>

#include <fstream>
#include "huffman.h"

bool readFile(const std::string & fileName, std::vector<std::pair<char, double> > & dest)
{
    std::fstream file(fileName, std::fstream::in);
    if(!file.is_open())
    {
        std::cout << "打不开文件!" << std::endl;
        return false;
    }
    while(!file.eof())
    {
        char c;
        double w;
        file.get(c);
        file.ignore();
        file >> w;
        file.ignore();
        dest.push_back(CWPair(c, w));
    }
    return true;
}

bool readConsole(std::vector<std::pair<char, double> > & dest)
{
    std::cout << "请输入字母表字符数:";
    int count;
    std::cin >> count;
    if(count <= 0)
    {
        std::cout << "参数不合法!" << std::endl;
        return false;
    }
    std::cout << "请按行输入字母表以及对应权值(e.g. A 0.08167): " << std::endl;

    for(unsigned int i = 0; i < count; i++)
    {
        char c;
        double w;
        //忽略回车
        std::cin.ignore();
        c = std::getchar();
        std::cin.ignore();
        std::cin >> w;
        dest.push_back(CWPair(c, w));
    }
    return true;
}


int main(int argc, char * argv[])
{
    std::cout << "Huffman Code." << std::endl;
    std::cout << "Written By G.Cui 2019.12.03" << std::endl;
    std::vector<std::pair<char, double> > freqVec;
    while(true)
    {
        std::cout << "请选择输入方式(f: 文件, c: 控制台):";
        std::string input;
        std::cin >> input;
        if(input == "f")
        {
            std::string fName;
            std::cout << "请输入读取文件名:";
            std::cin >> fName;
            //成功->继续
            if(readFile(fName, freqVec))
            {
                std::cout << "读取成功!" << std::endl;
                break;
            }
        }
        else if(input == "c")
        {
            if(readConsole(freqVec))
            {
                std::cout << "读取成功!" << std::endl;
                break;
            }
        }
    }
    HuffmanCode coder(freqVec);
    coder.printTable();
    while(true)
    {
        std::string str;

        std::cout << "请选择操作(0: 退出, 1: 编码, 2: 译码): ";
        std::string op;
        std::cin >> op;

        //退出
        if(op == "0")
        {
            break;
        }
        //编码
        else if(op == "1")
        {
            std::cout << "请输入欲编码的字符串:";
            //std::cin >> str;
            //空白符
            std::cin >> std::ws;
            std::getline(std::cin, str);
            try
            {
                std::cout << "结果:" << coder.getCode(str) << std::endl;
            }
            catch(const std::out_of_range &)
            {
                std::cout << "非法字符!" << std::endl;
            }
        }
        //译码
        else if(op == "2")
        {
            std::cout << "请输入欲译码的字符串(仅限01字符串):";
            std::cin >> str;
            try
            {
                std::cout << "结果:" << coder.getOriginal(str) << std::endl;
            }
            catch(const std::out_of_range &)
            {
                std::cout << "非法编码!" << std::endl;
            }
        }
        else
        {
            std::cout << "非法输入, 请重新选择!" << std::endl;
        }
    }

    return 0;
}