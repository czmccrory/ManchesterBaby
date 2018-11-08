#include <iostream>
#include <vector>
#include "line.h"


//this should not be here
void printVector(vector<bool> * v) {
	vector<bool>::iterator it;
	for (it=v->begin(); it != v->end(); ++it) {
		cout << *it << " " <<flush;
	}
	cout <<endl;
	
}

void Line::print(){
	printVector(line);
}

Line::Line() {
	line =  new vector<bool>(32, 0);
}

Line::~Line() {
	delete line;
}

vector<bool> * Line::getInstruction() {
	return new vector<bool>(line->begin() + 13, line->begin() + 16);
}

vector<bool> * Line::getAddress() {
	return new vector<bool>(line->begin(), line->begin() +13);
}


/*
//for testing
int main () {
	Line l;
	l.print();
	vector<bool> * ins = l.getInstruction();
	printVector(ins);
	printVector(l.getAddress());
	return 0;
}
*/

