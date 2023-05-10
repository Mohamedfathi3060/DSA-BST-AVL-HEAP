#pragma once
#include <iostream>
#include <string>

using namespace std;
template<typename T>
struct BSTNode {
	T data;
	BSTNode* left;
	BSTNode* right;
	BSTNode() {
		right = nullptr;
		left = nullptr;
	}
	BSTNode(const T value, BSTNode* l = nullptr, BSTNode* r = nullptr) {
		data = value;
		left = l;
		right = r;
	}
	T getData() {
		return data;
	}
	BSTNode* getLeft() {
		return left;
	}
	BSTNode* getRight() {
		return right;
	}
};



