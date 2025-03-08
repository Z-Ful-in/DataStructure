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

