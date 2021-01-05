#ifndef CALCULATOR
#define CALCULATOR

#include "sqlist.h"
#include "linkedlist.h"

template <typename T>
class Calculator
{
    public:
        Calculator(){};
        void printLogo();
        void printUsage();
    private:
    //————————————————————————必做———————————————————————————
        //顺序表测试
        void SqList_Test();
        //链表测试
        void LinkedList_Test();
        //向量加减法——顺序表实现
        void vectorCal_SqList(SqList<T> &A, SqList<T> &B, SqList<T> & Ans, char op);
        //多项式加减——顺序表实现
        void polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > &Ans, char op);
        //多项式加减——链表实现
        void polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans, char op);

    //————————————————————————选做———————————————————————————
        //向量夹角余弦值——顺序表实现
        double vectorAngCos_SqList(SqList<T> &A, SqList<T> &B);
        //多项式乘法——链表实现
        void polyMult_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans);
        //多项式求导times阶——链表实现
        void polyDeri_LinkedList(LinkedList<PolyNode<T> > & Ans, int times);

    //———————————————————————辅助函数————————————————————————
        //多项式加减(链表实现, 运算结果放入A中, 即 A +=/-= B), 辅助多项式乘法
        void polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, char op);
        //节点乘多项式(链表实现), 辅助多项式乘法
        void nodeMultPoly_LinkedList(PolyNode<T> & node, LinkedList<PolyNode<T> > & poly, LinkedList<PolyNode<T> > & dest);
        //向量输入num项
        void inputVec_SqList(SqList<T> & dest, int num);
        //void inputVec_LinkedList(LinkedList<T> & dest, int num);
        //多项式输入num项
        void inputPoly_SqList(SqList<PolyNode<T> > & dest, int num);
        void inputPoly_LinkedList(LinkedList<PolyNode<T> > & dest, int num);
        //打印多项式(两种数据结构)
        void printPoly_SqList(SqList<PolyNode<T> > & Ans);
        void printPoly_LinkedList(LinkedList<PolyNode<T> > & Ans);
};

