#pragma once


#include<map>
#include<stack>

#include"Instructions.h"
#include"Register.h"
#include "functions.h"
#include "Constants.h"
#include "interfaces.h"
#include "Error.h"
#include "datatypes.h"

using namespace std;

class Compiler : public Instructions, public executeClass, public saveClass
{

	map<_Bit16, map<string,string>> inst;
	map<_Label, _Bit16> label;
	map<_Bit16, _Bit8> memory;
	stack <pair<char, _Bit8>> programStack;
	bool subFlag = false;
	bool isSaveSuccessful = false;

	Constants constants;

	_Label newLabel;

	Instructions instructions;

	bool addLabel(_Label label)
	{
		try {

			this->label.at(label);
			return false;
		}
		catch (exception e)
		{
			this->label.insert(pair<_Label, _Bit16>(label, PC));
			return true;
		}
	}

	void addInst(map<string, string> mapinst)
	{
		this->inst.insert(pair<_Bit16, map<string, string>>(PC, mapinst));
	}

	void deleteInst()
	{
		if (newLabel != "")
			label.erase(newLabel);

		inst.erase(PC);
	}

	Compiler(){}

public:
	
	void execute()
	{
		if (isSaveSuccessful)
		{
			map<string, string> op = this->inst[PC];

			string opcode = toLowerCase(op[constants.MAP_OPCODE]);
			string dest = toLowerCase(op[constants.MAP_DEST]);
			string src = toLowerCase(op[constants.MAP_SRC]);

			if (funMap.find(opcode) != funMap.end())
			{
				bool isExecuted = instructions.funMap[opcode](dest, src);
				if (!isExecuted)
				{
					deleteInst();
					return;
				}
				PC += 1;
			}
			else
			{
				deleteInst();
				cout << INVALID_INST;
			}
		}
	}
	
	static saveClass* create() {
		return new Compiler();
	}

	executeClass* save(_Label label, vector<string> inst)
	{
		if (label != "")
			if (!addLabel(label))
			{
				cout << DUPLICATE_LABEL;
				isSaveSuccessful = false;
				return this;
			}

		if (inst.size() > 3)
		{
			cout << INVALID_INST;
			isSaveSuccessful = false;
			return this;
		}

		newLabel = label;

		vector<string> params = constants.MAP_PARAMS;

		map<string, string> kvparams;

		int count = 0;
		int instlen = inst.size();

		for (auto i = inst.begin(); i != inst.end(); i++, count++)
		{
			if (instlen == 2 and count == 1)
				count++;
			kvparams.insert(pair<string, string>(params[count], *i));
		}

		addInst(kvparams);
		
		isSaveSuccessful = true;
		return this;
	}
};

