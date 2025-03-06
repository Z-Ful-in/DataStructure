#pragma once
#include <iostream>

#define DEFAULT_CAPACITY 10 // 默认的vector的初始大小

template <typename T>
class Vector{
protected:
	int _size; // vector中已装填的元素个数
	T* _elem; // 指向元素数组的指针
	int _capacity; // vector的容量

	int getMax(int lo, int hi)const {
		// 找到[lo, hi)中的最大元素的秩
		int max = lo;
		for (int i = lo + 1; i < hi; i++) {
			if (_elem[max] < _elem[i]) {
				max = i;
			}
		}
		return max;
	}

	void selectionSort(int lo, int hi); // 选择排序
	void insertSort(int lo, int hi); // 插入排序
	void bubbleSort(int lo, int hi); // 冒泡排序
	void mergeSort(int lo, int hi); // 归并排序
	void quickSort(int lo, int hi); // 快速排序

	void copyFrom(T const* A, int lo, int hi); // 复制数组区间A[lo, hi): 包头不包尾
	void shrink(); // 空间过大时压缩
	void expand(); // 空间不足时扩容
	void swap(T& a, T& b)const {
		T tmp = a;
		a = b;
		b = tmp;
	}
public:
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T val = 0) { //构造函数，初始化vector的容量，初始值
		_elem = new T[_capacity = capacity];
		for(_size = 0; _size < size; _elem[_size++] = val);
	}

	Vector(T const*A, int n) { copyFrom(A, 0, n); } // 复制数组整体
	Vector(T const*A, int lo, int hi) { copyFrom(A, lo, hi); } // 复制数组区间
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } // 复制vector整体
	Vector(Vector<T> const& V, int lo, int hi) { copyFrom(V._elem, lo, hi); } // 复制vector区间

	~Vector() { delete [] _elem; } // 析构函数

	int size() const { return _size; }
	bool empty()const; //判空函数
	int disordered()const; //判断向量是否有序

	//上面是基本方法， 下面是需求操作， 基本的操作是增删查改
	int find(T const& e) const { return find(e, 0, _size); } //无序向量整体查找
	int find(T const& e, int lo, int hi) const; //无序向量区间查找
	int search(T const& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); } //有序向量整体查找
	int search(T const& e, int lo, int hi) const; //有序向量区间查找

	// 可写访问接口
	T& operator[](int r) const; //重载下标操作符
	Vector<T>& operator=(Vector<T> const&); //重载赋值操作符
	T remove(int r); //删除秩为r的元素
	int remove(int lo, int hi); //删除秩在区间[lo, hi)之内的元素
	int insert(int r, T const& e); //插入元素
	int insert(T const& e) { return insert(_size, e); } //默认插入到末尾
	void sort(int lo, int hi); //对[lo, hi)排序
	void sort() { sort(0, _size); } //整体排序
	void unsort(int lo, int hi); //对[lo, hi)置乱
	void unsort() { unsort(0, _size); } //整体置乱
	int deduplicate(); //无序去重
	int uniquify(); //有序去重

	// 遍历
	void traverse(void(*)(T&)); //通过函数指针遍历
	template <typename VST> void traverse(VST&); //通过模板遍历

	void print()const {
		for (int i = 0; i < _size; i++) {
			std::cout << _elem[i] << " ";
		}
		std::cout << std::endl;
	}
};

template<typename T>
void Vector<T>::selectionSort(int lo, int hi){
	// 从后往前遍历Vector， 每一次把(从lo 到 i的)最大元素和最后一个元(i)素交换
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
	// 从前往后遍历Vector， 每一次把i插入到前面的有序序列中
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
	// 从前往后遍历Vector， 每一次把最大的元素冒泡到最后
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
	//merge是一个函数， 用于合并两个有序数组
	mergeSort(lo, middle); // n/2
	mergeSort(middle, hi); // n/2
	// 十个数， 但是一号和三号先合并了， 就会合并到一号和二号位置上， 就会把二号的数值给覆盖， 就会影响二号的合并

	// 现在 lo , middle有序， middle到hi有序
	T* temp0 = elem + lo; // 原数组起始点
	T* temp2 = elem + (int)((hi + lo) / 2); //原数组中间点
	T* temp1 = new T[(int)(hi - lo) / 2]; //新数组，大小是原数组大小的一半
	for (int i = 0; i < (hi - lo) / 2; temp1[i] = temp0[i++]);  // 备份原数组的前半部分
	int p = 0, q = 0; // 两个下标，一个用于遍历左半边， 一个用于遍历右半边
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