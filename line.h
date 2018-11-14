#include <vector>
#include <string>

using namespace std;
const static int SIZE = 32;

class Line {
private:
	vector<bool> * line;
public:
	void print();
	vector<bool> * getInstruction(); //get the opcode bools from the appropriate places //maybe not int
	vector<bool> * getOperand(); //get the address bools from approptiate places in the array //maybe not int

	void set(string);
	Line();
	Line(string);
	~Line();
};