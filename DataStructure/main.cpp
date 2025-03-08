#include<iostream>
#include"Vector.h"

int main() {	
	int a[] = { 58,56,23,7,1,5,9,3,87,60 };
	Vector<int> t(a,10);
	t.print();
	t.sort(0,10);
	t.print();

}