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
	void bubbleSort(Node<T>* p, int n); // 对从p开始连续的n个节点冒泡排序
	void quickSort(Node<T>* p, int n); // 对从p开始连续的n个节点快速排序

public:
	LinkedList() { init();}; // 默认构造函数
	LinkedList(int size); // 生成指定大小的链表, 每个节点的值为0
	LinkedList(LinkedList<T> const& L); // 复制构造函数
	LinkedList(LinkedList<T> const& L, int n); // 复制构造函数, 复制L的从头开始的n个节点

	~LinkedList(); // 析构函数

	int size() const;// 返回链表的大小
	bool empty() const; // 判断链表是否为空

	Node<T>* first() const { return header->next; } // 返回首节点
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
	
	Node<T>*& operator[](int r) const; // 重载下标操作符, 在链表中像Vector一样使用下标访问元素

	void getMax(Node<T>* p, int n);
};

template<typename T>
LinkedList<T>::LinkedList(int size)
{
	init();  // 初始化哨兵节点  
	_size = size;//更新链表大小

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
	Node<T>* p = L.header->next;
	while (p!=nullptr)
	{
		insertAsLast(p->val);
		p = p->next;
	}
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T> const& L, int n)
{
	//检查传入参数是否正确
	if (n <= 0 || !L)return;
	//初始化哨兵节点
	init();
	Node<T>* p = L.header->next;
	for (int i = 0;i < n;i++)
	{
		insertAsLast(p->val);
		p = p->next;
	}
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
	if (header->next == trailer && header->prev == trailer)
		return true;
	else
		return false;
}

template<typename T>
void LinkedList<T>::init()//初始化
{
	header = new Node<T>;//ai改进意见，增加分配内存失败的改进
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
		Node<T>* next = p->next;//加*是因为他是指针
		remove(p);
		p = next;
		count++;
	}
	return count;
}

template<typename T>
void LinkedList<T>::copyNodes(Node<T>* p, int n)//将自p起的n项作为末节点依次插入
{
	if (!p || n <= 0)return;//检查参数是否有效
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

		if (!p || n <= 0) return nullptr;//检查参数是否有效

		Node<T>* maxNode = p;//将p先定义为最大节点
		Node<T>* current = p;//遍历链表的节点

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
inline void LinkedList<T>::mergeSort(Node<T>*& p, int n)
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
	//if (n < 2)return;
	// Node<T>* current=p->next;
	// for(int i=0;i<n;i++)
	// {
	// 
	//}

	if (n < 2) return; // 如果节点数小于2，则无需排序——right

	Node<T>* current = p->next; // 从第二个节点开始排序
	for (int i = 1; i < n; ++i) {
		T value = current->val;
		Node<T>* prev = current->prev;
		Node<T>* next = current->next;

		// 在已排序部分中找到插入位置
		while (prev != header && prev->val > value) {
			prev = prev->prev;
		}

		// 如果需要移动节点
		if (prev->next != current) {
			// 从链表中移除当前节点
			current->prev->next = next;
			if (next != nullptr) {
				next->prev = current->prev;
			}

			// 插入到正确位置
			current->next = prev->next;
			current->prev = prev;
			prev->next->prev = current;
			prev->next = current;
		}

		// 移动到下一个节点
		current = next;
	}
}

template<typename T>
inline void LinkedList<T>::bubbleSort(Node<T>* p, int n)
{
	if (n < 2) return; 

	for (int i = 0; i < n - 1; ++i) {
		Node<T>* current = p;
		Node<T>* next = current->next;

		for (int j = 0; j < n - 1 - i; ++j) {
			if (current->val > next->val) {
				// 交换节点的值
				T temp = current->val;
				current->val = next->val;
				next->val = temp;
			}
			current = next;
			next = next->next;
		}
	}
}

