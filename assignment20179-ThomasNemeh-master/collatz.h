#ifndef COLLATZ_H
#define COLLATZ_H

#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cstdint>
#include "counting_iterator.h"
#include "transformreduce.h"

// Do not add any extra #includes without asking on the KEATS discussion forum
uint64_t helper(uint64_t n, uint64_t x) {
	if (n == 1) {
		return x;
	}
	else if (n % 2 == 0) {
		return helper(n / 2, x + 1);
	}
	else {
		return helper(n * 3 + 1, x + 1);
	}
}

uint64_t collatz(uint64_t n) {
	return helper(n, 1);
}

std::pair<uint64_t, uint64_t> collatz_max(uint64_t bound) {

	uint64_t biggestCollatz = transform_reduce(
	 counting_iterator<uint64_t>(1), counting_iterator<uint64_t>(bound),
	 1,
	 [](const uint64_t ans, const uint64_t transf) {
		if (collatz(ans) > collatz(transf)) {
			return ans;
		}
		else {
			return transf;
		}
	 },
	 [](const uint64_t nextElem) {
		 return nextElem;
	 }
	);

	return std::pair<uint64_t, uint64_t>(collatz(biggestCollatz), biggestCollatz);


}

// Do not edit anything below this line

#endif
