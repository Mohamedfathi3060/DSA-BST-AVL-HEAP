// DS-ASS3-student-trees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;




template<class T>
class AVLNode {
public:
	T key;
	AVLNode* right;
	AVLNode* left;
	int freq;
	int height;
	AVLNode(T val = 0) {
		this->key = val;
		this->height = 0;
		this->freq = 0;
		right = left = NULL;
	}
	void updateHeight()
	{
		height = 1 + max((left == NULL ? -1 : left->height), (right == NULL ? -1 : right->height));
	}
	int BF() {
		if (this == NULL) return 0;

		return (left == NULL ? -1 : left->height) - (right == NULL ? -1 : right->height);
	}
};




template<class T>
class AVL {
private:
	AVLNode<T>* root;

	AVLNode<T>* rightRotation(AVLNode<T>*& node) {
		AVLNode<T>* child = node->left;
		node->left = child->right;
		child->right = node;

		child->updateHeight();
		node->updateHeight();

		return child;

	}
	AVLNode<T>* leftRotation(AVLNode<T>* node) {
		AVLNode<T>* child = node->right;
		node->right = child->left;
		child->left = node;

		child->updateHeight();
		node->updateHeight();


		return child;
	}
	void balance(AVLNode<T>*& node) {
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

	}

public:
	AVL() {
		root = NULL;
	}


	AVLNode<T>* insert(AVLNode<T>*& root, T el) {
		if (root == NULL) {
			return new AVLNode<T>(el);
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


		/*calc node BF {BALANACE FACTOR}*/
		/*
			ROTATE IS  {as -1 or 1 node}

			- TAKE IT AS RIGHT CHILD "IF R ROTATION"
			- RAKE IT AS LEFT CHILD  "IF L ROTATION"

			- HIS PARENT BECOME MY PARENT

			- MY SON BECOME HIS LEFT SON "IS r ROTAION"
			- MY SON BECOME HIS RIGHT SON "IS l ROTAION"

			ROTATE IS  {as -2 or 2 node}

			- TAKE ME AS YOUR LEFT  CHILD "IF l ROTAION"
			- TAKE ME AS YOUR RIGHT CHILD "IF R ROTAION"

			- MY PARENT BECOME YOUR PARENT

			- YOUR SON BECOME MY LEFT  CHILD "IF R ROTAION"
			- YOUR SON BECOME MY RIGHT CHILD "IF L ROTAION"

			THATS all

		*/

		balance(root);


		return root;
	}
	void insert(T el) {
		root = insert(root, el);
	}

	void BFS() {
		queue<AVLNode<T>*> Q;
		AVLNode<T>* curr = root;
		Q.push(curr);
		cout << curr->key << "=>" << curr->height << "\n";
		while (!Q.empty())
		{
			curr = Q.front();
			Q.pop();
			if (curr->left != NULL) {
				Q.push(curr->left);
				cout << curr->left->key << "=>" << curr->left->height << "    :    ";
			}
			if (curr->right != NULL) {
				Q.push(curr->right);
				cout << curr->right->key << "=>" << curr->right->height << "    :    ";
			}
			cout << "\n";
		}

	}
};













int main()
{
    cout << "Hello World!\n";
}

