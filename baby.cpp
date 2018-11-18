#include <iostream>
#include <fstream>
#include <vector>
#include "line.h"
#include "baby.h"

using namespace std;

ManchesterBaby::ManchesterBaby() {
	Line l;
	store = Store(32,l);
}

void ManchesterBaby::incrementCI() {
  instructionCounter++;
}

/*
  Fetches next instruction
*/
void ManchesterBaby::fetch()
{
  //PI (Present Instruction) is set to the current line of the store
  presentInstruction = store.at(instructionCounter);
}

/*
  Set the Control Instuction to what is in the store
*/
void ManchesterBaby::jmp(int operand){
  cout << "JMP " << endl;

  instructionCounter = store.at(operand).getDecOperand();
}

/*
  Set the Control Instuction to what is in the store
*/
void ManchesterBaby::imjmp(int operand){
  cout << "IMJMP " << endl;

  instructionCounter = operand;
}

/*
  Add the Store to the Control Inctruction
*/
void ManchesterBaby::jrp(int operand){
  cout << "JRP " << endl;

  instructionCounter += store.at(operand).getDecOperand();
}

/*
  Add the Store to the Control Instruction
*/
void ManchesterBaby::imjrp(int operand){
  cout << "IMJRP " << endl;
  
  instructionCounter += operand;
}

/*
  Get a value from the Store and make the negative of that value and store it in the accumulator
*/
void ManchesterBaby::ldn(int operand){
  cout << "LDN " << endl;

  //Get Store 
  int negativeValue = store.at(operand).getDecVector();

  //Negate value
  negativeValue = -negativeValue;

  //Add set the accumulator to the negative operand
  accumulator.setDecVector(negativeValue);
}

/*
  Get a value from the store and make the negative of that value and store it in the accumulator
*/
void ManchesterBaby::imldn(int operand){
  cout << "IMLDN " << endl;
  
  //Negate value
  int negativeValue = -operand;

  //Add set the accumulator to the negative operand
  accumulator.setDecVector(negativeValue);
}

/*
  Set the store to the accumulator
*/
void ManchesterBaby::sto(int operand){
  cout << "STO" << endl;

  store.at(operand) = accumulator;
}

/*
  Set the store to the accumulator
*/
void ManchesterBaby::imsto(Line value){
  cout << "imSTO" << endl;

  value = accumulator;
}

/*
  Subtract the store from the accumulator
*/
void ManchesterBaby::sub(int operand){
  cout << "SUB " << endl;
 
  //Get the accumulator
  int accumulatorDec = accumulator.getDecVector();
  cout << accumulatorDec << endl;

  //Get the Store operand
  int storeDec = store.at(operand).getDecVector(); 

  //Perform calculation
  int result = accumulatorDec- storeDec;

  accumulator.setDecVector(result);
}

/*
  Subtract the store from the accumulator
*/
void ManchesterBaby::imsub(int operand){
  cout << "IMSUB " << endl;

  //Get the accumulator
  int accumulatorDec = accumulator.getDecVector();

  // Perform calculation
  int result = accumulatorDec - operand;

  accumulator.setDecVector(result);
}

/*
  Add one to the control instruction if the accumulator is negative
*/
void ManchesterBaby::cmp(){
  cout << "CMP " << endl;
  
  int accumulatorValue = accumulator.getDecVector();

  if(accumulatorValue < 0){
    incrementCI();
  }
}

/*
  Halts the operation
*/
void ManchesterBaby::stp(){
  stopLamp = true;
  cout << "STP " << endl;
}

/*****START OF EXTENSIONS*****/

/*
  Multiplies accumulator and store
*/
void ManchesterBaby::mul(int operand) {
  cout << "MUL" << operand << endl;

/*
  //Get accumulator
  vector<bool> *accumulatorPtr = accumulator.getOperand();

  //Get Store operand
  vector<bool> *storePtr = store.at(operand).getOperand();

  //Convert to int
  int accumulatorDec = binToDec(accumulatorPtr);
  int storeDec = binToDec(storePtr);

  //Perform calculation
  accumulatorDec = (accumulatorDec*storeDec);

  //Convert back to binary and set as accumulator operand
  accumulator.setOperand(decToBin(accumulatorDec));
*/
	int accumulatorDec = accumulator.getDecVector();
	int storeDec = store.at(operand).getDecVector();
	int result = accumulatorDec * storeDec;
	accumulator.setDecVector(result);
}

