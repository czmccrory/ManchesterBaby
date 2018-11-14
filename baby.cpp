#include <iostream>
#include <fstream>
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


/*
  Converts a decimal number to a vector<bool>(32) in little-endian and returns the pointer
*/
vector<bool>* decToBin(int dec) 
{
  vector<bool>* bin = new vector<bool>(32, 0); // vector to hold binary value (in this case size 8 for rule.)

  for (int i=31; dec>0; i--)
  {
    // take the remainder of the dec / 2 and save it to the vector
    // this value will always be 1 or 0
    (*bin).at(31-i) = dec%2;
    // update dec
    dec /= 2;
  }
    return bin;

}

void ManchesterBaby::incrementCI() {
  decCounter++;
 // binCounter = decToBin(decCounter);
}

//Fetches next instruction
void ManchesterBaby::fetch()
{
  //CI (Control Instruction) points to memory address of the current line at the store
  controlInstruction = binCounter;

  //PI (Present Instruction) is set to the current line of the store
  presentInstruction = store.at(decCounter);
}


/*
  Set the Control Instuction to what is in the store
*/
void ManchesterBaby::jmp(int operand){
 // controlInstruction = store.at(operand);

  cout << "JMP " <<operand <<endl;
}

/*
  Add the Store to the Control Inctruction
*/
void ManchesterBaby::jrp(int operand){
  //controlInstruction= controlInstruction+store.at(operand);
  cout << "JRP " <<operand <<endl;
}

/*
  Make the stores values a negative

  NO
*/
void ManchesterBaby::ldn(int operand){
  //store= -store;
  cout << "LDN " <<operand <<endl;
}

/*
  Set the store to the accumulator
*/
void ManchesterBaby::sto(int operand){
  store.at(operand)=accumulator;
  cout << "STO " <<operand <<endl;
}

/*
  Subtract the store from the accumulator
*/
void ManchesterBaby::sub(int operand){
 // accumulator= accumulator-store;
  cout << "SUB " <<operand <<endl;
}

/*
  Add one to the control instruction if the accumulator is negative
*/
void ManchesterBaby::cmp(){
  //if(accumulator<0){controlInstruction=controlInstruction+1;}
  cout << "CMP " <<endl;
}

/*
  Halts the operation
*/
void ManchesterBaby::stp(){
  stopLamp=true;
  cout <<"STP " <<endl;
  exit(0);
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



/*
  This method contains the instruction set for the Manchester Baby
  Parameter(s):
  opcode- The instruction number
*/
void ManchesterBaby::execute(int opcode, int operand){
  //Process the opcode
  switch(opcode){
    case 0: 
    //Set CI to content of Store location
      jmp(operand);
    case 1:
    //Add content of Store location to CI
      jrp(operand);
    case 2:
    //Load Accumulator with negative form of store contents
      ldn(operand);
    case 3:
    //Copy Accumulator to Store location
      sto(operand);
    case 4:
    //Subtract content of Store location from Accumulator
      sub(operand);
    case 5:
    //Subtract content of Store location from Accumulator
      sub(operand);
    case 6:
    //Increment CI if Accumulator value negative, otherwise do nothing
      cmp();
    case 7:
    //Halt the Baby and light the 'stop lamp'
      stp();
  }

}

void ManchesterBaby::readFromFile(string path){
  ifstream file (path);
  if(file){
    string l;
    while (getline(file, l)) {
      Line myline(l);
      store.push_back(myline);
    }
    //file.close();
  }
  else {
    cout << "Unable to open file" << endl;
  }
  file.close();

}

void ManchesterBaby::output() {
  cout<< "here we would output the hw" <<endl;
}


void ManchesterBaby::runBaby() {
  readFromFile("BabyTest1-MC.txt");

  int instruction;
  do {
    incrementCI(); //increment program counter
    fetch(); //get next line and save it to the PI
    instruction = decodeInstruction(); //get the decimal opcode number
    int operand = decodeOperand();
    execute(instruction, operand); //execute the instruction
    output(); //display the store, PI, CI, acucmulator
  } while (instruction != 7); //run until the decoded opcode is halt/stop
}

int main() {
  ManchesterBaby mb;
  mb.runBaby();
  return 0; //later return the output of mb.runBaby() (if there were errors)
}