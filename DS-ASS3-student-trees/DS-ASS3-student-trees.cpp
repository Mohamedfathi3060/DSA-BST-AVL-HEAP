// DS-ASS3-Student-trees.cpp : 
// version: 0.1v
// authors: MohamedFathi,MoaazAdly,Abdo
// purpose: implement avl bst heap-max-min using student data file
//

#include <iostream>
#include <queue>
#include <string>
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <fstream>
#include <math.h>
#include <map>

#define _PATH_ "data.txt"

using namespace std;

class Student
{
public:
	Student(int id = 0 , string n = "Unknown", float gp = 0.0, string dep="Unknown DEP") {
		ID = id;
		name = n;
		GPA =  gp;
		department = dep;
	}
	int ID;
	string name;
	float GPA;
	string department;
	friend std::ostream& operator<<(std::ostream& o, Student const& x) {
		o << "[" << x.ID << ", " << x.name << ", " << x.GPA << ", " << x.department << "]" << '\n';
	
		return o;
	}
	friend bool operator<(Student const& x, Student const& y) {
		
		return x.ID < y.ID;
	}
	friend bool operator>(Student const& x, Student const& y) {

		return x.ID > y.ID;
	}
	friend bool operator==(Student const& x, Student const& y) {

		return x.ID == y.ID;
	}
};


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

class BST {
	BSTNode<Student>* root;
	map<string, int> deptStudents;
public:
	map<string, int>& getDeptStudent() { return deptStudents; }
	void reduceDeptStudents(string dept) { deptStudents[dept]--; }
	void increaseDeptStudents(string dept) { deptStudents[dept]++; }

	BST() {
		root = nullptr;
	}

	~BST() {
		root = nullptr;
	}

	bool isEmpty()
	{
		return root == nullptr;
	}

	Student* search(const int& studentID)
	{
		BSTNode<Student>* itr = root;
		while (itr != nullptr) {
			if (studentID == itr->data.ID) {
				return &itr->data;
			}
			else if (studentID < itr->data.ID) {
				itr = itr->getLeft();
			}
			else {
				itr = itr->getRight();
			}
		}
		return 0;
	}

	BSTNode<Student>* getRoot() {
		return root;
	}

	void BSTMenu()
	{
		loadFile();
		int choice = 0;
		bool flag = true;
		while (flag) {
			cout << ">>>>> BST <<<<<\n"
				<< "1- Add Student\n"
				<< "2- Remove Student\n"
				<< "3- Search Student\n"
				<< "4- Print All(Stored by ID)\n"
				<< "5- Return to Main Menu\n";
			cout << "Enter Number of Option: ";
			cin >> choice;
			int id = 0;
			string name = "", department = "";
			float GPA = 0;
			switch (choice) {
			case 1:
				cout << "ID: ";
				cin >> id;
				if (search(id) != nullptr) {
					while (search(id) != nullptr) {
						cout << "ID is Already Exist, Enter Another ID: ";
						cin >> id;
					}
				}
				cout << "Name: ";
				cin.ignore();
				getline(cin, name);
				cout << "GPA: ";
				cin >> GPA;
				if (GPA < 0 || GPA > 4) {
					while (GPA < 0 || GPA > 4) {
						cout << "Not Valid GPA, Enter Another GPA: ";
						cin >> GPA;
					}
				}
				cout << "Department: ";
				cin >> department;
				insert(id, name, GPA, department);
				cout << "Student Added Successfully\n";
				break;
			case 2:
				cout << "\nID of Student to Remove: ";
				cin >> id;
				if (search(id) != nullptr) {
					cout << "Student is Found\n";
					cout << (*search(id));
					remove(id);
					cout << "Student Removed Successfully\n";
				}
				break;
			case 3:
				cout << "\nID of Student to Search: ";
				cin >> id;
				if (search(id)) {
					cout << "Student is Found\n";
					cout << (*search(id));
				}
				else
					cout << "Student is Not Found\n";
				break;
			case 4:
				cout << "\nPrint " << studentsCount() << " Students: \n";
				inOrderTraverse(getRoot());
				printDeptCount();
				break;
			case 5:
				flag = false;
				break;
			default:
				cout << "Invalid Choice\n";
				break;
			}
			cout << endl;
		}
	}

	void printNodeData(BSTNode<Student>* node) {
		if (node != nullptr)
			cout << node->data;
	}


