#include <iostream>
#include <fstream>
#include <vector>
#include "line.h"
#include "baby.h"

using namespace std;

//initiasise the manchester baby with a store of empty lines (32 by default)
ManchesterBaby::ManchesterBaby() {
	Line l;
	store = Store(storeSize,l);
}

//increment the current instruction
void ManchesterBaby::incrementCI() {
  instructionCounter++;
}

//Fetches next instruction
void ManchesterBaby::fetch()
{
  //PI (Present Instruction) is set to the current line of the store
  presentInstruction = store.at(instructionCounter);
}


/*
  Set the Control Instuction to what is in the store
*/
void ManchesterBaby::jmp(int operand){
	presentMnemonic = "JMP " + to_string(operand);
  //Set instruction counter to the operand at the address
  instructionCounter = store.at(operand).getDecOperand();
}

/*
  Set the Control Instuction to what is in the store
*/
void ManchesterBaby::imjmp(int operand){

	presentMnemonic = "IMJMP " + to_string(operand);
  //Set the counter to the operand

  instructionCounter = operand;
}


/*
  Add the Store to the Control Inctruction
*/
void ManchesterBaby::jrp(int operand){

	presentMnemonic = "JRP " + to_string(operand);
  //Add the operands to the control instruction
  instructionCounter += store.at(operand).getDecOperand();
}

/*
  Add the Store to the Control Inctruction
*/
void ManchesterBaby::imjrp(int operand){
	presentMnemonic = "IMJRP " + to_string(operand);
  //Add the operands to the control instruction

    instructionCounter += operand;
}

/*
  Get a value from the store and make the negative of that value and store it in the accumulator
*/
void ManchesterBaby::ldn(int operand){

	presentMnemonic = "LDN " + to_string(operand);
  //Get the value at the store
  int negativeValue = store.at(operand).getDecVector();
  //make it negative
  negativeValue = -negativeValue;
  //Add set the accumulator to the negative operand
  accumulator.setDecVector(negativeValue);
}

/*
  load the negative of the operand into the accumulator
*/
void ManchesterBaby::imldn(int operand){
	presentMnemonic = "IMLDN " + to_string(operand);
  int negativeValue = -operand; 
  accumulator.setDecVector(negativeValue);
}

/*
  Set the store to the accumulator
*/
void ManchesterBaby::sto(int operand){
	presentMnemonic = "STO " + to_string(operand);
  store.at(operand) = accumulator;
}

/*
  Doesn't actually really do anything
*/
void ManchesterBaby::imsto(Line value){
  //cout << "imSTO" << value.getDecOperand() << endl;
	presentMnemonic = "IMSTO " + to_string(value.getDecOperand());
  value = accumulator;
}

/*
  Subtract the store from the accumulator
*/
void ManchesterBaby::sub(int operand){

	presentMnemonic = "SUB " + to_string(operand);
 
  //Get the accumulator value
  int accumulatorDec = accumulator.getDecVector();

  //Get the Store value
  int storeDec = store.at(operand).getDecVector(); 

  int result = accumulatorDec- storeDec;

  accumulator.setDecVector(result);

}

//increment the accumulator by 1
void ManchesterBaby::inc(){
	presentMnemonic = "INC ";
	int accumulatorDec = accumulator.getDecVector();
	accumulator.setDecVector(++accumulatorDec);
}

//decrement the accumulator by 1
void ManchesterBaby::dec(){

	presentMnemonic = "DEC ";
	int accumulatorDec = accumulator.getDecVector();
	accumulator.setDecVector(--accumulatorDec);
}

/*
  Subtract the operand from the accumulator
*/
void ManchesterBaby::imsub(int operand){

	presentMnemonic = "IMSUB " + to_string(operand);

  //Get the accumulator value
  int accumulatorDec = accumulator.getDecVector();

  int result = accumulatorDec - operand;
  accumulator.setDecVector(result);

}

/*
  Add one to the control instruction if the accumulator is negative
*/
void ManchesterBaby::cmp(){

	presentMnemonic = "CMP ";
  int accumulatorValue = accumulator.getDecVector();
  //increment the CI if the
  if(accumulatorValue<0){
    incrementCI();
  }
}

/*
  Halts the operation
*/
void ManchesterBaby::stp(){

	presentMnemonic = "STP ";
  stopLamp = true;

}



/*****START OF EXTENSIONS*****/

/*
  Multiplies accumulator and store
*/
void ManchesterBaby::mul(int operand) {

	presentMnemonic = "MUL " + to_string(operand);
	int accumulatorDec = accumulator.getDecVector();
	int storeDec = store.at(operand).getDecVector();
	int result = accumulatorDec * storeDec;
	accumulator.setDecVector(result);

}

/*
  Multiplies accumulator and store
*/
void ManchesterBaby::immul(int operand) {

	presentMnemonic = "IMMUL " + to_string(operand);
	  int accumulatorDec = accumulator.getDecVector();
  int result = accumulatorDec * operand;
  accumulator.setDecVector(result);
}

 /*
   Get a value from the store and store it in the accumulator
 */
void ManchesterBaby::ldp(int operand){
	presentMnemonic = "LDP " + to_string(operand);

	int storeValue = store.at(operand).getDecVector();
	//Add set the accumulator to the negative operand
 	accumulator.setDecVector(storeValue);
}

/*
  Get a value from the store and store it in the accumulator
*/
void ManchesterBaby::imldp(int operand){

	presentMnemonic = "IMLDP " + to_string(operand);
  accumulator.setDecVector(operand);
}

