#ifndef POLYCAL_H
#define POLYCAL_H

#include "sqlist.h"
#include "linkedlist.h"

//多项式计算器
template <typename T>
class PolyCalculator
{
    public:
        PolyCalculator(){}
        //基于顺序表的一元多项式运算
        void task3()
        {
            std::cout << std::endl << "以下是一元多项式运算(顺序表)演示:" << std::endl;
            std::cout << "请输入第一个多项式项数:";
            int d1;
            std::cin >> d1;
            SqList<PolyNode<T> > LA(d1);
            inputPoly_SqList(LA, d1);
            
            std::cout << "请输入第二个多项式项数:";
            int d2;
            std::cin >> d2;
            SqList<PolyNode<T> > LB(d2);
            inputPoly_SqList(LB, d2);
            
            std::cout << "请输入运算符(+/-):";
            char op = 0;
            std::cin >> op;
            while(op != '+' && op != '-')
            {
                std::cout << "运算符不合法! 请重新输入运算符(+/-):";
                std::cin >> op;
            }
            SqList<PolyNode<T> > Ans(d1 + d2);
            polyCal_SqList(LA, LB, Ans, op);
            std::cout << "结果:";
            printPoly_SqList(Ans);
        }
        //基于顺序表的多项式乘法
        void task4()
        {
            std::cout << std::endl << "以下是多项式乘法(顺序表)演示:" << std::endl;
            std::cout << "请输入第一个多项式项数:";
            int d1;
            std::cin >> d1;
            SqList<PolyNode<T> > LA(d1);
            inputPoly_SqList(LA, d1);
            
            std::cout << "请输入第二个多项式项数:";
            int d2;
            std::cin >> d2;
            SqList<PolyNode<T> > LB(d2);
            inputPoly_SqList(LB, d2);

            SqList<PolyNode<T> > Ans(d1 + d2);
            polyMult_SqList(LA, LB, Ans);
            std::cout << "结果:";
            printPoly_SqList(Ans);
        }
        //基于顺序表的多项式求导
        void task5()
        {
            std::cout << std::endl << "以下是多项式求导(顺序表)演示:" << std::endl;
            std::cout << "请输入多项式项数:";
            int d;
            std::cin >> d;
            SqList<PolyNode<T> > L;
            inputPoly_SqList(L, d);

            std::cout << "请输入求导次数(>=1): ";
            int times = 0;
            std::cin >> times;

            polyDeri_SqList(L, times);
            std::cout << "结果:";
            printPoly_SqList(L);
        }
        //基于链表的一元多项式运算
        void task6()
        {
            std::cout << std::endl << "以下是一元多项式运算(链表)演示:" << std::endl;
            
            std::cout << "请输入第一个多项式项数:";
            int d1;
            std::cin >> d1;
            LinkedList<PolyNode<T> > LA;
            inputPoly_LinkedList(LA, d1);
            
            std::cout << "请输入第二个多项式项数:";
            int d2;
            std::cin >> d2;
            LinkedList<PolyNode<T> > LB;
            inputPoly_LinkedList(LB, d2);
            
            std::cout << "请输入运算符(+/-):";
            char op = 0;
            std::cin >> op;
            while(op != '+' && op != '-')
            {
                std::cout << "运算符不合法! 请重新输入运算符(+/-):";
                std::cin >> op;
            }
            LinkedList<PolyNode<T> > Ans;
            polyCal_LinkedList(LA, LB, Ans, op);
            std::cout << "结果:";
            printPoly_LinkedList(Ans);
        }
        //基于链表的多项式乘法
        void task7()
        {
            std::cout << std::endl << "以下是多项式乘法(链表)演示:" << std::endl;
            std::cout << "请输入第一个多项式项数:";
            int d1;
            std::cin >> d1;
            LinkedList<PolyNode<T> > LA;
            inputPoly_LinkedList(LA, d1);
            
            std::cout << "请输入第二个多项式项数:";
            int d2;
            std::cin >> d2;
            LinkedList<PolyNode<T> > LB;
            inputPoly_LinkedList(LB, d2);

            LinkedList<PolyNode<T> > Ans;
            polyMult_LinkedList(LA, LB, Ans);
            std::cout << "结果:";
            printPoly_LinkedList(Ans);
        }
        //基于链表的多项式求导
        void task8()
        {
            std::cout << std::endl << "以下是多项式求导(链表)演示:" << std::endl;
            std::cout << "请输入多项式项数:";
            int d;
            std::cin >> d;
            LinkedList<PolyNode<T> > L;
            inputPoly_LinkedList(L, d);

            std::cout << "请输入求导次数(>=1): ";
            int times = 0;
            std::cin >> times;

            polyDeri_LinkedList(L, times);
            std::cout << "结果:";
            printPoly_LinkedList(L);
        }

