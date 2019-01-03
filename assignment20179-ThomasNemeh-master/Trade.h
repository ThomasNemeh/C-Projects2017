#ifndef TRADE_H
#define TRADE_H

#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cstdint>

// Do not add any extra #includes without asking on the KEATS discussion forum

// TODO your code goes here:
template<typename Iterator>
int bestProfit(Iterator start, Iterator end) {
/*
	transform(start, end, start,[start,end](const int x) {return *std::max_element(
			        start,
			        end,
			        [](const int & a, const int & b)
			        {
						return a < b;
			        }
			    ) - x;
	});
*/
	Iterator z = std::max_element(
				        start,
				        end,
				        [start,end](const int & x, const int & y)
				        {
							return *std::max_element(
							        find(start,end,x),
							        end,
							        [](const int & a, const int & b)
							        {
										return a < b;
							        }
							    ) - x < *std::max_element(
							    		find(start,end,y),
								        end,
								        [](const int & a, const int & b)
								        {
											return a < b;
								        }
								    ) - y;
				        }
				    );


	Iterator zed = std::max_element(
	        z,
	        end,
	        [](const int & a, const int & b)
	        {
				return a < b;
	        }
	    );


	return *zed - *z;

}





// Don't write any code below this line

#endif
