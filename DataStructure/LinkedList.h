#pragma once
#include "Node.h"
template <typename T>
class LinkedList{
protected:
	int _size;
	Node<T>* header;
	Node<T>* trailer;

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
	LinkedList() { init()  }; // Ĭ�Ϲ��캯��
	LinkedList(int size); // ����ָ����С������, ÿ���ڵ��ֵΪ0
	LinkedList(LinkedList<T> const& L); // ���ƹ��캯��
	LinkedList(LinkedList<T> const& L, int n); // ���ƹ��캯��, ����L�Ĵ�ͷ��ʼ��n���ڵ�

	~LinkedList(); // ��������

	int size() const;// ��������Ĵ�С
	bool empty() const; // �ж������Ƿ�Ϊ��

	Node<T>* first() const { return header->next; } // �����׽ڵ�
	Node<T>* last(); // ����β�ڵ�

	Node<T>* find(T const& e) const; // ����Ԫ��e
	Node<T>* find(T const& e, int n, Node<T>* p) const; // �ӽڵ�p��ʼ����Ԫ��e

	Node<T>* insertAsFirst(T const& e); // ���׽ڵ�֮ǰ����Ԫ��e
	Node<T>* insertAsLast(T const& e); // ��β�ڵ�֮�����Ԫ��e
	Node<T>* insertBefore(Node<T>* p, T const& e); // �ڽڵ�p֮ǰ����Ԫ��e
	Node<T>* insertAfter(Node<T>* p, T const& e); // �ڽڵ�p֮�����Ԫ��e

	T remove(Node<T>* p); // ɾ���ڵ�p

	void sort();

	void print() const;
	
	Node<T>* operator[](int r) const; // �����±������, ����������Vectorһ��ʹ���±����Ԫ��

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
	Node<T>*p = first();//���׽ڵ����
	while (0 < r--)//����ֻ��һ����˳����
		p = p->next;
	return p;//��ʱp�Ѿ�ָ��r�ڵ��е������ˣ�Ӧ�÷���ָ���е�����
}

template<typename T>
inline Node<T>* LinkedList<T>::find(T const& e) const
{
	Node<T>* p = first();//���׽ڵ����
	int i = 0;
	while (i < n)//���׽ڵ�˳�������ҵ�e
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
	Node<T>* p = new LinkedList(e, header, first);
	//��������
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
Node<T>* LinkedList<T>::insertBefore(Node<T>* p, T const& e)//ǰ���㷨
{
	//��������һ���ڵ�,�½ڵ�ǰ��Ϊthis��prev��������ΪҪ����Ľڵ�this
	Node<T>* q = new LinkedList(e, prev, this);
	//��������
	prev->next = q;//
	prev = q;//��ʱq�ڵ��Ѿ����this����ǰ��
	return q;//�����½ڵ�
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
