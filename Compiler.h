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

	bool subFlag = false;
	bool isSaveSuccessful = false;

	Constants constants;

	_Label newLabel;

	bool addLabel(const _Label label)
	{
		if (labelMap.find(label) == labelMap.end())
		{
			this->labelMap.insert(pair<_Label, _Bit16>(label, reg16["pc"]));
			return true;
		}
		else
		{
			cout << DUPLICATE_LABEL;
			return false;
		}
	}

	void addInst(map<string, string> mapinst)
	{
		this->inst.insert(pair<_Bit16, map<string, string>>(reg16["pc"], mapinst));
	}

	void deleteInst()
	{
		if (newLabel != "")
			labelMap.erase(newLabel);

		inst.erase(reg16["pc"]);
	}

	Compiler(){};

public:
	
	void execute()
	{
		if (isSaveSuccessful)
		{
			map<string, string> op = this->inst[reg16["pc"]];

			string opcode = op[constants.MAP_OPCODE];

			if (funMap.find(opcode) != funMap.end())
			{
				bool isExecuted = funMap[opcode](
						op[constants.MAP_DEST]
						, op[constants.MAP_SRC]
						);

				if (!isExecuted)
				{
					deleteInst();
					return;
				}
				reg16["pc"] += 1;
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

