#include <iostream>
#include <sstream>
#include <vector>
#include "line.h"



//this should not be here
void printVector(vector<bool> * v) {
	vector<bool>::iterator it;
	for (it=v->begin(); it != v->end(); ++it) {
		cout << *it << "" <<flush;
	}
	cout <<endl;
	
}

void Line::print(){
	printVector(line);
}

Line::Line() {
	line =  new vector<bool>(32, 0);
}

Line::Line(string s) {
	//line = new vector<bool>;
	set(s);
}

Line::~Line() {
	//delete line;
}

vector<bool> * Line::get(){
	return line;
}

vector<bool> * Line::getInstruction() {
	return new vector<bool>(line->begin() + 13, line->begin() + 16);
}

vector<bool> * Line::getOperand() {
	return new vector<bool>(line->begin(), line->begin() +operandWidth);
}

void Line::setOperand(vector<bool> *op) {
	//cout << "setting operand with size " << op->size() <<endl;
	for (size_t i=0; i< op->size(); i++) {
		line->at(i) = op->at(i);
	}
}

void Line::set(string s) {
	//cout << "trying to set(string) " << endl;
	//delete line;
	line = new vector<bool>; //use something else to empty it
	for (char &c : s) {
		if (c == '0') {
			line->push_back(0);
		} else { //anything that's not 0
			line->push_back(1);
		}
		//cout << c;
	}
	//cout <<endl;// << "all set. " <<endl;
	/*
	for (size_t i = 0; i < s.size(); i++) {
		line->push_back(s);
	}
	*/
}

/*
//for testing
int main () {
	Line l("10011000000000110000000000000000");
	l.print();
	vector<bool> * ins = l.getInstruction();
	printVector(ins);
	printVector(l.getOperand());
	return 0;
}
*/


