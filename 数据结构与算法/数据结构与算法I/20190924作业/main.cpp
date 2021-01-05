//------------------------------------
//    main.cpp
//    Written by G.Cui @ INFO.RUC
//    2019.9.24
//------------------------------------

#include <iostream>
#include <assert.h>
#include "list.h"

#define DEBUG

//比较用函数, 返回二者是否相等
bool _EqualCmp(ElemType a, ElemType b)
{
    return (a == b);
}

//遍历用函数, 返回元素是否大于零
bool _GreaterThanZero(ElemType e)
{
    return (e > 0);
}

//初始化一个线性表，将 size 置为0，根据capacity分配数据空间
// 若分配成功，返回 true；否则，返回 false
bool InitList(List & L)
{
    L.elements = (ElemType *)calloc(DEFAULT_SIZE, sizeof(ElemType));

    //内存分配失败
    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout << "Memory allocation failed!" << std::endl;
        #endif
        return false;
    }
    //else
    L.size = 0;
    L.capacity = DEFAULT_SIZE;
    #ifdef DEBUG
    std::cout << "List inited!" << std::endl;
    #endif
    return true;
}

//将数据空间收回
void DestroyList(List & L)
{
    L.capacity = L.size = 0;
    //根据C标准 free(NULL); 不进行任何操作, 所以不考虑.
    free(L.elements);

    #ifdef DEBUG
    std::cout << "List freed." << std::endl;
    #endif
}

//将线性表清空
void ClearList(List & L)
{
    if(!L.elements)
    {
        #ifdef DEBUG
        std::cout << "List doesn't exist!" << std::endl;
        #endif
        return;
    }
    //是否需要把内存置为0?
    memset(L.elements, 0, L.size);
    L.size = 0;
    #ifdef DEBUG
    std::cout << "List cleared!" << std::endl;
    #endif
}

//获取线性表L中第i个位置的元素, i= 1,..., size
//若 1<=i<=size, 将elements[i-1] 赋给e 指向 的空间并返回true
//否则 返回false
bool GetElem(List L, int i, ElemType & e)
{
    #ifdef DEBUG
    assert(i >= 1 && i <= L.size);
    #endif

    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return false;
    }
    //下标检查
    if(i >= 1 && i <= L.size)
    {
        e = L.elements[i - 1];
        return true;
    }
    else
    {
        #ifdef DEBUG
        std::cout << "Index out of range!" << std::endl;
        #endif
        return false;
    }
}

//若 1<=i<=size, 将e 放到L的第i个位置, return true
//否则，return  false
bool PutElem(List & L, int i, ElemType e)
{
    #ifdef DEBUG
    assert(i >= 1 && i <= L.size);
    #endif

    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return false;
    }
    //下标检查
    else if(i < 1 || i > L.size)
    {
        #ifdef DEBUG
        std::cout << "Index out of range!" << std::endl;
        #endif
        return false;
    }
    L.elements[i - 1] = e;
    return true;
}

//在线性表中的第i个位置插入元素 e
//若 i<=0  返回 false
//若 i > size ，则 elements[size + 1]= e
//否则，elements[i-1] = e, 将线性表中原有的从 i-1 到 size 的元素顺序后移一个位置
//注意： 1 size++   2 若线性表长度不够，须动态增加
bool ListInsert(List & L, int i, ElemType e)
{
    #ifdef DEBUG
    assert(i >= 1);
    #endif

    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return false;
    }
    else if(i <= 0)
    {
        #ifdef DEBUG
        std::cout << "Index out of range!" << std::endl;
        #endif
        return false;
    }

    //增加长度的情况
    if(L.size >= L.capacity)
    {
        L.capacity += INCREMENTAL_SIZE;
        L.elements = (ElemType *)realloc(L.elements, L.capacity * sizeof(ElemType));
    }
    //在尾部添加
    if(i > L.size)
    {
        L.elements[L.size] = e;
        L.size++;
        return true;
    }
    //在中间, 需要挪动
    for(int j = L.size - 1; j >= i - 1; j--)
    {
        L.elements[j + 1] = L.elements[j]; 
    }
    L.elements[i - 1] = e;
    L.size++;
    return true;
}

//返回L中第1个与e满足关系compare的数据元素的位置；若不存在这样的数据元素，则返回0
// compare为一个函数指针，其返回值为bool，第一个参数线性表中的某个元素,第二个参数为e;
//若满足compare关系，返回true；否则返回false
int LocateElem(List L, ElemType e, bool(* compare)(ElemType, ElemType))
{
    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return false;
    }
    //遍历
    for(int i = 0; i < L.size; i++)
    {
        if(compare(e, L.elements[i]))
        {
            return i + 1;
        }
    }
    return 0;
}

//若 i<1 或 i>size, 返回 false
//否则，删除 第 i 个位置元素(elements[i-1])，将其值存入e指向的空间，并返回true
//注意： 1. size--; 2.须将 i+1, ..., size 位置的元素前移一位
bool ListDelete(List &L, int i, ElemType & e)
{
    #ifdef DEBUG
    assert(i >= 1 && i <= L.size);
    #endif

    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return false;
    }
    else if(i < 1 || i > L.size)
    {
        #ifdef DEBUG
        std::cout << "Index out of range!" << std::endl;
        #endif
        return false;
    }
    L.size--;
    e = L.elements[i - 1];
    //在中间, 需要挪动
    for(int j = i - 1; j < L.size; j++)
    {
        L.elements[j] = L.elements[j + 1]; 
    }
    return true;
}

//依次对L的每个数据元素调用函数 visit，若任意的visit返回false，则本函数返回false；否则，返回true
bool ListTraverse(List L, bool(* visit)(ElemType))
{
    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return false;
    }
    for(int i = 0; i < L.size; i++)
    {
        if(!visit(L.elements[i]))
        {
            return false;
        }
    }
    return true;
}

