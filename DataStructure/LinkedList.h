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

	void init(); // ���캯��ͨ��init��ʼ������
	int clear(); // ������� ����ɾ���Ľڵ���
	void copyNodes(Node<T>* p, int n); // ������������λ��p���n��
	Node<T>* selectMax(Node<T>* p, int n); // ��p��ʼ������n���ڵ���ѡ�������

	void merge(Node<T>*& p, int n, LinkedList<T>& L, Node<T>* q, int m); // �鲢������������
	void mergeSort(Node<T>*& p, int n); // �Դ�p��ʼ������n���ڵ�鲢����
	void selectionSort(Node<T>* p, int n); // �Դ�p��ʼ������n���ڵ�ѡ������
	void insertionSort(Node<T>* p, int n); // �Դ�p��ʼ������n���ڵ��������
	void bubbleSord(Node<T>* p, int n); // �Դ�p��ʼ������n���ڵ�ð������
	void quickSort(Node<T>* p, int n); // �Դ�p��ʼ������n���ڵ��������

public:
	LinkedList() { init();}; // Ĭ�Ϲ��캯��
	LinkedList(int size); // ����ָ����С������, ÿ���ڵ��ֵΪ0
	LinkedList(LinkedList<T> const& L); // ���ƹ��캯��
	LinkedList(LinkedList<T> const& L, int n); // ���ƹ��캯��, ����L�Ĵ�ͷ��ʼ��n���ڵ�

	~LinkedList(); // ��������

	int size() const;// ��������Ĵ�С
	bool empty() const; // �ж������Ƿ�Ϊ��

	Node<T>*& first() const { return header->next; } // �����׽ڵ�
	Node<T>* last() const { return trailer->prev; }; // ����β�ڵ�

	Node<T>* find(T const& e) const; // ����Ԫ��e
	Node<T>* find(T const& e, int n, Node<T>* p) const; // �ӽڵ�p��ʼ����Ԫ��e

	Node<T>* insertAsFirst(T const& e); // ���׽ڵ�֮ǰ����Ԫ��e
	Node<T>* insertAsLast(T const& e); // ��β�ڵ�֮�����Ԫ��e
	Node<T>* insertBefore(Node<T>* p, T const& e); // �ڽڵ�p֮ǰ����Ԫ��e
	Node<T>* insertAfter(Node<T>* p, T const& e); // �ڽڵ�p֮�����Ԫ��e

	T remove(Node<T>* p); // ɾ���ڵ�p

	void sort(Node<T>* p, int n);

	void print() const;
	
	Node<T>* operator[](int r) const; // �����±������, ����������Vectorһ��ʹ���±����Ԫ��

	void getMax(Node<T>* p, int n);
};

template<typename T>
LinkedList<T>::LinkedList(int size)
{
	init();  // ��ʼ���ڱ��ڵ�  
	_size = size;

	Node<T>* current = header;
	for (int i = 0; i < _size; ++i) {
		// �����½ڵ㲢��ʼ������  
		Node<T>* newNode = new Node<T>();
		newNode->val = 1;  // Ĭ�ϳ�ʼ�����ݣ�����������������  

		// ˫������ָ��ά��  
		newNode->prev = current;
		newNode->next = trailer;
		current->next = newNode;
		trailer->prev = newNode;

		current = newNode;  // �ƶ�ָ�뵽�½ڵ�  
	}
}

template<typename T>
inline LinkedList<T>::LinkedList(LinkedList<T> const& L)
{
	init();//��ʼ��
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
void LinkedList<T>::init()//��ʼ��
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
	int count = 0;//��¼ɾ���Ľڵ���
	for (int i = 0;i < _size;i++)
	{
		remove(p);
		_size--;
		count++;
	}
	return count;
}

template<typename T>
void LinkedList<T>::copyNodes(Node<T>* p, int n)//����p���n����Ϊĩ�ڵ����β���
{
	init();//��ʼ��
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
void LinkedList<T>::insertionSort(Node<T>* p, int n)//��������
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
	Node<T>*p = first();//���׽ڵ����
	for (int i = 0;i < r;i++)
	{
		p = p->next;
	}
	return p;//��ʱp�Ѿ�ָ��r�ڵ��е������ˣ�Ӧ�÷���ָ���е�����
}

template<typename T>
inline void LinkedList<T>::getMax(Node<T>* p, int n)
{
	selectMax(p, n);
}

template<typename T>
inline Node<T>* LinkedList<T>::find(T const& e) const
{
	Node<T>* p = first();//���׽ڵ����
	int i = 0;
	while (i < _size)//���׽ڵ�˳�������ҵ�e
	{
		p = p->next;
		if (e == p)
			return p;
	}
	return nullptr;//��������������û���ҵ��ͷ��ؿ�ָ�룬��ʾ����
}

template<typename T>
Node<T>* LinkedList<T>::find(T const& e, int n, Node<T>* p) const//p��n��ǰ��
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
	//�½��ڵ�
	Node<T>* f = first();
	Node<T>* p = new Node<T>(e,header,f);
	//��������
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
Node<T>* LinkedList<T>::insertBefore(Node<T>* p, T const& e)//ǰ���㷨
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
inline Node<T>* LinkedList<T>::insertAfter(Node<T>* p, T const& e)//�ڽڵ�����
{
	//�����½ڵ�
	Node<T>* q = new LinkedList(e, this, next);
	//��������
	next->prev = q;
	next = q;
	return q;
}

template<typename T>
T LinkedList<T>::remove(Node<T>* p)
{
	T e = p->val;
	p->prev->next = p->next;//ͨ����⣬��p��ǰ���ĺ�̸�Ϊp�ĺ��
	p->next->prev = p->prev;//��p�ĺ�̵�ǰ����Ϊp�ĺ��
	_size--;
	delete p;
	return e;
}

template<typename T>
inline void LinkedList<T>::sort(Node<T>* p, int n)
{
	insertionSort(p,n);
}
