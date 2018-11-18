#ifndef _BABY_H_
#define _BABY_H_


using namespace std;

/* define new types for readability */
typedef vector<Line> Store; // 32 x 32 bit memory

//enum Instruction {JMP, JRP, LDN, STO, SUB, CMP, STP}; //may later use these as constants

void clrscr(); //clear the screen

int decodeOperand(); // operand (operand is a memory address)
int incVar(int var); // increments variable
int decVar(int var); // decrements variable

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

    //int decCounter = 0;
    int instructionCounter = 0;

   // Line binCounter;

    bool stopLamp = false;

  public:
    ManchesterBaby(); //constructor
    void extHWare();


    void menu();
  
    // runs the program
    void runBaby();

    // Takes in a 32x32 machine code file and places it into the store
    void readFromFile(string);
    //void updateCI();

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


      //void posldn(int); // load accumulator with positive form of store (A = S)
      
      void add(int); // add content of store location to accumulator (A = A + S)
      
      void negsto(int); // load store with negative contents of accumulator (S = -A)

      void mul(int);   
      // void opsub(int); // subtract content of accumulator location from store (S = S - A)
      
      // void opmul(int); // multiplies content of accumulator location with store (S = S * A)
      
      // void opadd(int); // add content of accumulator location to store (S = S + A)

      void stp(); // stop (halt the program)

    // (immediate) executes the given instruction (see tabbed bit below)
    void immediateEx(int,int);

      // instruction set

      void imjmp(int);

      void imjrp(int); // add content of store location to CI (CI = CI + S)

      void imldn(int); // load accumulator with negative form of store (A = -S)

      void imsto(Line); // copy accumulator contents to store location (S = A)

      void imsub(int); // subtract content of store location from accumulator (A = A - S)

      void immul(int); // multiplies content of store location with accumulator (A = A * S)

      void imposldn(int); // load accumulator with positive form of store (A = S)

      void imadd(int); // add content of store location to accumulator (A = A + S)

      void imnegsto(Line); // load store with negative contents of accumulator (S = -A)

    string getValidFile();
    // prints the store
    void output();

};

#endif