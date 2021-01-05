#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "sqlist.h"
#include "linkedlist.h"
#include "stack.h"
#include "unary_function.h"
#include "myexception.h"

#include <utility>
#include <map>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>

//函数表 <函数名, 一元函数对象>
typedef std::map<std::string, UnaryFunction> funcTable;
//符号表 <符号字面量, 值>
typedef std::map<std::string, double> SymbolTable;

//解析器状态
typedef enum _TOKENIZE_STATE
{
    INIT,
    INT,
    FLOAT,
    IDENTIFIER,
    OPERATOR,
    ERROR
}TOKENIZE_STATE;

//判断是否是空白字符组成的字符串
bool isWSStr(char * str)
{
    bool flag = true;
    char * p = str;
    while(*p != '\0')
    {
        //有非空字符
        if(*p != ' ' && *p != '\t')
        {
            flag = false;
            break;
        }
        p++;
    }
    return flag;
}

//是否是一个操作符
bool isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^');
}

//是否紧挨括号, 且在括号内
bool isNextInPar(char * now, const char * strHead)
{
    char * pCursor = now;
    //找到之前的第一个非空格字符
    while(pCursor > strHead)
    {
        pCursor--;
        if(*pCursor != ' ' && *pCursor != '\t')
        {
            break;
        }
        else if(pCursor == strHead)
        {
            return true;
        }
    }
    return (*pCursor == '(');
}

//是否是正号
bool isPos(char * now, const char * strHead)
{
	//根本不是+号
	if(*now != '+')
	{
		return false;
	}
	//第一个字符 前一个字符是(
	else if(now == strHead || isNextInPar(now, strHead))
	{
		if(*(now + 1) != '\0')
		{
			return std::isdigit(*(now + 1));
		}	
	}
	return false;
}

//是否是负号
bool isNeg(char * now, const char * strHead)
{
	//根本不是-号
	if(*now != '-')
	{
		return false;
	}
	//第一个字符 前一个字符是(
	else if(now == strHead || isNextInPar(now, strHead))
	{
		//之后是数字
		if(*(now + 1) != '\0')
		{
			return std::isdigit(*(now + 1));
		}	
	}
	return false;
}

//返回优先度之差
int deltaPrior(char a, char b)
{
    std::map<char, int> pr;
    pr['+'] = 0;
    pr['-'] = 0;
    pr['*'] = 1;
    pr['/'] = 2;
    pr['^'] = 3;
    pr['('] = 4;
    pr[')'] = 4;

    //两个幂运算, 后者优先级高
    if(a == '^' && b == '^')
    {
        return -1;
    }
    return pr[a] - pr[b];
}

//运算
//输出a op b 结果
//注意弹栈顺序
double cal(double a, char op, double b)
{
    if(op == '+')
    {
        return a + b;
    }
    else if(op == '-')
    {
        return a - b;
    }
    else if(op == '*')
    {
        return a * b;
    }
    else if(op == '/')
    {
        return double(a) / b;
    }
    else if(op == '^')
    {
        return std::pow(a, b);
    }
    return INFINITY;
}

template <typename T>
class Calculator
{
    public:
        Calculator(){};
        void printLogo();
        void printUsage();
    private:
    //————————————————————————必做———————————————————————————

