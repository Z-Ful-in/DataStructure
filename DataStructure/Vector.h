#pragma once

#define DEFAULT_CAPACITY 10 // 默认的vector的初始大小

template <typename T>
class Vector{
protected:
	int _size; // vector中已装填的元素个数
	T* _elem; // 指向元素数组的指针
	int _capacity; // vector的容量
	
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

};

