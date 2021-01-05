#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <string>
#include <exception>

//异常基类
class MyException
{
    public:
        virtual std::string what() const = 0;
};

//————————————————————顺序表异常————————————————————
class SqListException : public MyException
{
    public:
        virtual std::string what() const = 0;
};


//————————————————————链表异常————————————————————
class LinkedListException : public MyException
{
    public:
        virtual std::string what() const = 0;
};

//————————————————————栈异常————————————————————
class StackException : public MyException
{
    public:
        virtual std::string what() const = 0;
};

class PopEmptyStack : public StackException
{
    public:
        std::string what() const
        {
            return "试图弹空栈!"; 
        }
};

class TopEmptyStack : public StackException
{
    public:
        std::string what() const
        {
            return "栈为空!"; 
        }
};

//————————————————————计算器异常————————————————————
class CalculatorException : public MyException
{
    public:
        virtual std::string what() const = 0;
};
//解析器错误
class TokenizerException : public CalculatorException
{
    public:
        virtual std::string what() const = 0;
};

//执行器错误
class ExecException : public CalculatorException
{
    public:
        virtual std::string what() const = 0;
};


class IllegalChar : public TokenizerException
{
    public:
        std::string what() const
        {
            return "非法字符!"; 
        }
};

class IllegalNum : public TokenizerException
{
    public:
        std::string what() const
        {
            return "非法数值!"; 
        }
};

class IllegalIdentifier : public TokenizerException
{
    public:
        std::string what() const
        {
            return "非法标识符!"; 
        }
};

class NullExpr : public ExecException
{
    public:
        std::string what() const
        {
            return "空表达式!"; 
        }
};

class LackOperand : public ExecException
{
    public:
        std::string what() const
        {
            return "缺少操作数!"; 
        }
};

class MoreOperand : public ExecException
{
    public:
        std::string what() const
        {
            return "过多操作数!"; 
        }
};

class UnmatchPar : public ExecException
{
    public:
        std::string what() const
        {
            return "括号不匹配!"; 
        }
};

#endif