    //———————————————————————顺序表——————————————————————————
        //向量加减法——顺序表实现
        void vectorCal_SqList(SqList<T> &A, SqList<T> &B, SqList<T> & Ans, char op);
        //向量夹角余弦值——顺序表实现
        double vectorAngCos_SqList(SqList<T> &A, SqList<T> &B);
        //多项式加减——顺序表实现
        void polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > &Ans, char op);
        //多项式乘法——顺序表实现
        void polyMult_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > & Ans);
        //多项式求导times阶——顺序表实现
        void polyDeri_SqList(SqList<PolyNode<T> > & Ans, int times);

    //————————————————————————链表——————————————————————————
        //多项式加减——链表实现
        void polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans, char op);
        //多项式乘法——链表实现
        void polyMult_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, LinkedList<PolyNode<T> > & Ans);
        //多项式求导times阶——链表实现
        void polyDeri_LinkedList(LinkedList<PolyNode<T> > & Ans, int times);

    //—————————————————————————栈———————————————————————————
        //表达式求值——链栈实现
        double calcExpr(std::string & expr, SymbolTable & sTable);
        //函数编程器
        void funcProg();

    //———————————————————————辅助函数————————————————————————
        //向量输入num项
        void inputVec_SqList(SqList<T> & dest, int num);
        //void inputVec_LinkedList(LinkedList<T> & dest, int num);
        //多项式输入num项
        void inputPoly_SqList(SqList<PolyNode<T> > & dest, int num);
        void inputPoly_LinkedList(LinkedList<PolyNode<T> > & dest, int num);
        //打印多项式(两种数据结构)
        void printPoly_SqList(SqList<PolyNode<T> > & Ans);
        void printPoly_LinkedList(LinkedList<PolyNode<T> > & Ans);

        //多项式加减(顺序表实现, 运算结果放入A中, 即 A +=/-= B), 辅助多项式乘法
        void polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, char op);
        //节点乘多项式(顺序表实现), 辅助多项式乘法
        void nodeMultPoly_SqList(PolyNode<T> & node, SqList<PolyNode<T> > & poly, SqList<PolyNode<T> > & dest);

        //多项式加减(链表实现, 运算结果放入A中, 即 A +=/-= B), 辅助多项式乘法
        void polyCal_LinkedList(LinkedList<PolyNode<T> > &A, LinkedList<PolyNode<T> > &B, char op);
        //节点乘多项式(链表实现), 辅助多项式乘法
        void nodeMultPoly_LinkedList(PolyNode<T> & node, LinkedList<PolyNode<T> > & poly, LinkedList<PolyNode<T> > & dest);

        //获取下一个分词结果
        TOKENIZE_STATE getNextToken(char * str, const char * strHead, char * oprDest, char * opDest, int & len);

        //处理函数定义字符串, 保存到函数表里
        bool parseSaveFunc(std::string & str, funcTable & dest);
        //处理函数运行字符串, 从保存的函数表取得表达式
        bool parseRunFunc(std::string & str, funcTable & src);

};

template <typename T>
void Calculator<T>::printLogo()
{
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "|          Simple Calculator         |" << std::endl;
    std::cout << "|                                    |" << std::endl;
    std::cout << "|    Written by G.Cui, 2019.10.22    |" << std::endl;
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
        std::cout << "9. 四则运算表达式求值; \n10. 多变量表达式求值;\n";
        std::cout << "11. 简单函数." << std::endl;
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
        else if(fn == 2)
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
        //基于顺序表的一元多项式运算
        else if(fn == 3)
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
        else if(fn == 4)
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
        else if(fn == 5)
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
        else if(fn == 6)
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
        //表达式求值(9 && 10)
        else if(fn == 9 || fn == 10)
        {

            std::cout << std::endl << "以下是四则运算表达式/多变量表达式求值演示:" << std::endl;
            std::cout << "请输入表达式:";
            std::string inputExpr;
            //注意, 流里面有换行符, 先忽略掉
            std::cin.ignore();
            std::getline(std::cin, inputExpr);

            //符号表
            SymbolTable sTable;
            //try-catch
            try
            {
                double res = calcExpr(inputExpr, sTable);
                std::cout << "结果:" << res << std::endl;
            }
            //分词器错误
            catch(const TokenizerException & e)
            {
                std::cout << "发生分词时期错误:" << e.what() << "请检查输入是否正确!" << std::endl;
                std::cout << "处理停止!" << std::endl;
            }
            //执行器错误
            catch(const ExecException & e)
            {
                std::cout << "发生执行时期错误:" << e.what() << "请检查输入是否正确!" << std::endl;
                std::cout << "处理停止!" << std::endl;
            }
            /*
            catch(CalculatorException & e)
            {
                std::cout << e.what() << std::endl;
                std::cout << "处理停止!" << std::endl;
            }
            */
        }
        //简单函数编程器(11)
        else if(fn == 11)
        {
            std::cout << std::endl << "以下是简单函数编程演示:" << std::endl;
            std::cout << "请输入命令(DEF定义函数, RUN求值, QUIT退出):" << std::endl;
            //简单函数编程器
            funcProg();
        }
        else
        {
            std::cout << "不合法输入." << std::endl; 
        }
    }
};

//———————————————————————顺序表——————————————————————————
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
void Calculator<T>::polyMult_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, SqList<PolyNode<T> > &Ans)
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
void Calculator<T>::polyDeri_SqList(SqList<PolyNode<T> > & Ans, int times)
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
            Calculator<T>::polyDeri_SqList(Ans, 1);
        }
    }

}