    private:
        //以下主要函数
        //多项式加减——顺序表实现
        void polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > &Ans, char op);
        //多项式乘法——顺序表实现
        void polyMult_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > & Ans);
        //多项式求导times阶——顺序表实现
        void polyDeri_SqList(SqList<PolyNode<T> > & Ans, int times);

        //多项式加减——链表实现
        void polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans, char op);
        //多项式乘法——链表实现
        void polyMult_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans);
        //多项式求导times阶——链表实现
        void polyDeri_LinkedList(LinkedList<PolyNode<T> > & Ans, int times);

        //多项式输入num项
        void inputPoly_SqList(SqList<PolyNode<T> > & dest, int num);
        void inputPoly_LinkedList(LinkedList<PolyNode<T> > & dest, int num);
        //打印多项式(两种数据结构)
        void printPoly_SqList(SqList<PolyNode<T> > & Ans);
        void printPoly_LinkedList(LinkedList<PolyNode<T> > & Ans);

        //以下辅助函数
        //多项式加减(顺序表实现, 运算结果放入A中, 即 A +=/-= B), 辅助多项式乘法
        void polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, char op);
        //节点乘多项式(顺序表实现), 辅助多项式乘法
        void nodeMultPoly_SqList(PolyNode<T> & node, SqList<PolyNode<T> > & poly, SqList<PolyNode<T> > & dest);

        //多项式加减(链表实现, 运算结果放入A中, 即 A +=/-= B), 辅助多项式乘法
        void polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, char op);
        //节点乘多项式(链表实现), 辅助多项式乘法
        void nodeMultPoly_LinkedList(PolyNode<T> & node, LinkedList<PolyNode<T> > & poly, LinkedList<PolyNode<T> > & dest);
};

template <typename T>
void PolyCalculator<T>::polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > &Ans, char op)
{
    Ans.clear();
    //获取长度
    int La = A.length();
    int Lb = B.length();

    //下标从1开始遍历
    //count计数总项数
    int i = 1, j = 1, count = 1;
    //公共部分
    while(i <= La && j <= Lb)
    {
        //比较次数, 大的放到Ans里面
        PolyNode<T> nodeA, nodeB;
        A.getElem(i, nodeA);
        B.getElem(j, nodeB);
        if(nodeA.exp > nodeB.exp)
        {
            Ans.insertElem(count, nodeA);
            count++;
            i++;
        }
        else if(nodeA.exp < nodeB.exp)
        {
            //减的情况
            if(op == '-')
            {
                Ans.insertElem(count, -nodeB);
            }
            else
            {
                Ans.insertElem(count, nodeB);
            }
            count++;
            j++;
        }
        //次数相同进行运算
        else
        {
            if(op == '+')
            {
                Ans.insertElem(count, nodeA + nodeB);
            }
            else //if(op == '-')
            {
                Ans.insertElem(count, nodeA - nodeB);
            }
            count++;
            i++;
            j++;
        }
    }
    //剩余部分
    while(i <= La)
    {
        PolyNode<T> nodeA;
        A.getElem(i, nodeA);
        Ans.insertElem(count, nodeA);
        count++;
        i++;
    }
    while(j <= Lb)
    {
        PolyNode<T> nodeB;
        B.getElem(j, nodeB);

        if(op == '-')
        {
            Ans.insertElem(count, -nodeB);
        }
        else
        {
            Ans.insertElem(count, nodeB);
        }
        count++;
        j++;
    }
}

template <typename T>
void PolyCalculator<T>::polyMult_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > &Ans)
{
    Ans.clear();
    int L = A.length();

    //中间结果
    SqList<PolyNode<T> > midRes;
    for(int i = 1; i <= L; i++)
    {
        PolyNode<T> node;
        A.getElem(i, node);
        nodeMultPoly_SqList(node, B, midRes);
        polyCal_SqList(Ans, midRes, '+');
    }
}

template <typename T>
void PolyCalculator<T>::polyDeri_SqList(SqList<PolyNode<T> > & Ans, int times)
{
    //小于1次不操作
    if(times <= 0)
    {
        return;
    }
    else if(times == 1)
    {
        int L = Ans.length();
        for(int i = 1; i <= L; i++)
        {
            PolyNode<T> node;
            Ans.getElem(i, node);
            node.deri();
            Ans.putElem(i, node);
        }
    }
    else
    {
        for(int i = 1; i <= times; i++)
        {
            PolyCalculator<T>::polyDeri_SqList(Ans, 1);
        }
    }

}