	void  inOrderTraverse(BSTNode<Student>* node)
	{
		if (node != nullptr) {
			inOrderTraverse(node->getLeft());
			cout << node->getData();
			inOrderTraverse(node->getRight());
		}
	}

	void printDeptCount() {
		cout << "Number of Students in each Department:\n";
		for (auto itr = getDeptStudent().begin(); itr != getDeptStudent().end(); itr++) {
			cout << itr->first << ": " << itr->second << endl;
		}
	}

	int studentsCount() {
		int result = 0;
		for (auto itr = getDeptStudent().begin(); itr != getDeptStudent().end(); itr++) {
			result += itr->second;
		}
		return result;
	}

	void insert(const int& studentID, const string& name, const float& GPA, const string& department)
	{
		increaseDeptStudents(department);
		BSTNode<Student>* itr = root, * prev = nullptr;
		while (itr != nullptr) {

			if (studentID < itr->data.ID) {
				prev = itr;
				itr = itr->getLeft();
			}
			else {
				prev = itr;
				itr = itr->getRight();
			}
		}
		if (root == nullptr) {
			root = new BSTNode<Student>(Student(studentID, name, GPA, department));
		}
		else if (studentID < prev->data.ID) {
			prev->left = new BSTNode<Student>(Student(studentID, name, GPA, department));
		}
		else if (studentID > prev->data.ID) {
			prev->right = new BSTNode<Student>(Student(studentID, name, GPA, department));
		}
	}

	void remove(const int& studentID)
	{
		BSTNode<Student>* itr = root, * prev = nullptr;
		while (itr != nullptr && itr->data.ID != studentID) {

			if (studentID < itr->data.ID) {
				prev = itr;
				itr = itr->getLeft();
			}
			else {
				prev = itr;
				itr = itr->getRight();
			}
		}
		if (root == nullptr) {
			cout << "Tree is Empty\n";
		}
		else if (itr == nullptr) {
			cout << "Element not Found\n";
		}
		if (itr->data.ID == studentID) {
			reduceDeptStudents(itr->data.department);
			if (itr->getLeft() == nullptr && itr->getRight() == nullptr) {
				if (itr == prev->getLeft()) {
					prev->left = nullptr;
				}
				else {
					prev->right = nullptr;
				}
			}
			else if (itr->getLeft() == nullptr) {
				if (itr == prev->getLeft()) {
					prev->left = itr->right;
				}
				else {
					prev->right = itr->right;
				}
			}
			else if (itr->getRight() == nullptr) {
				if (itr == prev->getLeft()) {
					prev->left = itr->left;
				}
				else {
					prev->right = itr->left;
				}
			}
			else if (itr->getRight() != nullptr && itr->getLeft() != nullptr) {
				BSTNode<Student>* temp = itr;
				temp = temp->right;
				while (temp->getLeft() != nullptr) {
					prev = temp;
					temp = temp->getLeft();
				}
				itr->data = temp->data;
				if (temp->getRight() != nullptr) {
					prev->left = temp->right;
				}
				if (prev != nullptr)
					prev->left = nullptr;
				else
					itr->right = nullptr;
			}
		}
	}

	void loadFile()
	{
		string myText;
		ifstream MyReadFile(_PATH_);
		Student s;
		int counter = 0;
		if (!MyReadFile.fail()) {
			getline(MyReadFile, myText); // read first lINE which is the  number of students
			while (getline(MyReadFile, myText)) {
				if (counter == 0)
				{
					s.ID = stoi(myText);
				}
				else if (counter == 1)
				{
					s.name = myText;
				}
				else if (counter == 2)
				{
					s.GPA = stof(myText);
				}
				else
				{
					s.department = myText;
					insert(s.ID, s.name, s.GPA, s.department);
					counter = -1;
				}
				counter += 1;
			}
		}
		else {
			cout << "File Damaged!\n";
		}
		MyReadFile.close();
	}

};