/*
  Add content of store to accumulator
*/
void ManchesterBaby::add(int operand) {
	presentMnemonic = "ADD " + to_string(operand);

  int accumulatorDec = accumulator.getDecVector();
  int storeDec = store.at(operand).getDecVector(); 
  int result = accumulatorDec + storeDec;

  //accumulator.setOperand(decToBin(accumulatorDec));
  accumulator.setDecVector(result);
}

void ManchesterBaby::imadd(int operand) {

	presentMnemonic = "IMADD " + to_string(operand);


  int accumulatorDec = accumulator.getDecVector();

  int result = accumulatorDec + operand;

  accumulator.setDecVector(result);
}

/*
  Set the store to the negative of the accumulator
*/
void ManchesterBaby::negsto(int operand) {

	presentMnemonic = "NEGSTO " + to_string(operand);
  int accumulatorValue = accumulator.getDecVector();
  store.at(operand).setDecVector(0-accumulatorValue);
}


/*
  Set the store to the negative of the accumulator
*/
void ManchesterBaby::imnegsto(Line value) {

	presentMnemonic = "IMNEGSTO " + to_string(value.getDecOperand());

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




int ManchesterBaby::decodeInstruction() {
	return presentInstruction.getDecInstruction();
}

int ManchesterBaby::decodeOperand(){
	return presentInstruction.getDecOperand();
}

bool ManchesterBaby::decodeAddressingMode(){
	return presentInstruction.isImmAddressing();
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
    case 12:
    	inc();
    	break;
    case 13:
    	dec();
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
    case 12:
    	inc();
    	break;
    case 13:
    	dec();
    	break;
    default:
      break;
  }
}

void ManchesterBaby::addressedExecute(int opcode, int operand, bool immAddressing) {
	if (immAddressing){
		immediateEx(opcode, operand);
	} else {
		execute(opcode, operand);
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

	clrscr();
  cout<< "Store:" <<endl;
  for (size_t i = 0; i < store.size(); ++i)
  {
    //Print line
    cout << i << '\t';// << flush;
    store.at(i).print();
  }

  cout <<""<<endl;
  cout<< "Present Instruction" << "\n\t";
  presentInstruction.printNoEndl();
  cout << '\t' << presentMnemonic << endl;

  cout << "" <<endl;
  cout << "Control Instruction" <<"\n\t";
  Line ci;
  ci.setDecVector(instructionCounter);
  ci.printNoEndl();
  cout << '\t' <<  ci.getDecVector() <<endl;

  cout << "" <<endl;
  cout << "Accumulator" <<"\n\t";
  accumulator.printNoEndl();
  cout << '\t' <<  accumulator.getDecVector() <<endl;
  cout << "\nPress enter to see the next cycle, or input any other key to exit." <<endl;

  if (!stopLamp){
  	cout << "Stop Lamp: " << "\033[1;34mOFF\033[0m\n"<<endl;
  }else{
  	cout << "Stop Lamp: " << "\033[1;31mON\033[0m\n"<<endl;
  }
}

void ManchesterBaby::runBaby(string filename) {
	readFromFile(filename);
  cin.ignore();
  cin.clear();

    int instruction;
    char temp;
    do {
      incrementCI(); //increment program counter
      fetch(); //get next line and save it to the PI
      instruction = decodeInstruction(); //get the decimal opcode number
      int operand = decodeOperand();
  	  bool immAddressing = decodeAddressingMode();
      addressedExecute(instruction, operand, immAddressing);
      output(); //display the store, PI, CI, acucmulator
      cin.get(temp);
    } while (instruction != 7 && temp == '\n'); //run until the decoded opcode is halt/stop

}

void ManchesterBaby::runBaby() {
  string filename=getValidFile();
  runBaby(filename);
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
   cout << "\nPlease enter the filename: " << endl;
  
  //Store the file name
  cin >> filename;
   // Add the file extention to the filename
  //filename += ".txt";
   //Initalise variable
  ifstream infile;
   //filename=filename+".txt";
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

void ManchesterBaby::setParamFile(string filename) {
	this->paramfile = filename;
	hasParam = true;
}

void ManchesterBaby::menu() {
  int choice;
  bool isValid;
  do{
  	isValid = true;
  cout << "Manchester Baby:\n" << endl;
  cout << "1. Run Manchester Baby Simulation\n" << endl;
  cout << "2. Double memory capacity\n" << endl;
  cout << "3. Exit" <<endl;
  cin >> choice;
  if(choice == 1) {
  	try {
	  	if (hasParam) {
	  		cout <<paramfile<<endl;
	  		runBaby(paramfile);
	  	} else {
	    	runBaby();
	  	}	
  	} catch (...) {
  		cerr <<"Some error occured. The Manchester Baby may have run out of memory." <<endl;
  	}
  } 
  else if(choice == 2) {
    extHWare();
    isValid = false; //it is still valid but I want it to go to the loop again
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


int main(int argc, char** argv) {
  ManchesterBaby mb;
  if(argc > 2) {
  	cerr<<"Invalid use of program. Run using either \"" << argv[0]
  		<<"\" or \"" <<argv[0]<<" "<< argv[1] << "\"." <<endl;
  		return 1;
  } else if (argc == 2) {
  	mb.setParamFile(argv[1]);
  	mb.menu();
  } else {
 	mb.menu();
  }
  return 0;
}