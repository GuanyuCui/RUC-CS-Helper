#ifndef EXECER_H
#define EXECER_H

#include <map>
#include <cmath>
#include <regex>

#include "stack.h"
#include "unary_function.h"
#include "tokenizer.h"

//函数表 <函数名, 一元函数对象>
typedef std::map<std::string, UnaryFunction> FuncTable;
//符号表 <符号字面量, 值>
typedef std::map<std::string, double> SymbolTable;

//返回优先度之差
int deltaPrior(char a, char b)
{
    static std::map<char, int> pr;
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

//表达式执行器
class Execer
{
    public:
        Execer(){}
        void task9()
        {
            std::cout << std::endl << "以下是表达式求值/可编程计算器演示:" << std::endl;
            //简单函数编程器
            funcProg();
        }
    private:
        Tokenizer tokenizer;

        //表达式求值——链栈实现
        double calcExpr(std::string & expr, SymbolTable & sTable, FuncTable & fTable);
        //遇到函数, 把括号里的表达式计算完后, 把值带入符号表替换运算
        double calcFunc(char * funcStr, SymbolTable & sTable, FuncTable & fTable);
        //函数编程器
        void funcProg();

        //处理函数定义字符串, 保存到函数表里
        bool parseSaveFunc(std::string & str, FuncTable & dest);
};

double Execer::calcExpr(std::string & expr, SymbolTable & sTable, FuncTable & fTable)
{
    //操作数栈
    ListStack<double> operandStack;
    //操作符栈
    ListStack<char> opStack;

    if(expr.empty())
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
		    state = tokenizer.getNextToken(pCursor, strExpr, token, &op, len);
        }
        catch(const MyException &e)
        {
            delete[] strExpr;
	        delete[] token;
            throw;
        }

        //数值入栈
        if(state == INT || state == SCIINT
            || state == FLOAT || state == SCIFLOAT)
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
        else if(state == FUNCTION)
        {
            try
            {
                double funcRes = calcFunc(token, sTable, fTable);
                operandStack.push(funcRes);
            }
            catch(const MyException& e)
            {
                throw;
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
    catch(...)
    {
        NullExpr e;
        throw e;
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

double Execer::calcFunc(char * funcStr, SymbolTable & sTable, FuncTable & fTable)
{
    //分离函数名
    std::cmatch res;
    std::regex r(".+?(?=\\()");
    std::regex_search(funcStr, res, r);
    //查函数表
    FuncTable::iterator i = fTable.find(res.str());
    //没找着
    if(i == fTable.end())
    {
        UndefinedSymbol e;
        throw e;
    }
    else
    {
        //把函数括号里的内容取出
        int varLen = std::strlen(res.suffix().str().c_str()) - 2;
        char * varName = new char[varLen + 1];
        std::strncpy(varName, res.suffix().str().c_str() + 1, varLen);
        varName[varLen] = '\0';
        std::string tmpVarName(varName);
        //把括号内表达式执行一下
        double val;
        try
        {
            val = calcExpr(tmpVarName, sTable, fTable);
        }
        catch(const MyException & e)
        {
            throw;
        }
        //建立运行函数所用符号表
        SymbolTable runningSTable;
        try
        {
            //找到了函数, 变量替换
            runningSTable.insert(std::pair<std::string, double>(i -> second.getVarName(), val));
            double res = calcExpr(i -> second.getExpr(), runningSTable, fTable);
            return res;
        }
        catch(const MyException & e)
        {
            throw;
        }
        delete[] varName;
    }
}

void Execer::funcProg()
{
    std::cout << "\"Function C0mp1ler\" Written by G.Cui.   Ver.0.1" << std::endl;
    std::cout << "请输入命令(DEF定义函数, RUN求值, QUIT退出):" << std::endl;
    std::cout << ">>>";
    //符号表 —— 表达式求值要用
    SymbolTable sTable;
    //函数表 —— 存储定义的函数
    FuncTable fTable;

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

            try
            {
                double res = calcExpr(runStr, sTable, fTable);
                std::cout << "结果: " << res << std::endl;
            }
            catch(const MyException & e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else if(instr == "QUIT")
        {
            break;
        }
        else
        {
            //把其余指令读完, 忽略
            std::getline(std::cin, instr);
            std::cout << "非法指令!(DEF定义函数, RUN求值, QUIT退出)" << std::endl;
        }
        std::cout << ">>>";
        std::cin >> instr;
    }
}

//处理函数定义字符串, 保存到函数表里
bool Execer::parseSaveFunc(std::string & str, FuncTable & dest)
{
    //lambda表达式结合正则表达式确定是否合法标识符
    auto isIdent = [&](std::string str) -> bool
    {
        std::regex identReg("[_A-Za-z][_A-Za-z0-9]*");
        std::smatch identRes;
        std::regex_search(str, identRes, identReg);
        return (str == identRes.str());
    };
    
    //用 = 正则匹配, 分离为 f(x) = (expr)的形式
    std::regex r("=");
    //匹配结果
    std::smatch res;
    //匹配
    std::regex_search(str, res, r);

    if(res.empty() || res.suffix().str().empty())
    {
        std::cout << "函数定义缺少表达式!" << std::endl;
        return false;
    }
    //拷贝表达式部分
    char * expr = new char[ std::strlen(res.suffix().str().c_str()) + 1 ];
    std::strcpy(expr, res.suffix().str().c_str());

    std::string prefix = res.prefix().str();
    //再从前缀中分离函数名
    r = std::regex("[^ ]*[_A-Za-z][_A-Za-z0-9]*(?=\\()");
    std::regex_search(prefix, res, r);
    //函数名不是标识符名字
    if(res.str().empty() || !isIdent(res.str()))
    {
        std::cout << "函数名不合法!" << std::endl;
        delete[] expr;
        return false;
    }

    //拷贝函数名部分
    char * fName = new char[ std::strlen(res.str().c_str()) + 1 ];
    std::strcpy(fName, res.str().c_str());

    //再从中分离函数变量
    int varLen = std::strlen(res.suffix().str().c_str()) - 2;
    char * varName = new char[varLen + 1];
    std::strncpy(varName, res.suffix().str().c_str() + 1, varLen);
    varName[varLen] = '\0';
    std::string tmpVarName(varName);
    //检查函数变量是否合法
    if(!isIdent(tmpVarName))
    {
        std::cout << "函数变量名不合法!" << std::endl;
        delete[] fName;
        delete[] varName;
        delete[] expr;
        return false;
    }

    //重名覆盖
    FuncTable::iterator i = dest.find(fName);
    if(i != dest.end())
    {
        dest.erase(i);
        std::cout << "函数" << fName << "被覆盖." << std::endl;
    }
    dest.insert(std::pair<std::string, UnaryFunction>(fName, UnaryFunction(fName, varName, expr)));
    std::cout << "函数" << fName << "定义成功." << std::endl;
    delete[] fName;
    delete[] varName;
    delete[] expr;
    return true;
}
#endif