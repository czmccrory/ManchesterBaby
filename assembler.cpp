/*
  Group 4
   Melvin Abraham    170013110
   Kamila Gorska     170013107
   Charlie Hewitt    170015454
   Caoilainn McCrory 170001498
   Frantisek Pavlica 170020274
*/

#include "assembler.h"

using namespace std;


// Runs the assembler				
void Assembler::assemble()
{
	try
	{
		assembleFirstPass();
		assembleSecondPass();
		flushBufferToFile();
	}
	catch(AssemblerException e)
	{
		cout << "\033[1;31mAssembler Error: \033[0m" << e.what() << endl;
	}
}

// Runs the first pass of the assembler (completing symbol table)
void Assembler::assembleFirstPass()
{
	ifstream ifs(filePath);
	int counter = 0;
	int* lineCounter = &counter;
	string line = "";

	if (! ifs)
	{
		throw AssemblerException("Invalid filename");
	}

	cout << "FIRST PASS:" << endl;

	try
	{
		while (getline(ifs, line)) //while nextLine exists
		{
			string lineCopy = line;
			string* linePtr = &lineCopy;
			cout << "assembling line: " << line << endl;
		 	assembleLineFirstPass(linePtr, lineCounter);
		}
	}
	catch (AssemblerException &e)
	{
		cout << "\033[1;31mAssembler Error: \033[0m" << e.what() << endl;
		exit (0);
	}
} 

/* 	
	First pass of a line (updating symbol table)
*/
void Assembler::assembleLineFirstPass(string* line, int* lineCounter)
{
	string bufferLine;

	string parsed = parse(line);

	if (parsed == "") // nothing useful left on line
	{
		return;
	}

	// if theres a "LABEL": add it to symbol table along with current line number as address
	if (parsed.find(":") != string::npos)
	{
		//cout << "Label found: " << parsed;
		string label = parsed.substr(0, parsed.length()-1);

		addVariableToSymbolTable(label, *lineCounter);

		parsed = parse(line);

	}

	// if "VAR", declareVar(next word)
	if (parsed == "VAR")
	{
		int var;
		stringstream ss;
		try 
		{
			ss << parse(line);
			ss >> var;
		}
		catch (AssemblerException &e)
		{
			cout << "\033[1;31mAssembler Error: \033[0m" << e.what() << endl;
			exit(0);
		}
    
		bufferLine = declareVariable(var);
		cout << "Machine Code: " << bufferLine << "\n" << endl;

		(*lineCounter)++;

	}
	else if(iSet.contains(parsed)) // recognised instruction
	{
		if (parsed != "STP" && parsed != "CMP" && parsed != "INC" && parsed != "DEC") // has an operand
		{
			try 
			{
				string instrOperand = parse(line);
				if (instrOperand.find("#") == string::npos) // if direct addressing do nothing
				{
					bufferLine = encodeInstructionAddress(parsed, instrOperand);
				}
				cout << "Machine Code: " << bufferLine << "\n" << endl;
			}
			catch (AssemblerException &e)
			{
				cout << "\033[1;31mAssembler Error: \033[0m" << e.what() << endl;
				exit(0);
			}
		}
		
		(*lineCounter) = (*lineCounter + 1);
	}
	else
	{
		throw AssemblerException("Unidentified Opcode, this Opcode is not part of the instruction set");
		exit(0);
	 }	
}

// second pass: fills up buffer with the machine code
void Assembler::assembleSecondPass()
{
	// prints complete symbol table for reference
	sTable.printTable();

	cout << "\nSECOND PASS:" << endl;

	ifstream ifs(filePath);
	int counter = 0;
	int* lineCounter = &counter;
	string line = "";
	list<string>::iterator it = buffer.begin();

	if (! ifs)
	{
		cerr << "error: invalid filename" << endl;
		return;
	}

	while (getline(ifs, line))
	{
		string lineCopy = line;
		string* linePtr = &lineCopy;

		cout << "assembling line: " << line << endl;
	 	assembleLineSecondPass(linePtr, lineCounter, it);
	}

} 


/*
	Adds a line of machine code to buffer if needed (line contains code)
*/
void Assembler::assembleLineSecondPass(string* line, int* lineCounter, list<string>::iterator it)
{
	string bufferLine;

	string parsed = parse(line);

	if (parsed == "")
	{
		return;
	}

	// if theres a "LABEL": add it to symbol table along with current line number as address
	if (parsed.find(":") != string::npos)
	{
		string label = parsed.substr(0, parsed.length()-1);

		addVariableToSymbolTable(label, *lineCounter);

		parsed = parse(line);

	}

	// if "VAR", declareVar(next word) and push to buffer
	if (parsed == "VAR")
	{
		int var;
		stringstream ss;
		ss << parse(line);
		ss >> var;
		

		bufferLine = declareVariable(var);

		(*lineCounter)++;
		it = buffer.insert(it, bufferLine);
		cout << "Machine Code: " << *it << "\n" << endl;
	}
	else if(iSet.contains(parsed)) // recognised instruction
	{
		if (parsed != "STP" && parsed != "CMP" && parsed != "INC" && parsed != "DEC") // requires operand
		{
			string instrOperand = parse(line);
			if (instrOperand.find("#") == string::npos) // absolute addressing (mem address)
			{
				bufferLine = encodeInstructionAddress(parsed, instrOperand);
			}
			else //direct addressing (#value)
			{
				int value;
				stringstream ss;
				// remove #
				instrOperand = instrOperand.substr(1, instrOperand.length() - 1); 
				//convert to int
				ss << instrOperand;
				ss >> value;
				// encode
				bufferLine = encodeInstructionValue(parsed, value);
			}
		}
		else // blank operand
		{
			bufferLine = encodeInstructionAddress(parsed, "");
		}

		(*lineCounter) = (*lineCounter + 1);

		it = buffer.insert(it, bufferLine);
		cout << "Machine Code: " << *it << "\n" << endl;

 	}
 	else
 	{

 	}
}

