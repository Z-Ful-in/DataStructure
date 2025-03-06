#include<iostream>
#include "Vector.h"

int main() {	
	int a[10] = { 10,21,4,23,12,1,2,6,8 };
	Vector<int> test(a, 10);
	test.sort();
	test.print();
}