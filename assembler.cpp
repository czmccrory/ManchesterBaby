#include "assembler.h"
#include "assemblerError.h"

using namespace std;

void Assembler::assemble()
{
	assembleFirstPass();
	assembleSecondPass();
	flushBufferToFile();
}
void Assembler::assembleFirstPass()
{

	ifstream ifs(filePath);
	int counter = 0;
	int* lineCounter = &counter;
	string line = "";

	if (! ifs)
	{
		//cerr << "error: invalid filename" << endl;
		//return;
		throw AssemblerException("Invalid filename");
	}

	try
	{
		while (getline(ifs, line))
		{
			string lineCopy = line;
			string* linePtr = &lineCopy;
			cout << "assembling line: " << line << endl;
		 	assembleLineFirstPass(linePtr, lineCounter);
		}
	}
	catch (AssemblerException &e)
	{
		cout << "Assembler Error:" << e.what() << endl;
		exit (0);
	}
	

	//flushBufferToFile();
	//push to buffer file
} 

/* 	
	Push to buffer means push_back()
*/
void Assembler::assembleLineFirstPass(string* line, int* lineCounter)
{
	string bufferLine;

	string parsed = parse(line);
	//cout << " parsed: " << parsed << endl;

	if (parsed == "")
	{
		//cout << "-1" << endl;
		return;
	}

	// if theres a "LABEL": add it to symbol table along with current line number as address
	if (parsed.find(":") != string::npos)
	{
		cout << "Label found: " << parsed;
		string label = parsed.substr(0, parsed.length()-1);

		addVariableToSymbolTable(label, *lineCounter);

		// i think this should be here
		parsed = parse(line);

	}

	// if "VAR", declareVar(next word) and push to buffer
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
			cout << "Assembler Error: " << e.what() << endl;
			exit(0);
		}
		
		
		cout << "Declare var" << endl;
		bufferLine = declareVariable(var);

		cout << "pushed to buffer: " << bufferLine << endl;
		//buffer.push_back(bufferLine);
		(*lineCounter)++;
		//cout << " past increment" << endl;

	}
	else if(iSet.contains(parsed))
	{
		cout << "encode Instruction" << endl;
		cout << "parsed: " << parsed << endl;
		if (parsed != "STP")
		{
			try 
			{
				bufferLine = encodeInstruction(parsed, parse(line));
			}
			catch (AssemblerException &e)
			{
				cout << "Assembler Error: " << e.what() << endl;
				exit(0);
			}
		}
		

		cout << "pushed to buffer: " << bufferLine << endl;
		//buffer.push_back(bufferLine);
		(*lineCounter) = (*lineCounter + 1);
	}
	else
	{
		throw AssemblerException("Unidentified Opcode, this Opcode is not part of the instruction set");
		exit(0);
	 	//cout << "do nothing/ assumes MNE/ something is wrong" << endl;
	 	 // do nothing/dont add to buffer
	 }



	

}

void Assembler::assembleSecondPass()
{
	ifstream ifs(filePath);
	int counter = 0;
	int* lineCounter = &counter;
	string line = "";
	list<string>::iterator it = buffer.begin();
	size_t size = buffer.size();
	buffer = list<string>();

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

	//flushBufferToFile();
	//push to buffer file
} 


/*
	Push to buffer means overwrite ie iterate through the buffer
*/
void Assembler::assembleLineSecondPass(string* line, int* lineCounter, list<string>::iterator it)
{
	string bufferLine;

	string parsed = parse(line);
	//cout << " parsed: " << parsed << endl;

	if (parsed == "")
	{
		cout << "-1" << endl;
		return;
	}

	// if theres a "LABEL": add it to symbol table along with current line number as address
	if (parsed.find(":") != string::npos)
	{
		cout << "Label found: " << parsed;
		string label = parsed.substr(0, parsed.length()-1);

		addVariableToSymbolTable(label, *lineCounter);

		// i think this should be here
		parsed = parse(line);

	}

	// if "VAR", declareVar(next word) and push to buffer
	if (parsed == "VAR")
	{
		int var;
		stringstream ss;
		ss << parse(line);
		ss >> var;
		
		cout << "Declare var" << endl;
		bufferLine = declareVariable(var);

		cout << "overwritten buffer: " << bufferLine << endl;
		(*lineCounter)++;
		it = buffer.insert(it, bufferLine);

		cout << " past increment" << endl;

	}
	else if(iSet.contains(parsed))
	{
		cout << "encode Instruction" << endl;
		cout << "parsed: " << parsed << endl;
		if (parsed != "STP")
		{
			bufferLine = encodeInstruction(parsed, parse(line));
		}
		else 
		{
			bufferLine = encodeInstruction(parsed, "");
		}

		cout << "overwritten buffer: " << bufferLine << endl;
		(*lineCounter) = (*lineCounter + 1);

		it = buffer.insert(it, bufferLine);

 	}
 	else
 	{
 		cout << "error possible says this twice" << endl;
 	}
}

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

string Assembler::getOpcode(string mne)
{
	// getOpcode as int
	int opCodeInt = iSet.getOpcode(mne);

	// convert to 4 bit binary string and return
	string strOpcode = decToBinaryString(opCodeInt, 4);

	cout << "intOpCode: " << opCodeInt << " string: " << strOpcode << endl;

	return strOpcode;
}

string Assembler::encodeInstruction(string mne, string label)
{
	//get opcode (make it a binary string)
	string opcode = getOpcode(mne);

	cout << "mne: " << mne << " -> opcode: " << opcode << endl;

	//get memory address of operand
	string operand = sTable.getAddress(label);

	cout << "operand: " << operand << endl;

	//initialises templine to be 32 0s
	string tempLine = "";
	for (int i = 0; i < 32; i++)
	{
		tempLine += "0";
	}

	//cout << "templines: " <<endl;
	//cout << tempLine << endl;
	// 6 for 64x32 store
	// 4 for 4 bit opcode (0-15)
	tempLine.replace(0, 6, operand);

	//cout << tempLine << endl;
	tempLine.replace(13, 4, opcode);
	//cout <<tempLine << endl;
	//cout << "end of temp lines" << endl;

	return tempLine;

}

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

		cout << (*line) << endl;

		// 2 cases being there is a space, word is end of line
		if(line->find(" ") != string::npos)
		{
			size_t whiteSpaceIndex = line->find(" ");

			parsed = line->substr(0, whiteSpaceIndex);

			(*line) = line->substr(whiteSpaceIndex, line->length() - whiteSpaceIndex);

			cout << "returning parsed: "  << parsed << endl;
			return parsed;
		}
		else
		{
			parsed = (*line);

			(*line) = "";
			return parsed;

		}
	}

	throw AssemblerException("Opcode requiring operand with no operand");
}


/*
	to get a memory address do sTable.getAddress(label);
*/

//int main(int argc, char** argv)
int main()
{
	// if (argc != 2)
	// {
	// 	cerr << "error please enter filename as parameter" << endl;
	// 	return -1;
	// }

	 //Assembler assembler(argv[1]);
	 Assembler assembler("test.txt");
	 assembler.assemble();
	 return 0;
	
	
}

void Assembler::displayBuffer()
{
	list<string>::iterator it;

	for(it = buffer.begin(); it != buffer.end(); ++it)
	{
		cout << (*it) << endl;
	}
}

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




