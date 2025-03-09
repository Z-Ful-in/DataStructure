#include<iostream>
#include"Vector.h"
#include"LinkedList.h"

void test01()
{
	int a[] = { 58,56,23,7,1,5,9,3,87,60 };
	Vector<int> t(a, 10);
	t.print();
	t.sort(0, 10);
	t.print();
}

void test02()
{
	LinkedList<int> t1;//默认构造函数
	LinkedList<int> t2(10);//配置10个节点
	LinkedList<int> t3(t2);//复制
	LinkedList<int> t4(t2, 5);//从头复制5个
}

int main() 
{	
	test01();
	test02();
}