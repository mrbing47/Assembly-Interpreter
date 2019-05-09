#pragma once


#include<map>
#include<stack>

#include"Instructions.h"
#include"Register.h"
#include "typedefs.h"
#include "functions.h"
#include "Constants.h"
#include "interfaces.h"

using namespace std;

class Compiler : public Instructions, public executeClass, public saveClass
{

	map<Bit16, map<string,string>> inst;
	map<Label, Bit16> label;
	map<Bit16, Bit8> memory;
	stack <pair<Regname, Bit8>> programStack;
	bool subFlag = false;
	bool isSaveSuccessful = false;

	Constants constants;

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

	void addInst(map<string, string> mapinst)
	{
		this->inst.insert(pair<Bit16, map<string, string>>(PC, mapinst));
	}

	Compiler(){}

public:
	
	void execute()
	{
		map<string, string> op = this->inst[PC];

		for (auto i = op.begin(); i != op.end(); i++)
		{
			cout << i->first << '\t' << i->second << endl;
		}
		
		PC++;
	}
	
	static saveClass* create() {
		return new Compiler();
	}

	executeClass* save(Label label, vector<string> inst)
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