//若线性表为空，返回true；否则返回false
bool ListEmpty(List L)
{
    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return true;
    }
    return (L.size == 0);
}

//返回线性表中元素个数
int ListLength(List L)
{
    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return 0;
    }
    return L.size;
}

//若cur_e之前存在一个元素，则将其值赋给 pre_e, 并返回 true;
//否则，返回 false
bool PriorElem(List L, ElemType cur_e, ElemType &pre_e)
{
    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return false;
    }
    int index = LocateElem(L, cur_e, _EqualCmp);
    if(index > 1)
    {
        pre_e = L.elements[index - 1 - 1];
        return true;
    }
    return false;
}

//若cur_e之后存在一个元素，则将其值赋给 next_e, 并返回 true;
//否则，返回 false
bool NextElem(List L, ElemType cur_e, ElemType &next_e)
{
    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return false;
    }
    int index = LocateElem(L, cur_e, _EqualCmp);
    if(index < L.size)
    {
        next_e = L.elements[index];
        return true;
    }
    return false;
}

//打印线性表中的内容
void PrintList(List L)
{
    if(L.elements == NULL)
    {
        #ifdef DEBUG
        std::cout <<  "List doesn't exist!" << std::endl;
        #endif
        return;
    }
    for(int i = 0; i < L.size; i++)
    {
        std::cout << L.elements[i] << " ";
    }
    std::cout << std::endl;
}

//把L1、L2合并(取并集), 结果保存在Result里面
void Merge(const List & L1, const List & L2, List & Result)
{
    int LenA = ListLength(L1);
    int LenB = ListLength(L2);

    for(int i = 1; i <= LenA; i++)
    {
        ListInsert(Result, i, L1.elements[i - 1]);
    }
    for(int i = 1; i <= LenB; i++)
    {
        ElemType elemB;
        GetElem(L2, i, elemB);
        if(LocateElem(Result, elemB, _EqualCmp) == 0)
        {
            ListInsert(Result, i + LenA, L2.elements[i - 1]);
        }
    }
}

//两个顺序线性表(升序排列)合并为一个(升序排列)线性表, 结果放在Result里
void OrderedMerge(const List & L1, const List & L2, List & Result)
{
    int LenA = ListLength(L1);
    int LenB = ListLength(L2);

    int i = 1, j = 1, k = 0;
    //公共部分
    while(i <= LenA && j <= LenB)
    {
        ElemType elemA, elemB;
        GetElem(L1, i, elemA);
        GetElem(L2, j, elemB);
        if(elemA <= elemB)
        {
            k++;
            i++;
            ListInsert(Result, k, elemA);
        }
        else
        {
            k++;
            j++;
            ListInsert(Result, k, elemB);
        } 
    }
    while(i <= LenA)
    {
        ElemType elemA;
        GetElem(L1, i, elemA);
        i++;
        k++;
        ListInsert(Result, k, elemA);
    }
    while(j <= LenB)
    {
        ElemType elemB;
        GetElem(L2, j, elemB);
        j++;
        k++;
        ListInsert(Result, k, elemB);
    }
}

int main(int argc, char * argv[])
{
    List L;
    InitList(L);

    std::cout << "Is list empty? " << ListEmpty(L) << std::endl;

    for(int i = 1; i <= 10; i++)
    {
        ListInsert(L, i, i);
    }
    std::cout << "After inserted...";
    std::cout << "List has " << ListLength(L) << " elements. ";
    PrintList(L);

    std::cout << "Is every element greater than 0? " << ListTraverse(L, _GreaterThanZero) << std::endl;

    std::cout << "Element 5 is at " << LocateElem(L, 5, _EqualCmp) << "." << std::endl;
    std::cout << "Insert at begin... ";
    ListInsert(L, 1, 7);
    PrintList(L);
    std::cout << "Insert at middle... ";
    ListInsert(L, 5, 6);
    PrintList(L);
    std::cout << "Insert at end... ";
    ListInsert(L, L.size + 1, 0);
    PrintList(L);

    ElemType e = 66;
    std::cout << "Now e is " << e << "." << std::endl;
    PutElem(L, 11, e);
    std::cout << "After PutElem... ";
    PrintList(L);
    PutElem(L, 11, 9);
    std::cout << "Cancel... ";
    PrintList(L);
    GetElem(L, 7, e);
    std::cout << "After GetElem(L, 7, e), now e is " << e << "." << std::endl;

    std::cout << "Delete at end... ";
    ListDelete(L, L.size, e);
    PrintList(L);
    std::cout << "Delete at middle... ";
    ListDelete(L, 5, e);
    PrintList(L);
    std::cout << "Delete at begin... ";
    ListDelete(L, 1, e);
    PrintList(L);

    PriorElem(L, 2, e);
    std::cout << "Before 2 is " << e << "." << std::endl;
    NextElem(L, 2, e);
    std::cout << "After 2 is " << e << "." << std::endl;


    List L1, Result;
    InitList(L1);
    for(int i = 1; i <= 10; i++)
    {
        ListInsert(L1, i, 2 * i);
    }
    InitList(Result);
    std::cout << "Now L: ";
    PrintList(L);
    std::cout << "Now L1: ";
    PrintList(L1); 

    Merge(L, L1, Result);
    std::cout << "After Merge: ";
    PrintList(Result);
    ClearList(Result);

    OrderedMerge(L, L1, Result);
    std::cout << "After OrderedMerge: ";
    PrintList(Result);
    ClearList(Result);

    ClearList(L);

    DestroyList(L);
    DestroyList(L1);
    DestroyList(Result);
    return 0;
}