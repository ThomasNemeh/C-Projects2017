
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <initializer_list>
using std::initializer_list;


// TODO your code goes here:

template<typename T>
class LinkedList {

private:
	Node<T>* header;

	Node<T>* tail;

	int numberElements;

public:
	LinkedList() : header(nullptr), tail(nullptr), numberElements(0) {}

	LinkedList(std::initializer_list<T> l){
		if (l.size() < 1) {
			header = nullptr;
			tail = nullptr;
			numberElements = 0;
			return;
		}
		else if (l.size() == 1) {
			Node<T>* node = new Node<T>(l.begin()[0]);
			header = node;
			tail = header;
			numberElements = 1;
		}
		else {
			Node<T>* node = new Node<T>(l.begin()[0]);
			header = node;
			numberElements = 1;
			Node<T>* newNode;
			for (int i = 1; i < l.size() - 1; i++) {
				newNode = new Node<T>(l.begin()[i]);
				newNode->previous = node;
				node->next = newNode;
				node = newNode;
				numberElements++;
			}
			tail = new Node<T>(l.begin()[l.size() - 1]);
			tail->previous = node;
			node->next = tail;
			if (l.size() == 2) {
				delete newNode;
			}
		}


	}

	void push_front(T data) {
		if (numberElements == 0) {
			Node<int> *newNode = new Node<int>(data);
			tail = newNode;
			header = newNode;
			numberElements++;
		}
		else {
			Node<int> *newNode = new Node<int>(data);
			newNode->next = header;
			header->previous = newNode;
			header = newNode;
			numberElements++;
		}

	}

	T & front() {
		return header->data;
	}

	void push_back(T data) {
		if (numberElements == 0) {
			Node<int> *newNode = new Node<int>(data);
			tail = newNode;
			header = newNode;
			numberElements++;
		}
		else {
			Node<int> *newNode = new Node<int>(data);
			newNode->previous = tail;
			tail->next = newNode;
			tail = newNode;
			numberElements++;
		}
	}

	T & back() {
			return tail->data;
	}

	int size() {
		return numberElements;
	}

	NodeIterator<T> begin() {
		NodeIterator<T> head(header);
		return head;
	}

	NodeIterator<T> end() {
		NodeIterator<T> finis(tail->next);
		return finis;
	}

	NodeIterator<T> insert(NodeIterator<T> pos, T data) {
		Node<T>* currentNode = pos.get();
		Node<T>* prevNode = currentNode->previous;
		Node<T>* newNode = new Node<T>(data);
		if (currentNode == header) {
			header = newNode;
		}
		newNode->previous = prevNode;
		prevNode->next = newNode;
		newNode->next = currentNode;
		currentNode->previous = newNode;
		NodeIterator<T> newPos(newNode);
		return newPos;
	}

	NodeIterator<T> erase(NodeIterator<T> pos) {
		Node<T>* currentNode = pos.get();
		Node<T>* nextNode = currentNode->next;
		if (currentNode == header) {
			header = nextNode;
			header->previous = nullptr;
			NodeIterator<T> node(header);
			return node;
		}
		Node<T>* prevNode = currentNode->previous;
		if (currentNode == tail) {
			tail = prevNode;
			tail->next = nullptr;
			NodeIterator<T> node(nullptr);
			return node;
		}
		prevNode->next = nextNode;
		nextNode->previous = prevNode;
		NodeIterator<T> node(nextNode);
		return node;
	}

	~LinkedList() {
		while (header != nullptr) {
			Node<int> *nextNode = header->next;
			delete header;
			header = nextNode;
		}
	}

};



// do not edit below this line

#endif
