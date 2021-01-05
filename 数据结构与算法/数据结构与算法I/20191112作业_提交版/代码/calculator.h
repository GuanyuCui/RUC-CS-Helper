#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "polycal.h"
#include "veccal.h"
#include "execer.h"
#include "matrixcal.h"

template <typename T>
class Calculator
{
    public:
        Calculator(){};
        void printLogo();
        void printUsage();
    private:
        //向量计算器模块
        VecCalculator<T> vecCal;
        //多项式计算器模块
        PolyCalculator<T> polyCal;
        //表达式执行器模块
        Execer execer;
        //矩阵计算模块
        MatrixCal matrixCal;
};

template <typename T>
void Calculator<T>::printLogo()
{
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "|          Simple Calculator         |" << std::endl;
    std::cout << "|                                    |" << std::endl;
    std::cout << "|    Written by G.Cui, 2019.11.12    |" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

template <typename T>
void Calculator<T>::printUsage()
{
    while(1)
    {
        std::cout << std::endl;
        std::cout << "请选择功能模块:\n1. 向量运算(顺序表);\n2. 向量夹角余弦值(顺序表);\n";
        std::cout << "3. 一元多项式运算(顺序表);\n4. 多项式乘法(顺序表);\n";
        std::cout << "5. 多项式导数(顺序表);\n6. 一元多项式运算(链表);\n";
        std::cout << "7. 多项式乘法(链表);\n8. 多项式导数(链表);\n";
        std::cout << "9. 表达式求值/可编程计算器; \n10. 矩阵运算.\n";
        std::cout << "请输入需要的模块的数字(0退出): " << std::endl;
        int fn;
        std::cin >> fn;

        //退出
        if(fn == 0)
        {
            return;
        }
        //基于顺序表的向量运算
        else if(fn == 1)
        {
            vecCal.task1();
        }
        //基于顺序表的向量夹角余弦值
        else if(fn == 2)
        {
            vecCal.task2();
        }
        //基于顺序表的一元多项式运算
        else if(fn == 3)
        {
            polyCal.task3();
        }
        //基于顺序表的多项式乘法
        else if(fn == 4)
        {
            polyCal.task4();
        }
        //基于顺序表的多项式求导
        else if(fn == 5)
        {
            polyCal.task5();
        }
        //基于链表的一元多项式运算
        else if(fn == 6)
        {
            polyCal.task6();
        }
        //基于链表的多项式乘法
        else if(fn == 7)
        {
            polyCal.task7();
        }
        //基于链表的多项式求导
        else if(fn == 8)
        {
            polyCal.task8();
        }
        //表达式求值/简单函数编程器
        else if(fn == 9)
        {
            execer.task9();
        }
        //矩阵计算
        else if(fn == 10)
        {
            matrixCal.task10();
        }
        else
        {
            std::cout << "不合法输入." << std::endl; 
        }
    }
};

#endif