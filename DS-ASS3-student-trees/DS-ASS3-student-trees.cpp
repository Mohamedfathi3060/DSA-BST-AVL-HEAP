// DS-ASS3-Student-trees.cpp : Studenthis file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <string>
#include "BST.h"

using namespace std;

//class Student
//{
//public:
//	Student(int id = 0 , string n = "Unknown", float gp = 0.0, string dep="Unknown DEP") {
//		ID = id;
//		name = n;
//		GPA =  gp;
//		department = dep;
//	}
//	int ID;
//	string name;
//	float GPA;
//	string department;
//	friend std::ostream& operator<<(std::ostream& o, Student const& x) {
//		o << "[" << x.ID << ", " << x.name << ", " << x.GPA << ", " << x.department << "]" << '\n';
//	
//		return o;
//	}
//	friend bool operator<(Student const& x, Student const& y) {
//		
//		return x.ID < y.ID;
//	}
//	friend bool operator>(Student const& x, Student const& y) {
//
//		return x.ID > y.ID;
//	}
//	friend bool operator==(Student const& x, Student const& y) {
//
//		return x.ID == y.ID;
//	}
//};
//
//
//
//template<class Student>
//class AVLNode {
//public:
//	Student key;
//	AVLNode* right;
//	AVLNode* left;
//	int freq;
//	int height;
//	AVLNode(Student val = Student()) {
//		this->key = val;
//		this->height = 0;
//		this->freq = 0;
//		right = left = NULL;
//	}
//	void updateHeight()
//	{
//		if (this == NULL) return;
//
//		height = 1 + max((left == NULL ? -1 : left->height), (right == NULL ? -1 : right->height));
//	}
//	int BF() {
//		if (this == NULL) return 0;
//
//		return (left == NULL ? -1 : left->height) - (right == NULL ? -1 : right->height);
//	}
//};
//
//
//class AVL {
//private:
//	AVLNode<Student>* root;
//	AVLNode<Student>* rightRotation(AVLNode<Student>*& node) {
//		AVLNode<Student>* child = node->left;
//		node->left = child->right;
//		child->right = node;
//
//		node->updateHeight();
//		child->updateHeight();
//
//		return child;
//
//	}
//	AVLNode<Student>* leftRotation(AVLNode<Student>*& node) {
//		AVLNode<Student>* child = node->right;
//		node->right = child->left;
//		child->left = node;
//
//
//		node->updateHeight();
//		child->updateHeight();
//
//
//		return child;
//	}
//	void balance(AVLNode<Student>*& node) {
//		int bf = node->BF();
//		int rightbf = node->right->BF();
//		int leftbf = node->left->BF();
//		if (bf == 2 && leftbf == 1) {
//			/* LL rotate */
//			/*perform right roation in my {node} left child*/
//			node = rightRotation(node);
//
//		}
//		else if (bf == 2 && leftbf == -1) {
//			/* LR rotate */
//			node->left = leftRotation(node->left); // convert to LL
//			node = rightRotation(node);
//
//
//		}
//		else if (bf == -2 && rightbf == -1) {
//			/* RR rotate */
//			node = leftRotation(node);
//
//		}
//		else if (bf == -2 && rightbf == 1) {
//			/* RL rotate */
//			node->right = rightRotation(node->right); //convert to RR
//			node = leftRotation(node);
//
//		}
//
//		node->updateHeight();
//
//
//	}
//
//public:
//	AVL() {
//		root = NULL;
//	}
//
//	AVLNode<Student>* insert(AVLNode<Student>*& root, Student el) {
//		if (root == NULL) {
//			return new AVLNode<Student>(el);
//		}
//		else if (root->key == el) {
//			root->freq++;
//			return root;
//		}
//		else if (root->key > el) {
//			root->left = insert(root->left, el);
//		}
//		else if (root->key < el) {
//			root->right = insert(root->right, el);
//		}
//		/*update root height*/
//		root->updateHeight();
//
//
//		/*calc node BF {BALANACE FACStudentOR}*/
//		/*
//			ROStudentAStudentE IS  {as -1 or 1 node}
//
//			- StudentAKE IStudent AS RIGHStudent CHILD "IF R ROStudentAStudentION"
//			- RAKE IStudent AS LEFStudent CHILD  "IF L ROStudentAStudentION"
//
//			- HIS PARENStudent BECOME MY PARENStudent
//
//			- MY SON BECOME HIS LEFStudent SON "IS r ROStudentAION"
//			- MY SON BECOME HIS RIGHStudent SON "IS l ROStudentAION"
//
//			ROStudentAStudentE IS  {as -2 or 2 node}
//
//			- StudentAKE ME AS YOUR LEFStudent  CHILD "IF l ROStudentAION"
//			- StudentAKE ME AS YOUR RIGHStudent CHILD "IF R ROStudentAION"
//
//			- MY PARENStudent BECOME YOUR PARENStudent
//
//			- YOUR SON BECOME MY LEFStudent  CHILD "IF R ROStudentAION"
//			- YOUR SON BECOME MY RIGHStudent CHILD "IF L ROStudentAION"
//
//			StudentHAStudentS all
//
//		*/
//
//		balance(root);
//
//
//		return root;
//	}
//	
//	void insert(Student el) {
//		root = insert(root, el);
//	}
//
//
//
//	void inorder(AVLNode<Student> * root) {
//		if (root == NULL) {
//			return;
//		}
//		inorder(root->left);
//		cout << root->key  <<"\n";
//		inorder(root->right);
//	}
//	void inorder() {
//		inorder(root);
//	}
//
//	Student search( AVLNode<Student>* root  , int el) {
//		if (root == NULL) {
//			return Student();
//		}
//		else if (el == root->key.ID) {
//			return root->key;
//		}
//		else if (el > root->key.ID){
//			return search(root->right , el);
//		}
//		else if (el < root->key.ID) {
//			return search(root->left, el);
//		}
//	}
//	Student search(int el) {
//		return search(root, el);
//	}
//
//
//
//	void deleteByCopying(AVLNode<Student>*& node, int el) {
//		AVLNode<Student>* temp = node;
//
//		if (node == NULL) {
//			cout << "Student is not found.\n";
//			return;
//		}
//		else if (node->key.ID == el) {
//
//			if (node->left == NULL && node->right == NULL) { // has no children
//				delete node;
//				node = NULL;
//			}
//			else if (temp->left == NULL) {// has child at right
//				node = node->right;
//				delete temp;
//			}
//			else if (temp->right == NULL) { // has child at left
//				node = node->left;
//				delete temp;
//			}
//			else { // has two child
//				AVLNode<Student>* curr = node->left;
//				while (curr->right != NULL)
//				{
//					curr = curr->right;
//				}
//
//				Student x = curr->key;
//				deleteByCopying(node, curr->key.ID);
//				temp->key = x;
//
//
//
//				//node->key = curr->key;
//				//if (prev == NULL) { //one move to left {left node is the pred.}
//				//	// left child of deleted node is the predocessor and this may has left child {cannot be right} so you need to make left of node with new value taken from pred. point to left of pred.
//				//	node->left = curr->left;
//				//	// may be nulL if pred has no left child
//				//}
//				//else {//many moves to reach pred. left then many rights
//				//	// if we move many to get pred and pred has left child you need to make this child the right for prev of pred {as it greater than prev}
//				//	prev->right = curr->left;
//				//}
//				//delete curr;
//
//			}
//
//		}
//
//		else if (node->key.ID > el) {
//			deleteByCopying(node->left, el);
//		}
//		else if (node->key.ID < el) {
//			deleteByCopying(node->right, el);
//		}
//
//		if (node == NULL) return;
//
//		node->updateHeight();
//		balance(node);
//
//
//	}
//	void deleteByCopying(int el) {
//		deleteByCopying(root, el);
//		cout << "Student is deleted.\n";
//	}

