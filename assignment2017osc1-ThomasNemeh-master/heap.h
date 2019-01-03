#ifndef HEAP_H
#define HEAP_H

#include <cstddef>
#include <new>

#include <iostream>
using std::cout;
using std::endl;

class MemControlBlock {

public:

    /** @brief True if the MemControlBlock is before a block of available memory */
    bool available;

    /** @brief The size of the following block of memory, in bytes */
    size_t size;

    MemControlBlock * previous;
    MemControlBlock * next;

    MemControlBlock(const bool availableIn, const int sizeIn)
        : available(availableIn), size(sizeIn),
          previous(nullptr), next(nullptr)
    {
    }

};

class Heap {

private:
    char * const memory;

    /** @brief The first MemControlBlock for the heap -- the head of the list */
    MemControlBlock * startOfHeap;

public:

    ~Heap() {
        delete [] memory;
    }

    // no copy constructor, move constructor, assignment operator, ...
    Heap(const Heap &) = delete;
    Heap(Heap &&) = delete;
    Heap & operator=(const Heap &) = delete;
    Heap & operator=(Heap &&) = delete;

    Heap(const size_t sizeIn)
        : memory(new char[sizeIn]) {

        // make a MemControlBlock at the start of the reserved memory
        startOfHeap = new(memory) MemControlBlock(// true = is available
                                                  true,
                                                  // size = the size of the heap - the size of the MemControlBlock a the start of the heap
                                                  sizeIn - sizeof(MemControlBlock)
                                                 );
    }

    /** @brief Used for debugging - get the address of the start of the heap */
    char* getStartOfHeap() const {
        return memory;
    }

    /** @brief Used for debugging -- print out the details of the MemControlBlocks on the heap */
    void print() const {
        MemControlBlock * curr = startOfHeap;

        for (int i = 0; curr; ++i, curr = curr->next) {
            cout << "Block " << i << ": ";
            if (curr->available) {
                cout << " free, ";
            } else {
                cout << " in use, ";
            }
            cout << curr->size << " bytes\n";
        }

    }


    /** @brief Request a block of memory of the given size
     *
     * Uses the 'Worst Fit' algorithm to choose a suitable block of available memory
     *
     * Returns the memory address of the start of the requested memory
     * If no block is big enough, it returns nullptr.
     */
    char * allocateMemoryWorstFit(size_t requested) {
        // TODO: your code for allocateMemory memory goes here
    	MemControlBlock * maxSize = startOfHeap;
    	MemControlBlock * curr = startOfHeap;
    	char * address = getStartOfHeap();
    	char * maxAddress = getStartOfHeap();
    	size_t rounded = requested;

    	if (requested % 4 != 0) {
    		for (int i = 1; i < 4; i++) {
    			rounded = rounded + i;
    			if (rounded % 4 == 0) {
    				break;
    			}
    		}
    	}

    	while (curr != nullptr) {
    		if (curr->available && curr->size > maxSize->size) {
    			maxSize = curr;
    			maxAddress = address;
    		}
    		address = address + sizeof(MemControlBlock) + curr->size;
    		curr = curr-> next;
    	}

    	if (maxSize->size < requested + sizeof(MemControlBlock)) {
    		return nullptr;
    	}

    	maxSize-> available = false;

    	size_t spareSpace = maxSize->size - requested;
    	if (spareSpace > sizeof(MemControlBlock)) {
    		MemControlBlock * newBlock = new(maxAddress + sizeof(MemControlBlock) + requested) MemControlBlock(true, spareSpace);
    		MemControlBlock * next = maxSize->next;
    		maxSize->next = newBlock;
    		newBlock->next = next;
    		newBlock->previous = maxSize;
    		if (next != nullptr) {
    			next->previous = newBlock;
    		}
    		maxSize->size = requested;
    	}
    	return maxAddress + sizeof(MemControlBlock);

    }

    /** @brief Deallocate the memory used by the object at the given address */
    void deallocateMemory(char * toDeallocate) {
        // TODO: your code for deallocateMemory memory goes here

    	char * address = toDeallocate - sizeof(MemControlBlock);
    	char * pointer = getStartOfHeap();
    	MemControlBlock * curr = startOfHeap;

    	while (address != pointer) {
    		pointer = pointer + sizeof(MemControlBlock) + curr->size;
    		curr = curr->next;
    	}
    	int counter = 1;
    	curr->available = true;
    	MemControlBlock * prev = curr->previous;
    	while (prev != nullptr && prev->available) {
    		prev->size = prev->size + sizeof(MemControlBlock) + curr->size;
    		prev->next = curr->next;
    		prev->next->previous = prev;
    		prev->available = true;
    		curr = prev;
    		prev = curr->previous;
    		counter++;
    	}

    }
};

#endif
