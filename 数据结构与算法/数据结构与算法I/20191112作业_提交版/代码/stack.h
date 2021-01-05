#ifndef STACK_H
#define STACK_H

#include "linkedlist.h"
#include "myexception.h"

template <typename T>
class ListStack
{
    public:
        ListStack();
        ~ListStack();

        void pop();
        T & top();
        void push(T e);

        bool isEmpty();

    private:
        LinkedList<T> list;
};

template <typename T>
ListStack<T>::ListStack()
{
}

template <typename T>
ListStack<T>::~ListStack()
{

}

template <typename T>
void ListStack<T>::pop()
{
    if(list.isEmpty())
    {
        PopEmptyStack e;
        throw e;
    }
    list.deleteHead();
}

template <typename T>
T & ListStack<T>::top()
{
    if(list.isEmpty())
    {
        TopEmptyStack e;
        throw e;
    }
    list.resetCursor();
    return (list.pCursor -> next) -> data;
}

template <typename T>
void ListStack<T>::push(T e)
{
    list.insertHead(e);
}

template <typename T>
bool ListStack<T>::isEmpty()
{
    return list.isEmpty();
}

#endif