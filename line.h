/*
  Group 4
   Melvin Abraham    170013110
   Kamila Gorska     170013107
   Charlie Hewitt    170015454
   Caoilainn McCrory 170001498
   Frantisek Pavlica 170020274
*/
#ifndef _LINE_H_
#define _LINE_H_
#include <vector>
#include <string>

using namespace std;
const static int SIZE = 32;
//void printVector(vector<bool>*);

const static unsigned int operandWidth = 6, opcodeWidth = 4; 
void printVector(vector<bool> * v);
int uBinToDec(vector<bool> *bin);
int binToDec(vector<bool> * bin);
vector<bool> * decToUBin(int udec, int numOfBits=32);
vector<bool>* decToBin(int dec, int numOfBits=32);

class Line {
private:
	vector<bool> * line;
public:
	void print();
	void printNoEndl();

	vector<bool> * getInstruction(); //get the opcode bools from the appropriate places //maybe not int
	vector<bool> * getOperand(); //get the address bools from approptiate places in the array //maybe not int
	vector<bool> * getVector();
	void setOperand(vector<bool>*);
	void setVector(vector<bool>*);

	bool isImmAddressing();

	int getDecInstruction();
	int getDecOperand(); 
	int getDecVector();
	void setDecOperand(int);
	void setDecVector(int);

	void set(string);
	Line();
	Line(string);
	~Line();
};

#endif