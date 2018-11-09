#include <iostream>
#include <vector>
#include <cmath>
#include "line.h"
#include "baby.h"

 using namespace std;

/*
  converts an array of booleans (1's and 0's) to a decimal number (little-endian)
*/
int binToDec(vector<bool> * bin)
{
  int length = bin->size();
  int decimal = 0;

  for (int i = 0; i < length; i++)
  {
    if (bin->at(i) == 1) //add value of 2^(length - i - 1)(value of its position in the binary number)
    {
      decimal += (static_cast<int>(pow(2, i)));
    }
  }

  return decimal;
}

//Fetches next instruction
void ManchesterBaby::fetch()
{
  //CI (Control Instruction) points to memory address of the current line at the store
  controlInstruction = binCounter;

  //PI (Present Instruction) is set to the current line of the store
  presentInstruction = store.at(decCounter);
}

int ManchesterBaby::decodeInstruction() {
  vector <bool> * ins = presentInstruction.getInstruction();
  int ret = binToDec(ins);
  delete ins;
  return ret;
}

int ManchesterBaby::decodeOperand(){
  vector <bool> * operand = presentInstruction.getOperand();
  int ret = binToDec(operand);
  delete operand;
  return ret;
}

void ManchesterBaby::runBaby() {
  readProgramFromFile();

  int instruction;
  do {
    incrementCI(); //increment program counter
    fetch(); //get next line and save it to the PI
    instruction = decodeInstruction(); //get the decimal opcode number
    execute(instruction); //execute the instruction
    output(); //display the store, PI, CI, acucmulator
  } while (instruction != 7); //run until the decoded opcode is halt/stop
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
}