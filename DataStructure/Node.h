#pragma once
template <typename T>
struct Node{
	T val;
	Node* prev;
	Node* next;
	Node(T val = 0, Node* prev = nullptr, Node* next = nullptr)
		:val(val), prev(prev), next(next) {}
};

