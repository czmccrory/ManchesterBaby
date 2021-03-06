
/*
  Group 4
   Melvin Abraham    170013110
   Kamila Gorska     170013107
   Charlie Hewitt    170015454
   Caoilainn McCrory 170001498
   Frantisek Pavlica 170020274
*/

#ifndef ASSEMBLER
#define ASSEMBLER

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <stdexcept>

using namespace std;

string decToBinaryString(int dec, int length);

// Node to hold opcode + mnemonic
class InstructionNode
{
	private:
		string mnemonic;
		int number;

	public:
		InstructionNode(string mne, int num);
		InstructionNode();
		string getMnemonic();
		int getNumber();
};

// Data structure that holds InstructionNodes
class InstructionSet
{
	private:
		vector<InstructionNode> vec;
		int size;

	public:
		InstructionSet(); // initialises instruction set to manchester baby's "extended" one
		int getOpcode(string mnemonic);
		bool contains(string mnemonic); // checks if instruction set contains given mne

};

// Node that contains { label, address }
class SymbolNode
{
	private:
		string label;
		string address;

	public: 
		SymbolNode(string lab) { this -> label = lab; this -> address = "notdef";};
		string getLabel() { return this -> label; };
		string getAddress() { return this -> address;};
		void setAddress(string address) { this -> address = address;};


};

// Data structure that holds SymbolNodes, allows writing/access
class SymbolTable
{
	private:
		list<SymbolNode> table;

	public:
		SymbolTable(); // initialises empty symbol table
		void addLabel(string label);
		void addAddress(string label, string address);
		bool contains(string label); // check if label is already in table
		string getAddress(string label);
		void printTable();
};


// Assembler, for a given filename
class Assembler
{
	private: 
		InstructionSet iSet; // instruction set
		list<string> buffer; // output buffer
		SymbolTable sTable;
		string filePath;

	public:
		Assembler(string path); 
		void assemble();
		void assembleFirstPass();
		void assembleSecondPass();

		string parse(string* line);

		string encodeInstructionAddress(string mne, string label);
		string encodeInstructionValue(string mne, int value );
		string getOpcode(string mne);

		void assembleLineFirstPass(string* line, int* lineCounter);
		void assembleLineSecondPass(string* line, int* lineCounter, list<string>::iterator);

		void addVariableToSymbolTable(string label, int address);
		string declareVariable(int var);

		void displayBuffer();
		void flushBufferToFile();
};


class AssemblerException : public std::exception
{
protected: 
	std::string msg;

public:
	explicit AssemblerException(std::string message) : msg(message) {}
	const char* what() const noexcept {return msg.c_str();}
};

Assembler::Assembler(string path)
{
	this -> iSet = InstructionSet();
	this -> buffer = list<string>();
	this -> sTable = SymbolTable();
	this -> filePath = path;
}

InstructionSet::InstructionSet()
{
	this -> size = 14;
  
	string mne[14] = { "JMP", "JRP", "LDN", "STO", "SUB", "SUB", "CMP", "STP", "MUL", "LDP", "ADD", "NEGSTO", "INC", "DEC"};
	int num[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

	vector<InstructionNode> temp(14); 

	for (int i = 0; i < 14; i++)
	{
		temp.at(i) = InstructionNode(mne[i], num[i]);
	}

	this -> vec = temp;


}

bool InstructionSet::contains(string mne)
{
	for (vector<InstructionNode>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if ((*it).getMnemonic() == mne)
		{
			return true;
		}
	}
	return false;
}


int InstructionSet::getOpcode(string mne)
{
	vector<InstructionNode>::iterator it;

	for (it = vec.begin(); it != vec.end(); ++it)
	{
		if ((*it).getMnemonic() == mne)
		{
			return (*it).getNumber();
		}
	}

	return -1;
	// compile error
}

InstructionNode::InstructionNode()
{
	this -> mnemonic = "notdef";
	this -> number = 0;
}

InstructionNode::InstructionNode(string mne, int num)
{
	this -> mnemonic = mne;
	this -> number = num;
}

string InstructionNode::getMnemonic(){
	return this->mnemonic;
}

int InstructionNode::getNumber(){
	return this->number;
}

// check if label is in Table
bool SymbolTable::contains(string label)
{
	list<SymbolNode>::iterator it;

	for(it = table.begin(); it != table.end(); ++it)
	{
		string cLabel = (*it).getLabel();

		if(label == cLabel)
		{
			return true;
		}
	}

	return false;
}

void SymbolTable::printTable()
{
	list<SymbolNode>::iterator it;

	cout << "SYMBOL TABLE: " << endl;

	for(it = table.begin(); it != table.end(); ++it)
	{
		cout << "Label: " << (*it).getLabel() << "\t Address: " << (*it).getAddress() << endl;
	}
}

void SymbolTable::addLabel(string label)
{
	if(!contains(label))
	{
		SymbolNode node(label);
		table.push_back(node);
	}
	
}

void SymbolTable::addAddress(string label, string address)
{
	if(contains(label))
	{
		list<SymbolNode>::iterator it;

		for (it = table.begin(); it != table.end(); ++it)
		{
			if ((*it).getLabel() == label)
			{
				(*it).setAddress(address);
				return;
			}
		}

	}


	cout << "error undeclared variable" << endl;
}

string SymbolTable::getAddress(string label)
{
	if (contains(label))
	{
		list<SymbolNode>::iterator it;

		for(it = table.begin(); it != table.end(); ++it)
		{
			if ((*it).getLabel() == label)
			{
				return (*it).getAddress();
			}
		}
	}
	else
	{
		// return mem address 0 will be overwritten "later"
		return "000000";
	}
	//Should never get here
	return "000000";
}

SymbolTable::SymbolTable()
{
	this -> table = list<SymbolNode>();
}


string decToBinaryString(int dec, int length)
{
	string bin = ""; // vector to hold binary value (in this case size 8 for rule.)
	//cout << dec << endl;

	int i;
	for ( i=length; dec>0; i--)
	{
		// take the remainder of the dec / 2 and save it to the vector
		// this value will always be 1 or 0
		int mod = (dec%2);

		if (mod == 1)
		{
			bin += "1";
		}
		else
		{
			bin += "0";
		}

		// update dec
		dec /= 2;
	}

	while (i > 0)
	{
		bin += "0";
		i--;
	}
		//cout << bin <<endl;
		return bin;

}

#endif