#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include "line.h"
#include "baby.h"

using namespace std;

ManchesterBaby::ManchesterBaby() {
	Line l;
	store = Store(32,l);
}

void ManchesterBaby::incrementCI() {
  instructionCounter++;
 // binCounter.setOperand(decToBin(decCounter));
 // binCounter.setDecOperand(decCounter);
}

//Fetches next instruction
void ManchesterBaby::fetch()
{
  //CI (Control Instruction) points to memory address of the current line at the store
 // controlInstruction = binCounter;
  //PI (Present Instruction) is set to the current line of the store
  presentInstruction = store.at(instructionCounter);
}

/*
void ManchesterBaby::updateCI(){
  controlInstruction = Line();
  controlInstruction.setDecOperand(decCounter);
}
*/

/*
  Set the Control Instuction to what is in the store
*/
void ManchesterBaby::jmp(int operand){

  cout << "JMP " << operand << endl;
  //Get the operand from the store
 // vector <bool> *ci= store.at(operand).getOperand();
  //Set the counter t the operand
 // decCounter=binToDec(ci);
  instructionCounter = store.at(operand).getDecOperand();
  //updateCI();
}

/*
  Set the Control Instuction to what is in the store
*/
void ManchesterBaby::imjmp(int operand){
  cout << "IMJMP " << operand << endl;
  
  //Get the operand from the store
 // vector <bool> *ci= store.at(operand).getOperand();
  //Set the counter t the operand
 // decCounter=binToDec(ci);

  instructionCounter = operand;
  //updateCI();
}


/*
  Add the Store to the Control Inctruction
*/
void ManchesterBaby::jrp(int operand){
  cout << "JRP " <<operand <<endl;
  
  //Get the operand from the store
//  vector <bool> *ci= store.at(operand).getOperand();

  //Add the operands to the control instruction
//  decCounter+=binToDec(ci);

  instructionCounter += store.at(operand).getDecOperand();
	//updateCI();
}

/*
  Add the Store to the Control Inctruction
*/
void ManchesterBaby::imjrp(int operand){
  cout << "IMJRP " << operand << endl;
  
  //Get the operand from the store
//  vector <bool> *ci= store.at(operand).getOperand();
  //Add the operands to the control instruction
//  decCounter+=binToDec(ci);

    instructionCounter += operand;
  //updateCI();
}

/*
  Get a value from the store and make the negative of that value and store it in the accumulator
*/
void ManchesterBaby::ldn(int operand){

  cout << "LDN " << operand << endl;
  
  //Get the operand valye from the store
  //vector<bool> *valueFromStore= store.at(operand).getOperand();
  //COnvert the binary number to a decimal number and make it negative
  //int negativeValue= -(binToDec(valueFromStore));
  int negativeValue = store.at(operand).getDecVector();
  cout << negativeValue << endl;
  negativeValue = -negativeValue;
  cout << negativeValue << endl;
  //Add set the accumulator to the negative operand
  accumulator.setDecVector(negativeValue);
}

/*
  Get a value from the store and make the negative of that value and store it in the accumulator
*/
void ManchesterBaby::imldn(int operand){
  cout << "IMLDN " << operand << endl;
  //Get the operand valye from the store
  //vector<bool> *valueFromStore= store.at(operand).getOperand();
  //COnvert the binary number to a decimal number and make it negative
  //int negativeValue= -(binToDec(valueFromStore));
  int negativeValue = operand*-1;

  //Add set the accumulator to the negative operand
  accumulator.setDecVector(negativeValue);
}

/*
  Set the store to the accumulator
*/
void ManchesterBaby::sto(int operand){
  cout << "STO" << operand << endl;
  store.at(operand) = accumulator;
}

/*
  Set the store to the accumulator
*/
void ManchesterBaby::imsto(Line value){
  cout << "imSTO" << value.getDecOperand() << endl;
  value = accumulator;
}