/*
  Multiplies accumulator and store
*/
void ManchesterBaby::immul(int operand) {
  cout << "IMMUL" << operand << endl;

/*
  //Get accumulator
  vector<bool> *accumulatorPtr = accumulator.getOperand();

  //Get Store operand
  vector<bool> *storePtr = store.at(operand).getOperand();

  //Convert to int
  int accumulatorDec = binToDec(accumulatorPtr);
  int storeDec = binToDec(storePtr);

  //Perform calculation
  accumulatorDec = (accumulatorDec*storeDec);

  //Convert back to binary and set as accumulator operand
  accumulator.setOperand(decToBin(accumulatorDec));
*/
  int accumulatorDec = accumulator.getDecVector();
  int result = accumulatorDec * operand;
  accumulator.setDecVector(result);
}

/*
  Get a value from the store and store it in the accumulator
*/
void ManchesterBaby::ldp(int operand){
  cout << "POSLDN " << operand << endl;

  //Get the operand value from the store
  // vector<bool> *valueFromStore = store.at(operand).getOperand();

  // //Convert the binary number to a decimal number
  // int positiveValue = binToDec(valueFromStore);

  // //Add set the accumulator to the positive operand
  // accumulator.setOperand(decToBin(positiveValue));

	int storeValue = store.at(operand).getDecVector();
	//Add set the accumulator to the negative operand
 	accumulator.setDecVector(storeValue);
}

/*
  Get a value from the store and store it in the accumulator
*/
void ManchesterBaby::imldp(int operand){
  cout << "IMPOSLDN " << operand << endl;

/*
  //Get the operand value from the store
  vector<bool> *valueFromStore = store.at(operand).getOperand();

  //Convert the binary number to a decimal number
  int positiveValue = binToDec(valueFromStore);

  //Add set the accumulator to the positive operand
  accumulator.setOperand(decToBin(positiveValue));
*/
  //Add set the accumulator to the negative operand
  accumulator.setDecVector(operand);
}

/*
  Add content of store to accumulator
*/
void ManchesterBaby::add(int operand) {
  cout << "ADD" << operand << endl;

/*
  //Get the operand value from the store and accumulator
  vector<bool> *valueFromAccumulator = accumulator.getOperand();
  vector<bool> *valueFromStore = store.at(operand).getOperand();

  //Convert the binary number to a decimal number
  int accumulatorDec = binToDec(valueFromAccumulator);
  int storeDec = binToDec(valueFromStore);

  //Perform calculation
  accumulatorDec += storeDec;

  //Convert back to binary and set as accumulator operand
  accumulator.setOperand(decToBin(accumulatorDec));
  */

  int accumulatorDec = accumulator.getDecVector();
  int storeDec = store.at(operand).getDecVector(); 
  int result = accumulatorDec + storeDec;

  //accumulator.setOperand(decToBin(accumulatorDec));
  accumulator.setDecVector(result);
}

void ManchesterBaby::imadd(int operand) {
  cout << "IMADD" << operand << endl;

/*
  //Get the operand value from the store and accumulator
  vector<bool> *valueFromAccumulator = accumulator.getOperand();
  vector<bool> *valueFromStore = store.at(operand).getOperand();

  //Convert the binary number to a decimal number
  int accumulatorDec = binToDec(valueFromAccumulator);
  int storeDec = binToDec(valueFromStore);

  //Perform calculation
  accumulatorDec += storeDec;

  //Convert back to binary and set as accumulator operand
  accumulator.setOperand(decToBin(accumulatorDec));
  */

  int accumulatorDec = accumulator.getDecVector();
  int result = accumulatorDec + operand;

  //accumulator.setOperand(decToBin(accumulatorDec));
  accumulator.setDecVector(result);
}

/*
  Set the store to the negative of the accumulator
*/
void ManchesterBaby::negsto(int operand) {
  cout << "NEGSTO " << operand << endl;

/*
  //Get accumulator
  vector<bool> *valueFromAccumulator = accumulator.getOperand();

  //Convert to int
  int accumulatorDec = binToDec(valueFromAccumulator);

  //Convert negative of decimal to binary and set as store operand
  store.at(operand).setOperand(decToBin(-accumulatorDec));
*/
  int accumulatorValue = accumulator.getDecVector();
  store.at(operand).setDecVector(0-accumulatorValue);
}

/*
  Set the store to the negative of the accumulator
*/
void ManchesterBaby::imnegsto(Line value) {
  cout << "IMNEGSTO " << value.getDecOperand() << endl;

/*
  //Get accumulator
  vector<bool> *valueFromAccumulator = accumulator.getOperand();

  //Convert to int
  int accumulatorDec = binToDec(valueFromAccumulator);

  //Convert negative of decimal to binary and set as store operand
  store.at(operand).setOperand(decToBin(-accumulatorDec));
*/
  int accumulatorValue = accumulator.getDecVector();
  value.setDecVector(0-accumulatorValue);
}

/* 
  Extends hardware of Baby - more memory space 
*/
void ManchesterBaby::extHWare() {
  //Create new store size (double the size of the current store)
  int newStoreSize = 2*(store.size());

  //Set as new store size
  store.resize(newStoreSize);
}

