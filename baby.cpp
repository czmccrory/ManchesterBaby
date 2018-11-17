#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "line.h"
#include "baby.h"

using namespace std;

void printVector2(vector<bool> * v) {
  vector<bool>::iterator it;
  for (it=v->begin(); it != v->end(); ++it) {
    cout << *it << " " <<flush;
  }
  cout <<endl;
  
}
/*
  converts an array of booleans (1's and 0's) to a decimal number (little-endian)
*/
int binToDec(vector<bool> * bin)
{
  bool negative = bin->back(); //1/true means negative, 0/false means positive
  int length = bin->size();
  int decimal = 0;

   if (negative) {
    return 0-decimal;
  } else {
  return decimal;
  }
}

int uBinToDec(vector<bool> *bin) {
  bin->push_back(0);
  return binToDec(bin);
}

/*
  Converts a decimal number to a vector<bool>(32) in little-endian and returns the pointer
*/
vector<bool>* decToBin(int dec)
{
  vector<bool>* bin = new vector<bool>(32, 0); // vector to hold binary value (in this case size 8 for rule.)
  for (int i=31; dec>0; i--)
  const size_t maxDec = pow(2,operandWidth-1); //we are using operandWidth-bit numbers
   //with the last bit as the sign
  bool negative;
  if (dec < 0) {
    negative = true;
  } else {
    negative = false;
  }
  for (int i=maxDec-1; dec>0; i--)
  {
    // take the remainder of the dec / 2 and save it to the vector
    // this value will always be 1 or 0
    (*bin).at(31-i) = dec%2;
    (*bin).at(maxDec-i) = dec%2;
    // update dec
    dec /= 2;
  }
    return bin;
  bin->at(operandWidth-1) = negative; //setting the 13th bit
  return bin;
}

ManchesterBaby::ManchesterBaby() {
  Line l;
  store = Store(32,l);
}

void ManchesterBaby::incrementCI() {
  decCounter++;
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
  cout << "JMP " << operand << endl;

  //Get the operand from the store
  vector <bool> *ci = store.at(operand).getOperand();
  
  //Set the counter t the operand
  decCounter = binToDec(ci);
}

/*
  Add the Store to the Control Inctruction
*/
void ManchesterBaby::jrp(int operand){
  cout << "JRP " << operand << endl;
  
  //Get the operand from the store
  vector <bool> *ci = store.at(operand).getOperand();

  //Add the operands to the control instruction
  decCounter += binToDec(ci);
}

/*
  Get a value from the store and make the negative of that value and store it in the accumulator
*/
void ManchesterBaby::ldn(int operand){
  cout << "LDN " << operand << endl;

  //Get the operand value from the store
  vector<bool> *valueFromStore = store.at(operand).getOperand();

  //Convert the binary number to a decimal number and make it negative
  int negativeValue = -(binToDec(valueFromStore));

  //Add set the accumulator to the negative operand
  accumulator.setOperand(decToBin(negativeValue));
}

/*
  Set the store to the accumulator
*/
void ManchesterBaby::sto(int operand){
  cout << "STO " << operand << endl;

  store.at(operand) = accumulator;
}

/*
  Subtract the store from the accumulator
*/
void ManchesterBaby::sub(int operand){
  cout << "SUB " << operand << endl;

  //Get the accumulator
  vector <bool> *accumulatorPtr = accumulator.getOperand();

  //Get the Store operand
  vector<bool> *storePtr = store.at(operand).getOperand();

  //Convert to int
  int accumulatorDec = binToDec(accumulatorPtr);
  int storeDec = binToDec(storePtr);

  //Perform calculation
  accumulatorDec = (accumulatorDec-storeDec);

  //Convert back to binary and set as accumulator operand
  accumulator.setOperand(decToBin(accumulatorDec));

}

/*
  Add one to the control instruction if the accumulator is negative
*/
void ManchesterBaby::cmp(){
  //if(accumulator<0){controlInstruction=controlInstruction+1;}
  cout << "CMP " << endl;
  vector <bool> *accumulatorPtr = accumulator.getOperand();
  int accumulatorValue = binToDec(accumulatorPtr);
  if(accumulatorValue<0){
    incrementCI();
  }
}

/*
  Halts the operation
*/
void ManchesterBaby::stp(){
  stopLamp = true;
  cout << "STP" << endl;
  exit(0);
}

/*****START OF EXTENSIONS*****/

/*
  Multiplies accumulator and store
*/
void ManchesterBaby::mul(int operand) {
  cout << "MUL" << operand << endl;

  //Get accumulator
  vector<bool> *accumulatorPtr = accumulator.getOperand();

  //Get Store operand
  vector<bool> *storePtr = store.at(operand).getOperand();

  //Convert to int
  int accumulatorDec = binToDec(accumulatorPtr);
  int storeDec = binToDec(storePtr);

  //Perform calculation
  accumulatorDec = (accumulatorDec*storeDec);

  accumulator.setOperand(decToBin(accumulatorDec));
}

/*
  Get a value from the store and store it in the accumulator
*/
void ManchesterBaby::posldn(int operand){
  cout << "POSLDN " << operand << endl;

  //Get the operand value from the store
  vector<bool> *valueFromStore = store.at(operand).getOperand();

  //Convert the binary number to a decimal number
  int positiveValue = binToDec(valueFromStore);

  //Add set the accumulator to the positive operand
  accumulator.setOperand(decToBin(positiveValue));
}

