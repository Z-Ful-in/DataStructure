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
	LinkedList<int> t1;//Ĭ�Ϲ��캯��
	LinkedList<int> t2(10);//����10���ڵ�
	LinkedList<int> t3(t2);//����
	LinkedList<int> t4(t2, 5);//��ͷ����5��
}

int main() 
{	
	test01();
	test02();
}