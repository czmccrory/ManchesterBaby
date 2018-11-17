#include "assembler.h"

using namespace std;

void Assembler::assemble()
{
	//read stuff
	//

	//linecounter start from 0

	// while (nextLine not empty)
	// {
	// copy string and create pointer
	// 	assembleLineFirstPass(nextLine);
	// 	assembleLineSecondPass(nextLine);
	// }

	//push to buffer file
} 

/* 	
	Push to buffer means push_back()
*/
void Assembler::assembleLineFirstPass(string* line, int lineCounter)
{
	string bufferLine;

	string parsed = parse(line);

	// if theres a "LABEL": add it to symbol table along with current line number as address
	if (parsed.find(":") != string::npos)
	{
		parsed = parsed.substr(0, line->length()-1);

		addVariableToSymbolTable(parsed, lineCounter);

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
		
		bufferLine = declareVariable(var);

		buffer.push_back(bufferLine);

	}
	else //if(iSet.contains(parsed))
	{
		bufferLine = encodeInstruction(parsed, parse(line));

		buffer.push_back(bufferLine);
	}
	// else
	// {
	// 	 // do nothing/dont add to buffer
	// }



	

}

/*
	Push to buffer means overwrite ie iterate through the buffer
*/
void Assembler::assembleLineSecondPass(string* line, int lineCounter)
{

}

string Assembler::declareVariable(int value)
{
	return "00001111000011101010101010101010"; // convert value to 32bit binary string and return it
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
	//decToAddress(address)q
	string strAddress;
	sTable.addAddress(label, strAddress);
}

string Assembler::getOpcode(string mne)
{
	// getOpcode as int
	//int opCodeInt = iSet.getOpcode(mne);

	// convert to 4 bit binary string and return
	string strOpcode = "1101";
	return strOpcode;
}

string Assembler::encodeInstruction(string mne, string label)
{
	//get opcode (make it a binary string)
	string opcode = "1101"; //getOpcode(mne);

	//get memory address of operand
	string operand = "010101"; //sTable.getAddress(label);

	//initialises templine to be 32 0s
	string tempLine;
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

			parsed = line->substr(0,whiteSpaceIndex);

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
}


/*
	to get a memory address do sTable.getAddress(label);
*/

int main()
{
	Assembler assembler("test");

	string line =  "  		SUB MYNUM";
	string lineCopy = line;

	string* lineCopyPtr = &lineCopy;
	assembler.assembleLineFirstPass(lineCopyPtr, 0);

	assembler.displayBuffer();


}

void Assembler::displayBuffer()
{
	list<string>::iterator it;

	for(it = buffer.begin(); it != buffer.end(); ++it)
	{
		cout << (*it) << endl;
	}
}