template<typename T>
inline void LinkedList<T>::quickSort(Node<T>* p, int n)
{
	//if (n < 2) return; // 如果节点数小于2，则无需排序

	//// 选择基准
	//LinkedList<T> left;//左子链表
	//LinkedList<T> right;//右子链表
	//Node<T>* firstLeft = left.header->next;//左首节点
	//Node<T>* firstRight = right.header->prev;//右首节点
	//Node<T>* pivot = p;//选择头节点作为基准
	//Node<T>* con = p->next;
	//int countLeft = 0;//记录左长度
	//int countRight = 0;//记录右长度
	//for (int i = 1;i < n;i++)
	//{
	//	
	//	if (con->val >= pivot->val)
	//	{
	//		firstLeft= con;
	//		firstLeft = firstLeft->next;
	//		countLeft++;
	//	}
	//	else
	//	{
	//		firstRight= con;
	//		firstRight= firstRight->next;
	//		countRight++;
	//	}
	//	con = con->next;
	//}
	//quickSort(left.header->next,countLeft);
	//quickSort(right.header->next,countRight);

	//clear();
	//this->header = left.header;
	//Node<T>* t = this->header->next;
	//for (int j = 0;j < countLeft;j++)
	//{
	//	t = t->next;
	//}
	//t->next = right.header->next;




		//if (n < 2) return;


		//Node<T>* pivot = p;
		//Node<T>* curr = p->next;
		//Node<T>* left_head = nullptr, * left_tail = nullptr;
		//Node<T>* right_head = nullptr, * right_tail = nullptr;
		//int left_count = 0, right_count = 0;


		//while (curr != nullptr && --n > 0) {
		//	Node<T>* next = curr->next;
		//	if (curr->val < pivot->val) {
		//		if (!left_head) left_head = left_tail = curr;
		//		else left_tail = left_tail->next = curr;
		//		left_count++;
		//	}
		//	else {
		//		if (!right_head) right_head = right_tail = curr;
		//		else right_tail = right_tail->next = curr;
		//		right_count++;
		//	}
		//	curr->next = nullptr;
		//	curr = next;
		//}


		//if (left_head) quickSort(left_head, left_count);
		//if (right_head) quickSort(right_head, right_count);


		//if (left_head) {
		//	p = left_head;
		//	while (left_head->next) left_head = left_head->next;
		//	left_head->next = pivot;
		//}
		//else {
		//	p = pivot;
		//}
		//pivot->next = right_head;


		//header->next = p;


			if (n < 2) return;

			// 选择头节点为基准
			Node<T>* pivot = p;
			Node<T>* curr = p->next;
			Node<T>* left_head = nullptr, * left_tail = nullptr;
			Node<T>* right_head = nullptr, * right_tail = nullptr;
			int left_count = 0, right_count = 0;

			// 拆分链表（左：< pivot，右：>= pivot）
			while (curr != nullptr && --n > 0) {
				Node<T>* next = curr->next;
				if (curr->val < pivot->val) {
					if (!left_head) left_head = left_tail = curr;
					else left_tail = left_tail->next = curr;
					left_count++;
				}
				else {
					if (!right_head) right_head = right_tail = curr;
					else right_tail = right_tail->next = curr;
					right_count++;
				}
				curr->next = nullptr; // 断开当前节点与原链表的连接
				curr = next;
			}

			// 递归排序子链表
			if (left_head) quickSort(left_head, left_count);
			if (right_head) quickSort(right_head, right_count);

			// 合并左 + pivot + 右
			if (left_head) {
				p = left_head;
				while (left_head->next) left_head = left_head->next;
				left_head->next = pivot;
			}
			else {
				p = pivot;
			}

			pivot->next = right_head;

			// 更新链表头节点
			if (header) {
				header->next = p;
			}
}

template<typename T>
void LinkedList<T>::print() const
{
	if (empty())
	{
		cout << "链表为空" << endl;
		return;
	}
	Node<T>* p = first();
	while (p != trailer)
	{
		cout << p->val << "  ";
		p = p->next;
	}
	cout << endl;
}

template<typename T>
Node<T>*& LinkedList<T>::operator[](int r) const
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
Node<T>* LinkedList<T>::find(T const& e) const
{
	Node<T>* p = first();//从首节点出发
	while (p!=trailer)//从首节点顺下来，找到e
	{
		if (e == p)
			return p;
		p = p->next;
	}
	return nullptr;//遍历到链表的最后都没有找到就返回空指针，表示错误
}

template<typename T>
Node<T>* LinkedList<T>::find(T const& e, int n, Node<T>* p) const//p的n个前驱，如果说n在p前面就是p的前驱，如果n在p后面就是p的后继
{
	//检查传入的参数是否正确
	if (n <= 0 || p == nullptr)return nullptr;
	while (n-->0&&p!=header)
	{
		if (e == p->val)
			return p;
		p = p->prev;
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
	if (p == nullptr)return nullptr;
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
	Node<T>* oldnode = p->next;
	//生成新节点
	Node<T>* q = new Node<T>(e, p, oldnode);
	//建立链接
	p->next->prev = q;
	p->next= q;
	_size++;
	return q;
}

template<typename T>
T LinkedList<T>::remove(Node<T>* p)
{
	T e = p->val;//由于要返回删除值所以提前保存
	p->prev->next = p->next;//通俗理解，将p的前驱的后继改为p的后继
	p->next->prev = p->prev;//将p的后继的前驱改为p的后继
	_size--;
	delete p;
	return e;
}

template<typename T>
inline void LinkedList<T>::sort(Node<T>* p, int n)
{
	quickSort(p,n);
}
