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
	//LinkedList<int> t1 ;//Ĭ�Ϲ��캯��
	//t1.print();
	LinkedList<int> t2(1);//����10���ڵ�
	t2.insertAsLast(9);
	t2.insertAsLast(2);
	t2.insertAsLast(3);
	t2.insertAsLast(7);
	//t2.print();
	//t2.insertBefore(t2[2], 6);
	t2.print();
	//t2.remove(t2[2]);
	t2.sort(t2[0], 5);
	t2.print();
	//LinkedList<int> t3(t2);//����
	//LinkedList<int> t4(t2, 5);//��ͷ����5��
}

int main() 
{	
	//test01();
	test02();
}