#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H


#include "vector.h"
using pep::vector;


/** TODO: complete the definition of the class CircularBuffer here
 *
 * Its constructor should take the size of the buffer as an argument
 *
 * It needs to have the functions:
 * - count() which returns how many things are in the buffer
 * - full() which returns true iff the buffer is full
 * - add() which takes an element and adds it to the buffer (you can assume the buffer is not full)
 * - remove() which removes the next element from the buffer (you can assume the buffer is not empty)
 */
class CircularBuffer {
private:
	vector<char> buffer;

	int numElements;

	int lastOccupiedSpace;

	int firstAdd;

	int nextInLine;

public:
	CircularBuffer(int capacity) {
		vector<char>temp(capacity);
		buffer = temp;
		numElements = 0;
		lastOccupiedSpace = 0;
		firstAdd = 0;
	}

	int count() {
		return numElements;
	}

	bool full() {
		return numElements == buffer.size();
	}

	void add(char c) {
		if (firstAdd == 0) {
			firstAdd = 1;
			nextInLine = 0;
			lastOccupiedSpace = 0;
			buffer[0] = c;
		}
		else if (lastOccupiedSpace < buffer.size() - 1) {
			buffer[lastOccupiedSpace + 1] = c;
			lastOccupiedSpace = lastOccupiedSpace + 1;
		}
		else {
			buffer[0] = c;
			lastOccupiedSpace = 0;
		}
		numElements++;
	}

	char remove() {
		char returnThis = buffer[nextInLine];
		numElements--;
		if (nextInLine == buffer.size() - 1) {
			nextInLine = 0;
		}
		else {
			nextInLine = nextInLine + 1;
		}

		return returnThis;
	}
};


// don't write any code below this line

#endif

