using namespace std;

/* define new types for readability */
typedef vector<Line> Store; // 32 x 32 bit memory

//enum Instruction {JMP, JRP, LDN, STO, SUB, CMP, STP}; //may later use these as constants

int binToDec(vector<bool>);

class ManchesterBaby
{
  private:
    // the store is 32x32 bit memory
    Store store;

    // holds an opcode (+ operand)
    Line presentInstruction;

    // holds an address
    Line controlInstruction;

    // stores values during calculations??
    Line accumulator;

    int decCounter = 0;

    Line binCounter;

    bool stopLamp = false;

  public:
    // runs the program
    void runBaby();

    // Takes in a 32x32 machine code file and places it into the store
    void readFromFile(string);

    // increments control instruction by one
    void incrementCI();

    // fetches the next instruction (puts that into PI)
    void fetch(); // read CI (memory address), copy the instruction from store to PI

    // decodes the instruction (and fetches the operand if needed)
    int decodeInstruction(); // decodes Line into Opcode 
    int decodeOperand(); //+ operand (operand is a memory address)
    // executes the given instruction (see tabbed bit below)
    void execute(int, int);

      // instruction set

      void jmp(int); // set CI to content of Store (memory location) (CI = S)

      void jrp(int); // add content of store location to CI (CI = CI + S)

      void ldn(int); // load accumulator with negative form of store (A = -S)

      void sto(int); // copy accumulator contents to store location (S = A)

      void sub(int); // subtract content of store location from accumulator (A = A - S)

      void cmp(); // increment CI if accumulator value <0 (if A < 0) { CI++ };

      void stp(); // stop (halt the program)

    // prints the store
    void output();

};