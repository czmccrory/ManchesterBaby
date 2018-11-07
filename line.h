#include <array>

using namespace std;
const static int SIZE = 32;

class Line {
private:
	array<bool, SIZE> line;
public:
	void print();
	int getInstruction(); //maybe not int
	int getAddress(); //maybe not int

	Line();
};