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


/*
  Set the Control Instuction to what is in the store
*/
void jmp(){
  controlInstruction = store;
}

/*
  Add the Store to the Control Inctruction
*/
void jrp(){
  controlInstruction= controlInstruction+store;
}

/*
  Make the stores values a negative
*/
void ldna(){
  store= -store;
}

/*
  Set the store to the accumulator
*/
void sto(){
  store=accumulator;
}

/*
  Subtract the store from the accumulator
*/
void sub(){
  accumulator= accumulator-store;
}

/*
  Add one to the control instruction if the accumulator is negative
*/
void cmp(){
  if(accumulator<0){controlInstruction=controlInstruction+1;}
}

/*
  Halts the operation
*/
void stop(){
  stopLamp=true;
  exit(0);
}



/*
  This method contains the instruction set for the Manchester Baby
  Parameter(s):
  opcode- The instruction number
*/
void execute(int opcode){
  //Process the opcode
  switch(opcode){
    case 0: 
    //Set CI to content of Store location
      void jmp();
    case 1:
    //Add content of Store location to CI
      void jrp();
    case 2:
    //Load Accumulator with negative form of store contents
      void ldna();
    case 3:
    //Copy Accumulator to Store location
      void sto();
    case 4:
    //Subtract content of Store location from Accumulator
      void sub();
    case 5:
    //Subtract content of Store location from Accumulator
      void sub();
    case 6:
    //Increment CI if Accumulator value negative, otherwise do nothing
      void cmp();
    case 7:
    //Halt the Baby and light the 'stop lamp'
      void stp();
  }

}


int main() {
  ManchesterBaby mb;
  mb.runBaby();
  return 0; //later return the output of mb.runBaby() (if there were errors)

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