//	void menu() {
//		while (true)
//		{
//			cout <<
//				"1. Add student\n" <<
//				"2. Remove student\n" <<
//				"3. Search student\n" <<
//				"4. Print All (sorted by id)\n" <<
//				"5. Return to main menu" << "\n" <<
//				"Enter number of option: ";
//			string choice;
//			cin >> choice;
//			int id = 0;
//			string dep, name;
//			float gpa;
//			if (choice == "1") {
//				while (true)
//				{
//					cout << "id: ";
//					cin >> id;
//					if (search(id) == NULL) {
//						break;
//					}
//					else {
//						cout << "The student is added before..!\n";
//					}
//				}
//				cout << "Name: ";
//				cin.ignore();
//				getline(cin, name);
//
//
//				cout << "GPA: ";
//				cin >> gpa;
//
//
//				cout << "Department: ";
//				cin >> dep;
//
//				insert(Student(id, name, gpa, dep));
//
//
//
//
//			}
//			else if (choice == "2") {
//				cout << "id: ";
//				cin >> id;
//				Student x = search(id);
//				if (x.name != "Unknown") {
//					deleteByCopying(id);
//					cout << x;
//				}
//				else {
//					cout << "Student is not found.\n";
//				}
//
//			}
//			else if (choice == "3") {
//				cout << "id: ";
//				cin >> id;
//				Student x = search(id);
//				if (x.name != "Unknown") {
//					cout << "Student is found.\n";
//					cout << x;
//				}
//				else {
//					cout << "Student is not found.\n";
//				}
//			}
//			else if (choice == "4") {
//				inorder();
//			}
//			else {
//				break;
//			}
//		}
//
//	}
//
//};




int main()
{

	BST s;
	s.BSTMenu();
}

