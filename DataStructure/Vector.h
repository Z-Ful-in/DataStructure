#pragma once

#define DEFAULT_CAPACITY 10 // Ĭ�ϵ�vector�ĳ�ʼ��С
using namespace std;
template <typename T>
class Vector{
protected:
	int _size; // vector����װ���Ԫ�ظ���
	T* _elem; // ָ��Ԫ�������ָ��
	int _capacity; // vector������
	
	void copyFrom(T const* A, int lo, int hi); // ������������A[lo, hi): ��ͷ����β
	void shrink(); // �ռ����ʱѹ��
	void expand(); // �ռ䲻��ʱ����
public:
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T val = 0) { //���캯������ʼ��vector����������ʼֵ
		elem = new T[_capacity = capacity];
		for(_size = 0; _size < size; _elem[_size++] = val);
	}

	// ���еĹ��캯������ʹ��copyFrom���߼���ʵ��
	Vector(T const* A, int n); // ������������
	Vector(T const* A, int lo, int hi);  // ������������
	Vector(Vector<T> const& V);// ����vector����
	Vector(Vector<T> const& V, int lo, int hi);// ����vector����

	~Vector() { delete [] _elem; } // ��������

	int size() const { return _size; }
	bool empty()const; //�пպ���
	int disordered()const; //�ж������Ƿ�����

	//�����ǻ��������� ��������������� �����Ĳ�������ɾ���
	int find(T const& e) const;//���������������, ����ͨ������findʵ��
	int find(T const& e, int lo, int hi) const; //���������������
	int search(T const& e) const; //���������������, ����ͨ������searchʵ��
	int search(T const& e, int lo, int hi) const; //���������������

	// ��д���ʽӿ�
	T& operator[](int r) const; //�����±������
	Vector<T>& operator=(Vector<T> const&A); //���ظ�ֵ������
	T remove(int r); //ɾ����Ϊr��Ԫ��
	int remove(int lo, int hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
	int insert(int r, T const& e); //����Ԫ��
	int insert(T const& e) { return insert(_size, e); } //Ĭ�ϲ��뵽ĩβ
	void sort(int lo, int hi); //��[lo, hi)����
	void sort() { sort(0, _size); } //��������
	void unsort(int lo, int hi); //��[lo, hi)����
	void unsort() { unsort(0, _size); } //��������
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��

	// ����
	void traverse(void(*)(T&)); //ͨ������ָ�����
	template <typename VST> void traverse(VST&); //ͨ��ģ�����

};

