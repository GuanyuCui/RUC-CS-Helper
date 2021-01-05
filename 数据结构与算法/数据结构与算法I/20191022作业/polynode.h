#ifndef POLYNODE
#define POLYNODE

#include <iostream>

template <typename T>
bool _EqualCmp(T a, T b)
{
    return (a == b);
}

template <typename T>
bool _GreaterThanZero(T e)
{
    return (e > 0);
}

template <typename T>
class PolyNode
{
    public:
        PolyNode(T _coef = 0, unsigned int _exp = 0)
        :coef(_coef), exp(_exp)
        {}
        //重载operator 同次数节点相加减
        PolyNode<T> operator +(const PolyNode<T> & rhs)
        {
            PolyNode<T> retVal(this -> coef + rhs.coef, this -> exp);
            return retVal;
        }
        void operator +=(const PolyNode<T> & rhs)
        {
            this -> coef += rhs.coef;
            //this -> exp;
        }
        PolyNode<T> operator -(const PolyNode<T> & rhs)
        {
            PolyNode<T> retVal(this -> coef - rhs.coef, this -> exp);
            return retVal;
        }
        void operator -=(const PolyNode<T> & rhs)
        {
            this -> coef -= rhs.coef;
        }

        //重载负号
        PolyNode<T> operator -()
        {
            PolyNode<T> retVal(-this -> coef, this -> exp);
            return retVal;
        }
        //重载乘法
        PolyNode<T> operator *(const PolyNode<T> & rhs)
        {
            PolyNode<T> retVal(this -> coef * rhs.coef, this -> exp + rhs.exp);
            return retVal;
        }
        void operator *=(const PolyNode<T> & rhs)
        {
            this -> coef *= rhs.coef;
            this -> exp += rhs.exp;
        }

        //求导
        void deri()
        {
            if(exp == 0)
            {
                coef = 0;
            }
            else
            {
                coef *= exp;
                exp--;
            }
        }

        //系数
        T coef;
        //指数
        unsigned int exp;
};

//重载operator<<
template <typename T>
std::ostream & operator << (std::ostream & out, PolyNode<T> &node)
{
    //常数项
    if(node.exp == 0)
    {
        if(node.coef != 0)
        {
            out << node.coef;
        }
    }
    //一次项
    else if(node.exp == 1)
    {
        if(node.coef == 1)
        {
            out << 'x';
        }
        else if(node.coef == -1)
        {
            out << "-x";
        }
        else if(node.coef != 0)
        {
            out << node.coef << 'x';
        }
    }
    //其他
    else
    {
        if(node.coef == 1)
        {
            out << "x^" << node.exp; 
        }
        else if(node.coef == -1)
        {
            out << "-x^" << node.exp;
        }
        else if(node.coef != 0)
        {
            out << node.coef << "x^" << node.exp;
        }
    }
    return out;
}

#endif