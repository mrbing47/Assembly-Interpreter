#pragma once

#include<string>

#include "typedefs.h"

using namespace std;

class Register
{
public:

	Bit8 A, B, C, D, E, H, L;
	Bit16 SP, PC = 0x0000;
	Flag flags[8];
};

