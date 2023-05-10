#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <fstream>
#include "BSTNode.h"
#include "Student.h"
#include <math.h>
#define _PATH_ "data.txt"
using namespace std;
class BST {
	BSTNode<Student>* root;
	map<string, int> deptStudents;
public:
	BST();
	~BST();
	bool isEmpty();
	Student* search(const int& studentID);
	void inOrderTraverse(BSTNode<Student>* node);
	void printDeptCount();
	int studentsCount();
	void insert(const int& studentID, const string& name, const float& GPA, const string& department);
	void remove(const int& studentID);
	void printNodeData(BSTNode<Student>* node);
	void loadFile();
	BSTNode<Student>* getRoot();
	map<string, int>& getDeptStudent() { return deptStudents; }
	void reduceDeptStudents(string dept) { deptStudents[dept]--; }
	void increaseDeptStudents(string dept) { deptStudents[dept]++; }
	void BSTMenu();
};

