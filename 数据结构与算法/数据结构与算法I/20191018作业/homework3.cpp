#include <iostream>

//入队
void EnQueue(Queue & q, ElemType & e)
{
	//建立节点
	LNode * node = new LNode(e);
	//修改节点指针域, 使之指向头节点
	node -> next = q.rear -> next;
	//尾部插入节点
	q.rear -> next = node;
	//修改尾指针
	q.rear = node;
}

//出队
void DeQueue(Queue & q, ElemType & e)
{
	//队列空
	if(q.rear -> next == q.rear)
	{
		std::cout << "Empty Queue!" << std::endl;
		return;
	}
	//首元节点
	LNode * node = q.rear -> next -> next;
	//获取数据
	e = node -> data;
	//先记录下删之前的尾节点
	LNode * preRear = q.rear;
	//只有一个元素, 新尾节点设为头节点
	if(preRear -> next -> next == preRear)
	{
		q.rear = q.rear -> next;
	}
	//头节点指针域修改
	preRear -> next -> next = node -> next;
	//释放首元节点
	free(node);
}

int main(int argc, char *argv[])
{
	
	return 0;
}