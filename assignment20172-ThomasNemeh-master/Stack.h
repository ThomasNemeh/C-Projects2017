#ifndef STACK_H
#define STACK_H

#include "vector.h"
using pep::vector;
#include <string>
using std::string;
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;

// TODO: Your code for question 3 goes here
class Stack {
	private:
		vector<double> numbers;
	public:

		Stack() {};

		bool empty() {
			if (numbers.size() == 0) {
				return true;
			}
			else {
				return false;
			}
		}

		double pop() {
			double lastElement = numbers[numbers.size() - 1];
			numbers.pop_back();
			return lastElement;
		}

		void push(double x) {
			numbers.push_back(x);
		}
};

double evaluate(string expression) {
			Stack s;
			int start = 0;
			unsigned int index = 0;
			int substrLength = 0;
			string str = "";
			double first = 0.0;
			double second = 0.0;
			double number = 0.0;
			double answer = 0.0;
			while (index < expression.length()) {
				start = index;
				substrLength = 0;
				while (expression[index] != ' ' && index < expression.length()) {
					substrLength++;
					index++;
				}
				index++;
				str = expression.substr(start, substrLength);
				if (str == "+") {
					second = s.pop();
					first = s.pop();
					answer = first + second;
					//cout << first << " + " << second << endl;
					s.push(answer);
				}
				else if (str == "-") {
					second = s.pop();
					first = s.pop();
					answer = first - second;
					//cout << first << " - " << second << endl;
					s.push(answer);
				}
				else if (str == "*") {
					second = s.pop();
					first = s.pop();
					answer = first * second;
					//cout << first << " * " << second << endl;
					s.push(answer);
				}
				else if (str == "/") {
					second = s.pop();
					first = s.pop();
					answer = first / second;
					//cout << first << " / " << second << endl;
					s.push(answer);
				}
				else {
					std::stringstream ss;
					ss << str;
					ss >> number;
					s.push(number);
				}
			}
			return s.pop();
		}


// Do not write anything below this line

#endif


