#ifndef MAXIMUM_GATES_H
#define MAXIMUM_GATES_H

#include <vector>
using std::vector;

#include <iostream>
using namespace std;

// TODO: Your answer for question 2 goes here
int maximumGates(vector<int> arrives, vector<int> departs) {
	int maxGates = 0;
	int numberGates;
	int arrivalTime;
	for (int i = 0; i < arrives.size(); i++) {
		numberGates = 1;
		arrivalTime = arrives[i];
		for (int x = 0; x < i; x++) {
			if (departs[x] > arrivalTime) {
				numberGates++;
			}
		}
		if (numberGates > maxGates) {
			maxGates = numberGates;
		}
	}

	return maxGates;
}

// Do not write any code below this line


#endif