//————————————————————————链表——————————————————————————
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

//—————————————————————————栈———————————————————————————
template <typename T>
double Calculator<T>::calcExpr(std::string & expr, SymbolTable & sTable)
{
    //操作数栈
    ListStack<double> operandStack;
    //操作符栈
    ListStack<char> opStack;

    if(expr == "")
    {
        NullExpr e;
        throw e;
    }
    //待处理字符串
    char * strExpr = new char[std::strlen(expr.c_str()) + 1];
    std::strcpy(strExpr, expr.c_str());
    	
    //指针置于字符串开头
	char * pCursor = strExpr;

    //分离出来的操作数
    char * token = new char[std::strlen(expr.c_str()) + 1];
    //操作符
	char op;
    //操作数长度
	int len;
    //分词状态
    TOKENIZE_STATE state;

    //循环直到字符串尾为止
	while(*pCursor != '\0' && pCursor)
	{
        //略过空白
		while(*pCursor == ' ' || *pCursor == '\t')
		{
			pCursor++;
		}

        //分词 —— 如果捕获异常立即再次抛出
        try
        {
		    state = getNextToken(pCursor, strExpr, token, &op, len);
        }
        catch(const TokenizerException &e)
        {
            delete[] strExpr;
	        delete[] token;
            throw;
        }

        //数值入栈
        if(state == INT || state == FLOAT)
        {
            operandStack.push(std::stod(token));
        }
        else if(state == IDENTIFIER)
        {
            //先查表
            SymbolTable::iterator i = sTable.find(token);
            //表中不存在
            if(i == sTable.end())
            {
                std::cout << "请输入标识符" << token << "的值:";
                double valIdentifier;
                std::cin >> valIdentifier;
                sTable.insert(std::pair<std::string, double>(token, valIdentifier));
                operandStack.push(valIdentifier);
            }
            //表中存在, 直接替换值
            else
            {
                operandStack.push(i -> second);
            }
        }
        else if(state == OPERATOR)
        {
            //是右括号
            if(op == ')')
            {
                //运算直到左括号为止, 注意抛出异常
                //两个操作数
                double opr1, opr2;
                //一个操作符
                char c = '\0';

                while(c != '(')
                {
                    //弹出一个操作符 若此时栈空, 说明括号不匹配
                    try
                    {
                        c = opStack.top();
                        opStack.pop();
                    }
                    catch(TopEmptyStack &e)
                    {
                        UnmatchPar u;
                        throw u;
                    }
                    
                    //如果弹出的是括号, 说明直接去掉括号了
                    //(-1.2) -> operandStack : -1.2; opStack : (
                    if(c != '(')
                    {
                        try
                        {
                            opr1 = operandStack.top();
                            operandStack.pop();
                            opr2 = operandStack.top();
                            operandStack.pop();
                            double val = cal(opr2, c, opr1);
                            operandStack.push(val);
                        }
                        //有任何异常, 说明操作数不够
                        catch(...)
                        {
                            LackOperand e;
                            throw e;
                        }
                    }
                }

            }
            //操作符栈空或者操作符是左括号
            else if(opStack.isEmpty() || op == '(')
            {
                opStack.push(op);
            }
            //或者其他运算符紧压着(
            else if(opStack.top() == '(')
            {
                opStack.push(op);
            }
            else
            {
                //比较栈顶运算符(此时栈一定不空)
                char c = opStack.top();
                int delta = deltaPrior(c, op);
                //栈顶优先级高
                while(delta >= 0 && !opStack.isEmpty() && c != '(')
                {
                    double opr1, opr2;
                    opStack.pop();
                    try
                    {
                        opr1 = operandStack.top();
                        operandStack.pop();
                        opr2 = operandStack.top();
                        operandStack.pop();
                    }
                    //有任何异常, 说明操作数不够
                    catch(...)
                    {
                        LackOperand e;
                        throw e;
                    }
                    double val = cal(opr2, c, opr1);
                    operandStack.push(val);

                    //2*3+1 -> operandStack: 2 3; opStack: *; op: +
                    //-> operandStack: 6; opStack: ; op: +
                    if(!opStack.isEmpty())
                    {
                        c = opStack.top();
                        delta = deltaPrior(c, op);
                    }
                }
                //
                //if(delta < 0 || opStack.isEmpty())
                {
                    opStack.push(op);
                }
            }
        }
        //跳过分离的词
		pCursor += len;
	}

    //表达式处理完毕, 做剩余工作
    while(!opStack.isEmpty())
    {
        char c = opStack.top();
        if(c == '(')
        {
            UnmatchPar e;
            throw e;
        }
        opStack.pop();
        double opr1, opr2;
        try
        {
            opr1 = operandStack.top();
            operandStack.pop();
            opr2 = operandStack.top();
            operandStack.pop();
        }
        //缺少操作数
        catch(...)
        {
            LackOperand e;
            throw e;
        }
        
        double val = cal(opr2, c, opr1);
        operandStack.push(val);
    }

    //如果栈里没有值, 说明是空表达式
    //例子: ()
    double res;
    try
    {
        res = operandStack.top();
        operandStack.pop();
    }
    catch(TopEmptyStack & e)
    {
        NullExpr n;
        throw n;
    }

    //弹出结果后操作数栈非空, 说明操作数多了
    if(!operandStack.isEmpty())
    {
        delete[] strExpr;
	    delete[] token;
        MoreOperand e;
        throw e; 
    }

	delete[] strExpr;
	delete[] token;

    return res;
}

