#pragma once
#include "Node.h"
using namespace std;

template <typename T>
class LinkedList{
protected:
	int _size;
	Node<T>* header;
	Node<T>* trailer;

	void swap(Node<T>& a, Node<T>& b)
	{
		Node<T>* temp = nullptr;
		temp->val= a->val;
		a->val = b->val;
		b->val = temp->val;
	}

	void init(); // 构造函数通过init初始化链表
	int clear(); // 清空链表， 返回删除的节点数
	void copyNodes(Node<T>* p, int n); // 复制链表中自位置p起的n项
	Node<T>* selectMax(Node<T>* p, int n); // 从p开始连续的n个节点中选出最大者

	void merge(Node<T>*& p, int n, LinkedList<T>& L, Node<T>* q, int m); // 归并两个有序链表
	void mergeSort(Node<T>*& p, int n); // 对从p开始连续的n个节点归并排序
	void selectionSort(Node<T>* p, int n); // 对从p开始连续的n个节点选择排序
	void insertionSort(Node<T>* p, int n); // 对从p开始连续的n个节点插入排序
	void bubbleSord(Node<T>* p, int n); // 对从p开始连续的n个节点冒泡排序
	void quickSort(Node<T>* p, int n); // 对从p开始连续的n个节点快速排序

public:
	LinkedList() { init();}; // 默认构造函数
	LinkedList(int size); // 生成指定大小的链表, 每个节点的值为0
	LinkedList(LinkedList<T> const& L); // 复制构造函数
	LinkedList(LinkedList<T> const& L, int n); // 复制构造函数, 复制L的从头开始的n个节点

	~LinkedList(); // 析构函数

	int size() const;// 返回链表的大小
	bool empty() const; // 判断链表是否为空

	Node<T>*& first() const { return header->next; } // 返回首节点
	Node<T>* last() const { return trailer->prev; }; // 返回尾节点

	Node<T>* find(T const& e) const; // 查找元素e
	Node<T>* find(T const& e, int n, Node<T>* p) const; // 从节点p开始查找元素e

	Node<T>* insertAsFirst(T const& e); // 在首节点之前插入元素e
	Node<T>* insertAsLast(T const& e); // 在尾节点之后插入元素e
	Node<T>* insertBefore(Node<T>* p, T const& e); // 在节点p之前插入元素e
	Node<T>* insertAfter(Node<T>* p, T const& e); // 在节点p之后插入元素e

	T remove(Node<T>* p); // 删除节点p

	void sort(Node<T>* p, int n);

	void print() const;
	
	Node<T>* operator[](int r) const; // 重载下标操作符, 在链表中像Vector一样使用下标访问元素

	void getMax(Node<T>* p, int n);
};

template<typename T>
LinkedList<T>::LinkedList(int size)
{
	init();  // 初始化哨兵节点  
	_size = size;

	Node<T>* current = header;
	for (int i = 0; i < _size; ++i) {
		// 创建新节点并初始化数据  
		Node<T>* newNode = new Node<T>();
		newNode->val = 1;  // 默认初始化数据（或根据需求传入参数）  

		// 双向链表指针维护  
		newNode->prev = current;
		newNode->next = trailer;
		current->next = newNode;
		trailer->prev = newNode;

		current = newNode;  // 移动指针到新节点  
	}
}

template<typename T>
inline LinkedList<T>::LinkedList(LinkedList<T> const& L)
{
	init();//初始化
	Node<T>* p = L[0];
	while (p!=nullptr)
	{
		insertAsLast(p->val);
		p = p->next;
	}
}

template<typename T>
inline LinkedList<T>::LinkedList(LinkedList<T> const& L, int n)
{
	Node<T>* p = L[0];
	copyNodes(p, n);
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	clear();
	delete header;
	delete trailer;
}

template<typename T>
int LinkedList<T>::size() const
{
	return _size;
}

template<typename T>
bool LinkedList<T>::empty() const
{
	if(header->next==header)
	return false;
}

template<typename T>
void LinkedList<T>::init()//初始化
{
	header = new Node<T>;
	trailer = new Node<T>;
	header->next = trailer;
	header->prev = nullptr;
	trailer->next = nullptr;
	trailer->prev = header;
	_size = 0;
}

template<typename T>
int LinkedList<T>::clear()
{
	Node<T>* p = first();
	int count = 0;//记录删除的节点数
	for (int i = 0;i < _size;i++)
	{
		remove(p);
		_size--;
		count++;
	}
	return count;
}

template<typename T>
void LinkedList<T>::copyNodes(Node<T>* p, int n)//将自p起的n项作为末节点依次插入
{
	init();//初始化
	while (n-->0)
	{
		insertAsLast(p->val);
		p = p->next;
	}
}