/*
  Subtract the store from the accumulator
*/
void ManchesterBaby::sub(int operand){
  cout << "SUB " << operand << endl;
 
  //Get the accumulator
  // vector <bool> *accumulatorPtr=accumulator.getOperand();
  int accumulatorDec = accumulator.getDecVector();
  cout << accumulatorDec << endl;

  //Get the Store operand
  //vector<bool> *storePtr= store.at(operand).getOperand();
  int storeDec = store.at(operand).getDecVector(); 
  cout << storeDec << endl;

  //Convert to int
  //int accumulatorDec= binToDec(accumulatorPtr);
  //int storeDec= binToDec(storePtr);

  //accumulatorDec= (accumulatorDec-storeDec);

  int result = accumulatorDec- storeDec;

  cout << result << endl;

  //accumulator.setOperand(decToBin(accumulatorDec));
  accumulator.setDecVector(result);

}

/*
  Subtract the store from the accumulator
*/
void ManchesterBaby::imsub(int operand){
  cout << "IMSUB " << operand << endl;
 
  //Get the accumulator
  //vector <bool> *accumulatorPtr=accumulator.getOperand();
  int accumulatorDec = accumulator.getDecVector();

  //Convert to int
  //int accumulatorDec= binToDec(accumulatorPtr);
  //int storeDec= binToDec(storePtr);

  //accumulatorDec= (accumulatorDec-storeDec);
  int result = accumulatorDec - operand;

  //accumulator.setOperand(decToBin(accumulatorDec));
  accumulator.setDecVector(result);

}

/*
  Add one to the control instruction if the accumulator is negative
*/
void ManchesterBaby::cmp(){
  cout << "CMP " << endl;
  //vector <bool> *accumulatorPtr=accumulator.getOperand();
  //int accumulatorValue= binToDec(accumulatorPtr);
  int accumulatorValue = accumulator.getDecVector();
  if(accumulatorValue<0){
    incrementCI();
  }
}

