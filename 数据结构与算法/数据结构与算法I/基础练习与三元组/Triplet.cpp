//------------------------------------
//    Triplet.cpp
//    Written by G.Cui @ INFO.RUC
//    2019.9.17
//------------------------------------

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define ElemType int

typedef ElemType * Triplet;
typedef enum _Status
{
    OK = 1,
    ERROR = 0,
    INFEASIBLE = -1,
    OVERFLOW = -2
}Status;

//以v1, v2, v3初始化三元组T
Status InitTriplet(Triplet & T, ElemType v1, ElemType v2, ElemType v3)
{
    //已存在
    if(T != NULL)
    {
        std::cout << "Triplet exists!" << std::endl;
        return ERROR;
    }
    else
    {
        T = (ElemType *)malloc(3 * sizeof(ElemType));
        //分配失败
        if(T == NULL)
        {
            std::cout << "Memory allocation fails!" << std::endl;
            return OVERFLOW;
        }
        //分配成功
        else
        {
            T[0] = v1, T[1] = v2, T[2] = v3;
            return OK;
        }
    }
}

//释放三元组T
Status DestroyTriplet(Triplet & T)
{
    //释放
    //if(T != NULL)
    free(T);
    T = NULL;
    std::cout << "T freed." << std::endl;
    return OK;
}

//打印三元组T的元素
Status PrintTriplet(const Triplet & T)
{
    //不存在
    if(T == NULL)
    {
        std::cout << "Triplet doesn't exist!" << std::endl;
        return ERROR;
    }
    else
    {
        std::cout << "<" << T[0] << ", " << T[1] << ", " << T[2] << ">" << std::endl;
        return OK;
    }  
}

//获取三元组T下标为index的元素, 放到dest内
Status Get(const Triplet & T, int index, ElemType & dest)
{
    //不存在
    if(T == NULL)
    {
        std::cout << "Triplet doesn't exist!" << std::endl;
        return ERROR;
    }
    else
    {
        //下标检查
        #ifdef DEBUG
        assert(index >= 1 && index <= 3);
        #endif

        if(index < 1 || index > 3)
        {
            std::cout << "Index out of range!" << std::endl;
            return ERROR;
        }
        else
        {
            dest = T[index - 1];
            return OK;
        }
    }
}

//更改三元组T下标为index的元素, 改为src的值
Status Put(Triplet & T, int index, const ElemType & src)
{
    //不存在
    if(T == NULL)
    {
        std::cout << "Triplet doesn't exist!" << std::endl;
        return ERROR;
    }
    else
    {
        //下标检查
        #ifdef DEBUG
        assert(index >= 1 && index <= 3);
        #endif

        if(index < 1 || index > 3)
        {
            std::cout << "Index out of range!" << std::endl;
            return ERROR;
        }
        else
        {
            T[index - 1] = src;
            return OK;
        }
    }
}

//确定三元组T是否升序排列
bool IsAscending(const Triplet & T)
{
    //不存在
    if(T == NULL)
    {
        std::cout << "Triplet doesn't exist!" << std::endl;
        return false;
    }
    else
    {
        return ((T[0] <= T[1]) && (T[1] <= T[2]));
    }
}

//确定三元组T是否降序排列
bool IsDescending(const Triplet & T)
{
    //不存在
    if(T == NULL)
    {
        std::cout << "Triplet doesn't exist!" << std::endl;
        return false;
    }
    else
    {
        return ((T[0] >= T[1]) && (T[1] >= T[2]));
    }
}

//获取三元组T的最大元素, 放到dest内
Status Max(const Triplet & T, ElemType & dest)
{
    //不存在
    if(T == NULL)
    {
        std::cout << "Triplet doesn't exist!" << std::endl;
        return ERROR;
    }
    else
    {
        ElemType _max = T[0];
        for(int i = 1; i < 3; i++)
        {
            if(T[i] > _max)
            {
                _max = T[i];
            }
        }
        dest = _max;
        return OK;
    }
}

//获取三元组T的最小元素, 放到dest内
Status Min(const Triplet & T, ElemType & dest)
{
    //不存在
    if(T == NULL)
    {
        std::cout << "Triplet doesn't exist!" << std::endl;
        return ERROR;
    }
    else
    {
        ElemType _min = T[0];
        for(int i = 1; i < 3; i++)
        {
            if(T[i] < _min)
            {
                _min = T[i];
            }
        }
        dest = _min;
        return OK;
    }
}

//将T2 + T1的结果存放到T中
Status Add(const Triplet & T1, const Triplet & T2, Triplet & T)
{
    //不存在
    if(T == NULL)
    {
        InitTriplet(T, 0, 0, 0);
    }
    for(int i = 0; i < 3; i++)
    {
        T[i] = T2[i] + T1[i];
    }
    return OK;
}

//将T2 - T1的结果存放到T中
Status Subtract(const Triplet & T1, const Triplet & T2, Triplet & T)
{
    //不存在
    if(T == NULL)
    {
        InitTriplet(T, 0, 0, 0);
    }
    for(int i = 0; i < 3; i++)
    {
        T[i] = T2[i] - T1[i];
    }
    return OK;
}

int main(int argc, char * argv[])
{
    Triplet T = NULL;
    InitTriplet(T, 1, 2, 3);
    PrintTriplet(T);
    std::cout << "Is T in ascending order:" << IsAscending(T) << std::endl;
    std::cout << "Is T in descending order:" << IsDescending(T) << std::endl;
    ElemType e;
    Get(T, 2, e);
    std::cout << "The 2nd element of T is:" << e << std::endl;
    Put(T, 2, 10);
    Get(T, 2, e);
    std::cout << "After executing Put(T, 2, 10), the 2nd element of T is:" << e << std::endl;
    Max(T, e);
    std::cout << "Max element of T is:" << e << std::endl;
    Min(T, e);
    std::cout << "Min element of T is:" << e << std::endl;

    Triplet T1 = NULL, T2 = NULL;
    InitTriplet(T1, 1, 2, 3);
    InitTriplet(T2, 4, 5, 6);
    Add(T1, T2, T);
    std::cout << "<1,2,3> + <4,5,6>=" << std::endl;
    PrintTriplet(T);
    Subtract(T1, T2, T);
    std::cout << "<4,5,6> - <1,2,3>=" << std::endl;
    PrintTriplet(T);

    //小心内存泄漏!!!
    DestroyTriplet(T);
    DestroyTriplet(T1);
    DestroyTriplet(T2);
    return 0;
}