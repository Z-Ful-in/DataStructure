#pragma once

#define DEFAULT_CAPACITY 10 // Ĭ�ϵ�vector�ĳ�ʼ��С

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

	Vector(T const*A, int n) { copyFrom(A, 0, n); } // ������������
	Vector(T const*A, int lo, int hi) { copyFrom(A, lo, hi); } // ������������
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } // ����vector����
	Vector(Vector<T> const& V, int lo, int hi) { copyFrom(V._elem, lo, hi); } // ����vector����

	~Vector() { delete [] _elem; } // ��������

	int size() const { return _size; }
	bool empty()const; //�пպ���
	int disordered()const; //�ж������Ƿ�����

	//�����ǻ��������� ��������������� �����Ĳ�������ɾ���
	int find(T const& e) const { return find(e, 0, _size); } //���������������
	int find(T const& e, int lo, int hi) const; //���������������
	int search(T const& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); } //���������������
	int search(T const& e, int lo, int hi) const; //���������������

	// ��д���ʽӿ�
	T& operator[](int r) const; //�����±������
	Vector<T>& operator=(Vector<T> const&); //���ظ�ֵ������
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