/*
  Add content of store to accumulator
*/
void ManchesterBaby::add(int operand) {
  cout << "ADD" << operand << endl;

  //Get the operand value from the store and accumulator
  vector<bool> *valueFromAccumulator = store.at(operand).getOperand();
  vector<bool> *valueFromStore = store.at(operand).getOperand();

  //Convert the binary number to a decimal number
  int accumulatorDec = binToDec(valueFromAccumulator);
  int storeDec = binToDec(valueFromStore);

  //Perform calculation
  accumulatorDec += storeDec;

  accumulator.setOperand(decToBin(accumulatorDec));
}

/*
  Set the store to the negative of the accumulator
*/
void negsto(int operand) {
  cout << "NegSto" << operand << endl;

  store.at(operand) = -(accumulator);
}

/*
  Subtract the accumulator from the store
*/
void ManchesterBaby::opsub(int operand){
  cout << "OPSUB " << operand << endl;
 
  //Get the accumulator and store operands
  vector <bool> *accumulatorPtr = accumulator.getOperand();
  vector<bool> *storePtr = store.at(operand).getOperand();

  //Convert to int
  int accumulatorDec = binToDec(accumulatorPtr);
  int storeDec = binToDec(storePtr);

  //Perform calculation
  storeDec -= accumulatorDec;

  //Convert back to binary and set as store operand
  store.setOperand(decToBin(storeDec));

}

/*
  Multiplies store and accumulator
*/
void ManchesterBaby::opmul(int operand) {
  cout << "OPMUL" << operand << endl;

  //Get accumulator and store operands
  vector<bool> *accumulatorPtr = accumulator.getOperand();
  vector<bool> *storePtr = store.at(operand).getOperand();

  //Convert to int
  int accumulatorDec = binToDec(accumulatorPtr);
  int storeDec = binToDec(storePtr);

  //Perform calculation
  storeDec = (storeDec*accumulatorDec);

  store.setOperand(decToBin(storeDec));
}

/*
  Add content of accumulator to store
*/
void ManchesterBaby::opadd(int operand) {
  cout << "OPADD" << operand << endl;

  //Get the operand value from the store and accumulator
  vector<bool> *valueFromAccumulator = store.at(operand).getOperand();
  vector<bool> *valueFromStore = store.at(operand).getOperand();

  //Convert the binary number to a decimal number
  int accumulatorDec = binToDec(valueFromAccumulator);
  int storeDec = binToDec(valueFromStore);

  //Perform calculation
  storeDec += accumulatorDec;

  store.setOperand(decToBin(storeDec));
}

/* 
  Extends hardware of Baby - more memory space 
*/
void ManchesterBaby::extHWare() {
  int newStoreSize = 2*(store.size());
  store.resize(newStoreSize);
}

/*****END OF EXTENSIONS*****/

/*
  Increments variables
*/
int ManchesterBaby::incVar(int var) {
  int incrementedVar = var + 1;
  return incrementedVar;
}

/*
  Decrements variables
*/
int ManchesterBaby::decVar(int var) {
  int decrementedVar = var - 1;
  return decrementedVar;
}

int ManchesterBaby::decodeInstruction() {
  vector <bool> * ins = presentInstruction.getInstruction();
  int ret = uBinToDec(ins);
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
	//cout << "opcode " << opcode << ", operand " <<operand <<endl;
  //Process the opcode
  switch(opcode){
    case 0: 
    //Set CI to content of Store location
      jmp(operand);
      break;
    case 1:
    //Add content of Store location to CI
      jrp(operand);
      break;
    case 2:
    //Load Accumulator with negative form of store contents
      ldn(operand);
      break;
    case 3:
    //Copy Accumulator to Store location
      sto(operand);
      break;
    case 4:
    //Subtract content of Store location from Accumulator
      sub(operand);
      break;
    case 5:
    //Subtract content of Store location from Accumulator
      sub(operand);
      break;
    case 6:
    //Increment CI if Accumulator value negative, otherwise do nothing
      cmp();
      break;
    case 7:
    //Halt the Baby and light the 'stop lamp'
      stp();
      break;
  }

}

void ManchesterBaby::readFromFile(string path){
  ifstream file (path);
  if(file){
    string l;
    size_t i = 0;

    while (getline(file, l)) {
      Line myline(l);
      store.at(i) = myline;
      i++;
    }
  }
  else {
    cout << "Unable to open file" << endl;
  }
  file.close();

}

void ManchesterBaby::output() {
  cout<< "here we would output the hardware state" <<endl;
}


void ManchesterBaby::runBaby() {
  readFromFile("BabyTest1-MC.txt");
  char temp;

  int instruction;
  do {
    incrementCI(); //increment program counter
    fetch(); //get next line and save it to the PI
    instruction = decodeInstruction(); //get the decimal opcode number
    int operand = decodeOperand();
    execute(instruction, operand); //execute the instruction
    output(); //display the store, PI, CI, acucmulator
    cin.get(temp);
  } while (instruction != 7 || temp != '\n'); //run until the decoded opcode is halt/stop
}

int main() {
  ManchesterBaby mb;
  mb.runBaby();
  return 0; //later return the output of mb.runBaby() (if there were errors)
}