#pragma once
#include <iostream>

#define DEFAULT_CAPACITY 10 // Ĭ�ϵ�vector�ĳ�ʼ��С

template <typename T>
class Vector{
protected:
	int _size; // vector����װ���Ԫ�ظ���
	T* _elem; // ָ��Ԫ�������ָ��
	int _capacity; // vector������

	int getMax(int lo, int hi)const {
		// �ҵ�[lo, hi)�е����Ԫ�ص���
		int max = lo;
		for (int i = lo + 1; i < hi; i++) {
			if (_elem[max] < _elem[i]) {
				max = i;
			}
		}
		return max;
	}

	void selectionSort(int lo, int hi); // ѡ������
	void insertSort(int lo, int hi); // ��������
	void bubbleSort(int lo, int hi); // ð������
	void mergeSort(int lo, int hi); // �鲢����
	void quickSort(int lo, int hi); // ��������

	void copyFrom(T const* A, int lo, int hi); // ������������A[lo, hi): ��ͷ����β
	void shrink(); // �ռ����ʱѹ��
	void expand(); // �ռ䲻��ʱ����
	void swap(T& a, T& b)const {
		T tmp = a;
		a = b;
		b = tmp;
	}
public:
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T val = 0) { //���캯������ʼ��vector����������ʼֵ
		_elem = new T[_capacity = capacity];
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

	void print()const {
		for (int i = 0; i < _size; i++) {
			std::cout << _elem[i] << " ";
		}
		std::cout << std::endl;
	}
};

template<typename T>
void Vector<T>::selectionSort(int lo, int hi){
	// �Ӻ���ǰ����Vector�� ÿһ�ΰ�(��lo �� i��)���Ԫ�غ����һ��Ԫ(i)�ؽ���
	for (int i = hi - 1; i >= lo; i--) {
		swap(_elem[i], _elem[getMax(lo, i + 1)]);
	} // O(n^2)
}

template<typename T>
void Vector<T>::sort(int lo, int hi)
{
	insertSort(0, _size);
}

template<typename T>
void Vector<T>::insertSort(int lo, int hi){
	// ��ǰ�������Vector�� ÿһ�ΰ�i���뵽ǰ�������������
	for (int i = lo + 1; i < hi; i++) {
		T tmp = _elem[i];
		int j = i - 1;
		while (j >= lo && tmp < _elem[j]) {
			_elem[j + 1] = _elem[j];
			j--;
		}
		_elem[j + 1] = tmp;
	} // O(n^2)
}

template<typename T>
inline void Vector<T>::bubbleSort(int lo, int hi){
	// ��ǰ�������Vector�� ÿһ�ΰ�����Ԫ��ð�ݵ����
	for (int i = lo; i < hi; i++) {
		for (int j = lo; j < hi - i - 1; j++) {
			if (_elem[j] > _elem[j + 1]) {
				swap(_elem[j], _elem[j + 1]);
			}
		}
	}
}

template<typename T>
void Vector<T>::mergeSort(int lo, int hi){
	if (hi - lo < 2) return;
	int middle = (hi + lo) / 2; // merge(int *a, int *b) a[lo, middle) b[middle, hi)
	//merge��һ�������� ���ںϲ�������������
	mergeSort(lo, middle); // n/2
	mergeSort(middle, hi); // n/2
	// ʮ������ ����һ�ź������Ⱥϲ��ˣ� �ͻ�ϲ���һ�źͶ���λ���ϣ� �ͻ�Ѷ��ŵ���ֵ�����ǣ� �ͻ�Ӱ����ŵĺϲ�

	// ���� lo , middle���� middle��hi����
	T* temp0 = elem + lo; // ԭ������ʼ��
	T* temp2 = elem + (int)((hi + lo) / 2); //ԭ�����м��
	T* temp1 = new T[(int)(hi - lo) / 2]; //�����飬��С��ԭ�����С��һ��
	for (int i = 0; i < (hi - lo) / 2; temp1[i] = temp0[i++]);  // ����ԭ�����ǰ�벿��
	int p = 0, q = 0; // �����±꣬һ�����ڱ������ߣ� һ�����ڱ����Ұ��
	for (int i = lo; i < hi; i++) {
		if ((q == ceil((double)(hi - lo) / 2)) || ((p < (int)(hi - lo) / 2) && (temp1[p] < temp2[q]))) {
			elem[i] = temp1[p++];
		}
		else {
			elem[i] = temp2[q++];
		}
	}
	delete[] temp1;
	return;
}

template<typename T>
void Vector<T>::quickSort(int lo, int hi){
	if (hi - lo < 2) return;
	T number = _elem[lo];
	T* temp = new T[hi - lo];
	int startIndex = 0, endIndex = hi - lo;
	for(int i = lo + 1; i < hi; i++) {
		if (_elem[i] < number) {
			temp[startIndex++] = _elem[i];
		}
		else {
			temp[--endIndex] = _elem[i];
		}
	}
	temp[startIndex] = number;
	quickSort(lo, startIndex);
	quickSort(startIndex + 1, hi);
}
// 10,21,4,23,12,1,2,6,8
//     4 1 2 6 8         10  12 23 21



template<typename T>
inline void Vector<T>::copyFrom(T const* A, int lo, int hi){
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi) {
		_elem[_size++] = A[lo++];
	}
}


// 3 4 6 7 5 1
// 1 2 3 4 5 6