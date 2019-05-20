#pragma once


#include<map>
#include<stack>

#include"Instructions.h"
#include"Register.h"
#include "Constants.h"
#include "interfaces.h"
#include "Error.h"
#include "datatypes.h"

using namespace std;

class Compiler : public Instructions, public CompilerExecute, public CompilerSave, public CompilerProcess
{
	bool isProcessSuccessful = false;
	bool isSaveSuccessful = false;
	bool isLoopStarted = false;

	Constants constants;

	_Label label;
	vector<string> strs;
	bool isHLT = false;


	bool addLabel()
	{
		if (!this->labelMap.count(label))
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
		if (this->label != "")
			labelMap.erase(this->label);

		inst.erase(reg16["pc"]);
	}

	void stopLoop(map<string, string> op)
	{
		cout << ERROR_PT;

		cout << op[constants.MAP_OPCODE] << ' ';

		if (!op[constants.MAP_DEST].empty())
			cout << op[constants.MAP_DEST] << ' ';

		cout << op[constants.MAP_SRC];
		
		cout << ERROR_INSIDE << sub_stack.top().first << "\n\n";

		reg16["pc"] = sub_stack.top().second;
		sub_stack.pop();

		--sub_routine_count;

		if (!sub_routine_count and !isLoopEnable)
		{
			isLoopStarted = false;
		}
	}

	void execute_sub_or_loop()
	{
		while(isLoopEnable || sub_routine_count)
		{
			execute();
		}
	}

	Compiler()
	{
	};

public:

	static CompilerProcess* create() { return new Compiler(); }

	CompilerSave* process(string input) override
	{
		input = toLowerCase(trim(input));

		if (input.empty())
		{
			isProcessSuccessful = false;
			return this;
		}

		if (input == "hlt")
			this->isHLT = true;

		vector<string> inst = str_split(input, ":");

		this->label = inst.size() > 1 ? trim(inst[0]) : "";
		this->strs = str_split(inst[inst.size() - 1], " ,");

		isProcessSuccessful = true;
		return this;
	}

	CompilerExecute* save() override
	{
		if (isProcessSuccessful)
		{
			if (label != "")
				if (!addLabel())
				{
					isSaveSuccessful = false;
					return this;
				}

			if (this->strs.size() > 3)
			{
				cout << INVALID_INST;
				isSaveSuccessful = false;
				return this;
			}


			vector<string> params = constants.MAP_PARAMS;

			map<string, string> kvparams;

			int count = 0;
			const int instlen = this->strs.size();

			for (auto i = this->strs.begin(); i != this->strs.end(); i++, count++)
			{
				if (instlen == 2 and count == 1)
					count++;
				kvparams.insert(pair<string, string>(params[count], *i));
			}

			addInst(kvparams);

			isSaveSuccessful = true;
		}
		else
			isSaveSuccessful = false;

		return this;
	}

	bool execute() override
	{
		if (isSaveSuccessful)
		{
			if (!isSubRoutineEnable)
			{
				map<string, string> op = this->inst[reg16["pc"]];

				string opcode = op[constants.MAP_OPCODE];

				if (funMap.find(opcode) != funMap.end())
				{
					const bool isExecuted = funMap[opcode](
						op[constants.MAP_DEST]
						, op[constants.MAP_SRC]
						);

					if (!isLoopStarted and (isLoopEnable or sub_routine_count))
					{
						isLoopStarted = true;
						reg16["pc"] += 1;
						execute_sub_or_loop();
						return false;
					}
					if (isLoopStarted and !(isLoopEnable or sub_routine_count))
						isLoopStarted = false;
					

					if (!isExecuted)
					{
						if (!isLoopEnable and !sub_routine_count)
						{
							deleteInst();
							return false;
						}

						stopLoop(op);
					}
				}
				else
				{
					cout << INVALID_INST;
					if(sub_routine_count)
					{
						stopLoop(op);
					}
					else 
					{
						deleteInst();
						return false;
					}
					
				}
			}
			else
			{
				map<string, string> op = this->inst[reg16["pc"]];

				if(op[constants.MAP_OPCODE] == "ret")
				{
					isSubRoutineEnable = false;
				}
			}
			reg16["pc"] += 1;
		}
		return this->isHLT;
	}
};
