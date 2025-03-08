#pragma once
#include<iostream>
#define DEFAULT_CAPACITY 10 // Ĭ�ϵ�vector�ĳ�ʼ��С
using namespace std;
template <typename T>
class Vector{
protected:
	int _size; // vector����װ���Ԫ�ظ���
	T* _elem; // ָ��Ԫ�������ָ��
	int _capacity; // vector������

	int getMax(int lo,int hi)//����ֵ����
	{
		int max = lo;
		for (int i = lo+1;i <hi;i++)
		{
			if (_elem[i] > _elem[max])
				max = i;
		}
		return max;
	}

	void swap(T& a, T& b)
	{
		T temp;
		temp = a;
		a = b;
		b = temp;
	}
	
	void copyFrom(T const* A, int lo, int hi); // ������������A[lo, hi): ��ͷ����β
	void shrink(); // �ռ����ʱѹ��
	void expand(); // �ռ䲻��ʱ����
public:
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T val = 0);

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

	void print()const
	{
		for (int i = 0;i < _size;i++)
		{
			cout  << _elem[i]<<" ";

		}
		cout << endl;
	}

};

template<typename T>
void Vector<T>::copyFrom(T const* A, int lo, int hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi) {
		_elem[_size++] = A[lo++];
	}
}

template<typename T>
inline void Vector<T>::selectSort(int lo, int hi)
{
	for (int k = hi-1;k>lo;k--)
	{
		swap(_elem[k],_elem[getMax(lo, k+1)]);
	}
}
template<typename T>
void Vector<T>::insertSort(int lo, int hi)
{
	if (hi-lo<2)
		return;
	for (int i = lo+1;i < hi;i++)
	{
		T temp =_elem[i];
		int j=0;
		for (j = i-1;j >=lo&&_elem[j]>temp;j--)
		_elem[j+1] = _elem[j];
		_elem[j + 1] = temp;
	}
}
template<typename T>
inline void Vector<T>::bubbleSort(int lo, int hi)
{
	for (int j = lo;j < hi;j++)
	{
		for (int i = lo;i < hi-j-1;i++)
		{
			if (_elem[i] > _elem[i + 1])
			{
				swap(_elem[i], _elem[i + 1]);
			}
		}
	}
}
template<typename T>
inline void Vector<T>::mergeSort(int lo, int hi)
{
	if (hi - lo < 2) return;
	int middle = (lo + hi) / 2;
	mergeSort(lo, middle);
	mergeSort(middle, hi);

	//merge
    // �������Ұ���
	int leftLen = middle - lo;
	int rightLen = hi - middle;
	T* temp1 = new T[leftLen];
	T* temp2 = new T[rightLen];
	for (int i = 0; i < leftLen; i++) temp1[i] = _elem[lo + i];
	for (int j = 0; j < rightLen; j++) temp2[j] = _elem[middle + j];

	// �ϲ��߼�
	int p = 0, q = 0, idx = lo;
	while (p < leftLen && q < rightLen) 
	{
		_elem[idx++] = (temp1[p] <= temp2[q]) ? temp1[p++] : temp2[q++];
	}
	while (p < leftLen) _elem[idx++] = temp1[p++];
	while (q < rightLen) _elem[idx++] = temp2[q++];

	delete[] temp1;
	delete[] temp2;
}
template<typename T>
inline void Vector<T>::quickSort(int lo, int hi)
{
	if (hi - lo < 2)return;
	//ѡ���׼
	int sta = _elem[lo];
	T *temp = new T[hi - lo];
	int begin = 0, end = hi - lo;
	for (int i = lo+1;i < hi;i++)
	{
		if (_elem[i] > sta)
		{
			temp[--end] = _elem[i];
		}
		else
		{
			temp[begin++] = _elem[i];
		}

	}
	temp[begin] = sta;
	for (int k = 0;k < hi-lo;k++)
	{
		_elem[lo+k] = temp[k];
	}
	quickSort(lo, lo+begin);
	quickSort(lo+begin+1, hi);
	
	delete[] temp;
}
// 58,56,23,7,1,5,9,3,87,60
// 

template<typename T>
void Vector<T>::sort(int lo,int hi)
{
	quickSort(lo, hi);
}

template<typename T>
inline Vector<T>::Vector(T const* A, int n)
{
	copyFrom(A, 0, n);
}
