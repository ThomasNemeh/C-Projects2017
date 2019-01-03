#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <set>
using std::set;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <sstream>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;
#include<math.h>
using std::pair;
#include <memory>
using std::unique_ptr;

class Sudoku : public Searchable {
public:
	int size;
	vector<vector<set<int>>> sBoard;
	set<pair<int, int>> pairs;

	Sudoku(int length) {
		size = length;
		vector<set<int>> boardRow;
		set<int> s;
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				for (int i = 1; i <= size; ++i) {
					s.insert(i);
				}
				boardRow.push_back(s);
				s.clear();
			}
			sBoard.push_back(boardRow);
			boardRow.clear();
		}
		//cout << "size: " << sBoard[1][1].size() << endl;
	}

/*
	Sudoku(Sudoku* x) {
		size = x->size;
		sBoard = x->sBoard;
		pairs = x->pairs;
	}
*/

	int getSquare(int row, int col) {
		if (sBoard[row][col].size() != 1) {
			return -1;
		}
		else {
			return *sBoard[row][col].begin();
		}
	}

	bool setSquare(int row, int col, int value) {
		vector<vector<int>> list;
				vector<int> values;
				values.push_back(value);
				values.push_back(row);
				values.push_back(col);
				list.push_back(values);
				while (list.size() > 0) {
					col = list[0][2];
					list[0].pop_back();
					row = list[0][1];
					list[0].pop_back();
					value = list[0][0];
					list[0].pop_back();
					sBoard[row][col].clear();
					sBoard[row][col].insert(value);
					for (int i = 0; i < size; i++) {
						if (i != col) {
								sBoard[row][i].erase(value);
								pair<int, int> pair(row,i);
								if (sBoard[row][i].size() == 1 && pairs.find(pair) == pairs.end()) {
									values.clear();
									values.push_back(*sBoard[row][i].begin());
									values.push_back(row);
									values.push_back(i);
									list.push_back(values);
									pairs.insert(pair);
								}
								else if (sBoard[row][i].size() == 0) {
									return false;
								}

						}
					}
					for (int i = 0; i < size; i++) {
						if (i != row) {
								sBoard[i][col].erase(value);
								pair<int, int> pair(i,col);
								if (sBoard[i][col].size() == 1 && pairs.find(pair) == pairs.end())  {
									values.clear();
									values.push_back(*sBoard[i][col].begin());
									values.push_back(i);
									values.push_back(col);
									list.push_back(values);
									pairs.insert(pair);
								}
								else if (sBoard[i][col].size() == 0) {
									return false;
								}

						}
					}

					int squareSize = sqrt(size);
					int boxRow;
					int boxCol;
					int rowM;
					if (row < squareSize) {
						boxRow = 0;
					}
					else {
						rowM = row / squareSize;
						boxRow = rowM * squareSize;
					}
					int colM;
					if (col < squareSize) {
						boxCol = 0;
					}
					else {
						colM = col / squareSize;
						boxCol = colM * squareSize;
					}

					for (int x = boxRow; x < boxRow + squareSize; x++) {
						for (int y = boxCol; y < boxCol + squareSize; y++) {
							if (x != row && y != col) {
								sBoard[x][y].erase(value);
								pair<int, int> pair(x,y);
								if (sBoard[x][y].size() == 1 && pairs.find(pair) == pairs.end()) {
									values.clear();
									values.push_back(*sBoard[x][y].begin());
									values.push_back(x);
									values.push_back(y);
									list.push_back(values);
									pairs.insert(pair);
								}
								else if (sBoard[x][y].size() == 0) {
									return false;
								}
							}
						}
					}

					list.erase(list.begin());

				}

				return true;

			}

	bool isSolution() const{
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				if (sBoard[x][y].size() > 1) {
					return false;
				}
			}
		}
		return true;
	}

	void write(ostream & o) const{
		cout << "hi";
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				if (sBoard[x][y].size() == 1) {
					o << *sBoard[x][y].begin();
				}
				else {
					o << " ";
				}
			}
			o << endl;
		}
	}

	vector<unique_ptr<Searchable> > successors() const{

			vector<unique_ptr<Searchable> > success;
			int row;
			int col;
			for (int x = 0; x < size; x++) {
				for (int y = 0; y < size; y ++) {
					if (sBoard[x][y].size() > 1) {
						row = x;
						col = y;
					}
				}
			}
			for (int i = 0; i < sBoard[row][col].size(); i++) {
				int x = *std::next(sBoard[row][col].begin(), i);
				cout << x << endl;
				Sudoku* copySudoku = new Sudoku(*this);
				if (copySudoku->setSquare(row, col, x)) {
					success.emplace_back(copySudoku);
				}
				else {
					delete copySudoku;
				}
			}

			return success;

		}




};



#endif
