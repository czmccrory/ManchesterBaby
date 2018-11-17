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
  decCounter++;
 // binCounter.setOperand(decToBin(decCounter));
  binCounter.setDecOperand(decCounter);
}

//Fetches next instruction
void ManchesterBaby::fetch()
{
  //CI (Control Instruction) points to memory address of the current line at the store
  controlInstruction = binCounter;
  //PI (Present Instruction) is set to the current line of the store
  presentInstruction = store.at(decCounter);
}

void ManchesterBaby::updateCI(){
  controlInstruction = Line();
  controlInstruction.setDecOperand(decCounter);
}

/*
  Set the Control Instuction to what is in the store
*/
void ManchesterBaby::jmp(int operand){
  cout << "JMP " <<operand <<endl;
  //Get the operand from the store
 // vector <bool> *ci= store.at(operand).getOperand();
  //Set the counter t the operand
 // decCounter=binToDec(ci);
  decCounter = store.at(operand).getDecOperand();
  updateCI();

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

  	decCounter += store.at(operand).getDecOperand();
	updateCI();
}

/*
  Get a value from the store and make the negative of that value and store it in the accumulator
*/
void ManchesterBaby::ldn(int operand){
  cout << "LDN " <<operand <<endl;
  //Get the operand valye from the store
  //vector<bool> *valueFromStore= store.at(operand).getOperand();
  //COnvert the binary number to a decimal number and make it negative
  //int negativeValue= -(binToDec(valueFromStore));
  int negativeValue = store.at(operand).getDecVector();
  //Add set the accumulator to the negative operand
  accumulator.setDecVector(negativeValue);
}

/*
  Set the store to the accumulator
*/
void ManchesterBaby::sto(int operand){
  cout << "STO " <<operand <<endl;
  store.at(operand)=accumulator;
}

/*
  Subtract the store from the accumulator
*/
void ManchesterBaby::sub(int operand){
  cout << "SUB " <<operand <<endl;
  //A=A-S
 
  //Get the accumulator
  //vector <bool> *accumulatorPtr=accumulator.getOperand();
  int accumulatorDec = accumulator.getDecVector();

  //Get the Store operand
  //vector<bool> *storePtr= store.at(operand).getOperand();
  int storeDec = store.at(operand).getDecVector(); 

  //Convert to int
  //int accumulatorDec= binToDec(accumulatorPtr);
  //int storeDec= binToDec(storePtr);

  //accumulatorDec= (accumulatorDec-storeDec);
  int result = accumulatorDec - storeDec;

  //accumulator.setOperand(decToBin(accumulatorDec));
  accumulator.setDecVector(result);

}

/*
  Add one to the control instruction if the accumulator is negative
*/
void ManchesterBaby::cmp(){
  cout << "CMP " <<endl;
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
  stopLamp=true;
  cout <<"STP " <<endl;
 // exit(0);
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
  controlInstruction.printNoEndl();
  cout << '\t' <<  controlInstruction.getDecVector() <<endl;

  cout << "" <<endl;
  cout << "Accumulator" <<endl;
  accumulator.printNoEndl();
  cout << '\t' <<  accumulator.getDecVector() <<endl;
}


void ManchesterBaby::runBaby() {
  readFromFile("BabyTest1-MC.txt");
  //cout << "read from file successfully" <<endl;
  int instruction;
  char temp;
  do {
    incrementCI(); //increment program counter
    fetch(); //get next line and save it to the PI
    instruction = decodeInstruction(); //get the decimal opcode number
    int operand = decodeOperand();
    execute(instruction, operand); //execute the instruction
    output(); //display the store, PI, CI, acucmulator
    cin.get(temp);
  } while (instruction != 7 && temp == '\n'); //run until the decoded opcode is halt/stop
}

int main() {
  ManchesterBaby mb;
  mb.runBaby();
  return 0; //later return the output of mb.runBaby() (if there were errors)
}