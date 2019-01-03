#ifndef MAPOFITEMS_H
#define MAPOFITEMS_H

#include "Item.h"
#include <vector>
using std::vector;

// TODO: your code goes here
class MapOfItems {
private:
	vector<Item> items;
public:

	void addItem(Item item) {
		items.push_back(item);
	}

	int size () {
		return items.size();
	}

	vector<Item> getTour(double walkingSpeed) {
		double time = 0;
		vector<Item> tour;
		double earliestTime = 3600;
		int erasePosition;
		vector<Item> itemsCopy = items;
		Item item(-1,-1,"a",-1);
		bool continueOn = false;
		for (int i = 0; i < itemsCopy.size(); i++) {
			if (itemsCopy[i].getTimeAvailable() < earliestTime) {
				earliestTime = itemsCopy[i].getTimeAvailable();
				time = earliestTime;
				erasePosition = i;
				item = itemsCopy[i];
				continueOn = true;
			}
		}
		while (time < 3600 && continueOn && itemsCopy.size() > 0) {
			itemsCopy.erase(itemsCopy.begin() + erasePosition);
			tour.push_back(item);
			earliestTime = 3600;
			continueOn = false;
			for (int i = 0; i < itemsCopy.size(); i++) {
				int visitTime = visit(item, itemsCopy[i], time, walkingSpeed);
				if (visitTime < earliestTime) {
					earliestTime = visitTime;
					erasePosition = i;
				}
			}
			if (earliestTime != time && earliestTime != 3600) {
				time = earliestTime;
				item = itemsCopy[erasePosition];
				continueOn = true;
			}
		}
		return tour;
	}

	double visit(Item start, Item end, double time, double speed) {
		int timeX = end.distanceTo(start);
		int timeTo = start.distanceTo(end) / (speed);
		double visit1 = 3600;
		double fifteenMin = 60 * 15;
		if (time + timeTo < end.getTimeAvailable()) {
			visit1 = end.getTimeAvailable();

		}
		else if (time + timeTo >= end.getTimeAvailable() && time + timeTo <= end.getTimeAvailable() + fifteenMin) {
			visit1 = time + timeTo;
		}
		return visit1;
	}
};




// don't write any code below this line

#endif

