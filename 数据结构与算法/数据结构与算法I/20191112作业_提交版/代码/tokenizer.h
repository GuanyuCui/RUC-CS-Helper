#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cctype>
#include "myexception.h"

//分词器状态
typedef enum _TOKENIZE_STATE
{
    //初始,
    INIT,
    //整型,     整型(科学记数法),
    INT,    SCIINT,
    //浮点型,   浮点型(科学记数法),
    FLOAT,  SCIFLOAT,
    //标识符,   操作符,
    IDENTIFIER, OPERATOR,
    //函数,     错误
    FUNCTION, ERROR
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
	//第一个字符 前一个字符是(/e
	else if(now == strHead || isNextInPar(now, strHead) || (now > strHead && *(now - 1) == 'e'))
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
	else if(now == strHead || isNextInPar(now, strHead) || (now > strHead && *(now - 1) == 'e'))
	{
		//之后是数字
		if(*(now + 1) != '\0')
		{
			return std::isdigit(*(now + 1));
		}	
	}
	return false;
}

//分词器
class Tokenizer
{
    public:
        Tokenizer(){}
        //获取下一个分词结果
        TOKENIZE_STATE getNextToken(char * str, const char * strHead, char * oprDest, char * opDest, int & len);
};

//获取下一个Token 
//参数列表:
//str - 目前剩余字符串; strHead - 全字符串首, 用来判断正负号
//oprDest - 操作数/标识符字面值放置; opDest - 操作符放置地; len - Token长度

//注意: 状态机出错会抛出异常, 注意处理
TOKENIZE_STATE Tokenizer::getNextToken(char * str, const char * strHead, char * oprDest, char * opDest, int & len)
{
	//前后指针
	char * back = str;
	char * front = str;
	
	//初始状态
	TOKENIZE_STATE state = INIT;
	//分词结束的标志
	bool isFinished = false;
	//用来计算括号重数——函数调用
	int parDepth = 0;
	
	//持续分词
	while(!isFinished && front && *front != '\0')
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
				if(*front == ' ' || isOperator(*front))
				{
					isFinished = true;
				}
				//数字/e -> 整数值
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
                //e -> 整型(科学记数法)
                else if(*front == 'e')
                {
                    state = SCIINT;
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
            case SCIINT:
            {
                //+ -(正负号) 数字 -> 整数值
				if(isPos(front, strHead) || isNeg(front, strHead) || std::isdigit(*front))
				{
					state = SCIINT;
					front++;
				}
                else if(*front == ' ' || isOperator(*front))
                {
                    isFinished = true;
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
			case FLOAT:
			{
				//空格 + - * / ( ) -> 结束
				if(*front == ' ' || isOperator(*front))
				{
					isFinished = true;
				}
				//数字 -> 值
				else if(std::isdigit(*front))
				{
					state = FLOAT;
					front++;
				}
                //e -> 浮点型(科学记数法)
                else if(*front == 'e')
                {
                    state = SCIFLOAT;
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
            case SCIFLOAT:
            {
                //+ -(正负号) 数字 -> 值
				if(isPos(front, strHead) || isNeg(front, strHead) || std::isdigit(*front))
				{
					state = SCIFLOAT;
					front++;
				}
                else if(*front == ' ' || isOperator(*front))
                {
                    isFinished = true;
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
                //( -> 函数调用
                if(*front == '(')
                {
                    state = FUNCTION;
                    front++;
                }
				//空格 + - * / ) -> 结束
				else if(*front == ' ' || isOperator(*front))
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
            case FUNCTION:
            {
				//计算括号重数
				if(parDepth == 0)
				{
					parDepth = 1;
				}
				if(*front != '\0')
                {
					if(*front == '(')
					{
						parDepth++;
					}
					else if(*front == ')')
					{
						parDepth--;
						if(parDepth == 0)
						{
							isFinished = true;
							parDepth = 0;
						}
					}
                    front++;
                }
				else
				{
					state = ERROR;
					isFinished = true;
				}
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
	if(state == INT || state == SCIINT ||
        state == FLOAT || state == SCIFLOAT ||
        state == IDENTIFIER || state == FUNCTION)
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

#endif