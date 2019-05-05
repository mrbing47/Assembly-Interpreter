#pragma once

#include"Register.h"
#include "functions.h"
#include "typedefs.h"

using namespace std;

class Instructions : public Register
{

public:
	
	void ADD(string inst) 
	{
		switch (inst[4])
		{
		case 'A':
			A += A;
			break;
		case 'B':
			A += B;
			break;
		case 'C':
			A += C;
			break;
		case 'D':
			A += D;
			break;
		case 'E':
			A += E;
			break;
		case 'H':
			A += H;
			break;
		case 'L':
			A += L;
			break;
		default:
			cout << "ERROR: INVALID_REGISTER\n";
		}

		A %= 256;

		if (A == 0)
			flags[1] = true;
	}
	void ADI(int value) 
	{

	}

};
