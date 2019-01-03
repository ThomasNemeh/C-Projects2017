#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:
template<typename T>
class TreeNode {
public:
	T data;

	unique_ptr<TreeNode> leftChild;

	unique_ptr<TreeNode> rightChild;

	TreeNode* parent;

	TreeNode(T dataPiece) : data(dataPiece), parent(nullptr) {}

	void setLeftChild(TreeNode* child) {
		leftChild.reset(child);
		leftChild->parent = this;
	}

	void setRightChild(TreeNode* child) {
		rightChild.reset(child);
		rightChild->parent = this;
	}

	void write(std::ostream & o) const {
		if (leftChild) {
			leftChild->write(o);
		}
		o << " " << data << " ";

		if (rightChild) {
			rightChild->write(o);
		}
	}

	TreeNode<T>* findRoot() {
	    if (parent) {
	    	TreeNode<T>* v = parent;
	    	while (v->parent != nullptr) {
	    		v = v->parent;
	    	}
	    	return v;
	    }
	    else {
	    	return nullptr;
	    }
	}

	int maxDepth() {
		return findDepth(1);
	}

	int findDepth(int x) {
		if (!leftChild && !rightChild) {
			return x;
		}
		else if (leftChild && !rightChild) {
			return leftChild->findDepth(x + 1);
		}
		else if (!leftChild && rightChild) {
			return rightChild->findDepth(x + 1);
		}
		else {
			int l = leftChild->findDepth(x+1);
			int r = rightChild->findDepth(x+1);
			if (l > r) {
				return l;
			}
			else {
				return r;
			}
		}
	}

	T getData() {
		return data;
	}

};

template<typename T>
class TreeNodeIterator {

private:

    TreeNode<T>* current;

public:

    TreeNodeIterator(TreeNode<T>* currentIn)
        : current(currentIn) {
    }

    T & operator*() {
        return current->data;
    }

    // TODO: complete the code for NodeIterator here

    void operator++() {
    	if (current->rightChild) {
    		current = current->rightChild.get();
    		while (current->leftChild) {
    			current = current->leftChild.get();
    		}
    	}
    	else {
    		if (current->parent) {
    			if (current->parent->data > current->data ) {
    				current = current->parent;
    			}
    			else if (current->parent->data < current->data) {
    				if (current->findRoot()->data > current->data) {
    					current = current->findRoot();
    				}
    				else {
    					current = nullptr;
    				}
    			}
    		}
    		else {
    			current = nullptr;
    		}
    	}
    }

    bool operator==(const TreeNodeIterator<T>& rhs) {
    	return current == rhs.current;
    }

    bool operator!=(const TreeNodeIterator<T>& rhs) {
        	return !(current == rhs.current);
    }

};


// do not edit below this line

#endif
