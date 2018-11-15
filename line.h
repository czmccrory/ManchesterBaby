
#ifndef _LINE_H_
#define _LINE_H_
#include <vector>
#include <string>

using namespace std;
const static int SIZE = 32;
//void printVector(vector<bool>*);

const static unsigned int operandWidth = 5, opcodeWidth = 3; 

class Line {
private:
	vector<bool> * line;
public:
	void print();
	vector<bool> * getInstruction(); //get the opcode bools from the appropriate places //maybe not int
	vector<bool> * getOperand(); //get the address bools from approptiate places in the array //maybe not int
	vector<bool> * get();
	void setOperand(vector<bool>*);

	void set(string);
	Line();
	Line(string);
	~Line();
};

#endif