class minHeap
{
public:
	void heapify(vector<Student>& arr, int n, int i) {
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		if (left < n && arr[left].GPA > arr[largest].GPA)
			largest = left;
		if (right < n && arr[right].GPA > arr[largest].GPA)
			largest = right;

		if (largest != i) {
			swap(arr[i], arr[largest]);
			heapify(arr, n, largest);
		}
	}
	void sortedheap(vector<Student>& arr)
	{
		for (int i = arr.size() - 1; i >= 0; i--) {
			swap(arr[0], arr[i]);
			heapify(arr, i, 0);
		}
	}
	void min_heap(vector<Student>& arr) {
		int n = arr.size();

		for (int i = n / 2 - 1; i >= 0; i--)
			heapify(arr, n, i);
		sortedheap(arr);
	}
	void readFile(vector<Student>& Students)
	{
		string myText;
		ifstream MyReadFile(_PATH_);
		int counter = 0;
		Student s;
		getline(MyReadFile, myText); // read first lINE which is the  number of students
		while (getline(MyReadFile, myText)) {

			if (counter == 0)
			{
				s.ID = stoi(myText);
			}
			else if (counter == 1)
			{
				s.name = myText;

			}
			else if (counter == 2)
			{

				s.GPA = stof(myText);
			}
			else
			{
				s.department = myText;
				Students.push_back(s);
				counter = -1;
			}
			counter += 1;
		}
		MyReadFile.close();
	}
	void printAllStudents(vector<Student> Students)
	{
		cout << "Print " << Students.size() << " studnts." << endl;
		for (size_t i = 0; i < Students.size(); i++)
		{

			cout << "[" << Students[i].ID << ", " << Students[i].name << ", " << Students[i].GPA << ", " << Students[i].department << "]" << endl;
		}
	}
	void addStudent(vector<Student>& Students)
	{
		Student s;
		while (true)
		{
			string st;
			bool flag = true;
			cout << "ID: ";
			cin >> st;
			for (char c : st)
			{
				if (!isdigit(c))
				{
					cout << "please entre number." << endl;
					flag = false;
					break;
				}
			}
			if (flag)
			{
				for (size_t i = 0; i < Students.size(); i++)
				{
					if (stoi(st) == Students[i].ID)
					{
						cout << "ID is used please entre deffient ID." << endl;
						flag = false;
						break;
					}
				}
			}


			if (flag)
			{
				s.ID = stoi(st);
				break;
			}
		}
		cout << "Name: ";
		cin.ignore();
		getline(cin,s.name);
		while (true)
		{
			string stt;
			bool flag = true;
			cout << "GPA: ";
			cin >> stt;
			for (char cc : stt)
			{

				if (cc == '.')
				{
					continue;
				}
				if (!isdigit(cc))
				{
					cout << "please entre number." << endl;
					flag = false;
					break;
				}
			}
			if (flag)
			{
				if ((stof(stt) > 4) || (stof(stt) < 0))
				{
					cout << "GPA must be betwen 0 and 4" << endl;
				}
				else
				{
					s.GPA = stof(stt);
					break;
				}
			}
		}
		while (true)
		{
			cout << "Departmwnt: ";
			cin >> s.department;
			for (char& c : s.department)
			{
				c = toupper(c);
			}
			if ((s.department == "IT") || (s.department == "CS") || (s.department == "IS") || (s.department == "AI") || (s.department == "DS"))
			{
				break;
			}
			else
			{
				cout << "please entre department in our unvirsty [CS, IT, IS, AI, DS]." << endl;
			}
		}
		Students.push_back(s);
		cout << "The Student is added." << endl;
		min_heap(Students);
	}
	void menu()
	{
		string option;
		vector<Student> Students;
		readFile(Students);
		min_heap(Students);
		while (true)
		{
			cout << "choose one of the following options: \n" << "1. add a Student \n" << "2. print all Student(sorted by gpa) \n" << "3. exit \n";
			cin >> option;
			if (option == "1")
			{
				addStudent(Students);
			}
			else if (option == "2")
			{
				this->printAllStudents(Students);

			}
			else if (option == "3")
			{
				break;
			}
			else
			{
				cout << "invalid input" << endl;
			}
		}

	}
};
class maxHeap : public minHeap
{
public:
	void printAllStudents(vector<Student> Students)
	{
		reverse(Students.begin(), Students.end());
		cout << "Print " << Students.size() << " studnts." << endl;
		for (size_t i = 0; i < Students.size(); i++)
		{
			cout << "[" << Students[i].ID << ", " << Students[i].name << ", " << Students[i].GPA << ", " << Students[i].department << "]" << endl;
		}
	}
	void menu()
	{
		string option;
		vector<Student> Students;
		readFile(Students);
		min_heap(Students);
		while (true)
		{
			cout << "choose one of the following options: \n" << "1. add a Student \n" << "2. print all Student(sorted by gpa) \n" << "3. exit \n";
			cin >> option;
			if (option == "1")
			{
				addStudent(Students);
			}
			else if (option == "2")
			{
				this->printAllStudents(Students);

			}
			else if (option == "3")
			{
				break;
			}
			else
			{
				cout << "invalid input" << endl;
			}
		}

	}

};