template <typename T>
void PolyCalculator<T>::polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans, char op)
{
    //从头遍历
    A.resetCursor();
    B.resetCursor();
    LinkedListNode<PolyNode<T> > * p = A.pCursor -> next;
    LinkedListNode<PolyNode<T> > * q = B.pCursor -> next;
    //公共部分
    while(p && q)
    {
        //比较次数, 大的放到Ans里面
        if(p -> data.exp > q -> data.exp)
        {
            Ans.insertTail(p -> data);
            p = p -> next;
        }
        else if(p -> data.exp < q -> data.exp)
        {
            if(op == '-')
            {
                Ans.insertTail(-(q -> data));
            }
            else
            {
                Ans.insertTail(q -> data);
            }
            q = q -> next;
        }
        //次数相同进行运算
        else
        {
            if(op == '+')
            {
                Ans.insertTail(p -> data + q -> data);
            }
            else //if(op == '-')
            {
                Ans.insertTail(p -> data - q -> data);
            }
            p = p -> next;
            q = q -> next;
        }
    }
    //剩余部分
    while(p)
    {
        Ans.insertTail(p -> data);
        p = p -> next;
    }
    while(q)
    {
        if(op == '-')
        {
            Ans.insertTail(-(q -> data)); 
        }
        else
        {
            Ans.insertTail(q -> data);
        }
        q = q -> next;
    }
}

template <typename T>
void PolyCalculator<T>::polyMult_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans)
{
    A.resetCursor();
    B.resetCursor();

    LinkedListNode<PolyNode<T> > * p = A.pCursor -> next;

    //中间结果
    LinkedList<PolyNode<T> > midRes;
    while(p)
    {
        nodeMultPoly_LinkedList(p -> data, B, midRes);
        polyCal_LinkedList(Ans, midRes, '+');
        p = p -> next;
    }
}

template <typename T>
void PolyCalculator<T>::polyDeri_LinkedList(LinkedList<PolyNode<T> > & Ans, int times)
{
    //小于1次求导不操作
    if(times <= 0)
    {
        return;
    }
    //主要部分——求一次导数:每个节点求导即可
    else if(times == 1)
    {
        Ans.resetCursor();
        LinkedListNode<PolyNode<T> > * p = Ans.pCursor -> next;

        while(p)
        {
            p -> data.deri();
            p = p -> next;
        }
    }
    //其他情况不断调用一次求导即可
    else
    {
        for(int i = 1; i <= times; i++)
        {
            PolyCalculator<T>::polyDeri_LinkedList(Ans, 1);
        }
    }
}


template <typename T>
void PolyCalculator<T>::inputPoly_SqList(SqList<PolyNode<T> > & dest, int num)
{
    std::cout << "请按次数降序输入多项式, 两个数字为一项, 前者为系数, 后者为次数(0也要写):" << std::endl;
    std::cout << "例: 3x^2+2x+1 => 3 2 2 1 1 0" << std::endl;
    for(int i = 1; i <= num; i++)
    {
        T _coef;
        unsigned int _exp;
        std::cin >> _coef >> _exp;
        dest.insertElem(i, PolyNode<T>(_coef, _exp));
    }
    std::cout << "你输入的多项式为:";
    printPoly_SqList(dest);
}

template <typename T>
void PolyCalculator<T>::inputPoly_LinkedList(LinkedList<PolyNode<T> > & dest, int num)
{
    std::cout << "请按次数降序输入多项式, 两个数字为一项, 前者为系数, 后者为次数(0也要写):" << std::endl;
    std::cout << "例: 3x^2+2x+1 => 3 2 2 1 1 0" << std::endl;
    for(int i = 1; i <= num; i++)
    {
        T _coef;
        unsigned int _exp;
        std::cin >> _coef >> _exp;
        dest.insertTail(PolyNode<T>(_coef, _exp));
    }
    std::cout << "你输入的多项式为:";
    printPoly_LinkedList(dest);
}

template <typename T>
void PolyCalculator<T>::printPoly_SqList(SqList<PolyNode<T> > & Ans)
{
    //是否为0多项式
    bool isZeroPoly = true;


    int L = Ans.length();
    PolyNode<T> nodeA;
    Ans.getElem(1, nodeA);
    //第一项为0, 直接输出0
    if(nodeA.coef == 0 && nodeA.exp == 0)
    {
        std::cout << "0" << std::endl;
        return;
    }
    //用来控制第一位前的符号
    bool firstTerm = true;
    for(int i = 1; i <= L; i++)
    {
        Ans.getElem(i, nodeA);
        if(nodeA.coef > 0)
        {
            if(!firstTerm)
            {
                std::cout << "+" << nodeA;
            }
            //第一项前的'+'忽略
            else
            {
                std::cout << nodeA;
            }
            isZeroPoly = false;
            firstTerm = false;
        }
        else if(nodeA.coef != 0)
        {
            std::cout << nodeA;
            isZeroPoly = false;
            firstTerm = false;
        }
    }
    if(isZeroPoly)
    {
        std::cout << "0";
    }
    std::cout << std::endl;
}

