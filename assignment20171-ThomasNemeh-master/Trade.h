#ifndef TRADE_H
#define TRADE_H


#include "vector.h"
using pep::vector;


class Trade {
protected:
    int buyTime;
    int sellTime;

public:
    Trade(const int buyTimeIn, const int sellTimeIn)
        : buyTime(buyTimeIn), sellTime(sellTimeIn) {
    }

    int getBuyTime() const {
        return buyTime;
    }

    int getSellTime() const {
        return sellTime;
    }

};

// TODO your code goes here:
vector<int> maxPrice();

Trade bestBuySellTime(vector<int> prices) {
	int high = 0;
	int highValue;
	int lowValue;
	int low = 0;
	int profit = 0;
	for (int x = prices.size() - 1; x >= 1; x--) {
		if (prices[x] > profit) {
		for (int y = x - 1; y >= 0; y--) {
			highValue = prices[x];
			lowValue = prices[y];
			if (highValue - lowValue > profit) {
				high = x;
				low = y;
				profit = highValue - lowValue;
			}
			}
		}
	}

	return Trade(low, high);
}

vector<int> maxPrice(vector<int> a) {
	return a;
}

// Don't write any code below this line

#endif