template<class Student>
class AVLNode {
public:
	Student key;
	AVLNode* right;
	AVLNode* left;
	int freq;
	int height;
	AVLNode(Student val = Student()) {
		this->key = val;
		this->height = 0;
		this->freq = 0;
		right = left = NULL;
	}
	void updateHeight()
	{
		if (this == NULL) return;

		height = 1 + max((left == NULL ? -1 : left->height), (right == NULL ? -1 : right->height));
	}
	int BF() {
		if (this == NULL) return 0;

		return (left == NULL ? -1 : left->height) - (right == NULL ? -1 : right->height);
	}
};

class AVL {
private:
	map<string, int> deps;
	int numberOfStudents;
	AVLNode<Student>* root;
	AVLNode<Student>* rightRotation(AVLNode<Student>*& node) {
		AVLNode<Student>* child = node->left;
		node->left = child->right;
		child->right = node;

		node->updateHeight();
		child->updateHeight();

		return child;

	}
	AVLNode<Student>* leftRotation(AVLNode<Student>*& node) {
		AVLNode<Student>* child = node->right;
		node->right = child->left;
		child->left = node;


		node->updateHeight();
		child->updateHeight();


		return child;
	}
	void balance(AVLNode<Student>*& node) {
		int bf = node->BF();
		int rightbf = node->right->BF();
		int leftbf = node->left->BF();
		if (bf == 2 && leftbf == 1) {
			/* LL rotate */
			/*perform right roation in my {node} left child*/
			node = rightRotation(node);

		}
		else if (bf == 2 && leftbf == -1) {
			/* LR rotate */
			node->left = leftRotation(node->left); // convert to LL
			node = rightRotation(node);


		}
		else if (bf == -2 && rightbf == -1) {
			/* RR rotate */
			node = leftRotation(node);

		}
		else if (bf == -2 && rightbf == 1) {
			/* RL rotate */
			node->right = rightRotation(node->right); //convert to RR
			node = leftRotation(node);

		}

		node->updateHeight();


	}

public:
	AVL() {
		root = NULL;
		readFile();
	}

	AVLNode<Student>* insert(AVLNode<Student>*& root, Student el) {
		if (root == NULL) {
			return new AVLNode<Student>(el);
		}
		else if (root->key == el) {
			root->freq++;
			return root;
		}
		else if (root->key > el) {
			root->left = insert(root->left, el);
		}
		else if (root->key < el) {
			root->right = insert(root->right, el);
		}
		/*update root height*/
		root->updateHeight();


		/*calc node BF {BALANACE FACStudentOR}*/
		/*
			ROStudentAStudentE IS  {as -1 or 1 node}

			- StudentAKE IStudent AS RIGHStudent CHILD "IF R ROStudentAStudentION"
			- RAKE IStudent AS LEFStudent CHILD  "IF L ROStudentAStudentION"

			- HIS PARENStudent BECOME MY PARENStudent

			- MY SON BECOME HIS LEFStudent SON "IS r ROStudentAION"
			- MY SON BECOME HIS RIGHStudent SON "IS l ROStudentAION"

			ROStudentAStudentE IS  {as -2 or 2 node}

			- StudentAKE ME AS YOUR LEFStudent  CHILD "IF l ROStudentAION"
			- StudentAKE ME AS YOUR RIGHStudent CHILD "IF R ROStudentAION"

			- MY PARENStudent BECOME YOUR PARENStudent

			- YOUR SON BECOME MY LEFStudent  CHILD "IF R ROStudentAION"
			- YOUR SON BECOME MY RIGHStudent CHILD "IF L ROStudentAION"

			StudentHAStudentS all

		*/

		balance(root);


		return root;
	}

