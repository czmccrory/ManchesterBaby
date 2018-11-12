#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/* define new types for readability */
typedef vector<bool, 32> Line; // 32 bit Line of 1's/0's
typedef vector<Line, 32> Store; // 32 x 32 bit Line

class ManchesterBaby
{
  private:
    // the store is 32x32 bit memory
    Store store;

    // holds an opcode (+ operand)
    Line presentInstruction;

    // holds an address
    Line controlInstruction;

    // stores values during calculations?
    Line accumulator;

    // decimal counter
    int decCounter = 0;

    // stores which line you are at
    Line binCounter;

  public:
    // runs the program
    void runBaby();

    // Takes in a 32x32 machine code file and places it into the store
    void readProgramFromFile();

    // increments control instruction by one
    void incrementCI();

    // fetches the next instruction (puts that into PI)
    void fetch(); // read CI (memory address), copy the instruction from store to PI

    // decodes the instruction (and fetches the operand if needed)
    void decode(); // decodes Line into Opcode + operand (operand is a memory address)

    // executes the given instruction (see tabbed bit below)
    void execute();

      // instruction set

      void jmp(); // set CI to content of Store (memory location) (CI = S)

      void jrp(); // add content of store location to CI (CI = CI + S)

      void ldna(); // load accumulator with negative form of store (A = -S)

      void sto(); // copy accumulator contents to store location (S = A)

      void sub(); // subtract content of store location from accumulator (A = A - S)

      void cmp(); // increment CI if accumulator value <0 (if A < 0) { CI++ };

      void stp(); // stop (halt the program)

      // prints the store
      void output();
}

/* Initialises the passed in Line to all 0's */
void initialiseLine(Line* line)
{
  (*line).fill(0);
}

/* Converts an array of booleans (1's and 0's) to a decimal number (little-endian) */
int binToDec(vector<bool> bin)
{
	int length = bin.size();
	int decimal = 0;

	for (int i = 0; i < length; i++)
	{
		if (bin.at(i) == 1) //add value of 2^(length - i - 1)(value of its position in the binary number)
		{
			decimal += (static_cast<int>(pow(2, i)));
		}
	}

	return decimal;
}

void ManchesterBaby::incrementCI() {
	decCounter++;
	binCounter = decToBin(decCounter);
}

//Fetches next instruction
void fetch()
{
	//CI (Control Instruction) points to memory address of the current line at the store
	controlInstruction = binCounter;

	//PI (Present Instruction) is set to the current line of the store
	presentInstruction = Store.at(decCounter);
}

void readFromFile(){
	ifstream file ("");
	if(file.is_open()){
		for(int i=0; i<32; i++) {
			//do something
		}
		file.close();
	}
	else
		cout << "Unable to open file" << endl;
}