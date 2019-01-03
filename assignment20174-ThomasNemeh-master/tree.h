#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:
template<typename T>
class BinarySearchTree {
public:
	unique_ptr<TreeNode<T>> root;

public:

	void write(ostream & o) const {
		root->write(o);
	}

	TreeNode<T>* insert(T data) {
		//return insert3(data);
		if (!root) {
			TreeNode<T>* insertThis(new TreeNode<T>(data));
			root.reset(insertThis);
			return insertThis;
		}
		return insert2(data, root);
	}

	TreeNode<T>* insert2(T thisData, unique_ptr<TreeNode<T>> & node) {
		if (thisData < node->data) {
			if (!node->leftChild) {
				TreeNode<T> *left (new TreeNode<T>(thisData));
				node->setLeftChild(left);
				if (left->parent->parent != nullptr) {
					if (left->parent->parent->leftChild) {
						if (!left->parent->parent->rightChild) {
							rightRotate(left);
						}
					}
					else if (left->parent->parent->rightChild) {
						if (!left->parent->parent->leftChild) {
							rightLeftRotate(left);
						}
					}
				}

				return left;
			}
			else {
				insert2(thisData, node->leftChild);
			}
		}
		else if (node->data < thisData) {
			if (!node->rightChild) {
				TreeNode<T>* right (new TreeNode<T>(thisData));
				node->setRightChild(right);
				if (right->parent->parent != nullptr) {
					if (right->parent->parent->rightChild) {
						if (!right->parent->parent->leftChild) {
							leftRotate(right);
						}
					}
					else if (right->parent->parent->leftChild) {
						if (!right->parent->parent->rightChild) {
							leftRightRotate(right);
						}
					}
				}
				return right;
			}
			else {
				insert2(thisData, node->rightChild);
			}
		}
		else {
			return node.get();
		}
	}

	void rightRotate(TreeNode<T>* node) {
		TreeNode<T>* A = new TreeNode<T> (node->data);
		TreeNode<T>* B = new TreeNode<T> (node->parent->data);
		TreeNode<T>* C = new TreeNode<T> (node->parent->parent->data);
		B->setRightChild(C);
		B->setLeftChild(A);
		if (node->parent->parent->parent != nullptr) {
			if (node->parent->parent->parent->data < B->data) {
				node->parent->parent->parent->setRightChild(B);
			}
			else {
				node->parent->parent->parent->setLeftChild(B);
			}
		}
		else {
			root = nullptr;
			this->insert(B->data);
			root->setRightChild(C);
			root->setLeftChild(A);
		}
		A = nullptr;
		B = nullptr;
		C = nullptr;
	}

	void leftRotate(TreeNode<T>* node) {
		TreeNode<T>* A = new TreeNode<T> (node->data);
		TreeNode<T>* B = new TreeNode<T> (node->parent->data);
		TreeNode<T>* C = new TreeNode<T> (node->parent->parent->data);
		B->setLeftChild(C);
		B->setRightChild(A);
		if (node->parent->parent->parent != nullptr) {
			if (node->parent->parent->parent->data < B->data) {
				node->parent->parent->parent->setRightChild(B);
			}
			else {
				node->parent->parent->parent->setLeftChild(B);
			}

		}
		else {
			root = nullptr;
			this->insert(B->data);
			root->setRightChild(A);
			root->setLeftChild(C);
		}
		A = nullptr;
				B = nullptr;
				C = nullptr;

	}

	void leftRightRotate(TreeNode<T>* node) {
			TreeNode<T>* A = new TreeNode<T> (node->data);
			TreeNode<T>* B = new TreeNode<T> (node->parent->data);
			TreeNode<T>* C = new TreeNode<T> (node->parent->parent->data);
			A->setRightChild(C);
			A->setLeftChild(B);
			if (node->parent->parent->parent != nullptr) {
				if (node->parent->parent->parent->data < B->data) {
					node->parent->parent->parent->setRightChild(B);
				}
				else {
					node->parent->parent->parent->setLeftChild(B);
				}
			}
			else {
				root = nullptr;
				this->insert(A->data);
				root->setRightChild(C);
				root->setLeftChild(B);
			}
		}

	void rightLeftRotate(TreeNode<T>* node) {
			TreeNode<T>* A = new TreeNode<T> (node->data);
			TreeNode<T>* B = new TreeNode<T> (node->parent->data);
			TreeNode<T>* C = new TreeNode<T> (node->parent->parent->data);
			A->setLeftChild(C);
			A->setRightChild(B);
			if (node->parent->parent->parent != nullptr) {
				if (node->parent->parent->parent->data < B->data) {
					node->parent->parent->parent->setRightChild(A);
				}
				else {
					node->parent->parent->parent->setLeftChild(A);
				}

			}
			else {
				root = nullptr;
				this->insert(A->data);
				root->setRightChild(B);
				root->setLeftChild(C);
			}
			A = nullptr;
					B = nullptr;
					C = nullptr;
		}

	TreeNode<T>* find(T data) {
		if (!root) {
			return nullptr;
		}
		else {
			TreeNode<T>* v = root.get();
			bool complete = false;
			while (v != nullptr &&  complete == false ) {
				if (data < v->data) {
					v = v->leftChild.get();
				}
				else if (v->data < data) {
					v = v->rightChild.get();
				}
				else {
					complete = true;
				}
			}
			return v;
		}
	}

	TreeNodeIterator<T> begin() {
		if (!root) {
			return nullptr;
		}
		TreeNode<T>* v = root.get();
		while (v->leftChild) {
			v = v->leftChild.get();
		}
		TreeNodeIterator<T> first (v);
		return first;
	}

	TreeNodeIterator<T> end() {
		return nullptr;
	}

	int maxDepth() {
		if (!root) {
			return 0;
		}
		else {
			return root->maxDepth();
		}
	}


};


// do not edit below this line

#endif
