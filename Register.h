#pragma once

#include<string>

#include "typedefs.h"

using namespace std;

class Register
{
public:

	map<char,Bit8> reg;
	Bit16 SP, PC = 0x0000;
	Flag flags[8];
};