/*****END OF EXTENSIONS*****/

/*
  Increments variables
*/
int incVar(int var) {
  int incrementedVar = var + 1;
  return incrementedVar;
}

/*
  Decrements variables
*/
int decVar(int var) {
  int decrementedVar = var - 1;
  return decrementedVar;
}

int ManchesterBaby::decodeInstruction() {
	return presentInstruction.getDecInstruction();
}

int ManchesterBaby::decodeOperand(){
	return presentInstruction.getDecOperand();
}

/*
  This method contains the instruction set for the Manchester Baby
  Parameter(s):
  opcode- The instruction number
*/
void ManchesterBaby::execute(int opcode, int operand){
	clrscr();
	
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
    //Load Accumulator with negative form of Store contents
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
    case 8:
    //Multiply content of Store and Accumulator
      mul(operand);
      break;
    case 9:
    //Load Accumulator with (positive form of) Store contents
      ldp(operand);
      break;
    case 10:
    //Add content of Store and Accumulator
      add(operand);
      break;
    case 11:
    //Copy negative form of Accumulator to Store location
      negsto(operand);
      break;
    default:
      break;
  }
}

/*
  This method contains the instruction set for the Manchester Baby
  Parameter(s):
  opcode- The instruction number
*/
void ManchesterBaby::immediateEx(int opcode, int operand){
  Line value = store.at(operand);
  clrscr();
  
  //Process the opcode
  switch(opcode){
    case 0: 
    //Set CI to content of Store location
      imjmp(value.getDecOperand());
      break;
    case 1:
    //Add content of Store location to CI
      imjrp(value.getDecOperand());
      break;
    case 2:
    //Load Accumulator with negative form of Store contents
      imldn(value.getDecVector());
      break;
    case 3:
    //Copy Accumulator to Store location
      imsto(value);
      break;
    case 4:
    //Subtract content of Store location from Accumulator
      imsub(value.getDecVector());
      break;
    case 5:
    //Subtract content of Store location from Accumulator
      imsub(value.getDecVector());
      break;
    case 6:
    //Increment CI if Accumulator value negative, otherwise do nothing
      cmp();
      break;
    case 7:
    //Halt the Baby and light the 'stop lamp'
      stp();
      break;
    case 8:
    //Multiply content of Store and Accumulator
      immul(value.getDecVector());
      break;
    case 9:
    //Load Accumulator with (positive form of) Store contents
      imldp(value.getDecVector());
      break;
    case 10:
    //Add content of Store and Accumulator
      imadd(value.getDecVector());
      break;
    case 11:
    //Copy negative form of Accumulator to Store location
      imnegsto(value);
      break;
    default:
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

//clear the screen
void clrscr(){
	cout << "\033[2J\033[1;1H" << flush; //the character for clearing the screen
}


void ManchesterBaby::output() {
  cout<< "Store:" <<endl;
  for (size_t i = 0; i < store.size(); ++i)
  {
    //Print line
    store.at(i).print();
  }

  cout <<""<<endl;
  cout<< "Present Instruction" <<endl;
  presentInstruction.print();

  cout << "" <<endl;
  cout << "Control Instruction" <<endl;
  Line ci;
  ci.setDecVector(instructionCounter);
  ci.printNoEndl();
  cout << '\t' <<  ci.getDecVector() <<endl;

  cout << "" <<endl;
  cout << "Accumulator" <<endl;
  accumulator.printNoEndl();
  cout << '\t' <<  accumulator.getDecVector() <<endl;
}


void ManchesterBaby::runBaby(int choice) {
  readFromFile("BabyTest1-MC.txt");
  
    int instruction;
    char temp;
    do {
      incrementCI(); //increment program counter
      fetch(); //get next line and save it to the PI
      instruction = decodeInstruction(); //get the decimal opcode number
      int operand = decodeOperand();
      if(choice == 1) {
        execute(instruction, operand); //execute the instruction
      } else {
        immediateEx(instruction, operand); //execute the instruction
      }
      output(); //display the store, PI, CI, acucmulator
      cin.get(temp);
    } while (instruction != 11 && temp == '\n'); //run until the decoded opcode is halt/stop
}

void ManchesterBaby::menu() {
  int choice;

  cout << "What addressing type (immediate or absolute) would you like? Choose the corresponding number for you choice.\n" << endl;
  cout << "1. Absolute\n" << endl;
  cout << "2. Immediate\n" << endl;
  cin >> choice;
  if(choice == 1) {
    runBaby(choice);
  } 
  else if(choice == 2) {
    runBaby(choice);
  } else {
    cout << "Please enter a valid value" << endl;
  }
}

int main() {
  ManchesterBaby mb;
  mb.menu();
  return 0; //later return the output of mb.runBaby() (if there were errors)
}