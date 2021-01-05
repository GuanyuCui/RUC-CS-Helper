#ifndef SQLIST
#define SQLIST

#include "polynode.h"

template <typename T>
class SqList
{
    public:
        //默认构造函数, 将size置为0, 根据默认capacity分配数据空间
        SqList();
        //构造函数, 将size置为给定值
        SqList(int size);
        //析构函数, 将数据空间收回
        ~SqList();

        //将线性表清空
        void clear();
        //打印线性表()
        void print();

        //获取线性表L中第i个位置的元素, i= 1,..., size
        //若 1<=i<=size, 将elements[i-1] 赋给e指向的空间并返回true, 否则返回false
        bool getElem(int i, T & e);

        //若 1<=i<=size, 将e 放到L的第i个位置, return true
        //否则, return false
        bool putElem(int i, T e);

        //在线性表中的第i个位置插入元素 e
        //若 i<=0  返回 false
        //若 i > size ，则 elements[size + 1]= e
        //否则，elements[i-1] = e, 将线性表中原有的从 i-1 到 size 的元素顺序后移一个位置
        //注意： 1 size++   2 若线性表长度不够，须动态增加
        bool insertElem(int i, T e);

        //返回L中第1个与e满足关系compare的数据元素的位置；若不存在这样的数据元素，则返回0
        // compare为一个函数指针，其返回值为bool，第一个参数线性表中的某个元素,第二个参数为e;
        //若满足compare关系，返回true；否则返回false
        int locateElem(T e, std::function<bool(T, T)> compare);

        //若 i<1 或 i>size, 返回 false
        //否则，删除 第 i 个位置元素(elements[i-1])，将其值存入e指向的空间，并返回true
        //注意： 1. size--; 2.须将 i+1, ..., size 位置的元素前移一位
        bool deleteElem(int i, T & e);

        //依次对L的每个数据元素调用函数 visit，若任意的visit返回false，则本函数返回false；否则，返回true
        bool traverse(std::function<bool(T)> visit);

        //若线性表为空，返回true；否则返回false
        bool isEmpty();

        //返回线性表中元素个数
        int length();

        //若cur_e之前存在一个元素，则将其值赋给 pre_e, 并返回 true;
        //否则，返回 false
        bool priorElem(T cur_e, T & pre_e);

        //若cur_e之后存在一个元素，则将其值赋给 next_e, 并返回 true;
        //否则，返回 false
        bool nextElem(T cur_e, T & next_e);

    private:
        //线性表中元素个数
        int size;
        //当前线性表最多能容纳的元素个数
        int capacity;
        T * elements;

        const static int DEFAULT_SIZE = 50;
        const static int INCREMENTAL_SIZE = 5;
};

template <typename T>
SqList<T>::SqList()
{
    elements = new T[DEFAULT_SIZE];
    if(elements)
    {
        size = 0;
        capacity = DEFAULT_SIZE;
    }
}

template <typename T>
SqList<T>::SqList(int _size)
{
    elements = new T[_size];
    if(elements)
    {
        size = 0;
        capacity = _size;
    }
}

template <typename T>
SqList<T>::~SqList()
{
    delete[] elements;
}

template <typename T>
void SqList<T>::clear()
{
    size = 0;
}

template <typename T>
void SqList<T>::print()
{
    for(int i = 1; i <= size; i++)
    {
        std::cout << elements[i - 1] << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
bool SqList<T>::getElem(int i, T & e)
{
    //下标检查
    if(i >= 1 && i <= size)
    {
        e = elements[i - 1];
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

template <typename T>
bool SqList<T>::putElem(int i, T e)
{
    //下标检查
    if(i < 1 || i > size)
    {
        #ifdef DEBUG
        std::cout << "Index out of range!" << std::endl;
        #endif
        return false;
    }
    elements[i - 1] = e;
    return true;
}

template <typename T>
bool SqList<T>::insertElem(int i, T e)
{
    if(i <= 0)
    {
        #ifdef DEBUG
        std::cout << "Index out of range!" << std::endl;
        #endif
        return false;
    }

    //增加长度的情况
    if(size >= capacity)
    {
        capacity += INCREMENTAL_SIZE;
        elements = (T *)realloc(elements, capacity * sizeof(T));
    }
    //在尾部添加
    if(i > size)
    {
        elements[size] = e;
        size++;
        return true;
    }
    //在中间, 需要挪动
    for(int j = size - 1; j >= i - 1; j--)
    {
        elements[j + 1] = elements[j]; 
    }
    elements[i - 1] = e;
    size++;
    return true;
}

template <typename T>
int SqList<T>::locateElem(T e, std::function<bool(T, T)> compare)
{
    //遍历
    for(int i = 0; i < size; i++)
    {
        if(compare(e, elements[i]))
        {
            return i + 1;
        }
    }
    return 0;
}

template <typename T>
bool SqList<T>::deleteElem(int i, T & e)
{
    if(i < 1 || i > size)
    {
        #ifdef DEBUG
        std::cout << "Index out of range!" << std::endl;
        #endif
        return false;
    }
    size--;
    e = elements[i - 1];
    //在中间, 需要挪动
    for(int j = i - 1; j < size; j++)
    {
        elements[j] = elements[j + 1]; 
    }
    return true;
}

template <typename T>
bool SqList<T>::traverse(std::function<bool(T)> visit)
{
    for(int i = 0; i < size; i++)
    {
        if(!visit(elements[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool SqList<T>::isEmpty()
{
    return (size == 0);
}

template <typename T>
int SqList<T>::length()
{
    return size;
}

template <typename T>
bool SqList<T>::priorElem(T cur_e, T & pre_e)
{
    std::function<bool(T, T)> cmp = _EqualCmp<T>;
    int index = locateElem(cur_e, cmp);
    if(index > 1)
    {
        pre_e = elements[index - 1 - 1];
        return true;
    }
    return false;
}

template <typename T>
bool SqList<T>::nextElem(T cur_e, T & next_e)
{
    std::function<bool(T, T)> cmp = _EqualCmp<T>;
    int index = locateElem(cur_e, cmp);
    if(index < size)
    {
        next_e = elements[index];
        return true;
    }
    return false;
}


#endif