template <typename T>
void Calculator<T>::printLogo()
{
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "|          Simple Calculator         |" << std::endl;
    std::cout << "|                                    |" << std::endl;
    std::cout << "|    Written by G.Cui, 2019.10.12    |" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

template <typename T>
void Calculator<T>::printUsage()
{
    while(1)
    {
        std::cout << std::endl;
        std::cout << "请选择功能模块:\n1. 顺序表演示;\n2. 链表演示;\n";
        std::cout << "3. 向量运算(顺序表);\n4. 一元多项式运算(顺序表);\n";
        std::cout << "5. 一元多项式运算(链表);\n6. 向量夹角余弦值(顺序表);\n";
        std::cout << "7. 多项式乘法(链表);\n8. 多项式导数(链表)." << std::endl;
        std::cout << "请输入需要的模块的数字(0退出): " << std::endl;
        int fn;
        std::cin >> fn;

        //退出
        if(fn == 0)
        {
            return;
        }
        //顺序表演示
        else if(fn == 1)
        {
            std::cout << std::endl << "以下是顺序表演示:" << std::endl;
            SqList_Test();
        }
        //链表演示
        else if(fn == 2)
        { 
            std::cout << std::endl << "以下是链表演示:" << std::endl;
            LinkedList_Test();
        }
        //基于顺序表的向量运算
        else if (fn == 3)
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
        //基于顺序表的一元多项式运算
        else if(fn == 4)
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
        //基于链表的一元多项式运算
        else if(fn == 5)
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
        //向量夹角余弦值(顺序表)
        else if(fn == 6)
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
        //基于链表的多项式乘法
        else if(fn == 7)
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
        else if(fn == 8)
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
        else
        {
            std::cout << "不合法输入." << std::endl; 
        }
    }
};
template <typename T>
void Calculator<T>::SqList_Test()
{
    //创建顺序表
    SqList<T> L(10);
    //判空
    std::cout << "Is list empty? " << L.isEmpty() << std::endl;
    //插入一些数字
    for(int i = 1; i <= 10; i++)
    {
        L.insertElem(i, i);
    }
    std::cout << "After inserted...";
    std::cout << "List has " << L.length() << " elements. ";
    L.print();

    std::function<bool(T)> visit = _GreaterThanZero<T>;
    //遍历判断是否大于0
    std::cout << "Is every element greater than 0? " << L.traverse(visit) << std::endl;

    std::function<bool(T, T)> cmp = _EqualCmp<T>;
    //查找
    std::cout << "Element 5 is at " << L.locateElem(5, cmp) << "." << std::endl;
    //头插
    std::cout << "Insert at begin... ";
    L.insertElem(1, 7);
    L.print();
    //中间插入
    std::cout << "Insert at middle... ";
    L.insertElem(5, 6);
    L.print();
    //尾插
    std::cout << "Insert at end... ";
    L.insertElem(L.length() + 1, 0);
    L.print();

    //随机存取
    int e = 66;
    std::cout << "Now e is " << e << "." << std::endl;
    L.putElem(11, e);
    std::cout << "After PutElem... ";
    L.print();
    L.putElem(11, 9);
    std::cout << "Cancel... ";
    L.print();
    L.getElem(7, e);
    std::cout << "After L.getElem(7, e), now e is " << e << "." << std::endl;

    //尾删
    std::cout << "Delete at end... ";
    L.deleteElem(L.length(), e);
    L.print();
    //中间删除
    std::cout << "Delete at middle... ";
    L.deleteElem(5, e);
    L.print();
    //头删
    std::cout << "Delete at begin... ";
    L.deleteElem(1, e);
    L.print();

    //前后元素
    L.priorElem(2, e);
    std::cout << "Before 2 is " << e << "." << std::endl;
    L.nextElem(2, e);
    std::cout << "After 2 is " << e << "." << std::endl;
}

template <typename T>
void Calculator<T>::LinkedList_Test()
{
    LinkedList<T> L;

    //判空
    std::cout << "Is list empty? " << L.isEmpty() << std::endl;
    //插入一些数字
    for(int i = 1; i <= 10; i++)
    {
        L.insertTail(i);
    }
    std::cout << "After inserted...";
    std::cout << "List has " << L.getLength() << " elements. ";
    L.print();

    std::function<bool(T)> visit = _GreaterThanZero<T>;
    //遍历判断是否大于0
    std::cout << "Is every element greater than 0? " << L.traverse(visit) << std::endl;
    
    std::function<bool(T, T)> cmp = _EqualCmp<T>;
    //查找
    std::cout << "Element 5 is at " << L.locateElem(5, cmp) << "." << std::endl;
    //头插
    std::cout << "Insert at begin... ";
    L.insertHead(7);
    L.print();
    //中间插入
    std::cout << "Insert at middle... ";
    for(int i = 0; i < 5; i++)
    {
        L.pCursor = L.pCursor -> next;
    }
    L.insertAfter(6);
    L.print();
    //尾插
    std::cout << "Insert at end... ";
    L.insertTail(0);
    L.print();

    //尾删
    std::cout << "Delete at end... ";
    delete L.deleteTail();
    L.print();
    //中间删除
    std::cout << "Delete at middle... ";
    delete L.deleteAfter();
    L.print();
    //头删
    std::cout << "Delete at begin... ";
    delete L.deleteHead();
    L.print();
    
    L.resetCursor();
}


template <typename T>
void Calculator<T>::vectorCal_SqList(SqList<T> & A, SqList<T> & B, SqList<T> & Ans, char op)
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
void Calculator<T>::polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > &Ans, char op)
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
void Calculator<T>::polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans, char op)
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
double Calculator<T>::vectorAngCos_SqList(SqList<T> &A, SqList<T> &B)
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
void Calculator<T>::polyMult_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans)
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
        //midRes.clear();
    }
}

template <typename T>
void Calculator<T>::polyDeri_LinkedList(LinkedList<PolyNode<T> > & Ans, int times)
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
            Calculator<T>::polyDeri_LinkedList(Ans, 1);
        }
    }
}

template <typename T>
void Calculator<T>::inputVec_SqList(SqList<T> & dest, int num)
{
    for(int i = 1; i <= num; i++)
    {
        T tmp;
        std::cin >> tmp;
        dest.insertElem(i, tmp);
    }
}

template <typename T>
void Calculator<T>::inputPoly_SqList(SqList<PolyNode<T> > & dest, int num)
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
void Calculator<T>::inputPoly_LinkedList(LinkedList<PolyNode<T> > & dest, int num)
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
void Calculator<T>::polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, char op)
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
void Calculator<T>::nodeMultPoly_LinkedList(PolyNode<T> & node, LinkedList<PolyNode<T> > & poly, LinkedList<PolyNode<T> > & dest)
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

template <typename T>
void Calculator<T>::printPoly_SqList(SqList<PolyNode<T> > & Ans)
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
void Calculator<T>::printPoly_LinkedList(LinkedList<PolyNode<T> > & Ans)
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

#endif