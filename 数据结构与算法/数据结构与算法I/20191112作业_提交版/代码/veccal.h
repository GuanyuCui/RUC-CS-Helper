#ifndef VECCAL_H
#define VECCAL_H

#include "sqlist.h"
#include <cmath>

//向量计算器
template <typename T>
class VecCalculator
{
    public:
        VecCalculator(){}
        //基于顺序表的向量运算
        void task1()
        {
            std::cout << std::endl << "以下是向量运算(顺序表)演示:" << std::endl;
            std::cout << "请输入向量维度:";
            int d;
            std::cin >> d;

            SqList<T> LA(d);
            SqList<T> LB(d);
            SqList<T> Ans(d);

            std::cout << "请输入向量A:";
            inputVec_SqList(LA, d);
            std::cout << "请输入向量B:";
            inputVec_SqList(LB, d);

            std::cout << "请输入运算符(+/-):";
            char op = 0;
            std::cin >> op;
            while(op != '+' && op != '-')
            {
                std::cout << "运算符不合法! 请重新输入运算符(+/-):";
                std::cin >> op;
            }
            vectorCal_SqList(LA, LB, Ans, op);
            std::cout << "结果:";
            Ans.print();
        }
        //基于顺序表的向量夹角余弦值
        void task2()
        {
            std::cout << std::endl << "以下是向量夹角余弦值(顺序表)演示:" << std::endl;
            std::cout << "请输入向量维度:";
            int d;
            std::cin >> d;

            SqList<T> LA(d);
            SqList<T> LB(d);

            std::cout << "请输入向量A:";
            inputVec_SqList(LA, d);
            std::cout << "请输入向量B:";
            inputVec_SqList(LB, d);
            std::cout << "结果:" << vectorAngCos_SqList(LA, LB) << std::endl;
        }
    private:
        //向量加减法——顺序表实现
        void vectorCal_SqList(SqList<T> &A, SqList<T> &B, SqList<T> & Ans, char op);
        //向量夹角余弦值——顺序表实现
        double vectorAngCos_SqList(SqList<T> &A, SqList<T> &B);

        //以下为辅助函数
        //向量输入num项
        void inputVec_SqList(SqList<T> & dest, int num);
};

template <typename T>
void VecCalculator<T>::vectorCal_SqList(SqList<T> & A, SqList<T> & B, SqList<T> & Ans, char op)
{
    int dim = A.length();
    
    if(op == '+')
    {
        for(int i = 1; i <= dim; i++)
        {
            T a, b;
            A.getElem(i, a);
            B.getElem(i, b);
            Ans.insertElem(i, a + b);
        }
    }
    else if(op == '-')
    {
        for(int i = 1; i <= dim; i++)
        {
            T a, b;
            A.getElem(i, a);
            B.getElem(i, b);
            Ans.insertElem(i, a - b);
        }
    }
}

template <typename T>
double VecCalculator<T>::vectorAngCos_SqList(SqList<T> &A, SqList<T> &B)
{
    int L = A.length();
    T a,b;
    //点积
    double dotProd = 0.0;
    //两向量模的平方
    double Asqr = 0.0, Bsqr = 0.0;
    for(int i = 1; i <= L; i++)
    {
        A.getElem(i, a);
        B.getElem(i, b);
        dotProd += a * b;
        Asqr += a * a;
        Bsqr += b * b;
    }
    //算夹角余弦
    double retVal = dotProd / (std::sqrt(Asqr) * std::sqrt(Bsqr));
    return retVal;
}

template <typename T>
void VecCalculator<T>::inputVec_SqList(SqList<T> & dest, int num)
{
    for(int i = 1; i <= num; i++)
    {
        T tmp;
        std::cin >> tmp;
        dest.insertElem(i, tmp);
    }
}
#endif