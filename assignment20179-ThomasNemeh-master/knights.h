#ifndef KNIGHTS_H
#define KNIGHTS_H

#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cstdint>

// Do not add any extra #includes without asking on the KEATS discussion forum

using std::pair;
using std::make_pair;
using std::vector;

typedef vector<pair<int,int> > Path;

/** Helper function: adds two pairs of ints */
pair<int,int> operator+(const pair<int,int> & a, const pair<int,int> & b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

// TODO - your code goes here

Path moves(pair<int,int> position) {
	Path change;
	change.emplace_back(pair<int,int>(-2,1)); change.emplace_back(pair<int,int>(-1,2));
	change.emplace_back(pair<int,int>(1,2)); change.emplace_back(pair<int,int>(2,1));
	change.emplace_back(pair<int,int>(2,-1)); change.emplace_back(pair<int,int>(1,-2));
	change.emplace_back(pair<int,int>(-1,-2)); change.emplace_back(pair<int,int>(-2,-1));

	Path newChange(change.size());
	transform(change.begin(), change.end(), newChange.begin(),[position](const pair<int,int> x) {return position + x;});
	return newChange;
}

Path legal_moves(const int size, Path pastMoves, pair<int,int> position) {
	Path movesPossible = moves(position);
	Path final;
	copy_if(movesPossible.begin(), movesPossible.end(),
		 back_inserter(final),
		 [size, pastMoves](const pair<int,int> x) {
		 return (std::get<0>(x) >= 0 && std::get<0>(x) < size && std::get<1>(x) >= 0 && std::get<1>(x) < size 
				 && find(pastMoves.begin(), pastMoves.end(), x) == pastMoves.end());
		 });
	return final;
}

pair<Path,bool> first_tour_helper(const int size, Path path, pair<int,int> position) {
	path.emplace_back(position);
	if (path.size() == size * size) {
		return pair<Path,bool>(path,true);
	}

	Path legalMoves = legal_moves(size, path, path.back());

	for (int i = 0; i < legalMoves.size(); i++) {
		pair<Path,bool> returnTour = first_tour_helper(size,path,legalMoves[i]);
		if (std::get<1>(returnTour)) {
			return returnTour;
		}
	}
	Path emptyPath;
	return pair<Path,bool>(emptyPath, false);
}

pair<Path,bool> first_tour(const int size, Path path) {
	pair<int,int> pos = path.back();
	path.pop_back();
	return first_tour_helper(size, path, pos);
}





// Do not edit below this line

#endif