	void insert(Student el) {
		for (size_t i = 0; i < el.department.length(); i++)
		{
			el.department[i] = toupper(el.department[i]);
		}
		root = insert(root, el);
		numberOfStudents++;


		if (deps.find(el.department) != deps.end()) {
			deps[el.department]++;
		}
		else {
			deps[el.department] = 1;
		}
	}



	void inorder(AVLNode<Student>* root) {
		if (root == NULL) {
			return;
		}
		inorder(root->left);
		cout << root->key << "\n";
		inorder(root->right);
	}
	void inorder() {
		cout << "\nPrint " << numberOfStudents << " Students.\n\n";
		inorder(root);
		cout << "\n\n";
		cout << "Students per Departments: \n";
		for (auto i : deps)
		{
			if (i.second < 1)continue;
			cout << i.first << " " << i.second << " Students.\n";
		}

	}

	Student search(AVLNode<Student>* root, int el) {
		if (root == NULL) {
			return Student();
		}
		else if (el == root->key.ID) {
			return root->key;
		}
		else if (el > root->key.ID) {
			return search(root->right, el);
		}
		else if (el < root->key.ID) {
			return search(root->left, el);
		}
	}
	Student search(int el) {
		return search(root, el);
	}


	void readFile() {
		string myText;
		ifstream MyReadFile(_PATH_);
		int counter = 0;
		Student s;
		getline(MyReadFile, myText);// read first lINE which is the  number of students
		int x = stoi(myText);
		while (getline(MyReadFile, myText)) {

			if (counter == 0)
			{
				s.ID = stoi(myText);
			}
			else if (counter == 1)
			{
				s.name = myText;

			}
			else if (counter == 2)
			{

				s.GPA = stof(myText);
			}
			else
			{
				s.department = myText;
				insert(s);
				counter = -1;
			}
			counter += 1;
		}
		numberOfStudents = x;
		MyReadFile.close();
	}

	void deleteByCopying(AVLNode<Student>*& node, int el) {
		AVLNode<Student>* temp = node;

		if (node == NULL) {
			cout << "Student is not found.\n";
			return;
		}
		else if (node->key.ID == el) {

			if (node->left == NULL && node->right == NULL) { // has no children
				delete node;
				node = NULL;
			}
			else if (temp->left == NULL) {// has child at right
				node = node->right;
				delete temp;
			}
			else if (temp->right == NULL) { // has child at left
				node = node->left;
				delete temp;
			}
			else { // has two child
				AVLNode<Student>* curr = node->left;
				while (curr->right != NULL)
				{
					curr = curr->right;
				}

				Student x = curr->key;
				deleteByCopying(node, curr->key.ID);
				temp->key = x;



				//node->key = curr->key;
				//if (prev == NULL) { //one move to left {left node is the pred.}
				//	// left child of deleted node is the predocessor and this may has left child {cannot be right} so you need to make left of node with new value taken from pred. point to left of pred.
				//	node->left = curr->left;
				//	// may be nulL if pred has no left child
				//}
				//else {//many moves to reach pred. left then many rights
				//	// if we move many to get pred and pred has left child you need to make this child the right for prev of pred {as it greater than prev}
				//	prev->right = curr->left;
				//}
				//delete curr;

			}

		}

		else if (node->key.ID > el) {
			deleteByCopying(node->left, el);
		}
		else if (node->key.ID < el) {
			deleteByCopying(node->right, el);
		}

		if (node == NULL) return;

		node->updateHeight();
		balance(node);


	}
	void deleteByCopying(int el) {
		deps[search(el).department]--;
		deleteByCopying(root, el);
		cout << "Student is deleted.\n";
		numberOfStudents--;

	}

	void menu() {
		while (true)
		{
			cout <<
				"\n\n1. Add Student\n" <<
				"2. Remove Student\n" <<
				"3. Search Student\n" <<
				"4. Print All (sorted by id)\n" <<
				"5. Return to main menu" << "\n" <<
				"Enter number of option: ";
			string choice;
			cin >> choice;
			int id = 0;
			string dep, name;
			float gpa;
			if (choice == "1") {
				while (true)
				{
					cout << "id: ";
					cin >> id;
					if (search(id) == NULL) {
						break;
					}
					else {
						cout << "The Student is added before..!\n";
					}
				}
				cout << "Name: ";
				cin.ignore();
				getline(cin, name);


				cout << "GPA: ";
				cin >> gpa;


				cout << "Department: ";
				cin >> dep;

				insert(Student(id, name, gpa, dep));




			}
			else if (choice == "2") {
				cout << "id: ";
				cin >> id;
				Student x = search(id);
				if (x.name != "Unknown") {
					deleteByCopying(id);
					cout << x;
				}
				else {
					cout << "Student is not found.\n";
				}

			}
			else if (choice == "3") {
				cout << "id: ";
				cin >> id;
				Student x = search(id);
				if (x.name != "Unknown") {
					cout << "Student is found.\n";
					cout << x;
				}
				else {
					cout << "Student is not found.\n";
				}
			}
			else if (choice == "4") {
				inorder();
			}
			else {
				break;
			}
		}

	}

};


