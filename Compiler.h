#pragma once


#include<map>
#include<stack>

#include"Instructions.h"
#include"Register.h"
#include "functions.h"
#include "Constants.h"
#include "interfaces.h"
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

	Compiler(){}

public:
	
	void execute()
	{
		map<string, string> op = this->inst[PC];

		string opcode = toLowerCase(op[constants.MAP_OPCODE]);
		string dest = toLowerCase(op[constants.MAP_DEST]);
		string src = toLowerCase(op[constants.MAP_SRC]);

		instructions.funMap[opcode](dest, src);
		PC+=1;
	}
	
	static saveClass* create() {
		return new Compiler();
	}

	executeClass* save(_Label label, vector<string> inst)
	{
		if (label != "")
			if (!addLabel(label))
			{
				cout << "ERROR: DUPLICATE_LABEL\n";
				isSaveSuccessful = false;
				return this;
			}

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