template <typename T>
void PolyCalculator<T>::printPoly_LinkedList(LinkedList<PolyNode<T> > & Ans)
{
    bool isZeroPoly = true;
    Ans.resetCursor();
    LinkedListNode<PolyNode<T> > * p = Ans.pCursor -> next;

    //第一项为0, 直接输出0
    if(p -> data.coef == 0 && p -> data.exp == 0)
    {
        std::cout << "0" << std::endl;
        return;
    }
    //用来控制第一位前的符号
    bool firstTerm = true;
    while(p)
    {
        if(p -> data.coef > 0)
        {
            if(!firstTerm)
            {
                std::cout << "+" << p -> data;
            }
            //第一项前的'+'忽略
            else
            {
                std::cout << p -> data;
            }
            isZeroPoly = false;
            firstTerm = false;
        }
        else if(p -> data.coef != 0)
        {
            std::cout << p -> data;
            isZeroPoly = false;
            firstTerm = false;
        }
        p = p -> next;
    }
    if(isZeroPoly)
    {
        std::cout << "0";
    }
    std::cout << std::endl;
}

template <typename T>
void PolyCalculator<T>::polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, char op)
{
    int i = 1, j = 1;
    PolyNode<T> nodeA, nodeB;

    //公共部分
    while(i <= A.length() && j <= B.length())
    {
        A.getElem(i, nodeA);
        B.getElem(j, nodeB);
        //次数相同, 直接运算
        if(nodeA.exp == nodeB.exp)
        {
            if(op == '+')
            {
                nodeA += nodeB;
                A.putElem(i, nodeA);
            }
            else //if(op == '-)
            {
                nodeA -= nodeB;
                A.putElem(i, nodeA);
            }
            i++;
            j++;
        }
        //次数不同
        //A < B, q 插到 A
        else if(nodeA.exp < nodeB.exp)
        {
            A.insertElem(i, nodeB);
            i++;
            j++;
        }
        //A > B
        else
        {
            i++;
        }
    }
    //剩余部分
    while(j <= B.length())
    {
        B.getElem(j, nodeB);
        A.insertElem(A.length() + 1, nodeB);
        j++;
    }
}

template <typename T>
void PolyCalculator<T>::nodeMultPoly_SqList(PolyNode<T> & node, SqList<PolyNode<T> > & poly, SqList<PolyNode<T> > & dest)
{
    dest.clear();
    int L = poly.length();

    PolyNode<T> tmpNode;
    for(int i = 1; i <= L; i++)
    {
        poly.getElem(i, tmpNode);
        tmpNode *= node;
        dest.insertElem(i, tmpNode);
    }
}

template <typename T>
void PolyCalculator<T>::polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, char op)
{
    A.resetCursor();
    B.resetCursor();
    
    LinkedListNode<PolyNode<T> > * p = A.pCursor;
    LinkedListNode<PolyNode<T> > * q = B.pCursor;

    //公共部分
    while(p -> next && q -> next)
    {
        //次数相同, 直接运算
        if(p -> next -> data.exp == q -> next -> data.exp)
        {
            if(op == '+')
            {
                p -> next -> data += q -> next -> data;
            }
            else //if(op == '-)
            {
                p -> next -> data -= q -> next -> data;
            }
            p = p -> next;
            q = q -> next;
        }
        //次数不同
        //A < B, q 插到 A
        else if(p -> next -> data.exp < q -> next -> data.exp)
        {
            A.insertAfter(q -> next -> data);
            p = p -> next;
            q = q -> next;
        }
        //A > B
        else
        {
            p = p -> next;
        }
        
        A.pCursor = p;
    }
    //剩余部分
    while(q -> next)
    {
        A.insertAfter(q -> next -> data);
        p = p -> next;
        q = q -> next;
        A.pCursor = p;
    }
}

template <typename T>
void PolyCalculator<T>::nodeMultPoly_LinkedList(PolyNode<T> & node, LinkedList<PolyNode<T> > & poly, LinkedList<PolyNode<T> > & dest)
{
    poly.resetCursor();
    dest.clear();

    LinkedListNode<PolyNode<T> > * p = poly.pCursor -> next;
    while(p)
    {
        dest.insertTail(node * (p -> data));
        p = p -> next;
    }
}
#endif