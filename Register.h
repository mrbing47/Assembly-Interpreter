#pragma once
#include<map>
using namespace std;

#include "datatypes.h"

class Register
{
public:
	map<char, _Bit8> reg;
	_Bit16 SP, PC = 0x0000;
	bool flags[8] = { false };
};
