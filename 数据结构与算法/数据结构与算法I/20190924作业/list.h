#ifndef LIST_H
#define LIST_H

#define DEFAULT_SIZE 50
#define INCREMENTAL_SIZE 5
#define ElemType int

typedef struct{
    int size;//线性表中元素个数
    int capacity;//当前线性表最多能容纳的元素个数
    ElemType * elements;
}List;

//初始化一个线性表，将 size 置为0，根据capacity分配数据空间
// 若分配成功，返回 true；否则，返回 false
bool InitList(List & L);

//将 数据空间收回
void DestroyList(List & L);

//将线性表清空
void ClearList(List & L);

//获取线性表L中第i个位置的元素, i= 1,..., size
//若 1<=i<=size, 将elements[i-1] 赋给e 指向 的空间并返回true
//否则 返回false
bool GetElem(List L, int i, ElemType & e);

//若 1<=i<=size, 将e 放到L的第i个位置, return true
//否则，return  false
bool PutElem(List &L, int i, ElemType e);

//在线性表中的第i个位置插入元素 e
//若 i<=0  返回 false
//若 i > size ，则 elements[size + 1]= e
//否则，elements[i-1] = e, 将线性表中原有的从 i-1 到 size 的元素顺序后移一个位置
//注意： 1 size++   2 若线性表长度不够，须动态增加
bool ListInsert(List & L, int i, ElemType e);

//返回L中第1个与e满足关系compare的数据元素的位置；若不存在这样的数据元素，则返回0
// compare为一个函数指针，其返回值为bool，第一个参数线性表中的某个元素,第二个参数为e;
//若满足compare关系，返回true；否则返回false
int LocateElem(List L, ElemType e, bool(* compare)(ElemType, ElemType));

//若 i<1 或 i>size, 返回 false
//否则，删除 第 i 个位置元素(elements[i-1])，将其值存入e指向的空间，并返回true
//注意： 1. size--; 2.须将 i+1, ..., size 位置的元素前移一位
bool ListDelete(List &L, int i, ElemType & e);

//依次对L的每个数据元素调用函数 visit，若任意的visit返回false，则本函数返回false；否则，返回true
bool ListTraverse(List L, bool(* visit)(ElemType));

//若线性表为空，返回true；否则返回false
bool ListEmpty(List L);

//返回线性表中元素个数
int ListLength(List L);

//若cur_e之前存在一个元素，则将其值赋给 pre_e, 并返回 true;
//否则，返回 false
bool PriorElem(List L, ElemType cur_e, ElemType &pre_e);//

//若cur_e之后存在一个元素，则将其值赋给 next_e, 并返回 true;
//否则，返回 false
bool NextElem(List L, ElemType cur_e, ElemType &next_e);


//打印线性表中的内容
void PrintList(List L);

#endif // LIST_H
