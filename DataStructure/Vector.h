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

	void selectSort(int lo, int hi); // 选择排序
	void insertSort(int lo, int hi); // 插入排序
	void bubbleSort(int lo, int hi); // 冒泡排序
	void mergeSort(int lo, int hi); // 归并排序
	void quickSort(int lo, int hi); // 快速排序

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
	Vector<T>& operator=(Vector<T> const&A); //重载赋值操作符
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

	void print()const//常量函数可以不改变类内的值
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
	 for (int i=lo;i<hi-lo;i++)
	 {
		 _elem[i] = A[i];
	 }
}
template<typename T>
void Vector<T>::shrink()
{
	int _capacity = max(_capacity, DEFAULT_CAPACITY);
	T* newelem = _elem;
	int newCapacity = _size;
	_elem = new T[newCapacity];
	for (int i = 0;i < _size;i++)
	{
		_elem[i] = newelem[i];
	}
	delete[] newelem;
}
template<typename T>
void Vector<T>::expand()
{
	if (_size <_capacity)return;
	int _capacity = max(_capacity, DEFAULT_CAPACITY);
	T* newelem = _elem;
	int newCapacity = _capacity * 2;//将旧容量扩大两倍
	_elem = new T[newCapacity];
	for (int i = 0;i < _size;i++)
	{
		_elem[i] = newelem[i];
	}
	delete[] newelem;
}


template<typename T>
void Vector<T>::selectSort(int lo, int hi)
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
void Vector<T>::bubbleSort(int lo, int hi)
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
void Vector<T>::mergeSort(int lo, int hi)
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
void Vector<T>::quickSort(int lo, int hi)
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
template<typename T>
Vector<T>::Vector(int capacity, int size, T val)
{
	this->_capacity = capacity;
	this->_size = size;
	for (int k = 0;k < _size;k++)
	{
		_elem[k] = val;
	}
}
// 58,56,23,7,1,5,9,3,87,60
// 

template<typename T>
int Vector<T>::insert(int r, T const& e)
{
	expand();
	for (int i = _size;i > r;i--)
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e;
	_size++;//更新向量规模
	return r;//返回秩
}

template<typename T>
void Vector<T>::sort(int lo,int hi)
{
	quickSort(lo, hi);
}

template<typename T>
void Vector<T>::unsort(int lo, int hi)
{
	T* temp = new T[_capacity];
}

template<typename T>
int Vector<T>::deduplicate()//无序去重
{
	int oldsize = _size;
	int i = 1;
	while (i < _size)
	{
		find(_elem[i], 0, i) ?i++ : remove(i);
	}
	return oldsize-_size;//返回的是删除元素总数
}

template<typename T>
inline int Vector<T>::uniquify()
{
	int oldsize = _size;
	int i = 1;
	while (i < _size)
	{
		find(_elem[i], 0, i) ? i++ : remove(i);
	}
	return oldsize-_size;
}

template<typename T>
void Vector<T>::traverse(void(*)(T&))
{
	for (int i = 0;i < _size;i++)
		visit(_elem[i]);
}

template<typename T>
Vector<T>::Vector(T const* A, int n)
{
	copyFrom(A, 0, n);
}

template<typename T>
Vector<T>::Vector(T const* A, int lo, int hi)
{
	copyFrom(A, lo, hi);
}

template<typename T>
Vector<T>::Vector(Vector<T> const& V)
{
	copyFrom(V, 0, _size);
}

template<typename T>
Vector<T>::Vector(Vector<T> const& V, int lo, int hi)
{
	copyFrom(V, lo, hi);
}

template<typename T>
bool Vector<T>::empty() const
{
	if (_size = 0)
	return false;
}

template<typename T>
int Vector<T>::disordered() const
{
	int count = 0;//记录无序数组对数
		for (int i = 1;i < _size;i++)
		{
			if (_elem[i - 1] > _elem[i])
				count++;
	}
		return count;//返回值为无序数组对数
}

template<typename T>
int Vector<T>::find(T const& e) const
{
	int hi = _size;
	while ((0< hi--) && (e != _elem[hi]));
	return hi;
}

template<typename T>
inline int Vector<T>::find(T const& e, int lo, int hi) const
{
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template<typename T>
int Vector<T>::search(T const& e) const
{
	int lo = 0, hi = _size;
	while (lo < hi)
	{
		int middle = _size / 2;
		if (e > _elem[middle])
		{
			lo = middle;
		}
		else if (e == middle)
		{
			return middle;
		}
		else
		{
			hi = middle;
		}
		return -1;//查找失败
	}
}

template<typename T>
inline int Vector<T>::search(T const& e, int lo, int hi) const
{
	while (lo < hi)
	{
		int mi = (hi - lo) / 2;
		if (e < _elem[mi])
			hi = mi;
		else if (_elem[mi] < e)
			lo = mi;
		else
			return mi;
	}
	return -1;
}

template<typename T>
T& Vector<T>::operator[](int r) const
{
	return _elem[r];
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const&A)
{
	if (this != &A) 
	{
		T* newElem = new T[A._capacity];        // 先分配新内存‌
		for (int i = 0; i < A._size; ++i)
		{
			newElem[i] = A._elem[i];            // 拷贝数据‌
		}
		delete[] _elem;                           // 再释放旧内存‌
		_elem = newElem;
		_size = A._size;
		_capacity = A._capacity;                // 更新元数据‌
	}
	return *this;
}

template<typename T>
T Vector<T>::remove(int r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;//返回被删除元素
}

template<typename T>
inline int Vector<T>::remove(int lo, int hi)
{
	if (lo == hi)return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];//把后面的元素全部前移hi-lo位
	_size =_size-hi+lo;//更新数组长度
	shrink();//缩小容量，避免内存浪费
	return lo - hi;//返回删除元素数目
}

template<typename T>
template<typename VST>
inline void Vector<T>::traverse(VST&)
{
	for (int i = 0;i < _size;i++)
		visit(_elem[i]);
}
