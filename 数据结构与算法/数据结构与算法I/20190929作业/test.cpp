#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNode
{
    ElemType data;
    LNode * next;
}LNode, *LinkList;

//把链表中最小值“摘出来”
LNode * getMinFromList(LinkList &L)
{
    if(L -> next == NULL)
    {
        LNode * retVal = L;
        L = NULL;
        return retVal;
    }
    LNode * p = L;
    LNode * pBeforeMin = NULL;
    ElemType minElem = L -> data;
    while(p -> next != NULL)
    {
        if(p -> next -> data < minElem)
        {
            pBeforeMin = p;
            minElem = p -> next -> data;
        }
        p = p -> next;
    }
    
    LNode * retVal;
    if(pBeforeMin)
    {
        retVal = pBeforeMin -> next;
        pBeforeMin -> next = pBeforeMin -> next -> next;
    }
    else
    {
        retVal = L;
        L = L -> next;
    }
    return retVal;
}

void sortList(LinkList &L)
{
    if(!L)
    {
        return;
    }
    LinkList newHead = getMinFromList(L);
    LNode * pTail = newHead;
    while(L)
    {
        pTail -> next = getMinFromList(L);
        pTail = pTail -> next;
    }
    pTail -> next = NULL;
    L = newHead;
}

void printList(LinkList &L)
{
    LNode * p = L;
    while(p)
    {
        printf("%d ", p -> data);
        p = p -> next;
    }
    printf("\n");
}

int main()
{
    LNode * head = (LNode *)malloc(sizeof(LNode));
    LinkList L = head;
    L -> data = 2;
    LNode nodes[5];
    nodes[0].data = 1;
    nodes[1].data = 5;
    nodes[2].data = 3;
    nodes[3].data = 7;
    nodes[4].data = 4;

    L -> next = &nodes[0];
    nodes[0].next = &nodes[1];
    nodes[1].next = &nodes[2];
    nodes[2].next = &nodes[3];
    nodes[3].next = &nodes[4];
    nodes[4].next = NULL;

    printList(L);
    sortList(L);
    printList(L);
    
    free(head);
    return 0;
}