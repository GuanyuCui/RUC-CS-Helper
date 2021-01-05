#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "polynode.h"
#include "myexception.h"

//链表节点
template <typename T>
class LinkedListNode
{
    public:
    //三种构造函数
        LinkedListNode();
        LinkedListNode(T _data);
        LinkedListNode(T _data, LinkedListNode<T> * pNext);
    //析构函数
        ~LinkedListNode();
    //数据域
        T data;
    //指针域
        LinkedListNode * next;
};

template <typename T>
LinkedListNode<T>::LinkedListNode()
{

}

template <typename T>
LinkedListNode<T>::LinkedListNode(T _data)
{
    data = _data;
}

template <typename T>
LinkedListNode<T>::LinkedListNode(T _data, LinkedListNode<T> * pNext)
{
    data = _data;
    next = pNext;
}

template <typename T>
LinkedListNode<T>::~LinkedListNode()
{

}

template <typename T>
class LinkedList
{
    public:
        LinkedList();
        ~LinkedList();

        //清空节点
        void clear();
        //打印链表
        void print();
        //判空
        bool isEmpty();
        //表长
        int getLength();
        //遍历
        bool traverse(std::function<bool(T)> visit);
        //查找
        int locateElem(T data, std::function<bool(T, T)> compare);

        //头插节点
        void insertHead(T data);
        //尾插节点
        void insertTail(T data);
        //当前节点之后插入
        void insertAfter(T data);

        //删除后继节点
        LinkedListNode<T> * deleteAfter();

        LinkedListNode<T> * deleteHead();
        LinkedListNode<T> * deleteTail();

        //遍历用内部指针
        LinkedListNode<T> * pCursor;

        //移动Cursor
        //void moveCursor(int step);
        //指针回到开头
        void resetCursor();
    private:
        //头节点
        LinkedListNode<T> head;
        //头指针
        const LinkedListNode<T> * pHead;
        //尾指针
        LinkedListNode<T> * pTail;

        int length;
};

template <typename T>
LinkedList<T>::LinkedList()
:pHead(&head), pCursor(&head), pTail(&head)
{
    head.next = NULL;
    length = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
void LinkedList<T>::clear()
{
    pCursor = pHead -> next;
    LinkedListNode<T> * p = pCursor;
    //遍历
    while(pCursor)
    {
        //pCursor前进之后, 释放前面的节点
        pCursor = pCursor -> next;
        delete p;
        p = pCursor;
    }
    pTail = &head;
    pCursor = &head;
}

template <typename T>
void LinkedList<T>::print()
{
    LinkedListNode<T> * p = pHead -> next;
    while(p)
    {
        std::cout << p -> data << ' ';
        p = p -> next;
    }
    std::cout << std::endl;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
    return (pHead == pTail);
    //length == 0
}

template <typename T>
int LinkedList<T>::getLength()
{
    return length;
}

template <typename T>
bool LinkedList<T>::traverse(std::function<bool(T)> visit)
{
    LinkedListNode<T> * p = pHead -> next;
    while(p)
    {
        if(!visit(p -> data))
        {
            return false;
        }
        p = p -> next;
    }
    return true;
}

template <typename T>
int LinkedList<T>::locateElem(T data, std::function<bool(T, T)> compare)
{
    LinkedListNode<T> * p = pHead -> next;
    int index = 0;
    while(p)
    {
        index++;
        if(compare(data, p -> data))
        {
            return index;
        }
        p = p -> next;
    }
    return 0;
}

template <typename T>
void LinkedList<T>::insertHead(T data)
{
    LinkedListNode<T> * s = new LinkedListNode<T>(data);
    //尾指针
    if(pHead == pTail)
    {
        pTail = s;
    }
    s -> next = pHead -> next;
    head.next = s;
    length++;
    
}

template <typename T>
void LinkedList<T>::insertAfter(T data)
{
    LinkedListNode<T> * s = new LinkedListNode<T>(data);
    if(pCursor == pTail)
    {
        pTail = s;
    }
    s -> next = pCursor -> next;
    pCursor -> next = s;
    length++;
}

template <typename T>
void LinkedList<T>::insertTail(T data)
{
    LinkedListNode<T> * s = new LinkedListNode<T>(data);
    pTail -> next = s;
    s -> next = NULL;
    pTail = s;
    length++;
}

template <typename T>
LinkedListNode<T> * LinkedList<T>::deleteHead()
{
    if(isEmpty())
    {
        return NULL;
    }
    LinkedListNode<T> * retVal = pHead -> next;
    head.next = pHead -> next -> next;
    length--;
    if(retVal == pTail)
    {
        pTail = &head;
    }
    return retVal;
}

template <typename T>
LinkedListNode<T> * LinkedList<T>::deleteAfter()
{
    if(isEmpty())
    {
        return NULL;
    }
    LinkedListNode<T> * retVal = pCursor -> next;
    pCursor -> next = pCursor -> next -> next;
    length--;
    if(retVal == pTail)
    {
        pTail = &head;
    }
    return retVal;
}

template <typename T>
LinkedListNode<T> * LinkedList<T>::deleteTail()
{
    if(isEmpty())
    {
        return NULL;
    }
    
    LinkedListNode<T> * retVal = pTail;
    LinkedListNode<T> * p = &head;
    while(p -> next != pTail)
    {
        p = p -> next;
    }
    p -> next = NULL;
    length--;
    if(retVal == pTail)
    {
        pTail = &head;
    }
    return retVal;
}

template <typename T>
void LinkedList<T>::resetCursor()
{
    pCursor = &head;
}
#endif