template<typename T>
Node<T>* LinkedList<T>::selectMax(Node<T>* p, int n)
{
	//Node<T>* max = p;
	//for (int i = 0;i <n;i++)
	//{
	//	p = p->next;
	//	if (p->val > max->val)
	//		max = p;
	//}
	//return max;

		if (!p || n <= 0) return nullptr;

		Node<T>* maxNode = p;
		Node<T>* current = p;

		for (int i = 0; i < n && current != nullptr; ++i) {
			if (current->val > maxNode->val) {
				maxNode = current;
			}
			current = current->next;
		}
		return maxNode;
}

template<typename T>
inline void LinkedList<T>::merge(Node<T>*& p, int n, LinkedList<T>& L, Node<T>* q, int m)
{


}

template<typename T>
void LinkedList<T>::selectionSort(Node<T>* p, int n)
{
		Node<T>* head = p->prev;Node<T>* tail= p;
		for (int i = 0;i < n;i++)
			tail = tail->next;
		while (1 < n)
		{
			insertBefore(tail, remove(selectMax(head->next, n)));
			tail = tail->prev;
			n--;
		}
}

template<typename T>
void LinkedList<T>::insertionSort(Node<T>* p, int n)//插入排序
{
	if (_size < 2)return;
	Node<T>* head = p;
	Node<T>* tail = head->next;
	for(int i=0;i<n;i++)
	{
		int k = i;
		for (int j = 0;j < k;j++)
			tail = head->next;
		Node<T>* scan = tail;
		while (scan!=head)
		{
			scan = scan->prev;
			if (tail->val < scan->val)
			{
				insertBefore(scan, tail->val);
			}
		}
		remove(tail);
	}
}

template<typename T>
inline void LinkedList<T>::print() const
{
	Node<T>* p = first();
	for(int i=0;i<_size;i++)
	{
		cout << p->val << " ";
		p=p->next;
	}
	cout << endl;
}

template<typename T>
Node<T>* LinkedList<T>::operator[](int r) const
{
	Node<T>*p = first();//从首节点出发
	for (int i = 0;i < r;i++)
	{
		p = p->next;
	}
	return p;//此时p已经指向r节点中的数据了，应该返回指针中的数据
}

template<typename T>
inline void LinkedList<T>::getMax(Node<T>* p, int n)
{
	selectMax(p, n);
}

template<typename T>
inline Node<T>* LinkedList<T>::find(T const& e) const
{
	Node<T>* p = first();//从首节点出发
	int i = 0;
	while (i < _size)//从首节点顺下来，找到e
	{
		p = p->next;
		if (e == p)
			return p;
	}
	return nullptr;//遍历到链表的最后都没有找到就返回空指针，表示错误
}

template<typename T>
Node<T>* LinkedList<T>::find(T const& e, int n, Node<T>* p) const//p的n个前驱
{
	while (n > 0)
	{
		if (e == (p = p->prev))
			return p;
	}
	return nullptr;
}

template<typename T>
inline Node<T>* LinkedList<T>::insertAsFirst(T const& e)
{
	//新建节点
	Node<T>* f = first();
	Node<T>* p = new Node<T>(e,header,f);
	//建立链接
	header->next = p;
	f->prev = p;
	f = p;
	_size++;
	return p;
}

template<typename T>
inline Node<T>* LinkedList<T>::insertAsLast(T const& e)
{
	Node<T>* end = last();
	Node<T>* p = new Node<T>(e, end, trailer);
	end->next = p;
	trailer->prev = p;
	end = p;
	_size++;
	return p;
}

template<typename T>
Node<T>* LinkedList<T>::insertBefore(Node<T>* p, T const& e)//前插算法
{
	Node<T>* oldPrev = p->prev;        
	Node<T>* q = new Node<T>(e, oldPrev, p); 
	if (oldPrev != nullptr) {
		oldPrev->next = q;  
	}
	p->prev = q;  
	_size++;
	return q;
}

template<typename T>
inline Node<T>* LinkedList<T>::insertAfter(Node<T>* p, T const& e)//在节点后插入
{
	//生成新节点
	Node<T>* q = new LinkedList(e, this, next);
	//建立链接
	next->prev = q;
	next = q;
	return q;
}

template<typename T>
T LinkedList<T>::remove(Node<T>* p)
{
	T e = p->val;
	p->prev->next = p->next;//通俗理解，将p的前驱的后继改为p的后继
	p->next->prev = p->prev;//将p的后继的前驱改为p的后继
	_size--;
	delete p;
	return e;
}

template<typename T>
inline void LinkedList<T>::sort(Node<T>* p, int n)
{
	insertionSort(p,n);
}
