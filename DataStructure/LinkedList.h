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

