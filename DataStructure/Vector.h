#pragma once
#include<iostream>
#define DEFAULT_CAPACITY 10 // 默认的vector的初始大小
using namespace std;
template <typename T>
class Vector{
protected:
	int _size; // vector中已装填的元素个数
	T* _elem; // 指向元素数组的指针
	int _capacity; // vector的容量

	int getMax(int lo,int hi)//找最值函数
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
	
	void copyFrom(T const* A, int lo, int hi); // 复制数组区间A[lo, hi): 包头不包尾
	void shrink(); // 空间过大时压缩
	void expand(); // 空间不足时扩容
public:
	Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T val = 0);

	// 下列的构造函数可以使用copyFrom的逻辑来实现
	Vector(T const* A, int n); // 复制数组整体
	Vector(T const* A, int lo, int hi);  // 复制数组区间
	Vector(Vector<T> const& V);// 复制vector整体
	Vector(Vector<T> const& V, int lo, int hi);// 复制vector区间

	~Vector() { delete [] _elem; } // 析构函数

	int size() const { return _size; }
	bool empty()const; //判空函数
	int disordered()const; //判断向量是否有序

	//上面是基本方法， 下面是需求操作， 基本的操作是增删查改
	int find(T const& e) const;//无序向量整体查找, 可以通过区间find实现
	int find(T const& e, int lo, int hi) const; //无序向量区间查找
	int search(T const& e) const; //有序向量整体查找, 可以通过区间search实现
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
    // 备份左右半区
	int leftLen = middle - lo;
	int rightLen = hi - middle;
	T* temp1 = new T[leftLen];
	T* temp2 = new T[rightLen];
	for (int i = 0; i < leftLen; i++) temp1[i] = _elem[lo + i];
	for (int j = 0; j < rightLen; j++) temp2[j] = _elem[middle + j];

	// 合并逻辑
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
	//选择基准
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
