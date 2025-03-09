#pragma once
#include "Node.h"
template <typename T>
class LinkedList{
protected:
	int _size;
	Node<T>* header;
	Node<T>* trailer;

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
	LinkedList() { init()  }; // 默认构造函数
	LinkedList(int size); // 生成指定大小的链表, 每个节点的值为0
	LinkedList(LinkedList<T> const& L); // 复制构造函数
	LinkedList(LinkedList<T> const& L, int n); // 复制构造函数, 复制L的从头开始的n个节点

	~LinkedList(); // 析构函数

	int size() const;// 返回链表的大小
	bool empty() const; // 判断链表是否为空

	Node<T>* first() const { return header->next; } // 返回首节点
	Node<T>* last(); // 返回尾节点

	Node<T>* find(T const& e) const; // 查找元素e
	Node<T>* find(T const& e, int n, Node<T>* p) const; // 从节点p开始查找元素e

	Node<T>* insertAsFirst(T const& e); // 在首节点之前插入元素e
	Node<T>* insertAsLast(T const& e); // 在尾节点之后插入元素e
	Node<T>* insertBefore(Node<T>* p, T const& e); // 在节点p之前插入元素e
	Node<T>* insertAfter(Node<T>* p, T const& e); // 在节点p之后插入元素e

	T remove(Node<T>* p); // 删除节点p

	void sort();

	void print() const;
	
	Node<T>* operator[](int r) const; // 重载下标操作符, 在链表中像Vector一样使用下标访问元素

};

template<typename T>
LinkedList<T>::LinkedList(int size)
{
	init();
	for (int i = 0;i < size;i++)
	{

	}
}

template<typename T>
inline void LinkedList<T>::init()
{
	header = new LinkedList<T>;
	trailer = new LinkedList<T>;
	header->next = trailer;
	header->prev = NULL;
	trailer->next = NULL;
	trailer->prev = header;
	_size = 0;
}

template<typename T>
Node<T>* LinkedList<T>::operator[](int r) const
{
	Node<T>*p = first();//从首节点出发
	while (0 < r--)//链表只能一个个顺下来
		p = p->next;
	return p;//此时p已经指向r节点中的数据了，应该返回指针中的数据
}

template<typename T>
inline Node<T>* LinkedList<T>::find(T const& e) const
{
	Node<T>* p = first();//从首节点出发
	int i = 0;
	while (i < n)//从首节点顺下来，找到e
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
	Node<T>* p = new LinkedList(e, header, first);
	//建立链接
	header->next = p;
	first->prev = p;
	first = p;
	return p;
}

template<typename T>
inline Node<T>* LinkedList<T>::insertAsLast(T const& e)
{
	Node<T>* p = new LinkedList(e, last, trailer);
	last->next = p;
	trailer->prev = p;
	last = p;
	return p;
}

template<typename T>
Node<T>* LinkedList<T>::insertBefore(Node<T>* p, T const& e)//前插算法
{
	//首先生成一个节点,新节点前驱为this的prev，后驱变为要插入的节点this
	Node<T>* q = new LinkedList(e, prev, this);
	//建立链接
	prev->next = q;//
	prev = q;//此时q节点已经变成this的新前驱
	return q;//返回新节点
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
