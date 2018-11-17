#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

using namespace std;


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

class InstructionSet
{
	private:
		vector<InstructionNode> vec;
		int size;

	public:
		InstructionSet();
		int getOpcode(string mnemonic);

};

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

class SymbolTable
{
	private:
		list<SymbolNode> table;

	public:
		SymbolTable();
		void addLabel(string label);
		void addAddress(string label, string address);
		bool contains(string label);
		string getAddress(string label);
};


class Assembler
{
	private: 
		InstructionSet iSet;
		list<string> buffer;
		SymbolTable sTable;
		string filePath;

	public:
		Assembler(string path);
		void assemble();
		string parse(string* line);
		string encodeInstruction(string mne ,string label);
		string getOpcode(string mne);
		void assembleLineFirstPass(string* line, int lineCounter);
		void assembleLineSecondPass(string* line, int lineCounter);
		void addVariableToSymbolTable(string label, int address);
		string declareVariable(int var);
		void displayBuffer();
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
	this -> size = 8;

	string mne[8] = { "JMP", "JRP", "LDNA", "STO", "SUB", "SUB", "CMP", "STP"};
	int num[8] = { 0, 1, 2, 3, 4, 5, 6, 7};

	vector<InstructionNode> temp(8); 

	for (int i = 0; i < 8; i++)
	{
		temp.at(i) = InstructionNode(mne[i], num[i]);
	}

	this -> vec = temp;


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
		return "00000";
	}

}

SymbolTable::SymbolTable()
{
	this -> table = list<SymbolNode>();
}
