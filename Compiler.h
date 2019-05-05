#pragma once


#include<map>
#include<stack>

#include"Instructions.h"
#include"Register.h"
#include "typedefs.h"
#include "functions.h"

using namespace std;


class Compiler : public Instructions
{

	map<Bit16, string> inst;
	map<Label, Bit16> label;
	map<Bit16, Bit8> memory;
	stack <pair<Regname, Bit8>> programStack;

	size_t alphacount(string inst)
	{
		size_t count = 0;
		int strlen = inst.length();
		for (int i = 0; i < strlen; i++)
		{
			if (inst[i] != ' ')
				count++;
		}
		return count;
	}

public:
	
	void executeInst(string inst)
	{
		this->inst.insert(pair<Bit16,string>(PC,inst));
		string opcode = inst.substr(0, 3);
		if (opcode == "ADD")
		{
			if (alphacount(inst) != 4 || inst.length() > 5)
			{
				cout << "ERROR: INVALID_ARGUMENTS\n";
				return;
			}
			else
			{
				ADD(inst);
				
			}
		}
		else
		{
			if (opcode == "MVI")
			{
				string operand = inst.substr(4);
			}
		}
		PC++;
	}

	bool addLabel(Label label) 
	{
		try {

			this->label.at(label);
			return false;
		}
		catch (exception e)
		{
			this->label.insert(pair<Label, Bit16>(label, PC));
			return true;
		}
	}

	map<Label, Bit16> getLabel()
	{
		return this->label;
	}

	map<Bit16, string> getInst()
	{
		return this->inst;
	}
};