template <typename T>
void Calculator<T>::funcProg()
{
    //函数表 —— 存储定义的函数
    funcTable fTable;

    //指令
    std::string instr;
    std::cin >> instr;

    while(1)
    {
        if(instr == "DEF")
        {
            //函数定义字串
            std::string funcStr;
            std::cin >> funcStr;

            bool isOK = parseSaveFunc(funcStr, fTable);
            //解析失败 —— 字符串不合法
            if(!isOK)
            {
                std::cout << "不合法函数, 定义无效!" << std::endl;
            }
        }
        else if(instr == "RUN")
        {
            //运行指令字串
            std::string runStr;
            std::cin >> runStr;

            bool isOK = parseRunFunc(runStr, fTable);
            //运行失败 —— 字符串不合法/函数不存在
            if(!isOK)
            {
                std::cout << "函数不存在或语句有错!" << std::endl;
            }
        }
        else if(instr == "QUIT")
        {
            break;
        }
        else
        {
            std::cout << "非法指令!(DEF定义函数, RUN求值, QUIT退出)" << std::endl;
        }
        std::cin >> instr;
    }
}

//———————————————————————辅助函数————————————————————————
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

template <typename T>
void Calculator<T>::polyCal_SqList(SqList<PolyNode<T> > &A, SqList<PolyNode<T> > &B, char op)
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
void Calculator<T>::nodeMultPoly_SqList(PolyNode<T> & node, SqList<PolyNode<T> > & poly, SqList<PolyNode<T> > & dest)
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

//获取下一个Token 
//参数列表:
//str - 目前剩余字符串; strHead - 全字符串首, 用来判断正负号
//oprDest - 操作数/标识符字面值放置; opDest - 操作符放置地; len - Token长度