class menu
{
private:
	AVL avl;
	BST bst;
	minHeap  minheap;
	maxHeap maxheap;

public:
	
	void run() {
		while (true)
		{
			cout << "\nChoose Data Structure:\n" <<
				"1. BST \n" <<
				"2. AVL \n" <<
				"3. Min Heap \n" <<
				"4. Max Heap \n" <<
				"5. Exit Program \n" <<
				"Enter number of option: ";
			string c;
			cin >> c;
			if (c == "1") {
				bst.BSTMenu();
			}
			else if (c == "2") {
				avl.menu();
			}
			else if (c == "3") {
				minheap.menu();
			}
			else if (c == "4") {
				maxheap.menu();
			}
			else {
				break;
			}
		}
	}

};


int main()
{
	menu m;
	m.run();
	/*
	>>> BST,AVL <<<
	Enter number of option: 1 (Add student)
	id: 50
	Name: tamer said
	GPA: 3.5
	Department: CS
	The student is added.
	Enter number of option: 2 (remove student)
	Id: 5
	Student is found.
	[5, Omnia Osama, 3.6, IS]
	Student is deleted.
	Enter number of option: 2 (remove student)
	Id: 90
	Student is not found.
	Enter number of option: 3 (search student)
	id: 6
	Student is found.
	[6, Ahmed Omar, 3.9, CS]
	Enter number of option: 4 (print all students)
	Print 10 Students.
	[1, Mohamed Ali, 3.4, CS]
	[2, Mona Samir, 3.2, IT]
	[3, Ola Maher, 1.2, CS]
	[4, Magy Madgy, 2.3, DS]
	[5, Omnia Osama, 3.6, IS]
	[6, Ahmed Omar, 3.9, CS]
	[7, Mai Adel, 3.1, IS]
	[8, Mohamed Saleh, 2.4, CS]
	[9, Hany Mohsen, 1.8, DS]
	[10, Mohanad Bahaa, 2.9, IT]
	Students per Departments:
	CS 5 Students
	IT 2 Students
	DS 2 Students
	IS 2 Students
	>>> Min Heap <<<
	Enter number of option: 1
	id: 11
	Name: Hana Sobhy
	GPA: 3.2
	Department: IT
	The student is added.
	Print 11 studnts.
	[3, Ola Maher, 1.2, CS]
	[9, Hany Mohsen, 1.8, DS]
	[4, Magy Madgy, 2.3, DS]
	[8, Mohamed Saleh, 2.4, CS]
	[10, Mohanad Bahaa, 2.9, IT]
	[7, Mai Adel, 3.1, IS]
	[2, Mona Samir, 3.2, IT]
	[11, Hana Sobhy, 3.2, IT]
	[1, Mohamed Ali, 3.4, CS]
	[5, Omnia Osama, 3.6, IS]
	[6, Ahmed Omar, 3.9, CS]
	>>> Max Heap <<<
	Enter number of option: 1
	id: 11
	Name: Hana Sobhy
	GPA: 3.2
	Department: IT
	The student is added.
	Print 12 studnts.
	[6, Ahmed Omar, 3.9, CS]
	[5, Omnia Osama, 3.6, IS]
	[1, Mohamed Ali, 3.4, CS]
	[2, Mona Samir, 3.2, IT]
	[11, Hana Sobhy, 3.2, IT]
	[7, Mai Adel, 3.1, IS]
	[10, Mohanad Bahaa, 2.9, IT]
	[8, Mohamed Saleh, 2.4, CS]
	[4, Magy Madgy, 2.3, DS]
	[9, Hany Mohsen, 1.8, DS]
	[3, Ola Maher, 1.2, CS]
	*/
	
}

