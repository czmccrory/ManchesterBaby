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

int main() {
  ManchesterBaby mb;
  mb.runBaby();
  return 0; //later return the output of mb.runBaby() (if there were errors)
}