//注意: 状态机出错会抛出异常, 注意处理
template <typename T>
TOKENIZE_STATE Calculator<T>::getNextToken(char * str, const char * strHead, char * oprDest, char * opDest, int & len)
{
	//前后指针
	char * back = str;
	char * front = str;
	
	//初始状态
	TOKENIZE_STATE state = INIT;
	//分词结束的标志
	bool isFinished = false;
	
	//持续分词
	while(!isFinished && front)
	{
		switch(state)
		{
			//初始状态
			case INIT:
			{
				//字母、下划线 -> 标识符
				if(std::isalpha(*front) || (*front == '_'))
				{
					state = IDENTIFIER;
					front++;
				}
				//+ -(正负号) 数字 -> 整数值
				else if(isPos(front, strHead) || isNeg(front, strHead) || std::isdigit(*front))
				{
					state = INT;
					front++;
				}
				//. -> 浮点数
				else if(*front == '.')
				{
					state = FLOAT;
					front++;
				}
				// * / ( ) -> 操作符
				else if(isOperator(*front))
				{
					state = OPERATOR;
					front++;
				}
				//其他 -> 错误
				else // if(*front == '\0')
				{
					state = ERROR;
					isFinished = true;
                    //非法字符
					IllegalChar e;
                    throw e;
				}
				break;
			}
			//数值
			case INT:
			{
				//空格 + - * / ( ) -> 结束
				if(*front == ' ' || isOperator(*front) || !front || *front == '\0')
				{
					isFinished = true;
				}
				//数字 -> 整数值
				else if(std::isdigit(*front))
				{
					state = INT;
					front++;
				}
				//. -> 浮点数
				else if(*front == '.')
				{
					state = FLOAT;
					front++;
				}
				//字母、下划线 其他 -> 错误
				else
				{
					state = ERROR;
					isFinished = true;
                    IllegalNum e;
                    throw e;
				}
				break;
			}
			case FLOAT:
			{
				//空格 + - * / ( ) -> 结束
				if(*front == ' ' || isOperator(*front) || !front || *front == '\0')
				{
					isFinished = true;
				}
				//数字 -> 值
				else if(std::isdigit(*front))
				{
					state = FLOAT;
					front++;
				}
				else
				{
					state = ERROR;
					isFinished = true;
                    IllegalNum e;
                    throw e;
				}
				break;
			}
			case IDENTIFIER:
			{
				//空格 + - * / ( ) -> 结束
				if(*front == ' ' || isOperator(*front) || !front || *front == '\0')
				{
					isFinished = true;
				}
				//数字 字母 下划线
				else if(std::isalnum(*front) || *front == '_')
				{
					state = IDENTIFIER;
					front++;
				}
				else
				{
					state = ERROR;
					isFinished = true;
                    IllegalIdentifier e;
                    throw e;
				}
				break;
			}
			case OPERATOR:
			{
				//只考虑单字符运算符
				isFinished = true;
				break;
			}
			case ERROR:
			{
				isFinished = true;
				break;
			}
			default:
			{
				state = ERROR;
				isFinished = true;
				return state;
			}
		}
	}
	len = front - back;
	if(state == INT || state == FLOAT || state == IDENTIFIER)
	{
		std::strncpy(oprDest, str, len);
		oprDest[len] = '\0';
	}
	else if(state == OPERATOR)
	{
		*opDest = str[0];
	}
	return state;
}


//处理函数定义字符串, 保存到函数表里
template <typename T>
bool Calculator<T>::parseSaveFunc(std::string & str, funcTable & dest)
{
    //拷贝
    char * tmpStr = new char[ std::strlen(str.c_str()) + 1];
    std::strcpy(tmpStr, str.c_str());

    //函数名
    char * fName;
    //变量名
    char * varName;
    //表达式
    char * expr;
    //分词长度
    int tokenLen = 0;
    //分词后指针
    char * backCursor = tmpStr;

    //开始分词

    //分离函数名
    char * pCursor = std::strpbrk(backCursor, "(");
    if(!pCursor)
    {
        delete[] tmpStr;
        return false;
    }
    tokenLen = pCursor - backCursor;
    fName = new char[tokenLen + 1];
    std::strncpy(fName, backCursor, tokenLen);
    fName[tokenLen] = '\0';

    //跳过(
    pCursor++;
    //后指针向前
    backCursor = pCursor;

    //分离变量名
    pCursor = std::strpbrk(pCursor, ")");
    if(!pCursor)
    {
        delete[] tmpStr;
        delete[] fName;
        return false;
    }
    tokenLen = pCursor - backCursor;
    varName = new char[tokenLen + 1];
    std::strncpy(varName, backCursor, tokenLen);
    varName[tokenLen] = '\0';

    //检验变量名是否合法
    TOKENIZE_STATE state = INIT;
    char * pTmp = varName;
    char * pToken = new char [tokenLen + 1];
    char tmpOP;
    int tmpLen = 0;
    try
    {
        state = getNextToken(pTmp, varName, pToken, &tmpOP, tmpLen);
    }
    catch(const CalculatorException & e)
    {
        std::cout << e.what() << std::endl;
    }
    delete[] pToken;
    if(state != IDENTIFIER)
    {
        std::cout << "参数不为标识符!" << std::endl;
        delete[] tmpStr;
        delete[] fName;
        delete[] varName;
        return false;
    }
    
    //跳过)
    pCursor++;
    backCursor = pCursor;

    //到表达式前
    pCursor = std::strpbrk(pCursor, "=");
    if(!pCursor)
    {
        delete[] tmpStr;
        delete[] fName;
        delete[] varName;
        return false;
    }
    //跳过等号
    pCursor++;
    if(*pCursor == '\0')
    {
        std::cout << "空表达式!" << std::endl;
        delete[] tmpStr;
        delete[] fName;
        delete[] varName;
        return false;
    }

    expr = new char[ (tokenLen = std::strlen(pCursor)) + 1 ];
    std::strcpy(expr, pCursor);

    //检查表达式是否只含有该变量
    char * token = new char[tokenLen + 1];
    char op;

    pCursor = expr;
    while(*pCursor != '\0')
    {
        //略过空白
		while(*pCursor == ' ' || *pCursor == '\t')
		{
			pCursor++;
		}
        try
        {
            state = getNextToken(pCursor, expr, token, &op, tokenLen);
        }
        catch(const TokenizerException & e)
        {
            std::cout << e.what() << std::endl;
            delete[] tmpStr;
            delete[] fName;
            delete[] varName;
            delete[] expr;
            return false;
        }

        if(state == IDENTIFIER && strcmp(token, varName) != 0)
        {
            delete[] tmpStr;
            delete[] fName;
            delete[] varName;
            delete[] expr;
            return false;
        }
        pCursor++;
    }

    //重名覆盖
    funcTable::iterator i = dest.find(fName);
    if(i != dest.end())
    {
        dest.erase(i);
        std::cout << "函数" << fName << "被覆盖." << std::endl;
    }

    dest.insert(std::pair<std::string, UnaryFunction>(fName, UnaryFunction(fName, varName, expr)));

    std::cout << "函数" << fName << "定义成功." << std::endl;
    delete[] tmpStr;
    delete[] fName;
    delete[] varName;
    delete[] expr;
    delete[] token;
    return true;
}

