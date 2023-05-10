#include "BST.h"
#define _PATH_ "Students.txt"
BST::BST() {
	root = nullptr;
}

BST::~BST() {
	root = nullptr;
}

bool BST::isEmpty()
{
	return root == nullptr;
}

Student* BST::search(const int& studentID)
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

BSTNode<Student>* BST::getRoot() {
	return root;
}

void BST::BSTMenu()
{
	loadFile("Students.txt");
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

void BST::printNodeData(BSTNode<Student>* node) {
	if (node != nullptr)
		cout << node->data;
}

void BST::loadFile(string fileName)
{
	string myText;
	ifstream MyReadFile(_PATH_);
	int counter = 0;
	int ID = 0;
	string name = "", department = "";
	float GPA = 0;
	getline(MyReadFile, myText); // read first lINE which is the  number of students
	while (getline(MyReadFile, myText)) {
		if (counter == 0)
		{
			ID = stoi(myText);
		}
		else if (counter == 1)
		{
			name = myText;

		}
		else if (counter == 2)
		{

			GPA = stof(myText);
		}
		else
		{
			department = myText;
			insert(ID, name, GPA, department);
			counter = -1;
		}
		counter += 1;
	}
	MyReadFile.close();
}

void BST::inOrderTraverse(BSTNode<Student>* node)
{
	if (node != nullptr) {
		inOrderTraverse(node->getLeft());
		cout << node->getData();
		inOrderTraverse(node->getRight());
	}
}

void BST::printDeptCount() {
	cout << "Number of Students in each Department:\n";
	for (auto itr = getDeptStudent().begin(); itr != getDeptStudent().end(); itr++) {
		cout << itr->first << ": " << itr->second << endl;
	}
}

int BST::studentsCount() {
	int result = 0;
	for (auto itr = getDeptStudent().begin(); itr != getDeptStudent().end(); itr++) {
		result += itr->second;
	}
	return result;
}

void BST::insert(const int& studentID, const string& name, const float& GPA, const string& department)
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

void BST::remove(const int& studentID)
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


