#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include "line.h"


/*
  converts an array of booleans (1's and 0's) to a decimal number (little-endian)
*/
int binToDec(vector<bool> * bin)
{
	bool negative = bin->back(); //1/true means negative, 0/false means positive
  int length = bin->size();
  int decimal = 0;

  for (int i = 0; i < length; i++)
  {
    if (bin->at(i) == 1) //add value of 2^(length - i - 1)(value of its position in the binary number)
    {
      decimal += (static_cast<int>(pow(2, i)));
    }
  }

  if (negative) {
  	return 0-decimal;
  } else {
	return decimal;
  }

}

int uBinToDec(vector<bool> *bin) {
	vector<bool> temp = *bin;
	temp.push_back(0);
	return binToDec(&temp);
}


/*
  Converts a decimal number to a vector<bool>(32) in little-endian and returns the pointer
*/
vector<bool>* decToBin(int dec, int numOfBits) 
{	
  vector<bool>* bin = new vector<bool>(numOfBits, 0); // vector to hold binary value (in this case size 8 for rule.)

  const unsigned long long maxDec = pow(2,numOfBits)-1; //we are using operandWidth-bit numbers
   //with the last bit as the sign
  bool negative;
  if (dec < 0) {
  	negative = true;
  } else {
  	negative = false;
  }
  for (size_t i=maxDec; dec>0; i--)
  {
    // take the remainder of the dec / 2 and save it to the vector
    // this value will always be 1 or 0
    (*bin).at(maxDec-i) = dec%2;
    // update dec
    dec /= 2;
  }
  bin->at(numOfBits-1) = negative; //setting the 13th bit

  return bin;

}

vector<bool> * decToUBin(int udec, int numOfBits) {
	vector<bool> *bin = decToBin(udec, numOfBits +1);
	bin->pop_back();
	return bin;
}


//this should not be here
void printVector(vector<bool> * v) {
	vector<bool>::iterator it;
	for (it=v->begin(); it != v->end(); ++it) {
		cout << *it << "" <<flush;
	}
	cout <<flush;
	
}
void Line::printNoEndl(){
	printVector(line);
}

void Line::print(){
	printVector(line);
	cout <<endl;
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

vector<bool> * Line::getVector(){
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

void Line::setVector(vector<bool> *newVector) {
	this->line = newVector;
}

int Line::getDecInstruction(){
	return uBinToDec(getInstruction());
}
int Line::getDecOperand() {
	return uBinToDec(getOperand());
}
int Line::getDecVector() {
	return binToDec(getVector());
}
void Line::setDecOperand(int decOperand) {
	setOperand(decToUBin(decOperand));

}
void Line::setDecVector(int decNumber){
	setVector(decToBin(decNumber));
}




void Line::set(string s) {
	//cout << "trying to set(string) " << endl;
	//delete line;
	line = new vector<bool>; //use something else to empty it
	for (char &c : s) {
		if (c == '0') {
			line->push_back(0);
		} else if (c == '1'){ //anything that's not 0
			line->push_back(1);
		}
		//cout << c;
		//cout << static_cast<int>(c);
	}

	//cout <<endl;// << "all set. " <<endl;
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