//处理函数运行字符串, 从保存的函数表取得表达式, 最后运行并输出结果
template <typename T>
bool Calculator<T>::parseRunFunc(std::string & str, funcTable & src)
{
    //拷贝
    char * tmpStr = new char[ std::strlen(str.c_str()) + 1];
    std::strcpy(tmpStr, str.c_str());

    //函数名
    char * fName;
    //变量名
    char * varVal;

    //分词长度
    int tokenLen = 0;
    //分词后指针
    char * backCursor = tmpStr;

    //开始分词

    //分离函数名
    char * pCursor = std::strpbrk(backCursor, "(");
    if(!pCursor)
    {
        delete[] tmpStr;
        return false;
    }
    tokenLen = pCursor - backCursor;
    fName = new char[tokenLen + 1];
    std::strncpy(fName, backCursor, tokenLen);
    fName[tokenLen] = '\0';
    
    //跳过(
    pCursor++;
    //后指针向前
    backCursor = pCursor;

    //分离变量
    pCursor = std::strpbrk(pCursor, ")");
    if(!pCursor)
    {
        delete[] tmpStr;
        delete[] fName;
        return false;
    }
    tokenLen = pCursor - backCursor;
    varVal = new char[tokenLen + 1];
    std::strncpy(varVal, backCursor, tokenLen);
    varVal[tokenLen] = '\0';
    backCursor = pCursor;

    double val;
    try
    {
        val = std::stod(varVal);
    }
    catch(std::invalid_argument & e)
    {
        std::cout << "函数非法参数!" << std::endl;
        delete[] tmpStr;
        delete[] fName;
        delete[] varVal;
        return false;
    }

    //跳过)判断之后是不是全空白符
    pCursor++;
    bool isOK = isWSStr(pCursor);
    if(!isOK)
    {
        delete[] tmpStr;
        delete[] fName;
        delete[] varVal;
        return false;
    }


    //建立符号表
    SymbolTable sTable;
    try
    {
        //尝试找函数名
        funcTable::iterator i = src.find(fName);
        //找不到函数
        if(i == src.end())
        {
            delete[] tmpStr;
            delete[] fName;
            delete[] varVal;
            return false;
        }
        //找到了函数, 变量替换
        sTable.insert(std::pair<std::string, double>(i -> second.getVarName(), val));
        double res = calcExpr(i -> second.getExpr(), sTable);
        std::cout << "结果:" << res << std::endl;
    }
    catch(const CalculatorException & e)
    {
        std::cout << e.what() << std::endl;
    }
    
    delete[] tmpStr;
    delete[] fName;
    delete[] varVal;
    return true;
}
#endif