// encodes given opcode + #value for immediate addressing
string Assembler::encodeInstructionValue(string mne, int value)
{
	//get opcode (make it a binary string)
	string opcode = getOpcode(mne);
	cout << "mne: " << mne << " -> opcode: " << opcode << endl;
	//get memory address of operand
	string operand = decToBinaryString(value, 6);
	cout << "operand: " << operand << endl;
	//initialises templine to be 32 0s
	string tempLine = "";
	for (int i = 0; i < 32; i++)
	{
		tempLine += "0";
	}
	// 6 for 64x32 store
	// 4 for 4 bit opcode (0-15)
	tempLine.replace(0, 6, operand);
	tempLine.replace(13, 4, opcode);
	tempLine.replace(31,1, "1");
	return tempLine;
}

// declares variable
string Assembler::declareVariable(int value)
{
	return decToBinaryString(value,32); // convert value to 32bit binary string and return it
}

/*
	NUM01: -> address is this line (check if label in table, if not add it) then add address
	NUM01 -> label, so check in table add if not defined (sTable,addLabel(label);)
*/
void Assembler::addVariableToSymbolTable(string label, int address)
{
	// add label (if not already defined)
	sTable.addLabel(label);

	// convert address to binary and add to symboltable
	
	string strAddress = decToBinaryString(address, 6);
	sTable.addAddress(label, strAddress);
}

// gets the opcode
string Assembler::getOpcode(string mne)
{
	// getOpcode as int
	int opCodeInt = iSet.getOpcode(mne);

	// convert to 4 bit binary string and return
	string strOpcode = decToBinaryString(opCodeInt, 4);

	return strOpcode;
}

//encodes given opcode + address (operand) for absolute addressing
string Assembler::encodeInstructionAddress(string mne, string label)
{
	//get opcode (make it a binary string)
	string opcode = getOpcode(mne);

	//get memory address of operand
	string operand = sTable.getAddress(label);

	//initialises templine to be 32 0s
	string tempLine = "";
	for (int i = 0; i < 32; i++)
	{
		tempLine += "0";
	}

	// 6 for 64x32 store
	// 4 for 4 bit opcode (0-15)
	tempLine.replace(0, 6, operand);

	tempLine.replace(13, 4, opcode);

	return tempLine;

}

// returns the next useful bit of the line (string, no " ")
string Assembler::parse(string* line)
{
	string parsed = "";
	// is there a comment, if there is remove it
	if(line->find(";") != string::npos)
	{
		size_t semiColonIndex = line->find(";");

		if (semiColonIndex == 0)
		{
			return ""; //theres nothing useful on the line
		}
		else
		{
			(*line) = line->substr(0, semiColonIndex);
		}

	}

	// find first non whitespace character
	if(line->find_first_not_of(" ") != string::npos)
	{
		size_t firstIndex = line->find_first_not_of(" ");
		(*line) = line->substr(firstIndex, line->length() - firstIndex);


		// 2 cases being there is a space, word is end of line
		if(line->find(" ") != string::npos)
		{
			size_t whiteSpaceIndex = line->find(" ");

			parsed = line->substr(0, whiteSpaceIndex);

			(*line) = line->substr(whiteSpaceIndex, line->length() - whiteSpaceIndex);

			return parsed;
		}
		else
		{
			parsed = (*line);

			(*line) = "";
			return parsed;

		}
	}
	throw (AssemblerException("Expected Operand"));
	return "";
}



int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cerr << "error please (only) enter a filename as parameter" << endl;
		return -1;
	}

	// initialises assembler with given filename and runs it
	 Assembler assembler(argv[1]);
	 assembler.assemble();

	 return 0;
	
}
// // prints the buffer for debugging purposes
// void Assembler::displayBuffer()
// {
// 	list<string>::iterator it;

// 	for(it = buffer.begin(); it != buffer.end(); ++it)
// 	{
// 		//cout << (*it) << endl;
// 	}
// }

// flushes contents of buffer to filePath in the assembler
void Assembler::flushBufferToFile()
{
	ofstream ofs("a." + filePath);

	if (!ofs)
	{
		cerr << "Error opening file for output" << endl;
	}

	list<string>::iterator it;

	for(it = buffer.begin(); it != buffer.end(); ++it)
	{
		ofs << (*it) << endl;
	}

	ofs.close();
}