/*
  Halts the operation
*/
void ManchesterBaby::stp(){
  stopLamp = true;
  cout << "STP " << endl;
 // exit(0);
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

	int accumulatorDec = accumulator.getDecVector();
	int storeDec = store.at(operand).getDecVector();
	int result = accumulatorDec * storeDec;
	accumulator.setDecVector(result);
*/
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

// /*
//   Get a value from the store and store it in the accumulator
// */
// void ManchesterBaby::posldn(int operand){
//   cout << "POSLDN " << operand << endl;


//   //Get the operand value from the store
//   vector<bool> *valueFromStore = store.at(operand).getOperand();

//   //Convert the binary number to a decimal number
//   int positiveValue = binToDec(valueFromStore);

//   //Add set the accumulator to the positive operand
//   accumulator.setOperand(decToBin(positiveValue));

// 	int storeValue = store.at(operand).getDecVector();
// 	//Add set the accumulator to the negative operand
//  	accumulator.setDecVector(storeValue);
// }

/*
  Get a value from the store and store it in the accumulator
*/
void ManchesterBaby::imposldn(int operand){
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
 *
 *
 * I have decided to comment these out beacuse Iain said processors
 * should not be able to perform operations directly on the memory
 *
 * We can discuss this later and potentially get it back
 *
 */
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
 *
 *
 * I have decided to comment these out beacuse Iain said processors
 * should not be able to perform operations directly on the memory
 *
 * We can discuss this later and potentially get it back
 *
 */
/*

  Subtract the accumulator from the store

*//*
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
  store.at(operand).setOperand(decToBin(storeDec));

}


*//*
  Multiplies store and accumulator
*//*
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

  //Convert back to binary and set as store operand
  store.at(operand).setOperand(decToBin(storeDec));
}

*//*
  Add content of accumulator to store
*//*
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

  //Convert back to binary and set as store operand
  store.at(operand).setOperand(decToBin(storeDec));
}
*/

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
	/*
  vector <bool> * ins = presentInstruction.getInstruction();
  int ret = uBinToDec(ins);
  delete ins;
  return ret;
  */
	return presentInstruction.getDecInstruction();
}

int ManchesterBaby::decodeOperand(){
	/*
  vector <bool> * operand = presentInstruction.getOperand();
  int ret = binToDec(operand);
  delete operand;
  return ret;
  */
	return presentInstruction.getDecOperand();
}



/*
  This method contains the instruction set for the Manchester Baby
  Parameter(s):
  opcode- The instruction number
*/
void ManchesterBaby::execute(int opcode, int operand){
	clrscr();
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
    //Multiply content of Store and Accumulator
      mul(operand);
      break;
    // case 7:
    // //Load Accumulator with (positive form of) Store contents
    //   posldn(operand);
    //   break;
    case 7:
    //Add content of Store and Accumulator
      add(operand);
      break;
    case 8:
    //Copy negative form of Accumulator to Store location
      negsto(operand);
      break;
    case 9:
    //Increment CI if Accumulator value negative, otherwise do nothing
      cmp();
      break;
    case 10:
    //Halt the Baby and light the 'stop lamp'
      stp();
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
  //cout << "opcode " << opcode << ", operand " <<operand <<endl;
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
    //Multiply content of Store and Accumulator
      immul(value.getDecVector());
      break;
    case 7:
    //Load Accumulator with (positive form of) Store contents
      imposldn(value.getDecVector());
      break;
    case 8:
    //Add content of Store and Accumulator
      imadd(value.getDecVector());
      break;
    case 9:
    //Copy negative form of Accumulator to Store location
      imnegsto(value);
      break;
    case 10:
    //Increment CI if Accumulator value negative, otherwise do nothing
      cmp();
      break;
    case 11:
    //Halt the Baby and light the 'stop lamp'
      stp();
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
  //cout<< "here we would output the hardware state" <<endl;

	//clrscr();
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


void ManchesterBaby::runBaby() {
  string filename=getValidFile();
  readFromFile(filename);
  int choice=1;
  //cout << "read from file successfully" <<endl;

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
    } while (instruction != 10 && temp == '\n'); //run until the decoded opcode is halt/stop
}

string ManchesterBaby::getValidFile(){
  bool isValid=true;
  //Initalise the variable
  string filename="";

do{
  //Display the files available to load
  cout << "\nAvailable files to load: \n" << endl;
  
  //Display
  system("ls | grep .txt | cat");


  cout << "\nPlease enter the filename (Without the file type): " << endl;
  
  //Store the file name
  cin >> filename;

  // Add the file extention to the filename
  //filename += ".txt";

  //Initalise variable
  ifstream infile;

  filename=filename+".txt";
  //Open file
  infile.open(filename, ios::in);

  //Open the file to prove that it exists
  if(infile.is_open() == 1)
  {

    // P0W how-to-detect-empty-file-in-c stackoverflow
    // If file is empty 
    if(infile.peek() == ifstream::traits_type::eof())
    {

      cout << "\nFILE IS EMPTY. " << endl;
      isValid=false;
      cin.clear();
      cin.ignore();
    }

    // close file
    infile.close();



  }else{
    cout << "\nError- The file ente does not exist" << endl;
    cout << "Try again: " << endl;
    isValid=false;
    cin.clear();
    cin.ignore();
  }
}while(isValid==false);

return filename;
}

void ManchesterBaby::menu() {
  int choice;
  bool isValid=true;
  do{
  cout << "Manchester Baby:\n" << endl;
  cout << "1. Run Manchester Baby Simulation\n" << endl;
  cout << "2. Change memory capacity\n" << endl;
  cout << "3. Exit" <<endl;
  cin >> choice;
  if(choice == 1) {
    runBaby();
  } 
  else if(choice == 2) {
    extHWare();
    runBaby();
  }else if(choice ==3){
    cout << "Exiting" <<endl;
    exit(0);
  }else {
    cout<< "" <<endl;
    cout << "Please enter a valid value" << endl;
    cin.clear();
    cin.ignore();
    isValid=false;
  }
  }while(isValid==false);
}

int main() {
  ManchesterBaby mb;

  mb.menu();
  return 0; //later return the output of mb.runBaby() (if there were errors)
}