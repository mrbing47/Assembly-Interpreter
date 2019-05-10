#pragma once
#include<map>
using namespace std;

#include "datatypes.h"

class Register
{
public:
	map<string, _Bit8> reg;
	_Bit16 SP, PC = 0x0000;
	bool flags[8] = { false };

	Register()
	{
		reg["a"] = 0;
		reg["b"] = 0;
		reg["c"] = 0;
		reg["d"] = 0;
		reg["e"] = 0;
		reg["h"] = 0;
		reg["l"] = 0;
	}
};
